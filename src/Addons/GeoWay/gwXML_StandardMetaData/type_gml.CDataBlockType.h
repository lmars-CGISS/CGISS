#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDataBlockType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDataBlockType



namespace gie
{

namespace gml
{	

class CDataBlockType : public TypeBase
{
public:
	gie_EXPORT CDataBlockType(xercesc::DOMNode* const& init);
	gie_EXPORT CDataBlockType(CDataBlockType const& init);
	void operator=(CDataBlockType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CDataBlockType); }
	MemberElement<gml::CRangeParametersType, _altova_mi_gml_altova_CDataBlockType_altova_rangeParameters> rangeParameters;
	struct rangeParameters { typedef Iterator<gml::CRangeParametersType> iterator; };
	MemberElement<gml::CCoordinatesType, _altova_mi_gml_altova_CDataBlockType_altova_tupleList> tupleList;
	struct tupleList { typedef Iterator<gml::CCoordinatesType> iterator; };
	MemberElement<gml::CdoubleOrNilReasonListType, _altova_mi_gml_altova_CDataBlockType_altova_doubleOrNilReasonTupleList> doubleOrNilReasonTupleList;
	struct doubleOrNilReasonTupleList { typedef Iterator<gml::CdoubleOrNilReasonListType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDataBlockType
