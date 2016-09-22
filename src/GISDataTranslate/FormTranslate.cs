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
    partial class FormTranslate : Form
    {
        public FormTranslate()
        {
            InitializeComponent(); 
        }
         

        bool m_bImport;
        bool m_bVector;
        public List<KeyValuePair<StorageInformation, Addon>> DoTranslateBatch(bool bImport, bool bVector)
        {
            PrepareUI(bImport, bVector);
            if (bVector && bImport)
            {
                checkBoxSubSingleton.Checked = true;
                checkBoxSubSingleton.Visible = true;
            }
            if (this.ShowDialog() != System.Windows.Forms.DialogResult.OK)
                return null;

            if (string.IsNullOrEmpty(StandradFileName))
                return null;

            if (m_Storage.Key == null)
                return null;

            List<KeyValuePair<StorageInformation, Addon>> vList = new List<KeyValuePair<StorageInformation, Addon>>();
            if (m_bImport)
            {
                //如果选择了单独文件夹导入。
                if (m_bVector &&
                    checkBoxSubSingleton.Checked)
                {
                    System.IO.DirectoryInfo dir = new System.IO.DirectoryInfo(m_Storage.Key.Server);
                    
                    //输出标准矢量格式的目录
                    System.IO.DirectoryInfo dirOut = new System.IO.DirectoryInfo(StandradFileName);

                    foreach (var item in dir.GetDirectories())
                    {
                        m_Storage.Key.Server = item.FullName;

                        //已目录名称生成。
                        m_Storage.Key["Output"] = System.IO.Path.Combine(
                            dirOut.FullName,item.Name + ".gpkg");
                        
                        vList.Add(new KeyValuePair<StorageInformation, Addon>(
                            m_Storage.Key.Clone(), m_Storage.Value));

                    }
                }
                else
                {
                    m_Storage.Key["Output"] = StandradFileName;
                }
            }
            else
                m_Storage.Key["Input"] = StandradFileName;
             
            if(vList.Count ==0)
                    vList.Add(new KeyValuePair<StorageInformation, Addon>(
                     m_Storage.Key.Clone(), m_Storage.Value));

            return vList;
        }
        void PrepareUI(bool bImport, bool bVector)
        {
            m_bImport = bImport;
            m_bVector = bVector;
            string strCaption = "转换";
            if (bImport && bVector)
                strCaption = "矢量GIS数据==>>标准矢量数据格式";
            if (!bImport && bVector)
                strCaption = "标准矢量数据格式==>>矢量GIS数据";

            if (bImport && !bVector)
                strCaption = "栅格GIS数据==>>标准栅格数据格式";
            if (!bImport && !bVector)
                strCaption = "标准栅格数据格式==>>栅格GIS数据";
            if (bImport)
                textBoxSource.ReadOnly = true;
            else
                textBoxTarget.ReadOnly = true;

            Text = strCaption;
         
        }
        public KeyValuePair<string, Addon> DoTranslate(bool bImport, bool bVector)
        {
            PrepareUI(bImport, bVector);

            if (this.ShowDialog() != System.Windows.Forms.DialogResult.OK)
                return new KeyValuePair<string, Addon>(null, null);

            if (string.IsNullOrEmpty(StandradFileName))
                return  new KeyValuePair<string, Addon>(null, null);

            if(m_Storage.Key == null)
                return new KeyValuePair<string, Addon>(null, null);
            if (m_bImport)
                m_Storage.Key["Output"] = StandradFileName;
            else
                m_Storage.Key["Input"] = StandradFileName;

            return new KeyValuePair<string, Addon>(m_Storage.Key.ToString(), m_Storage.Value);
        }
        string StandradFileName
        {
            get
            {
                string strStand = "";
                if (m_bImport)
                    strStand = textBoxTarget.Text;
                else
                    strStand = textBoxSource.Text;
                if (string.IsNullOrEmpty(strStand))
                {
                    MessageBox.Show("没有输入标准格式数据的路径。", "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return "";
                }
                
                string ext = (new System.IO.FileInfo(strStand)).Extension;
                if (m_bImport && m_bVector && checkBoxSubSingleton.Checked)
                {
                    if (string.IsNullOrEmpty(ext))
                        return strStand;

                    MessageBox.Show("请重新选择目录作为输出路径。", "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return "";
                }
                bool bIsStand = false;
                if (m_bVector)
                    bIsStand = (string.Compare(ext, ".gpkg") == 0);
                else
                    bIsStand = System.IO.Directory.Exists(strStand);
                if (!bIsStand)
                {
                    MessageBox.Show("标准格式数据的路径不正确。", "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    return "";
                }
                return strStand;


            }
        }
        private void buttonSource_Click(object sender, EventArgs e)
        {
            if (m_bImport)
                OpenStorage(textBoxSource, m_bImport, m_bVector);
            else
                OpenStandformat(textBoxSource, m_bImport, m_bVector);


        } 
        void OpenStandformat(TextBox box, bool bImport, bool bVector)
        {
            if(!bVector || (checkBoxSubSingleton.Visible && checkBoxSubSingleton.Checked))
            {
                using (FolderBrowserDialog folder = new FolderBrowserDialog())
                {
                    if (folder.ShowDialog() != System.Windows.Forms.DialogResult.OK)
                        return;

                    box.Text = folder.SelectedPath;
                }
                return;
            }
            FileDialog f =null;
            if(bImport)
                f=  new SaveFileDialog();
            else 
                f= new OpenFileDialog();
            using (f)
            {
                if (bVector)
                    f.Filter = "*.gpkg|*.gpkg|*.gpkx|*.gpkx";
                else
                    f.Filter = "*.tif|*.tif";
                if (f.ShowDialog() != System.Windows.Forms.DialogResult.OK)
                    return;
                box.Text = f.FileName;
            }
        }
        KeyValuePair<StorageInformation, Addon> m_Storage = new KeyValuePair<StorageInformation, Addon>(null, null);
        void OpenStorage(TextBox box, bool bImport, bool bVector)
        {
            using (FormConnectStorage c = new FormConnectStorage())
            {
                AddonType type = AddonType.eErrorAddon;
                if (bImport && bVector)
                    type = AddonType.eVectorReader;
                if (!bImport && bVector)
                    type = AddonType.eVectorWriter;

                if (bImport && !bVector)
                    type = AddonType.eRasterReader;
                if (!bImport && !bVector)
                    type = AddonType.eRasterWriter;

                KeyValuePair<StorageInformation, Addon>  ret = c.ConnectToStorage(FormMain.m_AddonManager, type);
                if (ret.Key == null)
                    return;
                m_Storage = ret; 
                box.Text = m_Storage.Key.Server; 
            }
        } 
        private void buttonTarget_Click(object sender, EventArgs e)
        {
            if (m_bImport)
                OpenStandformat(textBoxTarget, m_bImport, m_bVector);
            else
                OpenStorage(textBoxTarget, m_bImport, m_bVector);
        }

        private void buttonOk_Click(object sender, EventArgs e)
        {
            if (string.IsNullOrEmpty(StandradFileName))
                return;
            if (m_Storage.Key== null)
            {
                MessageBox.Show("转换参数不足。", "错误", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
            DialogResult = System.Windows.Forms.DialogResult.OK;
            Close();
        }
         
         
    }
}
