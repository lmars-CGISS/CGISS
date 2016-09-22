#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTopoVolumeType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTopoVolumeType

#include "type_gml.CAbstractTopologyType.h"


namespace gie
{

namespace gml
{	

class CTopoVolumeType : public ::gie::gml::CAbstractTopologyType
{
public:
	gie_EXPORT CTopoVolumeType(xercesc::DOMNode* const& init);
	gie_EXPORT CTopoVolumeType(CTopoVolumeType const& init);
	void operator=(CTopoVolumeType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CTopoVolumeType); }
	MemberAttribute<string_type,_altova_mi_gml_altova_CTopoVolumeType_altova_aggregationType, 0, 6> aggregationType;	// aggregationType CAggregationType
	MemberElement<gml::CDirectedTopoSolidPropertyType, _altova_mi_gml_altova_CTopoVolumeType_altova_directedTopoSolid> directedTopoSolid;
	struct directedTopoSolid { typedef Iterator<gml::CDirectedTopoSolidPropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTopoVolumeType
