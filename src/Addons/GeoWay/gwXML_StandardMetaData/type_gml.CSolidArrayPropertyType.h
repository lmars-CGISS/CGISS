#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CSolidArrayPropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CSolidArrayPropertyType



namespace gie
{

namespace gml
{	

class CSolidArrayPropertyType : public TypeBase
{
public:
	gie_EXPORT CSolidArrayPropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CSolidArrayPropertyType(CSolidArrayPropertyType const& init);
	void operator=(CSolidArrayPropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CSolidArrayPropertyType); }

	MemberAttribute<bool,_altova_mi_gml_altova_CSolidArrayPropertyType_altova_owns, 0, 0> owns;	// owns Cboolean
	MemberElement<gml::CCompositeSolidType, _altova_mi_gml_altova_CSolidArrayPropertyType_altova_CompositeSolid> CompositeSolid;
	struct CompositeSolid { typedef Iterator<gml::CCompositeSolidType> iterator; };
	MemberElement<gml::CSolidType, _altova_mi_gml_altova_CSolidArrayPropertyType_altova_Solid> Solid;
	struct Solid { typedef Iterator<gml::CSolidType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CSolidArrayPropertyType
