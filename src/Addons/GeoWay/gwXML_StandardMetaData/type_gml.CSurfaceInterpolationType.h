#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CSurfaceInterpolationType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CSurfaceInterpolationType



namespace gie
{

namespace gml
{	

class CSurfaceInterpolationType : public TypeBase
{
public:
	gie_EXPORT CSurfaceInterpolationType(xercesc::DOMNode* const& init);
	gie_EXPORT CSurfaceInterpolationType(CSurfaceInterpolationType const& init);
	void operator=(CSurfaceInterpolationType const& other) { m_node = other.m_node; }
	static altova::meta::SimpleType StaticInfo() { return altova::meta::SimpleType(types + _altova_ti_gml_altova_CSurfaceInterpolationType); }

	enum EnumValues {
		Invalid = -1,
		k_none = 0, // none
		k_planar = 1, // planar
		k_spherical = 2, // spherical
		k_elliptical = 3, // elliptical
		k_conic = 4, // conic
		k_tin = 5, // tin
		k_parametricCurve = 6, // parametricCurve
		k_polynomialSpline = 7, // polynomialSpline
		k_rationalSpline = 8, // rationalSpline
		k_triangulatedSpline = 9, // triangulatedSpline
		EnumValueCount
	};
	void operator= (const string_type& value) 
	{
		altova::XmlFormatter* Formatter = static_cast<altova::XmlFormatter*>(altova::AnySimpleTypeFormatter);
		XercesTreeOperations::SetValue(GetNode(), Formatter->Format(value));
	}	
		
	operator string_type()
	{
		return CastAs<string_type >::Do(GetNode(), 0);
	}
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CSurfaceInterpolationType
