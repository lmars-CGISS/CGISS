#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CGeometricComplexPropertyType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CGeometricComplexPropertyType



namespace gie
{

namespace gml
{	

class CGeometricComplexPropertyType : public TypeBase
{
public:
	gie_EXPORT CGeometricComplexPropertyType(xercesc::DOMNode* const& init);
	gie_EXPORT CGeometricComplexPropertyType(CGeometricComplexPropertyType const& init);
	void operator=(CGeometricComplexPropertyType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CGeometricComplexPropertyType); }

	MemberAttribute<bool,_altova_mi_gml_altova_CGeometricComplexPropertyType_altova_owns, 0, 0> owns;	// owns Cboolean

	MemberAttribute<string_type,_altova_mi_gml_altova_CGeometricComplexPropertyType_altova_type, 0, 0> type;	// type Cstring

	MemberAttribute<string_type,_altova_mi_gml_altova_CGeometricComplexPropertyType_altova_href, 0, 0> href;	// href CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CGeometricComplexPropertyType_altova_role, 0, 0> role;	// role CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CGeometricComplexPropertyType_altova_arcrole, 0, 0> arcrole;	// arcrole CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CGeometricComplexPropertyType_altova_title, 0, 0> title;	// title Cstring
	MemberAttribute<string_type,_altova_mi_gml_altova_CGeometricComplexPropertyType_altova_show, 0, 5> show;	// show CshowType
	MemberAttribute<string_type,_altova_mi_gml_altova_CGeometricComplexPropertyType_altova_actuate, 0, 4> actuate;	// actuate CactuateType
	MemberAttribute<string_type,_altova_mi_gml_altova_CGeometricComplexPropertyType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType

	MemberAttribute<string_type,_altova_mi_gml_altova_CGeometricComplexPropertyType_altova_remoteSchema, 0, 0> remoteSchema;	// remoteSchema CanyURI
	MemberElement<gml::CGeometricComplexType, _altova_mi_gml_altova_CGeometricComplexPropertyType_altova_GeometricComplex> GeometricComplex;
	struct GeometricComplex { typedef Iterator<gml::CGeometricComplexType> iterator; };
	MemberElement<gml::CCompositeCurveType, _altova_mi_gml_altova_CGeometricComplexPropertyType_altova_CompositeCurve> CompositeCurve;
	struct CompositeCurve { typedef Iterator<gml::CCompositeCurveType> iterator; };
	MemberElement<gml::CCompositeSurfaceType, _altova_mi_gml_altova_CGeometricComplexPropertyType_altova_CompositeSurface> CompositeSurface;
	struct CompositeSurface { typedef Iterator<gml::CCompositeSurfaceType> iterator; };
	MemberElement<gml::CCompositeSolidType, _altova_mi_gml_altova_CGeometricComplexPropertyType_altova_CompositeSolid> CompositeSolid;
	struct CompositeSolid { typedef Iterator<gml::CCompositeSolidType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CGeometricComplexPropertyType
