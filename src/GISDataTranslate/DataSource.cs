using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using GeoStar.Utility;
namespace GISDataTranslate
{
    /// <summary>
    /// 用户生成数据节点的Factory
    /// </summary>
    abstract class DataSourceFactory
    {
        public abstract DataSourceCategoryNode[] MakeDataSourceNode(System.IO.DirectoryInfo dir);
        
    };

    /// <summary>
    /// 数据源的数据节点
    /// </summary>
    abstract class DataSourceCategoryNode : CategoryNode
    {
        public string Name
        {
            get;
            set;
        }
        public GeoStar.Kernel.DataRoomType Type
        {
            set;
            get;
        }
        public abstract GeoStar.Kernel.Layer MakerLayer();
    };
    /// <summary>
    /// FCS矢量地物类工厂
    /// </summary>
    class GeoStarFeatureClassFactory : DataSourceFactory
    {
        protected string m_strFilter;
        public GeoStarFeatureClassFactory(Config config)
        {
            m_strFilter = "*.fcs";
        }
        protected GeoStar.Kernel.GeoDatabaseFactory m_Fac = new GeoStar.Kernel.SqliteGeoDatabaseFactory();
        public override DataSourceCategoryNode[] MakeDataSourceNode(System.IO.DirectoryInfo dir)
        {
            System.IO.FileInfo[] files =  dir.GetFiles(m_strFilter);
            if (null == files || files.Length == 0)
                return null;
            GeoStar.Kernel.ConnectProperty conn = new GeoStar.Kernel.ConnectProperty();
            conn.Server = dir.FullName;
            GeoStar.Kernel.GeoDatabase gdb =  m_Fac.Open(conn);
            if (null == gdb)
                return null;

            List<DataSourceCategoryNode> vList = new List<DataSourceCategoryNode>();
            foreach (var item in gdb.EnumDataRoomName(GeoStar.Kernel.DataRoomType.eFeatureClassType))
            {
                GeoStar.Kernel.FeatureClass vFeaClass = gdb.OpenDataRoom(GeoStar.Kernel.DataRoomType.eFeatureClassType,item) as GeoStar.Kernel.FeatureClass;
                vList.Add(new GeoStarFeatureClassDataSource(vFeaClass));
            }

            return vList.ToArray();
        }
    };
    /// <summary>
    /// 栅格数据
    /// </summary>
    class GeoStarRasterClassDataSource : DataSourceCategoryNode
    {
         GeoStar.Kernel.RasterClass m_vRasterClass;
         public GeoStarRasterClassDataSource(GeoStar.Kernel.RasterClass vRasterClass)
        {
            m_vRasterClass = vRasterClass;
            CreateNode(m_vRasterClass.Name, m_vRasterClass.Name, "raster");
            Name = m_vRasterClass.Name;
            Type = GeoStar.Kernel.DataRoomType.eFeatureClassType;
        }
         GeoStar.Kernel.RasterLayer m_RasterLayer = null;
        public override GeoStar.Kernel.Layer MakerLayer()
        {
            if(null == m_RasterLayer)
            m_RasterLayer  =new GeoStar.Kernel.RasterLayer(m_vRasterClass);
            return m_RasterLayer;
        }
    }
    /// <summary>
    /// geostar的地物类节点
    /// </summary>
    class GeoStarFeatureClassDataSource : DataSourceCategoryNode
    {
        GeoStar.Kernel.FeatureClass m_vFeaClass;
        public GeoStarFeatureClassDataSource(GeoStar.Kernel.FeatureClass vFeaClass)
        {
            m_vFeaClass = vFeaClass;
            CreateNode(vFeaClass.Name, vFeaClass.Name, "featureclass");
            Name = vFeaClass.Name;
            Type = GeoStar.Kernel.DataRoomType.eFeatureClassType;
        }
        GeoStar.Kernel.FeatureLayer m_FeaLyr = null;
        public override GeoStar.Kernel.Layer MakerLayer()
        {
            if(m_FeaLyr == null)
                m_FeaLyr = new GeoStar.Kernel.FeatureLayer(m_vFeaClass);
            return m_FeaLyr;
        }
    };

    /// <summary>
    /// shp文件支持。
    /// </summary>
    class ShpFeatureClassFactory : GeoStarFeatureClassFactory
    {
        public ShpFeatureClassFactory(Config config):base(config)
        {
            m_strFilter = "*.shp";
            m_Fac = new GeoStar.Kernel.ShpGeoDatabaseFactory();
        }
         
    };
    /// <summary>
    /// 栅格文件的工厂。
    /// </summary>
    class RasterFileFactory : DataSourceFactory
    {
        string[] m_Filter;
        public RasterFileFactory(Config config)
        {
            m_Filter = config["FileType"].StringValue("*.tif").Split(',');

        }
        bool ExistRaster(System.IO.DirectoryInfo dir)
        {
            foreach (var item in m_Filter)
            {
                if (dir.GetFiles(item).Length > 0)
                    return true;
            }
            return true;
        }
        GeoStar.Kernel.FileGeoDatabaseFactory m_Fac = new GeoStar.Kernel.FileGeoDatabaseFactory();
        public override DataSourceCategoryNode[] MakeDataSourceNode(System.IO.DirectoryInfo dir)
        {
            List<DataSourceCategoryNode> vList = new List<DataSourceCategoryNode>();
            if (!ExistRaster(dir))
                return vList.ToArray();
            GeoStar.Kernel.ConnectProperty conn = new GeoStar.Kernel.ConnectProperty();
            conn.Server = dir.FullName;
            GeoStar.Kernel.GeoDatabase gdb = m_Fac.Open(conn);
            foreach (var item in gdb.EnumDataRoomName( GeoStar.Kernel.DataRoomType.eRasterClassType))
            {
                GeoStar.Kernel.RasterClass c = gdb.OpenDataRoom(GeoStar.Kernel.DataRoomType.eRasterClassType, item)
                     as GeoStar.Kernel.RasterClass;
                if (null == c)
                    continue;
                vList.Add(new GeoStarRasterClassDataSource(c));
            }
            return vList.ToArray();
        }

    };
    /// <summary>
    /// geopackage数据源工厂
    /// </summary>
    class GPKGFeatureClassFactory : DataSourceFactory
    {
        GeoStar.Kernel.GeoPackageGeoDatabaseFactory m_Fac = new GeoStar.Kernel.GeoPackageGeoDatabaseFactory();
        public GPKGFeatureClassFactory(Config config)
        {

        }
        System.IO.FileInfo[] FindGPKG(System.IO.DirectoryInfo dir)
        {
            List<System.IO.FileInfo> vList = new List<System.IO.FileInfo>();
            System.IO.FileInfo[] files =  dir.GetFiles("*.gpkg");
            if (null != files && files.Length > 0)
            {
                foreach (var item in files)
                {
                    vList.Add(item);
                }
            }

            files = dir.GetFiles("*.gpkx");
            if (null != files && files.Length > 0)
            {
                foreach (var item in files)
                {
                    vList.Add(item);
                }
            }
            return vList.ToArray();
        }
        public override DataSourceCategoryNode[] MakeDataSourceNode(System.IO.DirectoryInfo dir)
        {
            System.IO.FileInfo[] fileName = FindGPKG(dir);
            if (null == fileName || fileName.Length <= 0)
                return null;

            GeoStar.Kernel.ConnectProperty conn = new GeoStar.Kernel.ConnectProperty();
            List<DataSourceCategoryNode> vList = new List<DataSourceCategoryNode>();
            foreach (var item in fileName)
            {
                conn.Server = item.FullName;
                GeoStar.Kernel.GeoDatabase gdb = m_Fac.Open(conn);
                if (null == gdb)
                    continue;
                vList.Add(new GeoDatabaseCategoryNode(gdb,item.Name));
            }
            return vList.ToArray();
        }
    }
    /// <summary>
    /// 数据库的节点
    /// </summary>
    class GeoDatabaseCategoryNode : DataSourceCategoryNode
    {
        GeoStar.Kernel.GeoDatabase m_GDB;
        public GeoDatabaseCategoryNode(GeoStar.Kernel.GeoDatabase gdb,string strName)
        {
            m_GDB = gdb;
            Name = strName;
            Type = GeoStar.Kernel.DataRoomType.eDataRoomFolderType;
            CreateNode(strName, strName, "OpenDB");
            AppendNode(ReplaceNode);
        }
        public override GeoStar.Kernel.Layer MakerLayer()
        {
            return null;
        }
        protected override void OnExpand()
        {
            Dictionary<string, bool> vExist = new Dictionary<string, bool>();
            foreach (var item in m_GDB.EnumDataRoomName( GeoStar.Kernel.DataRoomType.eFeatureClassType))
            {
                GeoStar.Kernel.FeatureClass vFeaClass = m_GDB.OpenDataRoom(GeoStar.Kernel.DataRoomType.eFeatureClassType, item)
                     as GeoStar.Kernel.FeatureClass;
                if (null == vFeaClass)
                    continue;
                vExist[item] = true;
                if (!Node.Nodes.ContainsKey(item))
                {
                    CategoryNode vNode = new GeoStarFeatureClassDataSource(vFeaClass);
                    AppendNode(vNode.Node);
                }
            }
            RemoveDeletedNode(vExist);
        }
    }

}
