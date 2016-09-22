#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAngleChoiceType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAngleChoiceType



namespace gie
{

namespace gml
{	

class CAngleChoiceType : public TypeBase
{
public:
	gie_EXPORT CAngleChoiceType(xercesc::DOMNode* const& init);
	gie_EXPORT CAngleChoiceType(CAngleChoiceType const& init);
	void operator=(CAngleChoiceType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CAngleChoiceType); }
	MemberElement<gml::CAngleType, _altova_mi_gml_altova_CAngleChoiceType_altova_angle> angle;
	struct angle { typedef Iterator<gml::CAngleType> iterator; };
	MemberElement<gml::CDMSAngleType, _altova_mi_gml_altova_CAngleChoiceType_altova_dmsAngle> dmsAngle;
	struct dmsAngle { typedef Iterator<gml::CDMSAngleType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAngleChoiceType
