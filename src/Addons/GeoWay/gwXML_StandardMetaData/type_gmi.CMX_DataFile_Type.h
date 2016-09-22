#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMX_DataFile_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMX_DataFile_Type

#include "type_gco.CAbstractObject_Type.h"


namespace gie
{

namespace gmi
{	

class CMX_DataFile_Type : public ::gie::gco::CAbstractObject_Type
{
public:
	gie_EXPORT CMX_DataFile_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CMX_DataFile_Type(CMX_DataFile_Type const& init);
	void operator=(CMX_DataFile_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gmi_altova_CMX_DataFile_Type); }
	MemberElement<gmd::CMD_Format_PropertyType, _altova_mi_gmi_altova_CMX_DataFile_Type_altova_fileFormat> fileFormat;
	struct fileFormat { typedef Iterator<gmd::CMD_Format_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gmi

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gmi_ALTOVA_CMX_DataFile_Type
