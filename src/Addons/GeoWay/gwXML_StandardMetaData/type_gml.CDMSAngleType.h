#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDMSAngleType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDMSAngleType



namespace gie
{

namespace gml
{	

class CDMSAngleType : public TypeBase
{
public:
	gie_EXPORT CDMSAngleType(xercesc::DOMNode* const& init);
	gie_EXPORT CDMSAngleType(CDMSAngleType const& init);
	void operator=(CDMSAngleType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CDMSAngleType); }
	MemberElement<gml::CDegreesType, _altova_mi_gml_altova_CDMSAngleType_altova_degrees> degrees;
	struct degrees { typedef Iterator<gml::CDegreesType> iterator; };
	MemberElement<gml::CDecimalMinutesTypeType, _altova_mi_gml_altova_CDMSAngleType_altova_decimalMinutes> decimalMinutes;
	struct decimalMinutes { typedef Iterator<gml::CDecimalMinutesTypeType> iterator; };
	MemberElement<gml::CArcMinutesTypeType, _altova_mi_gml_altova_CDMSAngleType_altova_minutes> minutes;
	struct minutes { typedef Iterator<gml::CArcMinutesTypeType> iterator; };
	MemberElement<gml::CArcSecondsTypeType, _altova_mi_gml_altova_CDMSAngleType_altova_seconds> seconds;
	struct seconds { typedef Iterator<gml::CArcSecondsTypeType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDMSAngleType
