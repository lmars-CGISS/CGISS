#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractGeneralOperationParameterType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractGeneralOperationParameterType

#include "type_gml.CIdentifiedObjectType.h"


namespace gie
{

namespace gml
{	

class CAbstractGeneralOperationParameterType : public ::gie::gml::CIdentifiedObjectType
{
public:
	gie_EXPORT CAbstractGeneralOperationParameterType(xercesc::DOMNode* const& init);
	gie_EXPORT CAbstractGeneralOperationParameterType(CAbstractGeneralOperationParameterType const& init);
	void operator=(CAbstractGeneralOperationParameterType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CAbstractGeneralOperationParameterType); }
	MemberElement<xs::CnonNegativeIntegerType, _altova_mi_gml_altova_CAbstractGeneralOperationParameterType_altova_minimumOccurs> minimumOccurs;
	struct minimumOccurs { typedef Iterator<xs::CnonNegativeIntegerType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractGeneralOperationParameterType
