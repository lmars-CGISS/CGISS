using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using GeoStar.Utility;
using System.Runtime.InteropServices;
namespace GISDataTranslate
{
   
    /// <summary>
    /// 分类节点
    /// </summary>
    abstract class CategoryNode
    {
        /// <summary>
        /// 分类节点关联的树图节点。
        /// </summary>
        public TreeNode Node = null;

        /// <summary>
        /// 节点关联的树。
        /// </summary>
        public static TreeView TreeView;

        /// <summary>
        /// 树节点占位用的Key
        /// </summary>
        public static string ReplaceKey = Guid.NewGuid().ToString();

        /// <summary>
        /// 占位用的节点。
        /// </summary>
        public TreeNode ReplaceNode
        {
            get
            {
                TreeNode vNode = new TreeNode();
                vNode.Name = ReplaceKey;
                return vNode;
            }
        }
        /// <summary>
        /// 安全删除子节点。
        /// </summary>
        /// <param name="strKey"></param>
        public void RemoveChild(string strKey)
        {
            //如果线程不安全则使用安全委托
            if (Node.TreeView != null && Node.TreeView.InvokeRequired)
            {
                Node.TreeView.Invoke(new Action<string>(RemoveChild), strKey);
                return;
            }

            //删除节点
            Node.Nodes.RemoveByKey(strKey);
        }
        public bool NeverExpand
        {
            get
            {
                if (null == Node)
                    return false;
                return Node.Nodes.ContainsKey(ReplaceKey);
            }
        }
        /// <summary>
        /// 展开节点。
        /// </summary>
        public void Expand()
        {
            //如果包含占位节点则删除之。
            if (Node.Nodes.ContainsKey(ReplaceKey))
                RemoveChild(ReplaceKey);

            //展开数据。
            OnExpand();
        }
        /// <summary>
        /// 有子类继承实现的数据展开节点。
        /// </summary>
        protected virtual void OnExpand()
        {

        }
        /// <summary>
        /// 安全添加子节点
        /// </summary>
        /// <param name="vNode"></param>
        protected void AppendNode(TreeNode vNode)
        {
            //如果线程不安全则使用安全委托
            if (Node.TreeView != null && Node.TreeView.InvokeRequired)
            {
                Node.TreeView.Invoke(new Action<TreeNode>(AppendNode), vNode);
                return;
            }

            //删除节点
            Node.Nodes.Add(vNode);
        }
        /// <summary>
        /// 删除子节点中已经删除的对象
        /// </summary>
        /// <param name="vCache"></param>
        protected void RemoveDeletedNode(Dictionary<string, bool> vCache)
        {

            //遍历检测现有节点中那些被删除了。
            List<string> vDeleted = new List<string>();
            foreach (TreeNode item in Node.Nodes)
            {
                if (vCache.ContainsKey(item.Name))
                    continue;
                vDeleted.Add(item.Name);
            }
            //删除多余的节点。
            foreach (var item in vDeleted)
            {
                RemoveChild(item);
            }
        }
        /// <summary>
        /// 创建树节点
        /// </summary>
        /// <param name="strName"></param>
        /// <param name="strCaption"></param>
        /// <param name="strImage"></param>
        /// <returns></returns>
        protected TreeNode CreateNode(string strName, string strCaption, string strImage)
        {
            //创建树节点，将数据节点和树的物理节点关联起来。
            Node = new TreeNode(strCaption);
            Node.Name = strName;
            Node.Tag = this;
            Node.ImageKey = strImage;
            Node.SelectedImageKey = strImage;
            TreeView.PrepareImage(strImage);

            return Node;
        }


    }
    /// <summary>
    /// 我的电脑节点
    /// </summary>
    class MyComputerCategoryNode : CategoryNode
    {
        List<DataSourceFactory> m_Filter = new List<DataSourceFactory>();

        public MyComputerCategoryNode(Config config)
        {
            Config folder =config["Folder"];
            foreach (var item in folder)
            {
                DataSourceFactory f = item.ObjectValueConfig<DataSourceFactory>();
                if (null == f)
                    continue;
                m_Filter.Add(f);
            }
            //创建物理节点
            CreateNode(config.Name, config["Caption"].StringValue(config.Name),
                        config["Icon"].StringValue("computer"));

            //添加站位节点。
            AppendNode(ReplaceNode);

        }
        /// <summary>
        /// 展开数据。
        /// </summary>
        protected override void OnExpand()
        {
            ///获取所有的目录。
            Dictionary<string, bool> vDic = new Dictionary<string, bool>();
            foreach (var item in System.IO.DriveInfo.GetDrives())
            {
                if (!item.IsReady)
                    continue;
                vDic[item.RootDirectory.Name] = true;
                if (Node.Nodes.ContainsKey(item.RootDirectory.Name))
                    continue;

                //增加子节点
                FolderCategoryNode vNode = new FolderCategoryNode(item.RootDirectory, m_Filter);
                AppendNode(vNode.Node);
            }
            //移除删除的对象
            RemoveDeletedNode(vDic);

        }
    }
    /// <summary>
    /// 目录节点。
    /// </summary>
    class FolderCategoryNode : CategoryNode
    {
        System.IO.DirectoryInfo m_Dir;

        List<DataSourceFactory> m_Filter = new List<DataSourceFactory>();
        public FolderCategoryNode(System.IO.DirectoryInfo dir, List<DataSourceFactory> Filter)
        {
            m_Filter = Filter;
            m_Dir = dir;
            string strIcon = "folder";
            if (dir.Root.FullName == dir.FullName)
                strIcon = "disk";

            //创建物理节点
            CreateNode(m_Dir.Name, m_Dir.Name, strIcon);

            //添加站位节点。
            if (m_Dir.CanVisit())
                AppendNode(ReplaceNode);

        }

        /// <summary>
        /// 展开目录
        /// </summary>
        protected override void OnExpand()
        {
            //存储有效对象id
            Dictionary<string, bool> vCache = new Dictionary<string, bool>();
            foreach (var item in m_Dir.GetDirectories())
            {
                vCache[item.Name] = true;
                if (Node.Nodes.ContainsKey(item.Name))
                    continue;

                //增加子节点
                FolderCategoryNode vNode = new FolderCategoryNode(item, m_Filter);
                AppendNode(vNode.Node);
            }

            //数据源。
            foreach (var item in m_Filter)
            {
                DataSourceCategoryNode[] arr = item.MakeDataSourceNode(m_Dir);
                if (null == arr || arr.Length == 0)
                    continue;
                foreach (var d in arr)
                {
                    AppendNode(d.Node);
                    vCache[d.Name] = true;
                }
            }
            
            //移除删除的对象
            RemoveDeletedNode(vCache);
        }
    }
    
    class FileSystemManager 
    {
        MyComputerCategoryNode m_Root;
        TreeView m_TreeView;
        public FileSystemManager(Config config,TreeView tree)
        {
            m_TreeView = tree;
            CategoryNode.TreeView = tree;
            tree.ImageList = new ImageList();
            tree.ImageList.ImageSize = new System.Drawing.Size(16, 16);

            m_Root = new MyComputerCategoryNode(config);

            m_TreeView.BeforeExpand += new TreeViewCancelEventHandler(TreeView_BeforeExpand);
            m_TreeView.AfterCollapse += new TreeViewEventHandler(TreeView_AfterCollapse);
            m_TreeView.NodeMouseClick += new TreeNodeMouseClickEventHandler(TreeView_NodeMouseClick);
            m_TreeView.Nodes.Add(m_Root.Node);
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
            m_Root.Expand();
        }
        void TreeView_NodeMouseClick(object sender, TreeNodeMouseClickEventArgs e)
        {
            if (null == OnDisplayLayer)
                return;

            DataSourceCategoryNode vNode = e.Node.Tag as DataSourceCategoryNode;
            if (null == vNode)
            {
                OnDisplayLayer(null);
                return;
            }
            OnDisplayLayer(vNode.MakerLayer());
        }
        public delegate void DisplayLayer(GeoStar.Kernel.Layer lyr);
        public event DisplayLayer OnDisplayLayer;
        int ChildCount(TreeNode node)
        {
            int i = node.Nodes.Count;
            foreach (TreeNode item in node.Nodes)
            {
                i += ChildCount(item);
            }
            return i;
        }
        void TreeView_AfterCollapse(object sender, TreeViewEventArgs e)
        {
            if (ChildCount(e.Node) > 100)
            {
                e.Node.Nodes.Clear();
                e.Node.Nodes.Add(CategoryNode.ReplaceKey);
            }
        }

        void TreeView_BeforeExpand(object sender, TreeViewCancelEventArgs e)
        {
            CategoryNode vNode = e.Node.Tag as CategoryNode;
            if (vNode.NeverExpand)
            {
                using (Busy b = new Busy())
                {
                    vNode.Expand();
                }
            }
        }

    }
}
