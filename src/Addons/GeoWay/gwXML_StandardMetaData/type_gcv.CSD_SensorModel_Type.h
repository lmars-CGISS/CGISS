#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gcv_ALTOVA_CSD_SensorModel_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gcv_ALTOVA_CSD_SensorModel_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gcv
{	

class CSD_SensorModel_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CSD_SensorModel_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CSD_SensorModel_Type(CSD_SensorModel_Type const& init);
	void operator=(CSD_SensorModel_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gcv_altova_CSD_SensorModel_Type); }
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gcv_altova_CSD_SensorModel_Type_altova_sensorParameters> sensorParameters;
	struct sensorParameters { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gcv_altova_CSD_SensorModel_Type_altova_platformParameters> platformParameters;
	struct platformParameters { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gcv

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gcv_ALTOVA_CSD_SensorModel_Type
