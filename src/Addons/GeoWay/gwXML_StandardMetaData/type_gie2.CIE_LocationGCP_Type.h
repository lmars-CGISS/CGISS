#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_LocationGCP_Type
#define _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_LocationGCP_Type



namespace gie
{

namespace gie2
{	

class CIE_LocationGCP_Type : public TypeBase
{
public:
	gie_EXPORT CIE_LocationGCP_Type(xercesc::DOMNode* const& init);
	gie_EXPORT CIE_LocationGCP_Type(CIE_LocationGCP_Type const& init);
	void operator=(CIE_LocationGCP_Type const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gie2_altova_CIE_LocationGCP_Type); }
	MemberElement<gcv::CSD_GCPRepository_PropertyType, _altova_mi_gie2_altova_CIE_LocationGCP_Type_altova_GCPRepository> GCPRepository;
	struct GCPRepository { typedef Iterator<gcv::CSD_GCPRepository_PropertyType> iterator; };
	MemberElement<gcv::CSD_ImageIdentifiableGCP_PropertyType, _altova_mi_gie2_altova_CIE_LocationGCP_Type_altova_imageIdentifiableGCP> imageIdentifiableGCP;
	struct imageIdentifiableGCP { typedef Iterator<gcv::CSD_ImageIdentifiableGCP_PropertyType> iterator; };
	MemberElement<gcv::CSD_GCPLocation_PropertyType, _altova_mi_gie2_altova_CIE_LocationGCP_Type_altova_locationGCP> locationGCP;
	struct locationGCP { typedef Iterator<gcv::CSD_GCPLocation_PropertyType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gie2

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CIE_LocationGCP_Type
