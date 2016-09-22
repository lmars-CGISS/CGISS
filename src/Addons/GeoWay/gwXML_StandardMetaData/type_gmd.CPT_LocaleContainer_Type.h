#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CPT_LocaleContainer_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CPT_LocaleContainer_Type



namespace gie
{

namespace gmd
{	

class CPT_LocaleContainer_Type : public TypeBase
{
public:
	gie_EXPORT CPT_LocaleContainer_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CPT_LocaleContainer_Type(CPT_LocaleContainer_Type const& init);
	void operator=(CPT_LocaleContainer_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CPT_LocaleContainer_Type); }
	MemberElement<gco::CCharacterString_PropertyType, _altova_mi_gmd_altova_CPT_LocaleContainer_Type_altova_description> description;
	struct description { typedef Iterator<gco::CCharacterString_PropertyType> iterator; };
	MemberElement<gmd::CPT_Locale_PropertyType, _altova_mi_gmd_altova_CPT_LocaleContainer_Type_altova_locale> locale;
	struct locale { typedef Iterator<gmd::CPT_Locale_PropertyType> iterator; };
	MemberElement<gmd::CCI_Date_PropertyType, _altova_mi_gmd_altova_CPT_LocaleContainer_Type_altova_date> date;
	struct date { typedef Iterator<gmd::CCI_Date_PropertyType> iterator; };
	MemberElement<gmd::CCI_ResponsibleParty_PropertyType, _altova_mi_gmd_altova_CPT_LocaleContainer_Type_altova_responsibleParty> responsibleParty;
	struct responsibleParty { typedef Iterator<gmd::CCI_ResponsibleParty_PropertyType> iterator; };
	MemberElement<gmd::CLocalisedCharacterString_PropertyType, _altova_mi_gmd_altova_CPT_LocaleContainer_Type_altova_localisedString> localisedString;
	struct localisedString { typedef Iterator<gmd::CLocalisedCharacterString_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CPT_LocaleContainer_Type
