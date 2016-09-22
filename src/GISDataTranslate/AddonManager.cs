using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using GeoStar.Utility;
using System.Windows.Forms;
namespace GISDataTranslate
{
    /// <summary>
    /// 存储介质的类型
    /// </summary>
    enum StorageType
    {
        eFolderType,
        eFileType,
        eDatabaseType,
    };
    /// <summary>
    ///插件类型 
    /// </summary>
    enum AddonType
    {
        eErrorAddon,
        eVectorReader,
        eVectorWriter,
        eRasterReader,
        eRasterWriter,
        eVectorOperator,
        eRasterOperator,
    }
    /// <summary>
    /// 插件封装类，用于保存配置文件中插件的信息，方便程序使用。
    /// </summary>
    class Addon
    {
        /// <summary>
        /// 插件上下文，以C++封装C函数调用接口。
        /// 实际执行插件功能从此入口。
        /// </summary>
        public GIS.AddonContext Context
        {
            get;
            set;
        }
        /// <summary>
        /// 创建Context
        /// </summary>
        public bool CreateContext()
        {
            if (Context != null)
                return true;

            string strDLL = MakePath();
            if (string.IsNullOrEmpty(strDLL))
            {
                string txt = string.Format("无法正确获取插件{0}的路径。", Name);
                MessageBox.Show(txt, "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return false;
            }
            //将dll所在的路径添加到环境变量中。
            (new System.IO.FileInfo(strDLL)).Directory.FullName.AppendToPath();

            GIS.AddonContext context = FormMain.m_Container.CreateAddon(strDLL, Function);

            if (null == context)
                return false;
            if (!context.IsValid)
                return false;

            Context = context;
            return true;
        }
        /// <summary>
        /// 构造一个插件包装对象 。
        /// </summary>
        /// <param name="strName"></param>
        public Addon(string strName)
        {
            Dirty = false;
            Name = strName;
        }

        /// <summary>
        /// 从配置中读取实例化一个插件包装对象 。
        /// </summary>
        /// <param name="config"></param>
        public Addon(Config config)
        {
            Dirty = false;
            Path = config["Path"].Value;
            Name = config["Name"].Value;
            Function = config["Function"].Value;
            Type = config["Type"].EnumValue<AddonType>(AddonType.eErrorAddon);
            StorageType = config["StorageType"].EnumValue<StorageType>(StorageType.eDatabaseType); 
        }
        /// <summary>
        /// 插件设置信息否改动过了，用于插件设置功能。
        /// </summary>
        public bool Dirty
        {
            get;
            set;
        }
        /// <summary>
        /// 生成插件dll的路径，通过多种途径构造
        /// </summary>
        /// <returns></returns>
        public string MakePath()
        {
            //如果本身就是绝对路径则直接使用。
            if (System.IO.Path.IsPathRooted(Path))
                return Path;
            //由程序自动构成绝对路径，如果存在则使用之。
            string str =  System.IO.Path.GetFullPath(Path);
            if (System.IO.File.Exists(str))
                return str;
            //在目录下加入x86或者x64的子目录分别处理32位和64位的情况。
            str = System.IO.Path.Combine(AppDomain.CurrentDomain.BaseDirectory, Program.Platform);
            str = System.IO.Path.Combine(str, Path);
            if (System.IO.File.Exists(str))
                return str;
            //无法构成路径。
            return "";
        }
        /// <summary>
        /// 重载tostring用于显示。
        /// </summary>
        /// <returns></returns>
        public override string ToString()
        {
            return Name;
        }
        /// <summary>
        /// 插件的路径。通常为相对路径
        /// </summary>
        public string Path
        {
            get;
            set;
        }
        /// <summary>
        /// 插件的名称 
        /// </summary>
        public string Name
        {
            get;
            set;
        }
        /// <summary>
        /// 插件功能的入口C函数名称
        /// </summary>
        public string Function
        {
            get;
            set;
        }
        /// <summary>
        /// 存储类型。标识这个插件识别的是文件、目录还是数据库
        /// </summary>
        public StorageType StorageType
        {
            get;
            set;
        }
        /// <summary>
        /// 是否是读插件或者说是会导入插件。
        /// </summary>
        public bool IsRead
        {
            get
            {
                return Type == AddonType.eRasterReader ||
                    Type == AddonType.eVectorReader;
            }
        }
        /// <summary>
        /// 插件类型。
        /// </summary>
        public AddonType Type
        {
            get;
            set;
        }
    }
    /// <summary>
    /// 插件管理器，全局对象，管理所有的插件封装对象。
    /// </summary>
    class AddonManager
    {
        GeoStar.Utility.Config m_Config;
        string m_ConfigFile;
        /// <summary>
        /// 构造插件对象。
        /// </summary>
        public AddonManager()
        {
            m_ConfigFile = System.IO.Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "addon.xml");

            Addons = new List<Addon>();
            m_Config = new GeoStar.Utility.Config(m_ConfigFile);

            /// 循环载入所有的插件。
            foreach (var item in m_Config)
            {
                Addon add = item.ObjectValueConfig<Addon>();
                if (add == null)
                    continue;
                Addons.Add(add);
            }
        }
        /// <summary>
        /// 插件配置信息发生变化之后保存到配置文件中。
        /// </summary>
        public void SaveConfig()
        {
            m_Config.Clear();
            int i =0;
            Type t = typeof(Addon);
            foreach (var item in Addons)
            {
                i++;
                Config conf = m_Config.Child(i.ToString());

                conf.Child("Name").Value = item.Name;
                conf.Child("Path").Value = item.Path;
                conf.Child("Function").Value = item.Function;
                conf.Child("Type").Value = item.Type.ToString();
                conf.Child("StorageType").Value = item.StorageType.ToString();
                conf.TypeString = t.FullName;
            }

            //存储为文件。
            m_Config.Save(m_ConfigFile); 

        }
        /// <summary>
        /// 所有的插件
        /// </summary>
        public List<Addon> Addons
        {
            get;
            private set;
        }
       
    }
}
