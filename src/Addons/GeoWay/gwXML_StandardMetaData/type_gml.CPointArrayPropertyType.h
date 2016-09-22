#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CPointArrayPropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CPointArrayPropertyType



namespace gie
{

namespace gml
{	

class CPointArrayPropertyType : public TypeBase
{
public:
	gie_EXPORT CPointArrayPropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CPointArrayPropertyType(CPointArrayPropertyType const& init);
	void operator=(CPointArrayPropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CPointArrayPropertyType); }

	MemberAttribute<bool,_altova_mi_gml_altova_CPointArrayPropertyType_altova_owns, 0, 0> owns;	// owns Cboolean
	MemberElement<gml::CPointType, _altova_mi_gml_altova_CPointArrayPropertyType_altova_Point> Point;
	struct Point { typedef Iterator<gml::CPointType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CPointArrayPropertyType
