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
    /// <summary>
    /// 进度条显示窗口
    /// </summary>
    partial class FormProgress : Form
    {
        public FormProgress()
        {
            InitializeComponent();
            richTextBox1 = new RichTextBox();
            this.Controls.Add(richTextBox1);
            richTextBox1.Dock = DockStyle.Fill;
            richTextBox1.LinkClicked += new LinkClickedEventHandler(richTextBox1_LinkClicked);
        }
        RichTextBox richTextBox1;
        
        void richTextBox1_LinkClicked(object sender, LinkClickedEventArgs e)
        {
            try
            {
                System.Diagnostics.Process.Start(e.LinkText); // call default browser 
            }
            catch
            {

            }
        }
        protected override void OnClosing(CancelEventArgs e)
        {
            if (m_Progress != null)
            {
                if (m_Progress.Busy)
                {
                    MessageBox.Show("正在执行转换无法退出。","提示",  MessageBoxButtons.OK, MessageBoxIcon.Error);
                    e.Cancel = true;
                    return;
                }
            }
            base.OnClosing(e); 

        }
        List<KeyValuePair<string, Addon>> m_vList;
        AddonProgress m_Progress;
        public void DoProgress(List<KeyValuePair<string, Addon>> vList, Form f)
        {
            m_vList = vList;
            m_Progress = new AddonProgress(richTextBox1);
            this.Show(f);
        }
        public void DoProgress(string str, Addon addon,Form f)
        {
            m_vList = new List<KeyValuePair<string, Addon>>();
             
            m_vList.Add(new KeyValuePair<string, Addon>(str, addon));

            m_Progress = new AddonProgress(richTextBox1);
            this.Show(f);

        }
        protected override void OnLoad(EventArgs e)
        {
            base.OnLoad(e);
            System.Threading.Thread thread = new System.Threading.Thread(
                new System.Threading.ThreadStart(OnThread));
            thread.Start();
        }
        void OnThread()
        {

            m_Progress.Begin();
            foreach (var item in m_vList)
            {
                if (item.Value.Context == null)
                    continue;
                if (!item.Value.Context.IsValid)
                    continue;

                item.Value.Context.Execute(item.Key, m_Progress);
                m_Progress.AddLog(Color.Black, "");
            }
            
            m_Progress.End();
        }
    }
    
}
