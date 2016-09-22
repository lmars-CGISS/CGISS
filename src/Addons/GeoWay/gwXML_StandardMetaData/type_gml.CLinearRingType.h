#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CLinearRingType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CLinearRingType

#include "type_gml.CAbstractRingType.h"


namespace gie
{

namespace gml
{	

class CLinearRingType : public ::gie::gml::CAbstractRingType
{
public:
	gie_EXPORT CLinearRingType(xercesc::DOMNode* const& init);
	gie_EXPORT CLinearRingType(CLinearRingType const& init);
	void operator=(CLinearRingType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CLinearRingType); }
	MemberElement<gml::CDirectPositionType, _altova_mi_gml_altova_CLinearRingType_altova_pos> pos;
	struct pos { typedef Iterator<gml::CDirectPositionType> iterator; };
	MemberElement<gml::CPointPropertyType, _altova_mi_gml_altova_CLinearRingType_altova_pointProperty> pointProperty;
	struct pointProperty { typedef Iterator<gml::CPointPropertyType> iterator; };
	MemberElement<gml::CPointPropertyType, _altova_mi_gml_altova_CLinearRingType_altova_pointRep> pointRep;
	struct pointRep { typedef Iterator<gml::CPointPropertyType> iterator; };
	MemberElement<gml::CDirectPositionListType, _altova_mi_gml_altova_CLinearRingType_altova_posList> posList;
	struct posList { typedef Iterator<gml::CDirectPositionListType> iterator; };
	MemberElement<gml::CCoordinatesType, _altova_mi_gml_altova_CLinearRingType_altova_coordinates> coordinates;
	struct coordinates { typedef Iterator<gml::CCoordinatesType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CLinearRingType
