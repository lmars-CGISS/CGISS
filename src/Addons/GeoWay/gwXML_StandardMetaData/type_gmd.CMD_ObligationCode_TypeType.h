#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_ObligationCode_TypeType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_ObligationCode_TypeType



namespace gie
{

namespace gmd
{	

class CMD_ObligationCode_TypeType : public TypeBase
{
public:
	gie_EXPORT CMD_ObligationCode_TypeType(xercesc::DOMNode* const& init);
	gie_EXPORT CMD_ObligationCode_TypeType(CMD_ObligationCode_TypeType const& init);
	void operator=(CMD_ObligationCode_TypeType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CMD_ObligationCode_TypeType); }

	enum EnumValues {
		Invalid = -1,
		k_mandatory = 0, // mandatory
		k_optional = 1, // optional
		k_conditional = 2, // conditional
		EnumValueCount
	};

	
	gie_EXPORT int GetEnumerationValue();
	gie_EXPORT void SetEnumerationValue( const int index);
	gie_EXPORT void operator=(const string_type& value);
	gie_EXPORT operator string_type();
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_ObligationCode_TypeType
