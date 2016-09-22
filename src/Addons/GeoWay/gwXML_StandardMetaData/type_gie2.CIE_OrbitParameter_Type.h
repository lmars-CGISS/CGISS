#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_OrbitParameter_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_OrbitParameter_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gie2
{	

class CIE_OrbitParameter_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CIE_OrbitParameter_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CIE_OrbitParameter_Type(CIE_OrbitParameter_Type const& init);
	void operator=(CIE_OrbitParameter_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gie2_altova_CIE_OrbitParameter_Type); }
	MemberElement<gco::CDateTime_PropertyType, _altova_mi_gie2_altova_CIE_OrbitParameter_Type_altova_time> time;
	struct time { typedef Iterator<gco::CDateTime_PropertyType> iterator; };
	MemberElement<gco::CReal_PropertyType, _altova_mi_gie2_altova_CIE_OrbitParameter_Type_altova_velocityX> velocityX;
	struct velocityX { typedef Iterator<gco::CReal_PropertyType> iterator; };
	MemberElement<gco::CReal_PropertyType, _altova_mi_gie2_altova_CIE_OrbitParameter_Type_altova_velocityY> velocityY;
	struct velocityY { typedef Iterator<gco::CReal_PropertyType> iterator; };
	MemberElement<gco::CReal_PropertyType, _altova_mi_gie2_altova_CIE_OrbitParameter_Type_altova_velocityZ> velocityZ;
	struct velocityZ { typedef Iterator<gco::CReal_PropertyType> iterator; };
	MemberElement<gco::CReal_PropertyType, _altova_mi_gie2_altova_CIE_OrbitParameter_Type_altova_x> x;
	struct x { typedef Iterator<gco::CReal_PropertyType> iterator; };
	MemberElement<gco::CReal_PropertyType, _altova_mi_gie2_altova_CIE_OrbitParameter_Type_altova_y> y;
	struct y { typedef Iterator<gco::CReal_PropertyType> iterator; };
	MemberElement<gco::CReal_PropertyType, _altova_mi_gie2_altova_CIE_OrbitParameter_Type_altova_z> z;
	struct z { typedef Iterator<gco::CReal_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gie2

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_OrbitParameter_Type
