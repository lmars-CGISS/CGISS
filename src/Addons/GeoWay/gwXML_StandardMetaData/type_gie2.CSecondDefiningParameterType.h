#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CSecondDefiningParameterType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CSecondDefiningParameterType



namespace gie
{

namespace gie2
{	

class CSecondDefiningParameterType : public TypeBase
{
public:
	gie_EXPORT CSecondDefiningParameterType(xercesc::DOMNode* const& init);
	gie_EXPORT CSecondDefiningParameterType(CSecondDefiningParameterType const& init);
	void operator=(CSecondDefiningParameterType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gie2_altova_CSecondDefiningParameterType); }
	MemberElement<gml::CMeasureType, _altova_mi_gie2_altova_CSecondDefiningParameterType_altova_inverseFlattening> inverseFlattening;
	struct inverseFlattening { typedef Iterator<gml::CMeasureType> iterator; };
	MemberElement<gml::CLengthType, _altova_mi_gie2_altova_CSecondDefiningParameterType_altova_semiMinorAxis> semiMinorAxis;
	struct semiMinorAxis { typedef Iterator<gml::CLengthType> iterator; };
	MemberElement<gie2::CisSphereType, _altova_mi_gie2_altova_CSecondDefiningParameterType_altova_isSphere> isSphere;
	struct isSphere { typedef Iterator<gie2::CisSphereType> iterator; };
};



} // namespace gie2

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gie2_ALTOVA_CSecondDefiningParameterType
