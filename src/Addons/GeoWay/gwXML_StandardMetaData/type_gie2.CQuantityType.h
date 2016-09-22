#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CQuantityType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CQuantityType

#include "type_gml.CMeasureType.h"


namespace gie
{

namespace gie2
{	

class CQuantityType : public ::gie::gml::CMeasureType
{
public:
	gie_EXPORT CQuantityType(xercesc::DOMNode* const& init);
	gie_EXPORT CQuantityType(CQuantityType const& init);
	void operator=(CQuantityType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gie2_altova_CQuantityType); }
	gie_EXPORT void operator=(const double& value);
	MemberAttribute<string_type,_altova_mi_gie2_altova_CQuantityType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType
	gie_EXPORT void SetXsiType();
};



} // namespace gie2

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CQuantityType
