#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_TopicCategoryCode_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_TopicCategoryCode_Type



namespace gie
{

namespace gmd
{	

class CMD_TopicCategoryCode_Type : public TypeBase
{
public:
	gie_EXPORT CMD_TopicCategoryCode_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CMD_TopicCategoryCode_Type(CMD_TopicCategoryCode_Type const& init);
	void operator=(CMD_TopicCategoryCode_Type const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_gmd_altova_CMD_TopicCategoryCode_Type); }

	enum EnumValues {
		Invalid = -1,
		k_farming = 0, // farming
		k_biota = 1, // biota
		k_boundaries = 2, // boundaries
		k_climatologyMeteorologyAtmosphere = 3, // climatologyMeteorologyAtmosphere
		k_economy = 4, // economy
		k_elevation = 5, // elevation
		k_environment = 6, // environment
		k_geoscientificInformation = 7, // geoscientificInformation
		k_health = 8, // health
		k_imageryBaseMapsEarthCover = 9, // imageryBaseMapsEarthCover
		k_intelligenceMilitary = 10, // intelligenceMilitary
		k_inlandWaters = 11, // inlandWaters
		k_location = 12, // location
		k_oceans = 13, // oceans
		k_planningCadastre = 14, // planningCadastre
		k_society = 15, // society
		k_structure = 16, // structure
		k_transportation = 17, // transportation
		k_utilitiesCommunication = 18, // utilitiesCommunication
		EnumValueCount
	};
	void operator= (const string_type& value) 
	{
		altova::XmlFormatter* Formatter = static_cast<altova::XmlFormatter*>(altova::AnySimpleTypeFormatter);
		XercesTreeOperations::SetValue(GetNode(), Formatter->Format(value));
	}	
		
	operator string_type()
	{
		return CastAs<string_type >::Do(GetNode(), 0);
	}
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_TopicCategoryCode_Type
