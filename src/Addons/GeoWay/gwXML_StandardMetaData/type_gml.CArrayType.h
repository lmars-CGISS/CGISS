#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CArrayType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CArrayType

#include "type_gml.CAbstractGMLType.h"


namespace gie
{

namespace gml
{	

class CArrayType : public ::gie::gml::CAbstractGMLType
{
public:
	gie_EXPORT CArrayType(xercesc::DOMNode* const& init);
	gie_EXPORT CArrayType(CArrayType const& init);
	void operator=(CArrayType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CArrayType); }
	MemberElement<gml::CArrayAssociationType, _altova_mi_gml_altova_CArrayType_altova_members> members;
	struct members { typedef Iterator<gml::CArrayAssociationType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CArrayType
