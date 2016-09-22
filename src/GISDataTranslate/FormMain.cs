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
    public partial class FormMain : Form
    {
        internal static GIS.AddonContainer m_Container;
        internal static GeoStar.Control.GeoSpace2D m_GeoSpace;
        GConfig m_Config;
        CToolLoader m_MainToolBar,m_MainMenuBar;
        internal static AddonManager m_AddonManager;
        FileSystemManager m_FileSystemManager;
        
        public FormMain()
        {
            InitializeComponent();
            m_Config = new GConfig(System.IO.Path.Combine(AppDomain.CurrentDomain.BaseDirectory, "config.xml"));
            if (m_Config.Exist("Application"))
                LoadConfig(m_Config["Application"]);
            new IconManager(m_Config["Application"]);
            m_FileSystemManager = new FileSystemManager(m_Config["FileSystemTree"], treeView1);
            m_FileSystemManager.OnDisplayLayer += new FileSystemManager.DisplayLayer(m_FileSystemManager_OnDisplayLayer);
            m_Container = new GIS.AddonContainer();
            
            string str = GIS.AddonContainer.DllDirectory;
            m_GeoSpace = new GeoStar.Control.GeoSpace2D();
            splitContainerMap.Panel1.Controls.Add(m_GeoSpace);
            m_GeoSpace.Dock = DockStyle.Fill;

            m_MainToolBar.OnClick += new CToolLoader.Click(m_MainToolBar_OnClick);
            m_MainMenuBar.OnClick += new CToolLoader.Click(m_MainToolBar_OnClick);
            m_AddonManager = new AddonManager(); 

            m_GeoSpace.MouseMove += new MouseEventHandler(m_GeoSpace_MouseMove);
            m_GeoSpace.Cursor = Cursors.Hand;
            WindowState = FormWindowState.Maximized;
            splitContainer1.SplitterDistance = splitContainer1.Width / 4;

            splitContainerMap.SplitterDistance = 3 * splitContainerMap.Width / 4;
        }

        void m_FileSystemManager_OnDisplayLayer(GeoStar.Kernel.Layer lyr)
        {
            m_GeoSpace.ClearLayer();
            propertyGrid1.SelectedObject = null;
            if (null == lyr)
                return;

            m_GeoSpace.AddLayer(lyr);
            m_GeoSpace.ViewFullMap();
            if(lyr is GeoStar.Kernel.FeatureLayer)
                propertyGrid1.SelectedObject = new FeatureClassProperty(lyr as GeoStar.Kernel.FeatureLayer);
            else if(lyr is GeoStar.Kernel.RasterLayer)
                propertyGrid1.SelectedObject = new RasterClassProperty(lyr as GeoStar.Kernel.RasterLayer);
            
            if (m_QueryResult == null)
                return;
            if (m_QueryResult.Visible)
                m_QueryResult.Hide();
            
        }
         
        CursorMgr m_CursorMgr;
        void m_GeoSpace_MouseMove(object sender, MouseEventArgs e)
        {
            double mapx = 0, mapy = 0;
            m_GeoSpace.ToMap(e.X, e.Y, ref mapx, ref mapy);
            toolStripStatusLabelBasic.Text = string.Format("x={0} y={1}", mapx, mapy);
        } 
        
        protected override void WndProc(ref Message m)
        {
            m_FileSystemManager.WatchSystem(m);
            base.WndProc(ref m);

        } 
         protected override void OnMouseHover(EventArgs e)
         {
             this.Focus();
             base.OnMouseHover(e);
         }
        FormProgress m_TranslateProgress = null;
        protected override void OnClosing(CancelEventArgs e)
        {
            if (m_TranslateProgress != null)
            {
                if (m_TranslateProgress.Visible)
                {
                    m_TranslateProgress.Close();
                    if (m_TranslateProgress.Visible)
                    {
                        e.Cancel = true;
                        return;
                    }
                }
            }
            if (null != m_QueryResult)
            {
                m_QueryResult.ForceClose = true;
                m_QueryResult.Close();
            }
            base.OnClosing(e);
        }
        void Translate(bool bImport, bool bVecotr)
        {   
            using (FormTranslate f = new FormTranslate())
            {
                KeyValuePair<string, Addon> ret = f.DoTranslate(bImport, bVecotr);
                if (string.IsNullOrEmpty(ret.Key))
                    return;
                Translate(ret.Key, ret.Value);
            }
            
        }
        
        void Translate(string str, Addon add)
        {
            if (!add.CreateContext())
                return;
            
            m_TranslateProgress = new FormProgress();
            m_TranslateProgress.DoProgress(str, add, this);
        }
        
        void OnQuery(GeoStar.Kernel.Box box)
        {
            FeatureClassProperty pro = (FeatureClassProperty)(propertyGrid1.SelectedObject);
            if(null == pro)
                return;
            GeoStar.Kernel.FeatureLayer vLyr = pro.Layer;
            if (null == vLyr)
                return;
            GeoStar.Kernel.SelectionSet sel =  vLyr.FeatureClass.Select(box);
            if (null == sel)
                return;
            if (null == m_QueryResult)
                m_QueryResult = new FormQueryResult();

            using (WaitCursor wait = new WaitCursor())
            {
                m_QueryResult.Show(sel, vLyr);

                if (!m_QueryResult.Visible)
                    m_QueryResult.Show(this);
            }
        }
        /// <summary>
        /// 批量进行转换
        /// </summary>
        void BatchTranslate()
        {
            List<KeyValuePair<string, Addon>> vListOut = new List<KeyValuePair<string, Addon>>();
            using (FormBatch f = new FormBatch())
            {
                List<KeyValuePair<string, Addon>> vList = f.SelectBatch();
                if (null == vList)
                    return;
                foreach (var item in vList)
                {
                    if(!item.Value.CreateContext())
                        continue;
                    vListOut.Add(item);
                }
            }

            m_TranslateProgress = new FormProgress();
            m_TranslateProgress.DoProgress(vListOut, this);

        }
        FormQueryResult m_QueryResult = null;
        void m_MainToolBar_OnClick(object sender, ToolStripItem vItem)
        {
            switch (vItem.Name)
	        {
                case "Exit":
                    this.Close();
                    return;
                case "Pan":
                    m_GeoSpace.Cursor = m_CursorMgr.Cursor("ZoomPan");
                    m_GeoSpace.ZoomPan();
                    break;
                case "BatchTranslate":
                    BatchTranslate();
                    break;
                case "Query":
                    m_GeoSpace.ScreenDrawBox.TrackEnvelope(new GeoStar.Control.ScreenDrawBox.EnvelopeTracked(OnQuery));
                    m_GeoSpace.Cursor = m_CursorMgr.Cursor("Query");
                    
                    break;
                case "ZoomOut":
                    m_GeoSpace.Cursor = m_CursorMgr.Cursor("ZoomOut");
                    m_GeoSpace.ZoomOut();
                    break;
                case "ZoomIn":
                    m_GeoSpace.Cursor = m_CursorMgr.Cursor("ZoomIn");
                    m_GeoSpace.ZoomIn();
                    break;
                case "FullMap":
                    m_GeoSpace.ViewFullMap();
                    break;
                case "Update":
                    m_GeoSpace.UpdateMap();
                    break;
                case "ImportVector":
                    Translate(true, true);
                    break;
                case "ExportVector":
                    Translate(false, true);
                    break;
                case "ImportRaster":
                    Translate(true, false);
                    break;
                case "ExportRaster":
                    Translate(false, false);
                    break;
                case "AddonManager":
                    {
                        using (FormAddon f = new FormAddon())
                        {
                            f.ShowDialog();
                                
                        }
                    }
                    break;
		        default:
                    break;
               }
        } 
        void LoadConfig(GeoStar.Utility.Config config)
        {
            m_CursorMgr = new CursorMgr(config["Cursors"]);

            Text = config.Child("Caption").StringValue("");
            string strIcon = config.Child("Icon").StringValue("");
            if (!string.IsNullOrEmpty(strIcon))
            {
                if (!System.IO.Path.IsPathRooted(strIcon))
                    strIcon = System.IO.Path.Combine(AppDomain.CurrentDomain.BaseDirectory, strIcon);
                if (System.IO.File.Exists(strIcon))
                    this.Icon = new Icon(strIcon);
            }
            m_MainToolBar = new CToolLoader(toolStrip1);
            m_MainMenuBar = new CToolLoader(menuStrip1,16);

            if(config.Exist("Menu"))
                m_MainMenuBar.Load(config.Child("Menu"));
            
            if (config.Exist("ToolBar"))
                m_MainToolBar.Load(config.Child("ToolBar"));

        }
    }
}
