using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Windows.Forms;
namespace GISDataTranslate
{
    /// <summary>
    /// 扩展类函数，用于扩展一些对象的方法。便于使用。
    /// </summary>
    static class CExpandFunction
    {
        /// <summary>
        /// 判断一个目录是否可访问。
        /// </summary>
        /// <param name="dir"></param>
        /// <returns></returns>
        public static bool CanVisit(this System.IO.DirectoryInfo dir)
        {
            if (null == dir)
                return false;
            try
            {
                dir.GetDirectories();
                return true;
            }
            catch
            {
                return false;
            }
        }
        public static void PrepareImage(this TreeView tree, string img)
        {
            if (tree.ImageList.Images.ContainsKey(img))
                return;
            if (tree.InvokeRequired)
            {
                tree.Invoke(new Action<TreeView, string>(PrepareImage), new object[] { tree, img });
                return;
            }
            System.Drawing.Image pImg = GConfig.GlobalConfig.Icons.LoadIcon(img);
            tree.ImageList.Images.Add(img, pImg);
        }
        /// <summary>
        /// 以安全的方式获取子文件，避免打开了一些没有权限打开的目录。
        /// </summary>
        /// <param name="dir"></param>
        /// <param name="strPar"></param>
        /// <returns></returns>
        public static System.IO.FileInfo[]  SafeGetFiles(this System.IO.DirectoryInfo dir,string strPar)
        {
            try
            {
                return dir.GetFiles(strPar);
            }
            catch
            {
            }
            return new System.IO.FileInfo[0];
        }

        /// <summary>
        /// 将字符串的路径添加到环境变量中，如果不存在与环境变量的话。
        /// </summary>
        /// <param name="str"></param>
        /// <returns></returns>
        public static bool AppendToPath(this string str)
        {
            string strPath  = Environment.GetEnvironmentVariable("PATH");
            if (strPath.IndexOf(str) >= 0)
                return false;
            strPath = str + ";" + strPath;
            Environment.SetEnvironmentVariable("PATH", strPath);
            return true;
        }

        /// <summary>
        /// 判断按钮是否已经被按下了
        /// </summary>
        /// <param name="item"></param>
        /// <returns></returns>
        public static bool IsChecked(this System.Windows.Forms.ToolStripItem item)
        {
            if (item is System.Windows.Forms.ToolStripMenuItem)
                return (item as System.Windows.Forms.ToolStripMenuItem).Checked;

            if (item is System.Windows.Forms.ToolStripButton)
                return (item as System.Windows.Forms.ToolStripButton).Checked;
            return true;
        }
        /// <summary>
        /// 设置按钮的按下状态。
        /// </summary>
        /// <param name="item"></param>
        /// <param name="b"></param>
        public static void SetChecked(this System.Windows.Forms.ToolStripItem item,bool b)
        {
            if (item is System.Windows.Forms.ToolStripMenuItem)
                (item as System.Windows.Forms.ToolStripMenuItem).Checked = b;
            else if(item is System.Windows.Forms.ToolStripButton)
                (item as System.Windows.Forms.ToolStripButton).Checked = b;
            
        }
         
        /// <summary>
        /// 将字体大小磅转换为英寸
        /// </summary>
        /// <param name="point"></param>
        /// <returns></returns>
        public static float PointToInch(this float point)
        {
            return point / 72;
        }
        /// <summary>
        /// 将英寸转换为CM
        /// </summary>
        /// <param name="inch"></param>
        /// <returns></returns>
        public static float InchToCM(this float inch)
        {
            return inch * 2.54f;
        }
        /// <summary>
        /// 磅到毫米
        /// </summary>
        /// <param name="point"></param>
        /// <returns></returns>
        public static float PointToMM(this float point)
        {
            return (point / 72) * 25.4f;
        }
        /// <summary>
        /// 实例化为对象化的Value,初始化参数为空
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <returns></returns>
        public static Type ValueType(this GeoStar.Utility.Config config)
        {
            Type t = config.Type;
            if(null != t)
                return t;
            string strType = config.TypeString;
            t = Type.GetType(strType);
            if(null != t)
                return t;

            foreach (var item in AppDomain.CurrentDomain.GetAssemblies())
            {
                t = item.GetType(strType);
                if (null != t)
                    return t;
            }
            return t;
        }
        /// <summary>
        /// 实例化为对象化的Value,初始化参数为空
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <returns></returns>
        public static T ObjectValue<T>(this GeoStar.Utility.Config config) where T : class
        {

            Type t = config.ValueType();
            if (t == null)
                return null;
            try
            {
                return Activator.CreateInstance(t) as T;
            }
            catch (Exception e)
            {
            }
            return null;
        }
        /// <summary>
        /// 获取枚举类型的值。
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="eDefault"></param>
        /// <returns></returns>
        public static T EnumValue<T>(this GeoStar.Utility.Config config,T eDefault)// where T : Enum
        {
            string strValue = config.Value;
            if (string.IsNullOrEmpty(strValue))
                return eDefault;
            try
            {
                return (T)Enum.Parse(typeof(T), strValue, true);
            }
            catch (Exception e)
            {
            }
            return eDefault;
        }

        /// <summary>
        /// 将自身配置作为参数传递给对象。
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <returns></returns>
        public static T ObjectValueConfig<T>(this GeoStar.Utility.Config config) where T : class
        {
            Type t = config.ValueType();
            if (t == null)
                return null;
            try
            {

                return Activator.CreateInstance(t, new object[] { config }) as T;
            }
            catch (Exception e)
            {
            }
            return null;
        }

        /// <summary>
        /// 毫米到磅
        /// </summary>
        /// <param name="mm"></param>
        /// <returns></returns>
        public static float MMToPoint(this float mm)
        {
            return (mm / 25.4f) * 72;
        }
  
    }
}
