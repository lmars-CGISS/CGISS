#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDictionaryType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDictionaryType

#include "type_gml.CDefinitionType.h"


namespace gie
{

namespace gml
{	

class CDictionaryType : public ::gie::gml::CDefinitionType
{
public:
	gie_EXPORT CDictionaryType(xercesc::DOMNode* const& init);
	gie_EXPORT CDictionaryType(CDictionaryType const& init);
	void operator=(CDictionaryType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CDictionaryType); }
	MemberAttribute<string_type,_altova_mi_gml_altova_CDictionaryType_altova_aggregationType, 0, 6> aggregationType;	// aggregationType CAggregationType
	MemberElement<gml::CDictionaryEntryType, _altova_mi_gml_altova_CDictionaryType_altova_dictionaryEntry> dictionaryEntry;
	struct dictionaryEntry { typedef Iterator<gml::CDictionaryEntryType> iterator; };
	MemberElement<gml::CDictionaryEntryType, _altova_mi_gml_altova_CDictionaryType_altova_definitionMember> definitionMember;
	struct definitionMember { typedef Iterator<gml::CDictionaryEntryType> iterator; };
	MemberElement<gml::CIndirectEntryType, _altova_mi_gml_altova_CDictionaryType_altova_indirectEntry> indirectEntry;
	struct indirectEntry { typedef Iterator<gml::CIndirectEntryType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDictionaryType
