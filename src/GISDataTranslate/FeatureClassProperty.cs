using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.ComponentModel;
namespace GISDataTranslate
{ 
    [TypeConverter(typeof(ExpandableObjectConverter))]
    class Envelope
    {
        public override string ToString()
        {
            return string.Format("最小X:{0},最小Y:{1},最大X:{2},最大Y:{3}", XMin, YMin, XMax, YMax);
        }
        [Browsable(true), DisplayName("最小X[西]")]
        public double XMin
        {
            get;
            set;
        }
        [Browsable(true), DisplayName("最小Y[南]")]
        public double YMin
        {
            get;
            set;
        }
        [Browsable(true), DisplayName("最大X[东]")]
        public double XMax
        {
            get;
            set;
        }
        [Browsable(true), DisplayName("最大Y[北]")]
        public double YMax
        {
            get;
            set;
        }
    };
    class ExpandablePropertyDescriptor : PropertyDescriptor
    {
        object m_o;
        public ExpandablePropertyDescriptor(object o):base(o.ToString(),null)
        {
            m_o = o;
        }


        public override bool CanResetValue(object component)
        {
            return false;
        }

        public override Type ComponentType
        {
            get { return m_o.GetType(); }
        }

        public override object GetValue(object component)
        {
            return m_o;
        }

        public override bool IsReadOnly
        {
            get { return true; }
        }

        public override Type PropertyType
        {
            get { return m_o.GetType(); }
        }

        public override void ResetValue(object component)
        {
            
        }

        public override void SetValue(object component, object value)
        {
            
        }

        public override bool ShouldSerializeValue(object component)
        {
            return false;
        }
    };
    class ExpandArrayObjectConverter : ExpandableObjectConverter
    {
        public override PropertyDescriptorCollection GetProperties(ITypeDescriptorContext context, object value, Attribute[] attributes)
        {
            System.Collections.IEnumerable en = value as System.Collections.IEnumerable;
            if (null != en)
            {
                List<PropertyDescriptor> vList = new List<PropertyDescriptor>();
                foreach (var item in en)
                {
                    vList.Add(new ExpandablePropertyDescriptor(item));
                }
                return new PropertyDescriptorCollection(vList.ToArray());
            }
            PropertyDescriptorCollection coll =  base.GetProperties(context, value, attributes);
            return coll;
        }
    }
    [TypeConverter(typeof(ExpandArrayObjectConverter))]
    class MetadataDomains:List<MetadataDomain>
    {
        GeoStar.Kernel.RasterClass m_RasterClass;
        public MetadataDomains(GeoStar.Kernel.RasterClass vRaster)
        {
            m_RasterClass = vRaster;

            string[] arr = m_RasterClass.MetadataDomain;
            foreach (var item in arr)
            {
                Add(new MetadataDomain(m_RasterClass, item));
            }
        }
        public override string ToString()
        {
            return "元数据列表";
        }
    }

    class KVPPropertyDescriptor : PropertyDescriptor
    {
        string m_K;
        object m_V;
        public KVPPropertyDescriptor(string k, object v):base(k,null)
        {
            m_K = k;
            m_V = v;
        }
    
        public override bool  CanResetValue(object component)
        {
 	        return false;
        }

        public override Type  ComponentType
        {
            get { return typeof(System.Windows.Forms.RichTextBox); }
        }

        public override object  GetValue(object component)
        {
 	        return m_V;
        }

        public override bool  IsReadOnly
        {
	        get { return true; }
        }

        public override Type  PropertyType
        {
	        get { return m_V.GetType(); }
        }

        public override void  ResetValue(object component)
        {
 	        
        }

        public override void  SetValue(object component, object value)
        { 
        }

        public override bool  ShouldSerializeValue(object component)
        { 
            return false;
        }
    }
    class KVPObjectConverter : ExpandableObjectConverter
    {
        public override PropertyDescriptorCollection GetProperties(ITypeDescriptorContext context, object value, Attribute[] attributes)
        {
            if (!(value is MetadataDomain))
                return base.GetProperties(context, value, attributes);
            MetadataDomain domina = value as MetadataDomain;
            List<PropertyDescriptor> vList = new List<PropertyDescriptor>();
            foreach (var item in domina)
	        {
		        vList.Add(new KVPPropertyDescriptor(item.Key,item.Value));
	        }
            return new PropertyDescriptorCollection(vList.ToArray());
        }
    }

    [TypeConverter(typeof(ExpandableObjectConverter))]
    class MetadataItem
    {
        public MetadataItem(string k, string v)
        {
            Key = k;
            Value = v;
        }
        [Browsable(true), Category("基本信息"), DisplayName("名称")]
        public string Key
        {
            get;
            private set;
        }
        [Browsable(true), Category("基本信息"), DisplayName("值")]
        public string Value
        {
            get;
            private set;
        }

    }
    [TypeConverter(typeof(KVPObjectConverter))]
    class MetadataDomain : List<MetadataItem>
    {
        GeoStar.Kernel.RasterClass m_RasterClass;
        string m_strName;
        public MetadataDomain(GeoStar.Kernel.RasterClass vRaster,string strName)
        {
            m_strName = strName;
            m_RasterClass = vRaster;
            string[] arr = vRaster.MetadataNames(strName);
            if (null == arr)
                return;
            foreach (var item in arr)
            {
                Add(new MetadataItem(item, vRaster.MetadataItem(strName,item)));
            }
        }
        public override string ToString()
        {
            if (string.IsNullOrEmpty(m_strName))
                return "[缺省]";
            return m_strName;
        }
         
    };
    class RasterClassProperty
    {
        GeoStar.Kernel.RasterClass m_RasterClass;
        GeoStar.Kernel.RasterLayer m_Layer;
        public RasterClassProperty(GeoStar.Kernel.RasterLayer vRasterLayer)
        {
            m_Layer = vRasterLayer;
            m_RasterClass = vRasterLayer.RasterClass;
        }
        [Browsable(true), Category("基本信息"), DisplayName("名称")]
        public string Name
        {
            get
            {
                if (m_RasterClass != null)
                    return m_RasterClass.Name;
                return "";
            }
        }

        [Browsable(true), Category("基本信息"), DisplayName("范围")]
        public Envelope Extent
        {
            get
            {
                Envelope env = new Envelope();

                if (m_RasterClass != null)
                {
                    GeoStar.Kernel.Box box = m_RasterClass.Extent(true);
                    env.XMin = box.XMin;
                    env.YMin = box.YMin;
                    env.XMax = box.XMax;
                    env.YMax = box.YMax;
                }
                return env;
            }
        }

        [Browsable(true), Category("基本信息"), DisplayName("像素大小")]
        public System.Drawing.Size Size
        {
            get
            {
                return new System.Drawing.Size(m_RasterClass.Width, m_RasterClass.Height);
            }
        }
        [Browsable(true), Category("基本信息"), DisplayName("元数据")]
        public MetadataDomains Metadata
        {
            get
            {
                return new MetadataDomains(m_RasterClass);
            }
        }
        [Browsable(true), Category("空间参考"), DisplayName("空间参考名称")]
        public string SpatialReferenceName
        {
            get
            {
                if (null == m_RasterClass)
                    return "";

                GeoStar.Kernel.SpatialReference sr = m_RasterClass.SpatialReference;
                if (null == sr)
                    return "";
                return sr.Name;
            }
        }

        [Browsable(true), Category("空间参考"), DisplayName("椭球名称")]
        public string EllipsoidName
        {
            get
            {
                if (null == m_RasterClass)
                    return "";

                GeoStar.Kernel.SpatialReference sr = m_RasterClass.SpatialReference;
                if (null == sr)
                    return "";
                return sr.Ellipsoid;
            }
        }
        [Browsable(true), Category("空间参考"), DisplayName("投影名称")]
        public string ProjectionName
        {
            get
            {
                if (null == m_RasterClass)
                    return "";

                GeoStar.Kernel.SpatialReference sr = m_RasterClass.SpatialReference;
                if (null == sr)
                    return "";
                return sr.Projection;
            }
        }

        [Browsable(true), Category("空间参考"), DisplayName("WKT描述串")]
        public string WKT
        {
            get
            {
                if (null == m_RasterClass)
                    return "";

                GeoStar.Kernel.SpatialReference sr = m_RasterClass.SpatialReference;
                if (null == sr)
                    return "";
                return sr.WKT;
            }
        } 
    }
    class FeatureClassProperty
    {
        GeoStar.Kernel.FeatureClass m_FeatureClass;
        GeoStar.Kernel.FeatureLayer m_Layer;
        public FeatureClassProperty(GeoStar.Kernel.FeatureLayer vFeaLyr)
        {
            m_Layer = vFeaLyr;
            m_FeatureClass = vFeaLyr.FeatureClass;
        }

        [Browsable(false)]
        public GeoStar.Kernel.FeatureLayer Layer
        {
            get
            {
                return m_Layer;
            }
        }
        [Browsable(true),Category("基本信息"),DisplayName("名称")]
        public string Name
        {
            get
            {
                if(m_FeatureClass != null)
                    return m_FeatureClass.Name;
                return "";
            }
        }
        [Browsable(true), Category("基本信息"), DisplayName("范围")]
        public Envelope Extent
        {
            get
            {
                Envelope env = new Envelope();

                if (m_FeatureClass != null)
                {
                    GeoStar.Kernel.Box box = m_FeatureClass.Extent(true);
                    env.XMin = box.XMin;
                    env.YMin = box.YMin;
                    env.XMax = box.XMax;
                    env.YMax = box.YMax;
                }
                return env;
            }
        }
        [Browsable(true), Category("基本信息"), DisplayName("地物数量")]
        public long FeatureCount
        {
            get
            {
                if (m_FeatureClass != null)
                    return m_FeatureClass.FeatureCount;
                return 0;
            }
        }

        [Browsable(true), Category("空间参考"), DisplayName("空间参考名称")]
        public string SpatialReferenceName
        {
            get
            {
                if(null == m_FeatureClass)
                    return "";

                GeoStar.Kernel.SpatialReference sr = m_FeatureClass.SpatialReference;
                if (null == sr)
                    return "";
                return sr.Name;
            }
        }

        [Browsable(true), Category("空间参考"), DisplayName("椭球名称")]
        public string EllipsoidName
        {
            get
            {
                if (null == m_FeatureClass)
                    return "";

                GeoStar.Kernel.SpatialReference sr = m_FeatureClass.SpatialReference;
                if (null == sr)
                    return "";
                return sr.Ellipsoid;
            }
        }
        [Browsable(true), Category("空间参考"), DisplayName("投影名称")]
        public string ProjectionName
        {
            get
            {
                if (null == m_FeatureClass)
                    return "";

                GeoStar.Kernel.SpatialReference sr = m_FeatureClass.SpatialReference;
                if (null == sr)
                    return "";
                return sr.Projection;
            }
        }

        [Browsable(true), Category("空间参考"), DisplayName("WKT描述串")]
        public string WKT
        {
            get
            {
                if (null == m_FeatureClass)
                    return "";

                GeoStar.Kernel.SpatialReference sr = m_FeatureClass.SpatialReference;
                if (null == sr)
                    return ""; 
                return sr.WKT;
            }
        }

        [Browsable(true), Category("显示"), DisplayName("符号")]
        public GeoStar.Kernel.Symbol Symbol
        {
            get
            {
                return m_Layer.Symbol;
            }
        }
    }
     
}
