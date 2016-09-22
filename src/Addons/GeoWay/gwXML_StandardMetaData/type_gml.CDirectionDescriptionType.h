#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDirectionDescriptionType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDirectionDescriptionType



namespace gie
{

namespace gml
{	

class CDirectionDescriptionType : public TypeBase
{
public:
	gie_EXPORT CDirectionDescriptionType(xercesc::DOMNode* const& init);
	gie_EXPORT CDirectionDescriptionType(CDirectionDescriptionType const& init);
	void operator=(CDirectionDescriptionType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CDirectionDescriptionType); }
	MemberElement<gml::CCompassPointEnumerationType, _altova_mi_gml_altova_CDirectionDescriptionType_altova_compassPoint> compassPoint;
	struct compassPoint { typedef Iterator<gml::CCompassPointEnumerationType> iterator; };
	MemberElement<gml::CCodeType, _altova_mi_gml_altova_CDirectionDescriptionType_altova_keyword> keyword;
	struct keyword { typedef Iterator<gml::CCodeType> iterator; };
	MemberElement<xs::CstringType, _altova_mi_gml_altova_CDirectionDescriptionType_altova_description> description;
	struct description { typedef Iterator<xs::CstringType> iterator; };
	MemberElement<gml::CReferenceType, _altova_mi_gml_altova_CDirectionDescriptionType_altova_reference> reference;
	struct reference { typedef Iterator<gml::CReferenceType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDirectionDescriptionType
