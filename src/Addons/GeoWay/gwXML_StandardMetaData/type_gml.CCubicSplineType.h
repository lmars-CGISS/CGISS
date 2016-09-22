#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCubicSplineType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCubicSplineType

#include "type_gml.CAbstractCurveSegmentType.h"


namespace gie
{

namespace gml
{	

class CCubicSplineType : public ::gie::gml::CAbstractCurveSegmentType
{
public:
	gie_EXPORT CCubicSplineType(xercesc::DOMNode* const& init);
	gie_EXPORT CCubicSplineType(CCubicSplineType const& init);
	void operator=(CCubicSplineType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CCubicSplineType); }
	MemberAttribute<string_type,_altova_mi_gml_altova_CCubicSplineType_altova_interpolation, 0, 11> interpolation;	// interpolation CCurveInterpolationType

	MemberAttribute<__int64,_altova_mi_gml_altova_CCubicSplineType_altova_degree, 0, 0> degree;	// degree Cinteger
	MemberElement<gml::CDirectPositionType, _altova_mi_gml_altova_CCubicSplineType_altova_pos> pos;
	struct pos { typedef Iterator<gml::CDirectPositionType> iterator; };
	MemberElement<gml::CPointPropertyType, _altova_mi_gml_altova_CCubicSplineType_altova_pointProperty> pointProperty;
	struct pointProperty { typedef Iterator<gml::CPointPropertyType> iterator; };
	MemberElement<gml::CPointPropertyType, _altova_mi_gml_altova_CCubicSplineType_altova_pointRep> pointRep;
	struct pointRep { typedef Iterator<gml::CPointPropertyType> iterator; };
	MemberElement<gml::CDirectPositionListType, _altova_mi_gml_altova_CCubicSplineType_altova_posList> posList;
	struct posList { typedef Iterator<gml::CDirectPositionListType> iterator; };
	MemberElement<gml::CCoordinatesType, _altova_mi_gml_altova_CCubicSplineType_altova_coordinates> coordinates;
	struct coordinates { typedef Iterator<gml::CCoordinatesType> iterator; };
	MemberElement<gml::CVectorType, _altova_mi_gml_altova_CCubicSplineType_altova_vectorAtStart> vectorAtStart;
	struct vectorAtStart { typedef Iterator<gml::CVectorType> iterator; };
	MemberElement<gml::CVectorType, _altova_mi_gml_altova_CCubicSplineType_altova_vectorAtEnd> vectorAtEnd;
	struct vectorAtEnd { typedef Iterator<gml::CVectorType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCubicSplineType
