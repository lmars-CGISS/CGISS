#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CFileType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CFileType



namespace gie
{

namespace gml
{	

class CFileType : public TypeBase
{
public:
	gie_EXPORT CFileType(xercesc::DOMNode* const& init);
	gie_EXPORT CFileType(CFileType const& init);
	void operator=(CFileType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CFileType); }
	MemberElement<gml::CRangeParametersType, _altova_mi_gml_altova_CFileType_altova_rangeParameters> rangeParameters;
	struct rangeParameters { typedef Iterator<gml::CRangeParametersType> iterator; };
	MemberElement<xs::CanyURIType, _altova_mi_gml_altova_CFileType_altova_fileName> fileName;
	struct fileName { typedef Iterator<xs::CanyURIType> iterator; };
	MemberElement<xs::CanyURIType, _altova_mi_gml_altova_CFileType_altova_fileReference> fileReference;
	struct fileReference { typedef Iterator<xs::CanyURIType> iterator; };
	MemberElement<gml::CFileValueModelTypeType, _altova_mi_gml_altova_CFileType_altova_fileStructure> fileStructure;
	struct fileStructure { typedef Iterator<gml::CFileValueModelTypeType> iterator; };
	MemberElement<xs::CanyURIType, _altova_mi_gml_altova_CFileType_altova_mimeType> mimeType;
	struct mimeType { typedef Iterator<xs::CanyURIType> iterator; };
	MemberElement<xs::CanyURIType, _altova_mi_gml_altova_CFileType_altova_compression> compression;
	struct compression { typedef Iterator<xs::CanyURIType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CFileType
