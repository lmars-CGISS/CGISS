#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_COperationParameterType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_COperationParameterType

#include "type_gml.CAbstractGeneralOperationParameterType.h"


namespace gie
{

namespace gml
{	

class COperationParameterType : public ::gie::gml::CAbstractGeneralOperationParameterType
{
public:
	gie_EXPORT COperationParameterType(xercesc::DOMNode* const& init);
	gie_EXPORT COperationParameterType(COperationParameterType const& init);
	void operator=(COperationParameterType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_COperationParameterType); }
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_COperationParameterType
