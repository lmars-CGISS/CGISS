#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractSurfacePatchType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractSurfacePatchType



namespace gie
{

namespace gml
{	

class CAbstractSurfacePatchType : public TypeBase
{
public:
	gie_EXPORT CAbstractSurfacePatchType(xercesc::DOMNode* const& init);
	gie_EXPORT CAbstractSurfacePatchType(CAbstractSurfacePatchType const& init);
	void operator=(CAbstractSurfacePatchType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CAbstractSurfacePatchType); }
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CAbstractSurfacePatchType
