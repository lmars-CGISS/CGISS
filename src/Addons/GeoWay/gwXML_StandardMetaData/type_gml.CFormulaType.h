#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CFormulaType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CFormulaType



namespace gie
{

namespace gml
{	

class CFormulaType : public TypeBase
{
public:
	gie_EXPORT CFormulaType(xercesc::DOMNode* const& init);
	gie_EXPORT CFormulaType(CFormulaType const& init);
	void operator=(CFormulaType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CFormulaType); }
	MemberElement<xs::CdoubleType, _altova_mi_gml_altova_CFormulaType_altova_a> a;
	struct a { typedef Iterator<xs::CdoubleType> iterator; };
	MemberElement<xs::CdoubleType, _altova_mi_gml_altova_CFormulaType_altova_b> b;
	struct b { typedef Iterator<xs::CdoubleType> iterator; };
	MemberElement<xs::CdoubleType, _altova_mi_gml_altova_CFormulaType_altova_c> c;
	struct c { typedef Iterator<xs::CdoubleType> iterator; };
	MemberElement<xs::CdoubleType, _altova_mi_gml_altova_CFormulaType_altova_d> d;
	struct d { typedef Iterator<xs::CdoubleType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CFormulaType
