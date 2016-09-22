#ifndef _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDictionaryEntryType
#define _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDictionaryEntryType

#include "type_gml.CAbstractMemberType.h"


namespace gie
{

namespace gml
{	

class CDictionaryEntryType : public ::gie::gml::CAbstractMemberType
{
public:
	gie_EXPORT CDictionaryEntryType(xercesc::DOMNode* const& init);
	gie_EXPORT CDictionaryEntryType(CDictionaryEntryType const& init);
	void operator=(CDictionaryEntryType const& other) { m_node = other.m_node; }
	static altova::meta::ComplexType StaticInfo() { return altova::meta::ComplexType(types + _altova_ti_gml_altova_CDictionaryEntryType); }

	MemberAttribute<string_type,_altova_mi_gml_altova_CDictionaryEntryType_altova_type, 0, 0> type;	// type Cstring

	MemberAttribute<string_type,_altova_mi_gml_altova_CDictionaryEntryType_altova_href, 0, 0> href;	// href CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CDictionaryEntryType_altova_role, 0, 0> role;	// role CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CDictionaryEntryType_altova_arcrole, 0, 0> arcrole;	// arcrole CanyURI

	MemberAttribute<string_type,_altova_mi_gml_altova_CDictionaryEntryType_altova_title, 0, 0> title;	// title Cstring
	MemberAttribute<string_type,_altova_mi_gml_altova_CDictionaryEntryType_altova_show, 0, 5> show;	// show CshowType
	MemberAttribute<string_type,_altova_mi_gml_altova_CDictionaryEntryType_altova_actuate, 0, 4> actuate;	// actuate CactuateType
	MemberAttribute<string_type,_altova_mi_gml_altova_CDictionaryEntryType_altova_nilReason, 1, 5> nilReason;	// nilReason CNilReasonType

	MemberAttribute<string_type,_altova_mi_gml_altova_CDictionaryEntryType_altova_remoteSchema, 0, 0> remoteSchema;	// remoteSchema CanyURI
	MemberElement<gml::CDefinitionType, _altova_mi_gml_altova_CDictionaryEntryType_altova_Definition> Definition;
	struct Definition { typedef Iterator<gml::CDefinitionType> iterator; };
	MemberElement<gml::CAffineCSType, _altova_mi_gml_altova_CDictionaryEntryType_altova_AffineCS> AffineCS;
	struct AffineCS { typedef Iterator<gml::CAffineCSType> iterator; };
	MemberElement<gml::CBaseUnitType, _altova_mi_gml_altova_CDictionaryEntryType_altova_BaseUnit> BaseUnit;
	struct BaseUnit { typedef Iterator<gml::CBaseUnitType> iterator; };
	MemberElement<gml::CCartesianCSType, _altova_mi_gml_altova_CDictionaryEntryType_altova_CartesianCS> CartesianCS;
	struct CartesianCS { typedef Iterator<gml::CCartesianCSType> iterator; };
	MemberElement<gml::CCompoundCRSType, _altova_mi_gml_altova_CDictionaryEntryType_altova_CompoundCRS> CompoundCRS;
	struct CompoundCRS { typedef Iterator<gml::CCompoundCRSType> iterator; };
	MemberElement<gml::CConcatenatedOperationType, _altova_mi_gml_altova_CDictionaryEntryType_altova_ConcatenatedOperation> ConcatenatedOperation;
	struct ConcatenatedOperation { typedef Iterator<gml::CConcatenatedOperationType> iterator; };
	MemberElement<gml::CConventionalUnitType, _altova_mi_gml_altova_CDictionaryEntryType_altova_ConventionalUnit> ConventionalUnit;
	struct ConventionalUnit { typedef Iterator<gml::CConventionalUnitType> iterator; };
	MemberElement<gml::CConversionType, _altova_mi_gml_altova_CDictionaryEntryType_altova_Conversion> Conversion;
	struct Conversion { typedef Iterator<gml::CConversionType> iterator; };
	MemberElement<gml::CCoordinateSystemAxisType, _altova_mi_gml_altova_CDictionaryEntryType_altova_CoordinateSystemAxis> CoordinateSystemAxis;
	struct CoordinateSystemAxis { typedef Iterator<gml::CCoordinateSystemAxisType> iterator; };
	MemberElement<gml::CCylindricalCSType, _altova_mi_gml_altova_CDictionaryEntryType_altova_CylindricalCS> CylindricalCS;
	struct CylindricalCS { typedef Iterator<gml::CCylindricalCSType> iterator; };
	MemberElement<gml::CDictionaryType, _altova_mi_gml_altova_CDictionaryEntryType_altova_DefinitionCollection> DefinitionCollection;
	struct DefinitionCollection { typedef Iterator<gml::CDictionaryType> iterator; };
	MemberElement<gml::CDefinitionProxyType, _altova_mi_gml_altova_CDictionaryEntryType_altova_DefinitionProxy> DefinitionProxy;
	struct DefinitionProxy { typedef Iterator<gml::CDefinitionProxyType> iterator; };
	MemberElement<gml::CDerivedCRSType, _altova_mi_gml_altova_CDictionaryEntryType_altova_DerivedCRS> DerivedCRS;
	struct DerivedCRS { typedef Iterator<gml::CDerivedCRSType> iterator; };
	MemberElement<gml::CDerivedUnitType, _altova_mi_gml_altova_CDictionaryEntryType_altova_DerivedUnit> DerivedUnit;
	struct DerivedUnit { typedef Iterator<gml::CDerivedUnitType> iterator; };
	MemberElement<gml::CDictionaryType, _altova_mi_gml_altova_CDictionaryEntryType_altova_Dictionary> Dictionary;
	struct Dictionary { typedef Iterator<gml::CDictionaryType> iterator; };
	MemberElement<gml::CEllipsoidType, _altova_mi_gml_altova_CDictionaryEntryType_altova_Ellipsoid> Ellipsoid;
	struct Ellipsoid { typedef Iterator<gml::CEllipsoidType> iterator; };
	MemberElement<gml::CEllipsoidalCSType, _altova_mi_gml_altova_CDictionaryEntryType_altova_EllipsoidalCS> EllipsoidalCS;
	struct EllipsoidalCS { typedef Iterator<gml::CEllipsoidalCSType> iterator; };
	MemberElement<gml::CEngineeringCRSType, _altova_mi_gml_altova_CDictionaryEntryType_altova_EngineeringCRS> EngineeringCRS;
	struct EngineeringCRS { typedef Iterator<gml::CEngineeringCRSType> iterator; };
	MemberElement<gml::CEngineeringDatumType, _altova_mi_gml_altova_CDictionaryEntryType_altova_EngineeringDatum> EngineeringDatum;
	struct EngineeringDatum { typedef Iterator<gml::CEngineeringDatumType> iterator; };
	MemberElement<gml::CGeocentricCRSType, _altova_mi_gml_altova_CDictionaryEntryType_altova_GeocentricCRS> GeocentricCRS;
	struct GeocentricCRS { typedef Iterator<gml::CGeocentricCRSType> iterator; };
	MemberElement<gml::CGeodeticCRSType, _altova_mi_gml_altova_CDictionaryEntryType_altova_GeodeticCRS> GeodeticCRS;
	struct GeodeticCRS { typedef Iterator<gml::CGeodeticCRSType> iterator; };
	MemberElement<gml::CGeodeticDatumType, _altova_mi_gml_altova_CDictionaryEntryType_altova_GeodeticDatum> GeodeticDatum;
	struct GeodeticDatum { typedef Iterator<gml::CGeodeticDatumType> iterator; };
	MemberElement<gml::CGeographicCRSType, _altova_mi_gml_altova_CDictionaryEntryType_altova_GeographicCRS> GeographicCRS;
	struct GeographicCRS { typedef Iterator<gml::CGeographicCRSType> iterator; };
	MemberElement<gml::CImageCRSType, _altova_mi_gml_altova_CDictionaryEntryType_altova_ImageCRS> ImageCRS;
	struct ImageCRS { typedef Iterator<gml::CImageCRSType> iterator; };
	MemberElement<gml::CImageDatumType, _altova_mi_gml_altova_CDictionaryEntryType_altova_ImageDatum> ImageDatum;
	struct ImageDatum { typedef Iterator<gml::CImageDatumType> iterator; };
	MemberElement<gml::CLinearCSType, _altova_mi_gml_altova_CDictionaryEntryType_altova_LinearCS> LinearCS;
	struct LinearCS { typedef Iterator<gml::CLinearCSType> iterator; };
	MemberElement<gml::CObliqueCartesianCSType, _altova_mi_gml_altova_CDictionaryEntryType_altova_ObliqueCartesianCS> ObliqueCartesianCS;
	struct ObliqueCartesianCS { typedef Iterator<gml::CObliqueCartesianCSType> iterator; };
	MemberElement<gml::COperationMethodType, _altova_mi_gml_altova_CDictionaryEntryType_altova_OperationMethod> OperationMethod;
	struct OperationMethod { typedef Iterator<gml::COperationMethodType> iterator; };
	MemberElement<gml::COperationParameterType, _altova_mi_gml_altova_CDictionaryEntryType_altova_OperationParameter> OperationParameter;
	struct OperationParameter { typedef Iterator<gml::COperationParameterType> iterator; };
	MemberElement<gml::COperationParameterGroupType, _altova_mi_gml_altova_CDictionaryEntryType_altova_OperationParameterGroup> OperationParameterGroup;
	struct OperationParameterGroup { typedef Iterator<gml::COperationParameterGroupType> iterator; };
	MemberElement<gml::CPassThroughOperationType, _altova_mi_gml_altova_CDictionaryEntryType_altova_PassThroughOperation> PassThroughOperation;
	struct PassThroughOperation { typedef Iterator<gml::CPassThroughOperationType> iterator; };
	MemberElement<gml::CPolarCSType, _altova_mi_gml_altova_CDictionaryEntryType_altova_PolarCS> PolarCS;
	struct PolarCS { typedef Iterator<gml::CPolarCSType> iterator; };
	MemberElement<gml::CPrimeMeridianType, _altova_mi_gml_altova_CDictionaryEntryType_altova_PrimeMeridian> PrimeMeridian;
	struct PrimeMeridian { typedef Iterator<gml::CPrimeMeridianType> iterator; };
	MemberElement<gml::CProjectedCRSType, _altova_mi_gml_altova_CDictionaryEntryType_altova_ProjectedCRS> ProjectedCRS;
	struct ProjectedCRS { typedef Iterator<gml::CProjectedCRSType> iterator; };
	MemberElement<gml::CSphericalCSType, _altova_mi_gml_altova_CDictionaryEntryType_altova_SphericalCS> SphericalCS;
	struct SphericalCS { typedef Iterator<gml::CSphericalCSType> iterator; };
	MemberElement<gml::CTemporalCRSType, _altova_mi_gml_altova_CDictionaryEntryType_altova_TemporalCRS> TemporalCRS;
	struct TemporalCRS { typedef Iterator<gml::CTemporalCRSType> iterator; };
	MemberElement<gml::CTemporalCSType, _altova_mi_gml_altova_CDictionaryEntryType_altova_TemporalCS> TemporalCS;
	struct TemporalCS { typedef Iterator<gml::CTemporalCSType> iterator; };
	MemberElement<gml::CTemporalDatumType, _altova_mi_gml_altova_CDictionaryEntryType_altova_TemporalDatum> TemporalDatum;
	struct TemporalDatum { typedef Iterator<gml::CTemporalDatumType> iterator; };
	MemberElement<gml::CTimeCSType, _altova_mi_gml_altova_CDictionaryEntryType_altova_TimeCS> TimeCS;
	struct TimeCS { typedef Iterator<gml::CTimeCSType> iterator; };
	MemberElement<gml::CTimeCalendarType, _altova_mi_gml_altova_CDictionaryEntryType_altova_TimeCalendar> TimeCalendar;
	struct TimeCalendar { typedef Iterator<gml::CTimeCalendarType> iterator; };
	MemberElement<gml::CTimeClockType, _altova_mi_gml_altova_CDictionaryEntryType_altova_TimeClock> TimeClock;
	struct TimeClock { typedef Iterator<gml::CTimeClockType> iterator; };
	MemberElement<gml::CTimeCoordinateSystemType, _altova_mi_gml_altova_CDictionaryEntryType_altova_TimeCoordinateSystem> TimeCoordinateSystem;
	struct TimeCoordinateSystem { typedef Iterator<gml::CTimeCoordinateSystemType> iterator; };
	MemberElement<gml::CTimeOrdinalReferenceSystemType, _altova_mi_gml_altova_CDictionaryEntryType_altova_TimeOrdinalReferenceSystem> TimeOrdinalReferenceSystem;
	struct TimeOrdinalReferenceSystem { typedef Iterator<gml::CTimeOrdinalReferenceSystemType> iterator; };
	MemberElement<gml::CTimeReferenceSystemType, _altova_mi_gml_altova_CDictionaryEntryType_altova_TimeReferenceSystem> TimeReferenceSystem;
	struct TimeReferenceSystem { typedef Iterator<gml::CTimeReferenceSystemType> iterator; };
	MemberElement<gml::CTransformationType, _altova_mi_gml_altova_CDictionaryEntryType_altova_Transformation> Transformation;
	struct Transformation { typedef Iterator<gml::CTransformationType> iterator; };
	MemberElement<gml::CUnitDefinitionType, _altova_mi_gml_altova_CDictionaryEntryType_altova_UnitDefinition> UnitDefinition;
	struct UnitDefinition { typedef Iterator<gml::CUnitDefinitionType> iterator; };
	MemberElement<gml::CUserDefinedCSType, _altova_mi_gml_altova_CDictionaryEntryType_altova_UserDefinedCS> UserDefinedCS;
	struct UserDefinedCS { typedef Iterator<gml::CUserDefinedCSType> iterator; };
	MemberElement<gml::CVerticalCRSType, _altova_mi_gml_altova_CDictionaryEntryType_altova_VerticalCRS> VerticalCRS;
	struct VerticalCRS { typedef Iterator<gml::CVerticalCRSType> iterator; };
	MemberElement<gml::CVerticalCSType, _altova_mi_gml_altova_CDictionaryEntryType_altova_VerticalCS> VerticalCS;
	struct VerticalCS { typedef Iterator<gml::CVerticalCSType> iterator; };
	MemberElement<gml::CVerticalDatumType, _altova_mi_gml_altova_CDictionaryEntryType_altova_VerticalDatum> VerticalDatum;
	struct VerticalDatum { typedef Iterator<gml::CVerticalDatumType> iterator; };
	gie_EXPORT void SetXsiType();
};



} // namespace gml

}	// namespace gie

#endif // _ALTOVA_INCLUDED_gie_ALTOVA_gml_ALTOVA_CDictionaryEntryType
