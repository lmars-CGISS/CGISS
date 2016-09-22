#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CPassThroughOperationType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CPassThroughOperationType

#include "type_gml.CAbstractCoordinateOperationType.h"


namespace gie
{

namespace gml
{	

class CPassThroughOperationType : public ::gie::gml::CAbstractCoordinateOperationType
{
public:
	gie_EXPORT CPassThroughOperationType(xercesc::DOMNode* const& init);
	gie_EXPORT CPassThroughOperationType(CPassThroughOperationType const& init);
	void operator=(CPassThroughOperationType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CPassThroughOperationType); }
	MemberAttribute<string_type,_altova_mi_gml_altova_CPassThroughOperationType_altova_aggregationType, 0, 6> aggregationType;	// aggregationType CAggregationType
	MemberElement<xs::CpositiveIntegerType, _altova_mi_gml_altova_CPassThroughOperationType_altova_modifiedCoordinate> modifiedCoordinate;
	struct modifiedCoordinate { typedef Iterator<xs::CpositiveIntegerType> iterator; };
	MemberElement<gml::CCoordinateOperationPropertyType, _altova_mi_gml_altova_CPassThroughOperationType_altova_coordOperation> coordOperation;
	struct coordOperation { typedef Iterator<gml::CCoordinateOperationPropertyType> iterator; };
	MemberElement<gml::CCoordinateOperationPropertyType, _altova_mi_gml_altova_CPassThroughOperationType_altova_usesOperation> usesOperation;
	struct usesOperation { typedef Iterator<gml::CCoordinateOperationPropertyType> iterator; };
	MemberElement<gml::CCoordinateOperationPropertyType, _altova_mi_gml_altova_CPassThroughOperationType_altova_usesSingleOperation> usesSingleOperation;
	struct usesSingleOperation { typedef Iterator<gml::CCoordinateOperationPropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CPassThroughOperationType
