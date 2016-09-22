#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CArcByBulgeType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CArcByBulgeType



namespace gie
{

namespace gml
{	

class CArcByBulgeType : public TypeBase
{
public:
	gie_EXPORT CArcByBulgeType(xercesc::DOMNode* const& init);
	gie_EXPORT CArcByBulgeType(CArcByBulgeType const& init);
	void operator=(CArcByBulgeType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CArcByBulgeType); }

	MemberAttribute<__int64,_altova_mi_gml_altova_CArcByBulgeType_altova_numDerivativesAtStart, 0, 0> numDerivativesAtStart;	// numDerivativesAtStart Cinteger

	MemberAttribute<__int64,_altova_mi_gml_altova_CArcByBulgeType_altova_numDerivativesAtEnd, 0, 0> numDerivativesAtEnd;	// numDerivativesAtEnd Cinteger

	MemberAttribute<__int64,_altova_mi_gml_altova_CArcByBulgeType_altova_numDerivativeInterior, 0, 0> numDerivativeInterior;	// numDerivativeInterior Cinteger
	MemberAttribute<string_type,_altova_mi_gml_altova_CArcByBulgeType_altova_interpolation, 0, 11> interpolation;	// interpolation CCurveInterpolationType

	MemberAttribute<__int64,_altova_mi_gml_altova_CArcByBulgeType_altova_numArc, 0, 0> numArc;	// numArc Cinteger
	MemberElement<gml::CDirectPositionType, _altova_mi_gml_altova_CArcByBulgeType_altova_pos> pos;
	struct pos { typedef Iterator<gml::CDirectPositionType> iterator; };
	MemberElement<gml::CPointPropertyType, _altova_mi_gml_altova_CArcByBulgeType_altova_pointProperty> pointProperty;
	struct pointProperty { typedef Iterator<gml::CPointPropertyType> iterator; };
	MemberElement<gml::CPointPropertyType, _altova_mi_gml_altova_CArcByBulgeType_altova_pointRep> pointRep;
	struct pointRep { typedef Iterator<gml::CPointPropertyType> iterator; };
	MemberElement<gml::CDirectPositionListType, _altova_mi_gml_altova_CArcByBulgeType_altova_posList> posList;
	struct posList { typedef Iterator<gml::CDirectPositionListType> iterator; };
	MemberElement<gml::CCoordinatesType, _altova_mi_gml_altova_CArcByBulgeType_altova_coordinates> coordinates;
	struct coordinates { typedef Iterator<gml::CCoordinatesType> iterator; };
	MemberElement<xs::CdoubleType, _altova_mi_gml_altova_CArcByBulgeType_altova_bulge> bulge;
	struct bulge { typedef Iterator<xs::CdoubleType> iterator; };
	MemberElement<gml::CVectorType, _altova_mi_gml_altova_CArcByBulgeType_altova_normal> normal;
	struct normal { typedef Iterator<gml::CVectorType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CArcByBulgeType
