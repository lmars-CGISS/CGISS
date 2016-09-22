#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_PixelOrientationCode_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_PixelOrientationCode_Type



namespace gie
{

namespace gmd
{	

class CMD_PixelOrientationCode_Type : public TypeBase
{
public:
	gie_EXPORT CMD_PixelOrientationCode_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CMD_PixelOrientationCode_Type(CMD_PixelOrientationCode_Type const& init);
	void operator=(CMD_PixelOrientationCode_Type const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_gmd_altova_CMD_PixelOrientationCode_Type); }

	enum EnumValues {
		Invalid = -1,
		k_center = 0, // center
		k_lowerLeft = 1, // lowerLeft
		k_lowerRight = 2, // lowerRight
		k_upperRight = 3, // upperRight
		k_upperLeft = 4, // upperLeft
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

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_PixelOrientationCode_Type
