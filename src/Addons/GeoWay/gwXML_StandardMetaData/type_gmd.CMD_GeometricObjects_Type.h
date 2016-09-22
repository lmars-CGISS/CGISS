#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_GeometricObjects_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_GeometricObjects_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gmd
{	

class CMD_GeometricObjects_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CMD_GeometricObjects_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CMD_GeometricObjects_Type(CMD_GeometricObjects_Type const& init);
	void operator=(CMD_GeometricObjects_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CMD_GeometricObjects_Type); }
	MemberElement<gmd::CMD_GeometricObjectTypeCode_PropertyType, _altova_mi_gmd_altova_CMD_GeometricObjects_Type_altova_geometricObjectType> geometricObjectType;
	struct geometricObjectType { typedef Iterator<gmd::CMD_GeometricObjectTypeCode_PropertyType> iterator; };
	MemberElement<gco::CInteger_PropertyType, _altova_mi_gmd_altova_CMD_GeometricObjects_Type_altova_geometricObjectCount> geometricObjectCount;
	struct geometricObjectCount { typedef Iterator<gco::CInteger_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_GeometricObjects_Type
