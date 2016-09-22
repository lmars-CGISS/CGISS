#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractCurveSegmentType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractCurveSegmentType



namespace gie
{

namespace gml
{	

class CAbstractCurveSegmentType : public TypeBase
{
public:
	gie_EXPORT CAbstractCurveSegmentType(xercesc::DOMNode* const& init);
	gie_EXPORT CAbstractCurveSegmentType(CAbstractCurveSegmentType const& init);
	void operator=(CAbstractCurveSegmentType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CAbstractCurveSegmentType); }

	MemberAttribute<__int64,_altova_mi_gml_altova_CAbstractCurveSegmentType_altova_numDerivativesAtStart, 0, 0> numDerivativesAtStart;	// numDerivativesAtStart Cinteger

	MemberAttribute<__int64,_altova_mi_gml_altova_CAbstractCurveSegmentType_altova_numDerivativesAtEnd, 0, 0> numDerivativesAtEnd;	// numDerivativesAtEnd Cinteger

	MemberAttribute<__int64,_altova_mi_gml_altova_CAbstractCurveSegmentType_altova_numDerivativeInterior, 0, 0> numDerivativeInterior;	// numDerivativeInterior Cinteger
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractCurveSegmentType
