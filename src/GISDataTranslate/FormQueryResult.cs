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
    public partial class FormQueryResult : Form
    {
        public FormQueryResult()
        {
            InitializeComponent();
            m_RootNode = treeView1.Nodes.Add("查询结果");
            treeView1.NodeMouseClick += new TreeNodeMouseClickEventHandler(treeView1_NodeMouseClick);
            ForceClose = false;
        }
        public bool ForceClose
        {
            get;
            set;
        }
        protected override void OnClosing(CancelEventArgs e)
        {
            if (!ForceClose)
            {
                e.Cancel = true;
                this.Hide();
                return;
            }
            base.OnClosing(e);
        }
        void treeView1_NodeMouseClick(object sender, TreeNodeMouseClickEventArgs e)
        {
            propertyGrid1.SelectedObject = null;
            if (e.Node == m_RootNode)
                return;
            if (e.Node.Tag != null)
                return;
            GeoStar.Kernel.FeatureLayer vFeaLyr = (GeoStar.Kernel.FeatureLayer)e.Node.Parent.Tag;
            long nOID = long.Parse(e.Node.Text);
            GeoStar.Kernel.Feature vFea = vFea = vFeaLyr.FeatureClass.GetFeature(nOID);
            if(null != vFea)
                FormMain.m_GeoSpace.HighlightBox.Highlight(vFea);

            propertyGrid1.SelectedObject = new FeatureAdapter(vFea);
        }
        TreeNode m_RootNode;
        public void Show(GeoStar.Kernel.SelectionSet sel,GeoStar.Kernel.FeatureLayer vLyr)
        {
            propertyGrid1.SelectedObject = null;
            m_RootNode.Nodes.Clear();
            Append(sel, vLyr);
            m_RootNode.Expand();
        }
        void Append(GeoStar.Kernel.SelectionSet sel, GeoStar.Kernel.FeatureLayer vLyr)
        {
            TreeNode vNodeLyr = m_RootNode.Nodes.Add(vLyr.FeatureClass.Name);
            vNodeLyr.Tag = vLyr;
            Append(sel, vNodeLyr);
        }
        void Append(GeoStar.Kernel.SelectionSet sel,TreeNode vNode)
        {
            sel.Reset();
            long nOID =0;
            while ((nOID = sel.Next()) > 0)
            {
                vNode.Nodes.Add(nOID.ToString());
            }
        }
    }

    class FeatureAdapter : ICustomTypeDescriptor
    {
        GeoStar.Kernel.Feature m_Fea;
        public FeatureAdapter(GeoStar.Kernel.Feature Fea)
        {
            m_Fea = Fea;
        }
        //Three of the ICustomTypeDescriptor methods are never called by the property grid, but we'll stub them out properly anyway:
        public string GetComponentName()
        {
            return TypeDescriptor.GetComponentName(this, true);
        }

        public EventDescriptor GetDefaultEvent()
        {
            return TypeDescriptor.GetDefaultEvent(this, true);
        }

        public string GetClassName()
        {
            return TypeDescriptor.GetClassName(this, true);
        }
        //Then there's a whole slew of methods that are called by PropertyGrid, but we don't need to do anything interesting in them:

        public EventDescriptorCollection GetEvents(Attribute[] attributes)
        {
            return TypeDescriptor.GetEvents(this, attributes, true);
        }

        EventDescriptorCollection System.ComponentModel.ICustomTypeDescriptor.GetEvents()
        {
            return TypeDescriptor.GetEvents(this, true);
        }

        public TypeConverter GetConverter()
        {
            return TypeDescriptor.GetConverter(this, true);
        }

        public object GetPropertyOwner(PropertyDescriptor pd)
        {
            return m_Fea;
        }

        public AttributeCollection GetAttributes()
        {
            return TypeDescriptor.GetAttributes(this, true);
        }

        public object GetEditor(Type editorBaseType)
        {
            return TypeDescriptor.GetEditor(this, editorBaseType, true);
        }

        public PropertyDescriptor GetDefaultProperty()
        {
            return null;
        }

        PropertyDescriptorCollection
            System.ComponentModel.ICustomTypeDescriptor.GetProperties()
        {
            return ((ICustomTypeDescriptor)this).GetProperties(new Attribute[0]);
        }
        
        public PropertyDescriptorCollection GetProperties(Attribute[] attributes)
        {
            List<PropertyDescriptor> vList = new List<PropertyDescriptor>();
            for (int i = 0; i < m_Fea.FieldCount; i++)
            {
                string strCat;
                if (i < 2)
                    strCat = "基本信息";
                else
                    strCat = "属性信息";
                vList.Add(new KVPDescriptor(m_Fea.FieldName(i), m_Fea.GetValue(i), strCat));
            }
            
            return new PropertyDescriptorCollection(vList.ToArray());
        }
    }

    class KVPDescriptor : PropertyDescriptor
    {
        string m_Key;
        object m_Value;
        string m_strCategory;
        internal KVPDescriptor(string key,object v,string strCategory)
            : base(key.ToString(), null)
        {
            m_strCategory = strCategory;
            m_Key = key;
            m_Value = v;
        }
        
        public override string Category
        {
            get
            {
                return m_strCategory;
            }
        }
        public override Type PropertyType
        {
            get 
            {
                if (null == m_Value)
                    return null;

                return m_Value.GetType(); 
            }
        }
        //If you knew that all of your values were strings, for example, you could just return typeof(string).

        //Then we implement SetValue and GetValue:

        public override void SetValue(object component, object value)
        {
            
        }

        public override object GetValue(object component)
        {
            return m_Value;
        }
        public override bool IsReadOnly
        {
            get { return true; }
        }

        public override Type ComponentType
        {
            get { return null; }
        }

        public override bool CanResetValue(object component)
        {
            return false;
        }

        public override void ResetValue(object component)
        {
        }

        public override bool ShouldSerializeValue(object component)
        {
            return false;
        }
    }


}
