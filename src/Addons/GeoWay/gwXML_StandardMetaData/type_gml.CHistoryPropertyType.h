#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CHistoryPropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CHistoryPropertyType



namespace gie
{

namespace gml
{	

class CHistoryPropertyType : public TypeBase
{
public:
	gie_EXPORT CHistoryPropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CHistoryPropertyType(CHistoryPropertyType const& init);
	void operator=(CHistoryPropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CHistoryPropertyType); }

	MemberAttribute<bool,_altova_mi_gml_altova_CHistoryPropertyType_altova_owns, 0, 0> owns;	// owns Cboolean
	MemberElement<gml::CMovingObjectStatusType, _altova_mi_gml_altova_CHistoryPropertyType_altova_MovingObjectStatus> MovingObjectStatus;
	struct MovingObjectStatus { typedef Iterator<gml::CMovingObjectStatusType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CHistoryPropertyType
