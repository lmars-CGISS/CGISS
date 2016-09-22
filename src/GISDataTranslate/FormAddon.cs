using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace GISDataTranslate
{
    public partial class FormAddon : Form
    {
        public FormAddon()
        {
            InitializeComponent();
            foreach (var item in FormMain.m_AddonManager.Addons)
            {
                listBoxAddon.Items.Add(item);
            }
            listBoxAddon.SelectedIndexChanged += new EventHandler(listBoxAddon_SelectedIndexChanged);
            comboBoxType.Items.Add(new WrapAddonType(AddonType.eVectorReader));
            comboBoxType.Items.Add(new WrapAddonType(AddonType.eVectorWriter));
            comboBoxType.Items.Add(new WrapAddonType(AddonType.eRasterReader));
            comboBoxType.Items.Add(new WrapAddonType(AddonType.eRasterWriter));
            comboBoxType.SelectedIndex = 0;


            comboBoxStorageType.Items.Add(new WrapStorageType(StorageType.eDatabaseType));
            comboBoxStorageType.Items.Add(new WrapStorageType(StorageType.eFileType));
            comboBoxStorageType.Items.Add(new WrapStorageType(StorageType.eFolderType));
            comboBoxStorageType.SelectedIndex = 0;

            
            textBoxName.TextChanged += new EventHandler(OnTextChanged); 
            textBoxPath.TextChanged += new EventHandler(OnTextChanged);
            comboBoxFunction.TextChanged += new EventHandler(OnTextChanged);
            comboBoxFunction.SelectedIndexChanged += new EventHandler(comboBoxFunction_SelectedIndexChanged);
            comboBoxType.SelectedIndexChanged += new EventHandler(comboBoxType_SelectedIndexChanged);
            comboBoxStorageType.SelectedIndexChanged += new EventHandler(comboBoxStorageType_SelectedIndexChanged);
        }

        void comboBoxFunction_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (m_InnerFlag)
                return;
            TempAddon tempAdd = CurrentAddon;
            tempAdd.Function = comboBoxFunction.Text;
        }

        void comboBoxStorageType_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (m_InnerFlag)
                return;
            TempAddon tempAdd = CurrentAddon;
            tempAdd.StorageType = (comboBoxStorageType.SelectedItem as WrapStorageType).Type;
        }

        void comboBoxType_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (m_InnerFlag)
                return;
            TempAddon tempAdd = CurrentAddon;
            tempAdd.Type = (comboBoxType.SelectedItem as WrapAddonType).Type;

        }
        void OnTextChanged(object sender, EventArgs e)
        {
            if (m_InnerFlag)
                return;
            Control box = sender as Control;
            TempAddon tempAdd = CurrentAddon;
            if (box.Name == "textBoxName")
                tempAdd.Name = box.Text; 
            else if (box.Name == "textBoxPath")
                tempAdd.Path = box.Text;
            else if (box.Name == "comboBoxFunction")
                tempAdd.Function = box.Text;

            if (box.Name == "textBoxName")
            {
                m_InnerFlag = true;
                listBoxAddon.Items[listBoxAddon.SelectedIndex] = tempAdd;
                box.Focus();
                m_InnerFlag = false;
            }
        }
        TempAddon CurrentAddon
        {
            get
            {
                Addon addon = listBoxAddon.SelectedItem as Addon;
                if (addon is TempAddon)
                    return addon as TempAddon;
                TempAddon add =  new TempAddon(addon);
                listBoxAddon.Items[listBoxAddon.SelectedIndex] = add;
                return add;
            }
        }
        bool m_InnerFlag = false;
        void listBoxAddon_SelectedIndexChanged(object sender, EventArgs e)
        {
            groupBox1.Enabled = false;
            buttonDel.Visible = (listBoxAddon.SelectedIndex >= 0);
            if (listBoxAddon.SelectedIndex < 0)
                return;
            
            groupBox1.Enabled = true;
            if (m_InnerFlag)
                return;
            
            Addon add = listBoxAddon.SelectedItem as Addon; 
            m_InnerFlag = true;
            textBoxName.Text = add.Name;
            comboBoxFunction.Items.Clear();
            comboBoxFunction.Text = add.Function;
            textBoxPath.Text = add.Path;
            comboBoxType.SelectedIndex = comboBoxType.Items.IndexOf(new WrapAddonType(add.Type));
            comboBoxStorageType.SelectedIndex = comboBoxStorageType.Items.IndexOf(new WrapStorageType(add.StorageType));
            m_InnerFlag = false;
            
        }
        protected override void OnClosing(CancelEventArgs e)
        {
            base.OnClosing(e);
        }
        private void buttonDel_Click(object sender, EventArgs e)
        {
            int i = listBoxAddon.SelectedIndex;
            listBoxAddon.Items.RemoveAt(i);
            if (listBoxAddon.Items.Count == 0)
                return;
            if (i >= listBoxAddon.Items.Count)
                i--;
            listBoxAddon.SelectedIndex = i;
            m_bRemoveFlag = true;
            buttonApply.Enabled = true;
        }
        bool m_bRemoveFlag = false;

        private void buttonAdd_Click(object sender, EventArgs e)
        {
            listBoxAddon.Items.Add(new TempAddon());
            listBoxAddon.SelectedIndex = listBoxAddon.Items.Count - 1;
        }

        private void buttonApply_Click(object sender, EventArgs e)
        {
            Apply();
        }
        void Apply()
        {
            bool bChanged = false;
            if (!m_bRemoveFlag)
            {
                foreach (Addon item in listBoxAddon.Items)
                {
                    if (item is TempAddon)
                        bChanged = true;
                }
                if (!bChanged)
                    return;
            }
            FormMain.m_AddonManager.Addons.Clear();
            foreach (Addon item in listBoxAddon.Items)
            {
                if (item is TempAddon)
                {
                    Addon add = new Addon(item.Name);
                    add.Path = item.Path;
                    add.StorageType = item.StorageType;
                    add.Type = item.Type;
                    add.Function = item.Function;
                    FormMain.m_AddonManager.Addons.Add(add);        
                }
                else
                    FormMain.m_AddonManager.Addons.Add(item);        
            }
            FormMain.m_AddonManager.SaveConfig();
            
        }
        private void buttonOk_Click(object sender, EventArgs e)
        {
            Apply();
        }
        string RelationPath(string from, string to)
        {
            if (!System.IO.Path.IsPathRooted(to))
                return to;
            List<string> vec1 = new List<string>(from.Split('\\'));
            List<string> vec2 = new List<string>(to.Split('\\'));

            
            int i = 0;
            for (; i < vec1.Count; i++)
            {
                if (vec2.Count == 0)
                    break;
                if (string.Compare(vec1[i], vec2[0], true) == 0)
                    vec2.RemoveAt(0);
                else
                    break;
            }
            while (i < vec1.Count)
            {
                vec2.Insert(0, "..");
                i++;
            }
            if(vec2.Count ==0)
		        vec2.Add(".");
            else if(!vec2[0].StartsWith("."))
		        vec2.Insert(0,".");

            StringBuilder b = new StringBuilder();
            foreach (var item in vec2)
            {
                if (b.Length > 0)
                    b.Append("\\");
                b.Append(item);
            }
            return b.ToString();
           
        }
        /// <summary>
        /// 是否是C函数的开头。
        /// </summary>
        /// <param name="c"></param>
        /// <returns></returns>
        bool IsCFunctionHead(char c)
        {
            if (char.IsLetter(c))
                return true;
            if (c == '_')
                return true;
            
            return false;
        }
        bool IsCFunctionChar(char c)
        {
            if (char.IsLetterOrDigit(c))
                return true;
            if (c == '_')
                return true;

            return false;
        }
        /// <summary>
        /// 判断一个字符串是否是C风格的函数名称
        /// </summary>
        /// <param name="c"></param>
        /// <returns></returns>
        bool IsCFunction(string c)
        {
            //空字符串肯定不是的。
            if (string.IsNullOrEmpty(c))
                return false;
            
            //如果函数头必须是_和字符构成才能是C的函数。
            if (!IsCFunctionHead(c[0]))
                return false;
            //遍历所有的字符必须是字符、数字、_
            foreach (char item in c)
            {
                if (!IsCFunctionChar(item))
                    return false;
            }
            return true;
        }
        void AddFunction(string str)
        {
            m_InnerFlag = true;
            comboBoxFunction.Items.Clear();
            string[] arr = GIS.AddonContainer.ParserDllExport(str);
            if (null != arr)
            {
                foreach (var item in arr)
                {
                    //判断如果是C的函数则增加到建议列表中。
                    if (IsCFunction(item))
                        comboBoxFunction.Items.Add(item);
                }
                
            }
            m_InnerFlag = false;
        }
        private void buttonPath_Click(object sender, EventArgs e)
        {
            using (OpenFileDialog f = new OpenFileDialog())
            {
                f.Filter = "windows动态库*.dll|*.dll";
                if (f.ShowDialog() != System.Windows.Forms.DialogResult.OK)
                    return;
                string strFile = f.FileName;
                AddFunction(strFile);
                textBoxPath.Text = RelationPath(
                    new System.IO.FileInfo( Application.ExecutablePath).Directory.FullName,strFile);
            }
        }
         
         
    }
    class TempAddon : Addon
    {
        public TempAddon():base("[新插件]")
        {
            Type = AddonType.eVectorReader;
            StorageType = StorageType.eFileType;

        }
        public TempAddon(Addon add):base(add.Name)
        {
            Function = add.Function;
            Path = add.Path;
            Type = add.Type;
            StorageType = add.StorageType;
        }
    };
    class WrapAddonType
    {
        public WrapAddonType(AddonType t)
        {
            Type = t;
        }
        public AddonType Type
        {
            get;
            set;
        }
        public override bool Equals(object obj)
        {
            if (obj == null)
                return false;
            WrapAddonType on = obj as WrapAddonType;
            if(null ==on)
                return false;
            return on.Type == Type;
        }
        public override string ToString()
        {
            return Type.ToReadableString();
        }
    };


    class WrapStorageType
    {
        public WrapStorageType(StorageType t)
        {
            Type = t;
        }
        public StorageType Type
        {
            get;
            set;
        }
        public override bool Equals(object obj)
        {
            if (obj == null)
                return false;
            WrapStorageType on = obj as WrapStorageType;
            if (null == on)
                return false;
            return on.Type == Type;
        }
        public override string ToString()
        {
            return Type.ToReadableString();
        }
    };
    static class ExtentFunction
    {
        public static string ToReadableString(this StorageType eType)
        {
            switch (eType)
            {
                case StorageType.eFolderType:
                    return "目录";
                    break;
                case StorageType.eFileType:
                    return "文件";
                case StorageType.eDatabaseType:
                    return "数据库";
                default:
                    break;
            }

            return "未知类型";
        }
        public static string ToReadableString(this AddonType eType)
        {
            switch (eType)
            {
                case AddonType.eErrorAddon:
                    return "错误插件";
                case AddonType.eVectorReader:
                    return "矢量读插件";
                case AddonType.eVectorWriter:
                    return "矢量写插件";
                case AddonType.eRasterReader:
                    return "栅格读插件";
                case AddonType.eRasterWriter:
                    return "栅格写插件";
                case AddonType.eVectorOperator:
                    return "矢量操作插件";
                case AddonType.eRasterOperator:
                    return "栅格操作插件";
                default:
                    break;
            }
            return "";
        }
    }
}
