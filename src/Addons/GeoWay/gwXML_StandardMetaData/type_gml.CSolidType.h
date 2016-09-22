#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CSolidType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CSolidType

#include "type_gml.CAbstractSolidType.h"


namespace gie
{

namespace gml
{	

class CSolidType : public ::gie::gml::CAbstractSolidType
{
public:
	gie_EXPORT CSolidType(xercesc::DOMNode* const& init);
	gie_EXPORT CSolidType(CSolidType const& init);
	void operator=(CSolidType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CSolidType); }
	MemberElement<gml::CShellPropertyType, _altova_mi_gml_altova_CSolidType_altova_exterior> exterior;
	struct exterior { typedef Iterator<gml::CShellPropertyType> iterator; };
	MemberElement<gml::CShellPropertyType, _altova_mi_gml_altova_CSolidType_altova_interior> interior;
	struct interior { typedef Iterator<gml::CShellPropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CSolidType
