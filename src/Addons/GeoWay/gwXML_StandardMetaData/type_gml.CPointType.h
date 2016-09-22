#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CPointType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CPointType

#include "type_gml.CAbstractGeometricPrimitiveType.h"


namespace gie
{

namespace gml
{	

class CPointType : public ::gie::gml::CAbstractGeometricPrimitiveType
{
public:
	gie_EXPORT CPointType(xercesc::DOMNode* const& init);
	gie_EXPORT CPointType(CPointType const& init);
	void operator=(CPointType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CPointType); }
	MemberElement<gml::CDirectPositionType, _altova_mi_gml_altova_CPointType_altova_pos> pos;
	struct pos { typedef Iterator<gml::CDirectPositionType> iterator; };
	MemberElement<gml::CCoordinatesType, _altova_mi_gml_altova_CPointType_altova_coordinates> coordinates;
	struct coordinates { typedef Iterator<gml::CCoordinatesType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CPointType
