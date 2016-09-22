#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CURL_PropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CURL_PropertyType



namespace gie
{

namespace gmd
{	

class CURL_PropertyType : public TypeBase
{
public:
	gie_EXPORT CURL_PropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CURL_PropertyType(CURL_PropertyType const& init);
	void operator=(CURL_PropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CURL_PropertyType); }
	MemberAttribute<string_type,_altova_mi_gmd_altova_CURL_PropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType
	MemberElement<xs::CanyURIType, _altova_mi_gmd_altova_CURL_PropertyType_altova_URL> URL;
	struct URL { typedef Iterator<xs::CanyURIType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CURL_PropertyType
