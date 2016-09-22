#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CLineStringSegmentType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CLineStringSegmentType

#include "type_gml.CAbstractCurveSegmentType.h"


namespace gie
{

namespace gml
{	

class CLineStringSegmentType : public ::gie::gml::CAbstractCurveSegmentType
{
public:
	gie_EXPORT CLineStringSegmentType(xercesc::DOMNode* const& init);
	gie_EXPORT CLineStringSegmentType(CLineStringSegmentType const& init);
	void operator=(CLineStringSegmentType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CLineStringSegmentType); }
	MemberAttribute<string_type,_altova_mi_gml_altova_CLineStringSegmentType_altova_interpolation, 0, 11> interpolation;	// interpolation CCurveInterpolationType
	MemberElement<gml::CDirectPositionType, _altova_mi_gml_altova_CLineStringSegmentType_altova_pos> pos;
	struct pos { typedef Iterator<gml::CDirectPositionType> iterator; };
	MemberElement<gml::CPointPropertyType, _altova_mi_gml_altova_CLineStringSegmentType_altova_pointProperty> pointProperty;
	struct pointProperty { typedef Iterator<gml::CPointPropertyType> iterator; };
	MemberElement<gml::CPointPropertyType, _altova_mi_gml_altova_CLineStringSegmentType_altova_pointRep> pointRep;
	struct pointRep { typedef Iterator<gml::CPointPropertyType> iterator; };
	MemberElement<gml::CDirectPositionListType, _altova_mi_gml_altova_CLineStringSegmentType_altova_posList> posList;
	struct posList { typedef Iterator<gml::CDirectPositionListType> iterator; };
	MemberElement<gml::CCoordinatesType, _altova_mi_gml_altova_CLineStringSegmentType_altova_coordinates> coordinates;
	struct coordinates { typedef Iterator<gml::CCoordinatesType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CLineStringSegmentType
