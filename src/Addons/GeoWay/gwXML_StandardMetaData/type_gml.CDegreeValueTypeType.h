#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDegreeValueTypeType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDegreeValueTypeType



namespace gie
{

namespace gml
{	

class CDegreeValueTypeType : public TypeBase
{
public:
	gie_EXPORT CDegreeValueTypeType(xercesc::DOMNode* const& init);
	gie_EXPORT CDegreeValueTypeType(CDegreeValueTypeType const& init);
	void operator=(CDegreeValueTypeType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CDegreeValueTypeType); }
	gie_EXPORT void operator=(const unsigned __int64& value);
	gie_EXPORT operator unsigned __int64();
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDegreeValueTypeType
