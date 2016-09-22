#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CRangeSetType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CRangeSetType



namespace gie
{

namespace gml
{	

class CRangeSetType : public TypeBase
{
public:
	gie_EXPORT CRangeSetType(xercesc::DOMNode* const& init);
	gie_EXPORT CRangeSetType(CRangeSetType const& init);
	void operator=(CRangeSetType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CRangeSetType); }
	MemberElement<gml::CValueArrayType, _altova_mi_gml_altova_CRangeSetType_altova_ValueArray> ValueArray;
	struct ValueArray { typedef Iterator<gml::CValueArrayType> iterator; };
	MemberElement<gml::CbooleanOrNilReasonListType, _altova_mi_gml_altova_CRangeSetType_altova_BooleanList> BooleanList;
	struct BooleanList { typedef Iterator<gml::CbooleanOrNilReasonListType> iterator; };
	MemberElement<gml::CCodeOrNilReasonListType, _altova_mi_gml_altova_CRangeSetType_altova_CategoryList> CategoryList;
	struct CategoryList { typedef Iterator<gml::CCodeOrNilReasonListType> iterator; };
	MemberElement<gml::CintegerOrNilReasonListType, _altova_mi_gml_altova_CRangeSetType_altova_CountList> CountList;
	struct CountList { typedef Iterator<gml::CintegerOrNilReasonListType> iterator; };
	MemberElement<gml::CMeasureOrNilReasonListType, _altova_mi_gml_altova_CRangeSetType_altova_QuantityList> QuantityList;
	struct QuantityList { typedef Iterator<gml::CMeasureOrNilReasonListType> iterator; };
	MemberElement<gml::CDataBlockType, _altova_mi_gml_altova_CRangeSetType_altova_DataBlock> DataBlock;
	struct DataBlock { typedef Iterator<gml::CDataBlockType> iterator; };
	MemberElement<gml::CFileType, _altova_mi_gml_altova_CRangeSetType_altova_File> File;
	struct File { typedef Iterator<gml::CFileType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CRangeSetType
