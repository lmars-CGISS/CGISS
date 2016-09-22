#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CConcatenatedOperationType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CConcatenatedOperationType

#include "type_gml.CAbstractCoordinateOperationType.h"


namespace gie
{

namespace gml
{	

class CConcatenatedOperationType : public ::gie::gml::CAbstractCoordinateOperationType
{
public:
	gie_EXPORT CConcatenatedOperationType(xercesc::DOMNode* const& init);
	gie_EXPORT CConcatenatedOperationType(CConcatenatedOperationType const& init);
	void operator=(CConcatenatedOperationType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CConcatenatedOperationType); }
	MemberAttribute<string_type,_altova_mi_gml_altova_CConcatenatedOperationType_altova_aggregationType, 0, 6> aggregationType;	// aggregationType CAggregationType
	MemberElement<gml::CCoordinateOperationPropertyType, _altova_mi_gml_altova_CConcatenatedOperationType_altova_coordOperation> coordOperation;
	struct coordOperation { typedef Iterator<gml::CCoordinateOperationPropertyType> iterator; };
	MemberElement<gml::CCoordinateOperationPropertyType, _altova_mi_gml_altova_CConcatenatedOperationType_altova_usesOperation> usesOperation;
	struct usesOperation { typedef Iterator<gml::CCoordinateOperationPropertyType> iterator; };
	MemberElement<gml::CCoordinateOperationPropertyType, _altova_mi_gml_altova_CConcatenatedOperationType_altova_usesSingleOperation> usesSingleOperation;
	struct usesSingleOperation { typedef Iterator<gml::CCoordinateOperationPropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CConcatenatedOperationType
