#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractRingType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractRingType



namespace gie
{

namespace gml
{	

class CAbstractRingType : public TypeBase
{
public:
	gie_EXPORT CAbstractRingType(xercesc::DOMNode* const& init);
	gie_EXPORT CAbstractRingType(CAbstractRingType const& init);
	void operator=(CAbstractRingType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CAbstractRingType); }
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractRingType
