#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CScopedName_PropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CScopedName_PropertyType



namespace gie
{

namespace gco
{	

class CScopedName_PropertyType : public TypeBase
{
public:
	gie_EXPORT CScopedName_PropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CScopedName_PropertyType(CScopedName_PropertyType const& init);
	void operator=(CScopedName_PropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gco_altova_CScopedName_PropertyType); }
	MemberAttribute<string_type,_altova_mi_gco_altova_CScopedName_PropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType
	MemberElement<gml::CCodeType, _altova_mi_gco_altova_CScopedName_PropertyType_altova_ScopedName> ScopedName;
	struct ScopedName { typedef Iterator<gml::CCodeType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gco

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CScopedName_PropertyType
