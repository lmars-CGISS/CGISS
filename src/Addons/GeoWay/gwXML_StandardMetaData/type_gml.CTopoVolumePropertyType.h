#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTopoVolumePropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTopoVolumePropertyType



namespace gie
{

namespace gml
{	

class CTopoVolumePropertyType : public TypeBase
{
public:
	gie_EXPORT CTopoVolumePropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CTopoVolumePropertyType(CTopoVolumePropertyType const& init);
	void operator=(CTopoVolumePropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CTopoVolumePropertyType); }

	MemberAttribute<bool,_altova_mi_gml_altova_CTopoVolumePropertyType_altova_owns, 0, 0> owns;	// owns Cboolean
	MemberElement<gml::CTopoVolumeType, _altova_mi_gml_altova_CTopoVolumePropertyType_altova_TopoVolume> TopoVolume;
	struct TopoVolume { typedef Iterator<gml::CTopoVolumeType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CTopoVolumePropertyType
