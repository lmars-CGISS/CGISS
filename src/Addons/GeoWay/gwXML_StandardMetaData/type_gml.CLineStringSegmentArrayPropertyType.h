#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CLineStringSegmentArrayPropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CLineStringSegmentArrayPropertyType



namespace gie
{

namespace gml
{	

class CLineStringSegmentArrayPropertyType : public TypeBase
{
public:
	gie_EXPORT CLineStringSegmentArrayPropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CLineStringSegmentArrayPropertyType(CLineStringSegmentArrayPropertyType const& init);
	void operator=(CLineStringSegmentArrayPropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CLineStringSegmentArrayPropertyType); }
	MemberElement<gml::CLineStringSegmentType, _altova_mi_gml_altova_CLineStringSegmentArrayPropertyType_altova_LineStringSegment> LineStringSegment;
	struct LineStringSegment { typedef Iterator<gml::CLineStringSegmentType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CLineStringSegmentArrayPropertyType
