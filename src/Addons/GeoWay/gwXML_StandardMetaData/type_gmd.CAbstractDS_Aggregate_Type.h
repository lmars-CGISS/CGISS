#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CAbstractDS_Aggregate_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CAbstractDS_Aggregate_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gmd
{	

class CAbstractDS_Aggregate_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CAbstractDS_Aggregate_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CAbstractDS_Aggregate_Type(CAbstractDS_Aggregate_Type const& init);
	void operator=(CAbstractDS_Aggregate_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmd_altova_CAbstractDS_Aggregate_Type); }
	MemberElement<gmd::CDS_DataSet_PropertyType, _altova_mi_gmd_altova_CAbstractDS_Aggregate_Type_altova_composedOf> composedOf;
	struct composedOf { typedef Iterator<gmd::CDS_DataSet_PropertyType> iterator; };
	MemberElement<gmd::CMD_Metadata_PropertyType, _altova_mi_gmd_altova_CAbstractDS_Aggregate_Type_altova_seriesMetadata> seriesMetadata;
	struct seriesMetadata { typedef Iterator<gmd::CMD_Metadata_PropertyType> iterator; };
	MemberElement<gmd::CDS_Aggregate_PropertyType, _altova_mi_gmd_altova_CAbstractDS_Aggregate_Type_altova_subset> subset;
	struct subset { typedef Iterator<gmd::CDS_Aggregate_PropertyType> iterator; };
	MemberElement<gmd::CDS_Aggregate_PropertyType, _altova_mi_gmd_altova_CAbstractDS_Aggregate_Type_altova_superset> superset;
	struct superset { typedef Iterator<gmd::CDS_Aggregate_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmd

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmd_ALTOVA_CAbstractDS_Aggregate_Type
