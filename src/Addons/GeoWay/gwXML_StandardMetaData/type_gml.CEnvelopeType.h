#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CEnvelopeType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CEnvelopeType



namespace gie
{

namespace gml
{	

class CEnvelopeType : public TypeBase
{
public:
	gie_EXPORT CEnvelopeType(xercesc::DOMNode* const& init);
	gie_EXPORT CEnvelopeType(CEnvelopeType const& init);
	void operator=(CEnvelopeType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CEnvelopeType); }

	MemberAttribute<string_type,_altova_mi_gml_altova_CEnvelopeType_altova_srsName, 0, 0> srsName;	// srsName CanyURI

	MemberAttribute<unsigned __int64,_altova_mi_gml_altova_CEnvelopeType_altova_srsDimension, 0, 0> srsDimension;	// srsDimension CpositiveInteger

	MemberAttribute<string_type,_altova_mi_gml_altova_CEnvelopeType_altova_axisLabels, 0, 0> axisLabels;	// axisLabels CNCNameList

	MemberAttribute<string_type,_altova_mi_gml_altova_CEnvelopeType_altova_uomLabels, 0, 0> uomLabels;	// uomLabels CNCNameList
	MemberElement<gml::CDirectPositionType, _altova_mi_gml_altova_CEnvelopeType_altova_lowerCorner> lowerCorner;
	struct lowerCorner { typedef Iterator<gml::CDirectPositionType> iterator; };
	MemberElement<gml::CDirectPositionType, _altova_mi_gml_altova_CEnvelopeType_altova_upperCorner> upperCorner;
	struct upperCorner { typedef Iterator<gml::CDirectPositionType> iterator; };
	MemberElement<gml::CDirectPositionType, _altova_mi_gml_altova_CEnvelopeType_altova_pos> pos;
	struct pos { typedef Iterator<gml::CDirectPositionType> iterator; };
	MemberElement<gml::CCoordinatesType, _altova_mi_gml_altova_CEnvelopeType_altova_coordinates> coordinates;
	struct coordinates { typedef Iterator<gml::CCoordinatesType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CEnvelopeType
