#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CcontrolPointType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CcontrolPointType



namespace gie
{

namespace gml
{	

class CcontrolPointType : public TypeBase
{
public:
	gie_EXPORT CcontrolPointType(xercesc::DOMNode* const& init);
	gie_EXPORT CcontrolPointType(CcontrolPointType const& init);
	void operator=(CcontrolPointType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CcontrolPointType); }
	MemberElement<gml::CDirectPositionListType, _altova_mi_gml_altova_CcontrolPointType_altova_posList> posList;
	struct posList { typedef Iterator<gml::CDirectPositionListType> iterator; };
	MemberElement<gml::CDirectPositionType, _altova_mi_gml_altova_CcontrolPointType_altova_pos> pos;
	struct pos { typedef Iterator<gml::CDirectPositionType> iterator; };
	MemberElement<gml::CPointPropertyType, _altova_mi_gml_altova_CcontrolPointType_altova_pointProperty> pointProperty;
	struct pointProperty { typedef Iterator<gml::CPointPropertyType> iterator; };
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CcontrolPointType
