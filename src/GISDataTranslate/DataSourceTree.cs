using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace GISDataTranslate
{
    enum NodeSourceType
    { 
        eComputer,
        eDriverSource,
        eFolderSource,
        eVectorDatabase,
        eFeatureClass,
        eImageFile,
    };
    /// <summary>
    /// 封装数据源
    /// </summary>
    class NodeSource
    {
        System.IO.DriveInfo m_Driver;
        System.IO.DirectoryInfo m_Dir;
        GeoStar.Kernel.GeoDatabase m_gdb;
        GeoStar.Kernel.FeatureClass m_FeaClass;
        string m_File;
        public NodeSource()
        {
         
        }
        public GeoStar.Kernel.FeatureClass FeatureClass
        {
            get
            {
                return m_FeaClass;
            }
        }
        public System.IO.DirectoryInfo Folder
        {
            get
            {
                if (m_Driver != null)
                    return m_Driver.RootDirectory;
                if (null != m_Dir)
                    return m_Dir;
                return null;
            }
        }
        public NodeSource(System.IO.DriveInfo d)
        {
            m_Driver = d;
        }
        public NodeSource(System.IO.DirectoryInfo dir)
        {
            m_Dir = dir;
        }
        public NodeSource(GeoStar.Kernel.GeoDatabase gdb)
        {
            m_gdb = gdb;
        }
        public NodeSource(GeoStar.Kernel.FeatureClass feaclass)
        {
            m_FeaClass = feaclass;
        }
        public NodeSource(string strimgfile)
        {
            m_File = strimgfile;
        }
        public string Name
        {
            get
            {
                if (null != m_Driver)
                    return m_Driver.Name;
                if (null != m_Dir)
                    return m_Dir.Name;
                if (null != m_FeaClass)
                    return m_FeaClass.Name;
                if (null != m_gdb)
                {
                    string str = m_gdb.ConnectPropertyInformation.Server;
                    if(System.IO.File.Exists(str))
                        return new System.IO.FileInfo(str).Name;
                    if (System.IO.Directory.Exists(str))
                        return new System.IO.DirectoryInfo(str).Name;

                    return str;
                }
                if (!string.IsNullOrEmpty(m_File))
                    return new System.IO.FileInfo(m_File).Name;
                return "";
            }
        }
        public NodeSource[] Sub
        {
            get
            {
                switch (Type)
                {
                    case NodeSourceType.eComputer:
                        {
                            List<NodeSource> vList = new List<NodeSource>();

                            foreach (var item in System.IO.DriveInfo.GetDrives())
                            {
                                if(item.IsReady)
                                    vList.Add(new NodeSource(item));
                            }
                            return vList.ToArray();
                        }
                    case NodeSourceType.eFeatureClass:
                        return new NodeSource[0];
                    case NodeSourceType.eDriverSource:
                        {
                        List<NodeSource> vList = new List<NodeSource>();
                        foreach (var item in m_Driver.RootDirectory.GetDirectories())
                        {
                            vList.Add(new NodeSource(item));
                        }
                        return vList.ToArray();
                        }
                    case NodeSourceType.eFolderSource:
                        {
                            List<NodeSource> vList = new List<NodeSource>();
                            
                            try
                            {
                                foreach (var item in m_Dir.GetDirectories())
                                {
                                    vList.Add(new NodeSource(item));
                                }
                            }
                            catch
                            {
                            } 
                            return vList.ToArray();
                        }
                    case NodeSourceType.eImageFile:
                    case NodeSourceType.eVectorDatabase:
                        {
                            List<NodeSource> vList = new List<NodeSource>();
                            for (int i = 0; i < m_gdb.FeatureClassCount; i++)
                            {
                                vList.Add(new NodeSource(m_gdb.FeatureClassByIndex(i)));
                            }
                            
                            return vList.ToArray();
                        } 
                    default:
                    break;
                }
                return new NodeSource[0];
            }
        }
        public NodeSourceType Type
        {
            get
            {
                if (null != m_Driver)
                    return NodeSourceType.eDriverSource;
                if (null != m_Dir)
                    return NodeSourceType.eFolderSource;
                if (null != m_gdb)
                    return NodeSourceType.eVectorDatabase;
                if (null != m_FeaClass)
                    return NodeSourceType.eFeatureClass;
                if (!string.IsNullOrEmpty(m_File))
                    return NodeSourceType.eImageFile;
                return NodeSourceType.eComputer;
            }
        }

    };
    /// <summary>
    /// 数据源树
    /// </summary>
    class DataSourceTree
    {
        TreeView m_TreeView;
        TreeNode m_Root;
        string m_ReplaceKey = Guid.NewGuid().ToString();
        ImageList m_ImageList = new ImageList();
        string ReplaceKey
        {
            get
            {
                return m_ReplaceKey;
            }
        }
        TreeNode ReplaceNode
        {
            get
            {
                TreeNode tree = new TreeNode("");
                tree.Name = ReplaceKey;
                return tree;
            }
        }
        void LoadImage(GeoStar.Utility.Config config)
        {
            int w = 0;
            int h = 0;
            Dictionary<string, System.Drawing.Image> vIcons = new Dictionary<string, System.Drawing.Image>();
            foreach (var item in config)
            {
                string strKey = item.Name;
                string strIcon = item.Value;
                if (!System.IO.Path.IsPathRooted(strIcon))
                    strIcon = System.IO.Path.GetFullPath(strIcon);
                if (!System.IO.File.Exists(strIcon))
                    return;
                System.Drawing.Image pIcon = System.Drawing.Image.FromFile(strIcon);
                vIcons[strKey] = pIcon;
                if (w < pIcon.Size.Width)
                    w = pIcon.Size.Width;
                if (h < pIcon.Size.Height)
                    h = pIcon.Size.Height;
            }
            if (w > 24 || h > 24)
            {
                w = 16;
                h = 16;
            }
            m_ImageList.ImageSize = new System.Drawing.Size(w, h);
            foreach (var item in vIcons)
            {
                m_ImageList.Images.Add(item.Key, item.Value);
            }

        }
        [StructLayout(LayoutKind.Sequential)]
        public struct DEV_BROADCAST_VOLUME
        {
            public int dbcv_size;
            public int dbcv_devicetype;
            public int dbcv_reserved;
            public int dbcv_unitmask;
        }
        /// <summary>
        /// 监视系统事件
        /// </summary>
        /// <param name="m"></param>
        public void WatchSystem(Message m)
        {
            // 发生设备变动
            const int WM_DEVICECHANGE = 0x0219;
            // 系统检测到一个新设备
            const int DBT_DEVICEARRIVAL = 0x8000;
            // 系统完成移除一个设备
            const int DBT_DEVICEREMOVECOMPLETE = 0x8001;
            // 逻辑卷标
            const int DBT_DEVTYP_VOLUME = 0x00000002;
            const int DBT_DEVNODES_CHANGED = 0x0007;

            switch (m.Msg)
            {
                case WM_DEVICECHANGE:
                    switch (m.WParam.ToInt32())
                    {
                        case DBT_DEVICEARRIVAL:
                            int devType = Marshal.ReadInt32(m.LParam, 4);
                            if (devType == DBT_DEVTYP_VOLUME)
                            {
                                DEV_BROADCAST_VOLUME vol;
                                vol = (DEV_BROADCAST_VOLUME)Marshal.PtrToStructure(
                                    m.LParam, typeof(DEV_BROADCAST_VOLUME));
                                DeviceChanged();
                            }
                            break;
                        case DBT_DEVICEREMOVECOMPLETE:
                        case DBT_DEVNODES_CHANGED:
                            DeviceChanged(); 
                            break;
                    }
                    break;
            }
        }
        void DeviceChanged()
        {
            UpdateNode(m_Root, m_Root.Tag as NodeSource);
        }
        string ImageKey(NodeSourceType t)
        {
            switch (t)
            {
                case NodeSourceType.eComputer:
                    return "Computer";
                case NodeSourceType.eDriverSource:
                    return "Driver";
                case NodeSourceType.eFolderSource:
                    return "Folder";
                case NodeSourceType.eVectorDatabase:
                    return "GDB";
                case NodeSourceType.eFeatureClass:
                    return "FeatureClass";
                case NodeSourceType.eImageFile:
                    return "Image";
                default:
                    break;
            }
            return "";
        }
        Dictionary<string, CToolLoader> m_ContextMenus = new Dictionary<string, CToolLoader>();
        void LoadContextMenu(GeoStar.Utility.Config config)
        {
            foreach (var item in config)
            {
                ContextMenuStrip menu = new ContextMenuStrip();
                menu.Name = item.Name;
                CToolLoader load = new CToolLoader(menu);
                load.Load(item);
            }
        }
        public DataSourceTree(GeoStar.Utility.Config config, TreeView tree)
        {
            LoadImage(config["Image"]);
            LoadContextMenu(config["Image"]);
            m_TreeView = tree;
            m_TreeView.ImageList = m_ImageList; 
            m_Root = m_TreeView.Nodes.Add("文件");
            m_Root.Nodes.Add(ReplaceNode);
            m_Root.ImageKey = ImageKey(NodeSourceType.eComputer);
            m_Root.SelectedImageKey = m_Root.ImageKey;
            m_Root.Tag = new NodeSource();

            m_TreeView.BeforeExpand += new TreeViewCancelEventHandler(m_TreeView_BeforeExpand);
            m_TreeView.AfterCollapse += new TreeViewEventHandler(m_TreeView_AfterCollapse);
            m_TreeView.NodeMouseClick += new TreeNodeMouseClickEventHandler(m_TreeView_NodeMouseClick);
        }
        public delegate void ClickFeatureClass(GeoStar.Kernel.FeatureClass fea);
        public event ClickFeatureClass OnClickFeatureClass;
        void m_TreeView_NodeMouseClick(object sender, TreeNodeMouseClickEventArgs e)
        {
            NodeSource s = e.Node.Tag as NodeSource;
            if (s.Type == NodeSourceType.eFeatureClass)
            {
                if (null != OnClickFeatureClass)
                    OnClickFeatureClass(s.FeatureClass);
            }
        }

        int ChildCount(TreeNode node)
        {
            int i = node.Nodes.Count;
            foreach (TreeNode item in node.Nodes)
            {
                i += ChildCount(item);
            }
            return i;
        }
        void m_TreeView_AfterCollapse(object sender, TreeViewEventArgs e)
        {
            if (ChildCount(e.Node) > 100)
            {
                e.Node.Nodes.Clear();
                e.Node.Nodes.Add(ReplaceKey);
            }
        }
        List<System.IO.DirectoryInfo> SubFolder(TreeNode vNode)
        {
            List<System.IO.DirectoryInfo> vList = new List<System.IO.DirectoryInfo>();
            if (vNode.Tag == null)
            {
                foreach (var item in System.IO.DriveInfo.GetDrives())
                {
                    vList.Add(item.RootDirectory);
                }
            }
            else
            {
                System.IO.DirectoryInfo dir = vNode.Tag as System.IO.DirectoryInfo;
                try
                {
                    vList.AddRange(dir.GetDirectories());
                }
                catch
                {
                }
            }
            return vList;
        } 
        void AppendTo(TreeNode vNode, NodeSource[] sub)
        {
            Dictionary<string, bool> vDic = new Dictionary<string, bool>();
            foreach (var item in sub)
            {
                vDic[item.Name] = true;
                if (vNode.Nodes.ContainsKey(item.Name))
                    continue;
                TreeNode v = vNode.Nodes.Add(item.Name);
                v.Name = item.Name;
                v.Tag = item;
                v.ImageKey = ImageKey(item.Type);
                v.SelectedImageKey = v.ImageKey;
                if (item.Type != NodeSourceType.eFeatureClass &&
                    item.Type != NodeSourceType.eImageFile)
                    v.Nodes.Add(ReplaceNode);
            }
            List<TreeNode> vListMore = new List<TreeNode>();
            foreach (TreeNode item in vNode.Nodes)
            {
                if (vDic.ContainsKey(item.Name))
                    continue;
                vListMore.Add(item);
            }
            foreach (var item in vListMore)
            {
                item.Remove();
            }
        }
        void UpdateNode(TreeNode vNode,NodeSource source)
        {
            List<NodeSource> list = new List<NodeSource>();
            NodeSource[] sub = source.Sub;
            if (null != sub && sub.Length > 0)
                list.AddRange(sub);

            System.IO.DirectoryInfo folder = source.Folder;
            if (null != folder)
            {
                sub = FileDataSource(folder);
                if (null != sub && sub.Length > 0)
                    list.AddRange(sub);
            }
            AppendTo(vNode, list.ToArray());
        }
        NodeSource[] FindFCS(System.IO.DirectoryInfo dir)
        {

            System.IO.FileInfo[] files = dir.GetFiles("*.fcs");
            if (files.Length == 0)
                return null;
            List<NodeSource> vList = new List<NodeSource>();
            GeoStar.Kernel.SqliteGeoDatabaseFactory fac = new GeoStar.Kernel.SqliteGeoDatabaseFactory();
            GeoStar.Kernel.ConnectProperty conn = new GeoStar.Kernel.ConnectProperty();
            conn.Server = dir.FullName;
            GeoStar.Kernel.GeoDatabase gdb  = fac.Open(conn);
            for (int i = 0; i < gdb.FeatureClassCount; i++)
            {
                vList.Add(new NodeSource(gdb.FeatureClassByIndex(i)));
            }
            return vList.ToArray();
        }
        NodeSource[] FindSHP(System.IO.DirectoryInfo dir)
        {

            System.IO.FileInfo[] files = dir.GetFiles("*.shp");
            if (files.Length == 0)
                return null;
            List<NodeSource> vList = new List<NodeSource>();
            GeoStar.Kernel.ShpGeoDatabaseFactory fac = new GeoStar.Kernel.ShpGeoDatabaseFactory();
            GeoStar.Kernel.ConnectProperty conn = new GeoStar.Kernel.ConnectProperty();
            conn.Server = dir.FullName;
            GeoStar.Kernel.GeoDatabase gdb = fac.Open(conn);
            for (int i = 0; i < gdb.FeatureClassCount; i++)
            {
                vList.Add(new NodeSource(gdb.FeatureClassByIndex(i)));
            }
            return vList.ToArray();
        }
        NodeSource[] FindGPKG(System.IO.DirectoryInfo dir)
        {
            System.IO.FileInfo[] files = dir.GetFiles("*.gpkg");
            if (files.Length == 0)
                return null;
            GeoStar.Kernel.GeoPackageGeoDatabaseFactory fac = new GeoStar.Kernel.GeoPackageGeoDatabaseFactory();
            List<NodeSource> vList = new List<NodeSource>();
            foreach (var item in files)
            {
                GeoStar.Kernel.ConnectProperty conn = new GeoStar.Kernel.ConnectProperty();
                conn.Server = item.FullName;
                GeoStar.Kernel.GeoDatabase gdb = fac.Open(conn);
                if (null != gdb)
                    vList.Add(new NodeSource(gdb));
                
            }
            return vList.ToArray();    
            
        }
        NodeSource[] FileDataSource(System.IO.DirectoryInfo dir)
        {
            List<NodeSource> vList = new List<NodeSource>();
            NodeSource[] arr = FindFCS(dir);
            if(null != arr && arr.Length >0)
                vList.AddRange(arr);
            arr = FindSHP(dir);
            if (null != arr && arr.Length > 0)
                vList.AddRange(arr);
            
            arr = FindGPKG(dir);
            if (null != arr && arr.Length > 0)
                vList.AddRange(arr);
            
            
            return vList.ToArray();
        }

        void m_TreeView_BeforeExpand(object sender, TreeViewCancelEventArgs e)
        {
            if (e.Node.Nodes.ContainsKey(ReplaceKey))
                e.Node.Nodes.Clear();
            UpdateNode(e.Node,e.Node.Tag as NodeSource);
        }

    }
}
