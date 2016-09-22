#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTopoCurvePropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTopoCurvePropertyType



namespace gie
{

namespace gml
{	

class CTopoCurvePropertyType : public TypeBase
{
public:
	gie_EXPORT CTopoCurvePropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CTopoCurvePropertyType(CTopoCurvePropertyType const& init);
	void operator=(CTopoCurvePropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CTopoCurvePropertyType); }

	MemberAttribute<bool,_altova_mi_gml_altova_CTopoCurvePropertyType_altova_owns, 0, 0> owns;	// owns Cboolean
	MemberElement<gml::CTopoCurveType, _altova_mi_gml_altova_CTopoCurvePropertyType_altova_TopoCurve> TopoCurve;
	struct TopoCurve { typedef Iterator<gml::CTopoCurveType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTopoCurvePropertyType
