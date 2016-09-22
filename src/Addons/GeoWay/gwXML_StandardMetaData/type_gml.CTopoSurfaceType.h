#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTopoSurfaceType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTopoSurfaceType

#include "type_gml.CAbstractTopologyType.h"


namespace gie
{

namespace gml
{	

class CTopoSurfaceType : public ::gie::gml::CAbstractTopologyType
{
public:
	gie_EXPORT CTopoSurfaceType(xercesc::DOMNode* const& init);
	gie_EXPORT CTopoSurfaceType(CTopoSurfaceType const& init);
	void operator=(CTopoSurfaceType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CTopoSurfaceType); }
	MemberAttribute<string_type,_altova_mi_gml_altova_CTopoSurfaceType_altova_aggregationType, 0, 6> aggregationType;	// aggregationType CAggregationType
	MemberElement<gml::CDirectedFacePropertyType, _altova_mi_gml_altova_CTopoSurfaceType_altova_directedFace> directedFace;
	struct directedFace { typedef Iterator<gml::CDirectedFacePropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTopoSurfaceType
