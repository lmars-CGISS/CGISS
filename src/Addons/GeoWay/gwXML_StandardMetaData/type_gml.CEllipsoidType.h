#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CEllipsoidType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CEllipsoidType

#include "type_gml.CIdentifiedObjectType.h"


namespace gie
{

namespace gml
{	

class CEllipsoidType : public ::gie::gml::CIdentifiedObjectType
{
public:
	gie_EXPORT CEllipsoidType(xercesc::DOMNode* const& init);
	gie_EXPORT CEllipsoidType(CEllipsoidType const& init);
	void operator=(CEllipsoidType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CEllipsoidType); }
	MemberElement<gml::CMeasureType, _altova_mi_gml_altova_CEllipsoidType_altova_semiMajorAxis> semiMajorAxis;
	struct semiMajorAxis { typedef Iterator<gml::CMeasureType> iterator; };
	MemberElement<gie2::CsecondDefiningParameterType2, _altova_mi_gml_altova_CEllipsoidType_altova_secondDefiningParameter> secondDefiningParameter;
	struct secondDefiningParameter { typedef Iterator<gie2::CsecondDefiningParameterType2> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CEllipsoidType
