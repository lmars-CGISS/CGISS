#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CValueArrayType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CValueArrayType

#include "type_gml.CCompositeValueType.h"


namespace gie
{

namespace gml
{	

class CValueArrayType : public ::gie::gml::CCompositeValueType
{
public:
	gie_EXPORT CValueArrayType(xercesc::DOMNode* const& init);
	gie_EXPORT CValueArrayType(CValueArrayType const& init);
	void operator=(CValueArrayType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CValueArrayType); }

	MemberAttribute<string_type,_altova_mi_gml_altova_CValueArrayType_altova_codeSpace, 0, 0> codeSpace;	// codeSpace CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CValueArrayType_altova_uom, 0, 0> uom;	// uom CUomIdentifier
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CValueArrayType
