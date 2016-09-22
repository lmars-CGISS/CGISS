#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CUnitOfMeasureType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CUnitOfMeasureType



namespace gie
{

namespace gml
{	

class CUnitOfMeasureType : public TypeBase
{
public:
	gie_EXPORT CUnitOfMeasureType(xercesc::DOMNode* const& init);
	gie_EXPORT CUnitOfMeasureType(CUnitOfMeasureType const& init);
	void operator=(CUnitOfMeasureType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CUnitOfMeasureType); }

	MemberAttribute<string_type,_altova_mi_gml_altova_CUnitOfMeasureType_altova_uom, 0, 0> uom;	// uom CUomIdentifier
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CUnitOfMeasureType
