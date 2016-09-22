#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CRectifiedGridType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CRectifiedGridType

#include "type_gml.CGridType.h"


namespace gie
{

namespace gml
{	

class CRectifiedGridType : public ::gie::gml::CGridType
{
public:
	gie_EXPORT CRectifiedGridType(xercesc::DOMNode* const& init);
	gie_EXPORT CRectifiedGridType(CRectifiedGridType const& init);
	void operator=(CRectifiedGridType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CRectifiedGridType); }
	MemberElement<gml::CPointPropertyType, _altova_mi_gml_altova_CRectifiedGridType_altova_origin> origin;
	struct origin { typedef Iterator<gml::CPointPropertyType> iterator; };
	MemberElement<gml::CVectorType, _altova_mi_gml_altova_CRectifiedGridType_altova_offsetVector> offsetVector;
	struct offsetVector { typedef Iterator<gml::CVectorType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CRectifiedGridType
