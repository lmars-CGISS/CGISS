using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using GeoStar.Utility;

namespace GISDataTranslate
{
    /// <summary>
    /// 工具条载入，根据配置动态载入工具按钮菜单。
    /// </summary>
    class CToolLoader
    {
        ToolStrip m_vToolStrip; 
        public delegate void Click(object sender,ToolStripItem vItem);
        public event Click OnClick;

        public delegate void ToolCreate(object sender, ToolStripItem vItem);
        public event ToolCreate OnToolCreate;


        static Dictionary<string, string> m_dicGroup = new Dictionary<string, string>();
        static Dictionary<string, ToolStripItem> m_dicGroupItem = new Dictionary<string, ToolStripItem>();
        void AddGroup(string strGroup, ToolStripItem vItemTool)
        {
            m_dicGroup[vItemTool.Name] = strGroup;
            m_dicGroupItem[vItemTool.Name] = vItemTool;
        }

        void CheckGroup(ToolStripItem button)
        {
            if (button.IsChecked())
                return;
            if (!m_dicGroup.ContainsKey(button.Name))
                return;
            string strGroupName = m_dicGroup[button.Name];
            //寻找所有和这个按钮有相同group名称的按钮。
            List<string> vList = new List<string>();
            foreach (var item in m_dicGroup)
            {
                if (string.Compare(item.Value, strGroupName, true) != 0)
                    continue;
                vList.Add(item.Key);
            }
            foreach (var item in vList)
            {
                ToolStripItem b = m_dicGroupItem[item];
                if (b == null)
                    continue;
                b.SetChecked(string.Compare(item, button.Name, true) == 0);
            }

        }
        int m_ImageSize = 32;

        /// <summary>
        /// 工具栏
        /// </summary>
        /// <param name="vToolStrip">为工具栏对象提供容器</param>
        public CToolLoader(ToolStrip vToolStrip)
        {
            m_vToolStrip = vToolStrip; 
        }

        /// <summary>
        /// 工具栏
        /// </summary>
        /// <param name="vToolStrip">为工具栏对象提供容器</param>
        public CToolLoader(ToolStrip vToolStrip,int imgSize)
        {
            m_ImageSize = imgSize;
            m_vToolStrip = vToolStrip;
        }
        /// <summary>
        /// 加载子工具
        /// </summary>
        /// <param name="vItem">子工具</param>
        /// <param name="config">配置对象</param>
        void LoadSubTool(ToolStripMenuItem vItem, Config config)
        {
            if (null == vItem)
                return;
            LoadSubTool(vItem.DropDownItems, config);
        }
        /// <summary>
        /// 加载自工具
        /// </summary>
        /// <param name="vColl">子工具集合</param>
        /// <param name="config">配置对象</param>
        void LoadSubTool(ToolStripItemCollection vColl, Config config)
        {
            if (null == vColl)
                return;
            foreach (var item in config)
            { 
                ToolStripItem vItemTool = item.ObjectValue<ToolStripItem>();
                if (null != vItemTool)
                {
                    ConfigTool(vItemTool, item);
                    vColl.Add(vItemTool);
                    if(null != OnToolCreate)
                        OnToolCreate(this, vItemTool);
                    LoadSubTool(vItemTool as ToolStripMenuItem, item["SubTool"]);
                }
            }
            
        }
        /// <summary>
        /// 给控件设置图像
        /// </summary>
        /// <param name="vItemTool">控件</param>
        /// <param name="config">配置库</param>
        void SetImage(ToolStripItem vItemTool, Config config)
        {
            string strImg = config.StringValue("");
            if (string.IsNullOrEmpty(strImg))
                return;
            if (!System.IO.Path.IsPathRooted(strImg))
                strImg = System.IO.Path.GetFullPath(strImg);
            System.IO.FileInfo vFile = new System.IO.FileInfo(strImg);
            if (!vFile.Exists)
                return;
            if (null == m_List)
            {
                m_List = new ImageList();
                m_List.ImageSize = new System.Drawing.Size(
                    config["IconSize"].IntValue(m_ImageSize),
                    config["IconSize"].IntValue(m_ImageSize));
                
                m_vToolStrip.ImageScalingSize = m_List.ImageSize;
                m_vToolStrip.ImageList = m_List;
            }
            if (!m_List.Images.ContainsKey(vFile.FullName))
                m_List.Images.Add(vFile.FullName,System.Drawing.Image.FromFile(
                    vFile.FullName));
            vItemTool.ImageKey = vFile.FullName;
            
            
        }
        System.Windows.Forms.ImageList m_List;
        /// <summary>
        /// 给控件设置属性
        /// </summary>
        /// <param name="vItemTool">对事件和布局进行管理的基类</param>
        /// <param name="config">配置对象</param>
        void ConfigTool(ToolStripItem vItemTool, Config config)
        {
            vItemTool.AutoSize = true;
            vItemTool.Name = config.Name;
            vItemTool.Text = config["Caption"].StringValue(config.Name);
            vItemTool.DisplayStyle = config["DisplayStyle"].EnumValue<
                ToolStripItemDisplayStyle>(vItemTool.DisplayStyle);
            vItemTool.ToolTipText = config["ToolTip"].StringValue(vItemTool.Text);

            SetImage(vItemTool, config["Image"]);
            vItemTool.Click += new EventHandler(vItemTool_Click);
            string strGroup = config["Group"].StringValue("");
            if (!string.IsNullOrEmpty(strGroup))
                AddGroup(strGroup, vItemTool);
            
        }
        /// <summary>
        /// click事件
        /// </summary>
        /// <param name="sender"事件发送者</param>
        /// <param name="e">事件数据</param>
        void vItemTool_Click(object sender, EventArgs e)
        {
            ToolStripItem item = sender as ToolStripItem;
            if (null == item)
                return;
            CheckGroup(item);
            if (null != OnClick)
                OnClick(this, item);
        }
        /// <summary>
        /// 加载配置
        /// </summary>
        /// <param name="config">配置对象</param>
        public void Load(Config config)
        {
            LoadSubTool(m_vToolStrip.Items, config);
        }
    }
}
