#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCompoundCRSType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCompoundCRSType

#include "type_gml.CAbstractCRSType.h"


namespace gie
{

namespace gml
{	

class CCompoundCRSType : public ::gie::gml::CAbstractCRSType
{
public:
	gie_EXPORT CCompoundCRSType(xercesc::DOMNode* const& init);
	gie_EXPORT CCompoundCRSType(CCompoundCRSType const& init);
	void operator=(CCompoundCRSType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CCompoundCRSType); }
	MemberAttribute<string_type,_altova_mi_gml_altova_CCompoundCRSType_altova_aggregationType, 0, 6> aggregationType;	// aggregationType CAggregationType
	MemberElement<gml::CSingleCRSPropertyType, _altova_mi_gml_altova_CCompoundCRSType_altova_componentReferenceSystem> componentReferenceSystem;
	struct componentReferenceSystem { typedef Iterator<gml::CSingleCRSPropertyType> iterator; };
	MemberElement<gml::CSingleCRSPropertyType, _altova_mi_gml_altova_CCompoundCRSType_altova_includesSingleCRS> includesSingleCRS;
	struct includesSingleCRS { typedef Iterator<gml::CSingleCRSPropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CCompoundCRSType
