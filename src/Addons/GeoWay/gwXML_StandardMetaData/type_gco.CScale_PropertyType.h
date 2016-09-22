#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CScale_PropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CScale_PropertyType



namespace gie
{

namespace gco
{	

class CScale_PropertyType : public TypeBase
{
public:
	gie_EXPORT CScale_PropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CScale_PropertyType(CScale_PropertyType const& init);
	void operator=(CScale_PropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gco_altova_CScale_PropertyType); }
	MemberAttribute<string_type,_altova_mi_gco_altova_CScale_PropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType
	MemberElement<gml::CScaleType, _altova_mi_gco_altova_CScale_PropertyType_altova_Scale> Scale;
	struct Scale { typedef Iterator<gml::CScaleType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gco

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gco_ALTOVA_CScale_PropertyType
