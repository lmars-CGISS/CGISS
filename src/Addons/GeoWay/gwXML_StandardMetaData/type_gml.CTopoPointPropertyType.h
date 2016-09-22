#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTopoPointPropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTopoPointPropertyType



namespace gie
{

namespace gml
{	

class CTopoPointPropertyType : public TypeBase
{
public:
	gie_EXPORT CTopoPointPropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CTopoPointPropertyType(CTopoPointPropertyType const& init);
	void operator=(CTopoPointPropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CTopoPointPropertyType); }

	MemberAttribute<bool,_altova_mi_gml_altova_CTopoPointPropertyType_altova_owns, 0, 0> owns;	// owns Cboolean
	MemberElement<gml::CTopoPointType, _altova_mi_gml_altova_CTopoPointPropertyType_altova_TopoPoint> TopoPoint;
	struct TopoPoint { typedef Iterator<gml::CTopoPointType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTopoPointPropertyType
