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
    partial class FormConnectStorage : Form
    {
        public FormConnectStorage()
        {
            InitializeComponent();
            comboBoxType.SelectedIndexChanged += new EventHandler(comboBoxType_SelectedIndexChanged); 
        }
         

        void comboBoxType_SelectedIndexChanged(object sender, EventArgs e)
        {
            buttonFolder.Enabled = false;
            if (comboBoxType.SelectedIndex < 0)
                return;
            Addon add = comboBoxType.SelectedItem as Addon;

            buttonFolder.Enabled = add.StorageType != StorageType.eDatabaseType;
            
        }
        public KeyValuePair<StorageInformation, Addon> ConnectToStorage(AddonManager mgr, AddonType type)
        {
            foreach (var item in mgr.Addons)
            {
                if (item.Type != type)
                    continue;
                comboBoxType.Items.Add(item);
            }
            if(comboBoxType.Items.Count >0)
                comboBoxType.SelectedIndex = 0;
            if (this.ShowDialog() != System.Windows.Forms.DialogResult.OK)
                return new KeyValuePair<StorageInformation, Addon>(null, null);
            if (comboBoxType.SelectedIndex < 0)
                return new KeyValuePair<StorageInformation, Addon>(null, null);

            Addon addon = comboBoxType.SelectedItem as Addon;
            StorageInformation info = new StorageInformation(addon.StorageType);
            info.Server = textBoxServer.Text;
            info.Database = textBoxDatabase.Text;
            info.User = textBoxUser.Text;
            info.Password = textBoxPassword.Text;
            info.Port = Convert.ToInt32(numericUpDownPort.Value);

            return new KeyValuePair<StorageInformation, Addon>(info, addon);
        }

        private void buttonFolder_Click(object sender, EventArgs e)
        {
            if (comboBoxType.SelectedIndex < 0)
                return;
            Addon add = comboBoxType.SelectedItem as Addon;
            if (add.StorageType == StorageType.eFileType)
            {
                if (add.Type == AddonType.eRasterWriter ||
                    add.Type == AddonType.eVectorWriter)
                {
                    using (SaveFileDialog f = new SaveFileDialog())
                    {
                        f.Filter = "*.*|*.*";
                        if (f.ShowDialog() != System.Windows.Forms.DialogResult.OK)
                            return;
                        textBoxServer.Text = f.FileName;
                    }
                }
                else
                {
                    using (OpenFileDialog f = new OpenFileDialog())
                    {
                        f.Filter = "*.*|*.*";
                        if (f.ShowDialog() != System.Windows.Forms.DialogResult.OK)
                            return;
                        textBoxServer.Text = f.FileName;
                    }
                }
            }
            else
            {
                using (FolderBrowserDialog f = new FolderBrowserDialog())
                {
                    if (f.ShowDialog() != System.Windows.Forms.DialogResult.OK)
                        return;
                    textBoxServer.Text = f.SelectedPath;
                }
            }
        }
    }
    
    /// <summary>
    /// 存储介质信息
    /// </summary>
    class StorageInformation:Dictionary<string,string>
    {
        public StorageInformation(StorageType t)
        {
            Type = t;
        }
        public StorageInformation Clone()
        {
            StorageInformation info = new StorageInformation(Type);
            foreach (var item in this)
            {
                info[item.Key] = item.Value;
            }
            info.Server = Server;
            info.Port = Port;
            info.Database = Database;
            info.User = User;
            info.Password = Password;
            return info;

        }
        System.Xml.XmlElement NewElement(System.Xml.XmlElement e,string strName)
        {
            System.Xml.XmlElement ele = e.OwnerDocument.CreateElement(strName);
            e.AppendChild(ele);
            return ele;
        }
        void AppendKVP(System.Xml.XmlElement root, string k, string v)
        {
            System.Xml.XmlElement param = NewElement(root, "Parameter");
            System.Xml.XmlElement value = NewElement(param, "Value");
            param.SetAttribute("Key", k);
            value.InnerText = v;
        }
        
        public override string ToString()
        {
            System.Xml.XmlDocument doc = new System.Xml.XmlDocument();
            doc.AppendChild(doc.CreateElement("GIS"));

            if (Type == StorageType.eDatabaseType)
            {
                AppendKVP(doc.DocumentElement, "Server", Server);
                AppendKVP(doc.DocumentElement, "Database", Database);
                AppendKVP(doc.DocumentElement, "User", User);
                AppendKVP(doc.DocumentElement, "Password", Password);
                AppendKVP(doc.DocumentElement, "Port", Port.ToString());
            }
            else
                AppendKVP(doc.DocumentElement, "Path", Server);

            foreach (var item in this)
            {
                AppendKVP(doc.DocumentElement, item.Key, item.Value);
            }
            return doc.OuterXml;
        }
        public StorageType Type
        {
            get;
            private set;
        }
        public String Server
        {
            get;
            set;
        }
        public String Database
        {
            get;
            set;
        }
        public String User
        {
            get;
            set;
        }
        public String Password
        {
            get;
            set;
        }
        public int Port
        {
            get;
            set;
        }
    };

}
