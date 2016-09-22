#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTopoSolidType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTopoSolidType

#include "type_gml.CAbstractTopoPrimitiveType.h"


namespace gie
{

namespace gml
{	

class CTopoSolidType : public ::gie::gml::CAbstractTopoPrimitiveType
{
public:
	gie_EXPORT CTopoSolidType(xercesc::DOMNode* const& init);
	gie_EXPORT CTopoSolidType(CTopoSolidType const& init);
	void operator=(CTopoSolidType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CTopoSolidType); }
	MemberAttribute<string_type,_altova_mi_gml_altova_CTopoSolidType_altova_aggregationType, 0, 6> aggregationType;	// aggregationType CAggregationType
	MemberElement<gml::CDirectedFacePropertyType, _altova_mi_gml_altova_CTopoSolidType_altova_directedFace> directedFace;
	struct directedFace { typedef Iterator<gml::CDirectedFacePropertyType> iterator; };
	MemberElement<gml::CSolidPropertyType, _altova_mi_gml_altova_CTopoSolidType_altova_solidProperty> solidProperty;
	struct solidProperty { typedef Iterator<gml::CSolidPropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTopoSolidType
