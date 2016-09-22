#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CImageDatumType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CImageDatumType

#include "type_gml.CAbstractDatumType.h"


namespace gie
{

namespace gml
{	

class CImageDatumType : public ::gie::gml::CAbstractDatumType
{
public:
	gie_EXPORT CImageDatumType(xercesc::DOMNode* const& init);
	gie_EXPORT CImageDatumType(CImageDatumType const& init);
	void operator=(CImageDatumType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CImageDatumType); }
	MemberElement<gml::CCodeWithAuthorityType, _altova_mi_gml_altova_CImageDatumType_altova_pixelInCell> pixelInCell;
	struct pixelInCell { typedef Iterator<gml::CCodeWithAuthorityType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CImageDatumType
