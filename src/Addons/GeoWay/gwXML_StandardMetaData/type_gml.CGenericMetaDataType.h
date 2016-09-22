#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CGenericMetaDataType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CGenericMetaDataType

#include "type_gml.CAbstractMetaDataType.h"


namespace gie
{

namespace gml
{	

class CGenericMetaDataType : public ::gie::gml::CAbstractMetaDataType
{
public:
	gie_EXPORT CGenericMetaDataType(xercesc::DOMNode* const& init);
	gie_EXPORT CGenericMetaDataType(CGenericMetaDataType const& init);
	void operator=(CGenericMetaDataType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CGenericMetaDataType); }
	gie_EXPORT void operator=(const string_type& value);
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CGenericMetaDataType
