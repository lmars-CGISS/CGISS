#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_PixelOrientationCode_PropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_PixelOrientationCode_PropertyType



namespace gie
{

namespace gmd
{	

class CMD_PixelOrientationCode_PropertyType : public TypeBase
{
public:
	gie_EXPORT CMD_PixelOrientationCode_PropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CMD_PixelOrientationCode_PropertyType(CMD_PixelOrientationCode_PropertyType const& init);
	void operator=(CMD_PixelOrientationCode_PropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CMD_PixelOrientationCode_PropertyType); }
	MemberAttribute<string_type,_altova_mi_gmd_altova_CMD_PixelOrientationCode_PropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType
	MemberElement<gmd::CMD_PixelOrientationCode_TypeType, _altova_mi_gmd_altova_CMD_PixelOrientationCode_PropertyType_altova_MD_PixelOrientationCode> MD_PixelOrientationCode;
	struct MD_PixelOrientationCode { typedef Iterator<gmd::CMD_PixelOrientationCode_TypeType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CMD_PixelOrientationCode_PropertyType
