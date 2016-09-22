#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CBezierType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CBezierType



namespace gie
{

namespace gml
{	

class CBezierType : public TypeBase
{
public:
	gie_EXPORT CBezierType(xercesc::DOMNode* const& init);
	gie_EXPORT CBezierType(CBezierType const& init);
	void operator=(CBezierType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CBezierType); }

	MemberAttribute<__int64,_altova_mi_gml_altova_CBezierType_altova_numDerivativesAtStart, 0, 0> numDerivativesAtStart;	// numDerivativesAtStart Cinteger

	MemberAttribute<__int64,_altova_mi_gml_altova_CBezierType_altova_numDerivativesAtEnd, 0, 0> numDerivativesAtEnd;	// numDerivativesAtEnd Cinteger

	MemberAttribute<__int64,_altova_mi_gml_altova_CBezierType_altova_numDerivativeInterior, 0, 0> numDerivativeInterior;	// numDerivativeInterior Cinteger
	MemberAttribute<string_type,_altova_mi_gml_altova_CBezierType_altova_interpolation, 0, 11> interpolation;	// interpolation CCurveInterpolationType

	MemberAttribute<bool,_altova_mi_gml_altova_CBezierType_altova_isPolynomial, 0, 0> isPolynomial;	// isPolynomial Cboolean
	MemberAttribute<string_type,_altova_mi_gml_altova_CBezierType_altova_knotType, 0, 3> knotType;	// knotType CKnotTypesType
	MemberElement<gml::CDirectPositionType, _altova_mi_gml_altova_CBezierType_altova_pos> pos;
	struct pos { typedef Iterator<gml::CDirectPositionType> iterator; };
	MemberElement<gml::CPointPropertyType, _altova_mi_gml_altova_CBezierType_altova_pointProperty> pointProperty;
	struct pointProperty { typedef Iterator<gml::CPointPropertyType> iterator; };
	MemberElement<gml::CPointPropertyType, _altova_mi_gml_altova_CBezierType_altova_pointRep> pointRep;
	struct pointRep { typedef Iterator<gml::CPointPropertyType> iterator; };
	MemberElement<gml::CDirectPositionListType, _altova_mi_gml_altova_CBezierType_altova_posList> posList;
	struct posList { typedef Iterator<gml::CDirectPositionListType> iterator; };
	MemberElement<gml::CCoordinatesType, _altova_mi_gml_altova_CBezierType_altova_coordinates> coordinates;
	struct coordinates { typedef Iterator<gml::CCoordinatesType> iterator; };
	MemberElement<xs::CnonNegativeIntegerType, _altova_mi_gml_altova_CBezierType_altova_degree> degree;
	struct degree { typedef Iterator<xs::CnonNegativeIntegerType> iterator; };
	MemberElement<gml::CKnotPropertyType, _altova_mi_gml_altova_CBezierType_altova_knot> knot;
	struct knot { typedef Iterator<gml::CKnotPropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CBezierType
