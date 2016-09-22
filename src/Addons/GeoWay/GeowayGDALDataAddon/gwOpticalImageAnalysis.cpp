
#include "stdafx.h"
#include "gwOpticalImageAnalysis.h"
#include "gwAddonFunction.h"

gwOpticalImageAnalysis::gwOpticalImageAnalysis()
:m_ieOpticalImage(NULL)
{
	xercesc::XMLPlatformUtils::Initialize();
	m_strMetaData = "";
}
gwOpticalImageAnalysis::gwOpticalImageAnalysis(xercesc::DOMNode* const& init )
:m_ieOpticalImage(init)
{
	xercesc::XMLPlatformUtils::Initialize();
	m_strMetaData = "";
}
gwOpticalImageAnalysis::~gwOpticalImageAnalysis()
{
	xercesc::XMLPlatformUtils::Terminate();
}
void gwOpticalImageAnalysis::WriteStandardMetadata(const ieSimpleRasterInfo& m_gInfo)
{
	
	m_gie = gie2::Cgie::CreateDocument();
	m_ieOpticalImage = m_gie.IE_OpticalImage.append();

	//gwEnvelope eEnve = m_gInfo.m_extent;

	//处理范围
	gie::gmd::CEX_Extent_PropertyType extent = m_ieOpticalImage.domainExtent.append();
	gie::gmd::CEX_Extent_Type extentType = extent.EX_Extent.append();
	gie::gmd::CEX_GeographicExtent_PropertyType exetentPro = extentType.geographicElement.append();
	gie::gmd::CEX_GeographicBoundingBox_Type box = exetentPro.EX_GeographicBoundingBox.append();
	gie::gco::CDecimal_PropertyType eastPro = box.eastBoundLongitude.append();
	gie::xs::CdecimalType realeast = eastPro.Decimal.append();
	gie::gco::CDecimal_PropertyType westPro = box.westBoundLongitude.append();
	gie::xs::CdecimalType realwest = westPro.Decimal.append();
	gie::gco::CDecimal_PropertyType northPro = box.northBoundLatitude.append();
	gie::xs::CdecimalType realnorth = northPro.Decimal.append();
	gie::gco::CDecimal_PropertyType southPro = box.southBoundLatitude.append();
	gie::xs::CdecimalType realsouth = southPro.Decimal.append();

	realeast = m_gInfo.right;
	realwest = m_gInfo.left;
	realnorth = m_gInfo.top;
	realsouth = m_gInfo.bottom;

	gcv::CCV_DomainObject_PropertyType domainPro = m_ieOpticalImage.domainElement.append();
	gcv::CCV_DomainObject_Type cvDomain = domainPro.CV_DomainObject.append();
	gss::CGM_Object_PropertyType gmObjectPro = cvDomain.spatialElement.append();
	gml::CPointType mlPoint = gmObjectPro.Point.append();
	gml::CDirectPositionType gml_Pos = mlPoint.pos.append();
	
	/*double dStartX = m_gInfo.getGeoStartPosX(m_gInfo.getRasterOrgPos());
	double dStartY = m_gInfo.getGeoStartPosY(m_gInfo.getRasterOrgPos());
	gwString strPos ;
	strPos.Format(L"%lf %lf",dStartX,dStartY);

	xercesc::DOMNode* pgml_Pos = gml_Pos.GetNode();
	pgml_Pos->setTextContent(XSTR(strPos.wsz()));*/


	//处理空间参考
	std::string strWKT = m_gInfo.m_strProjectionRef;
	//string strType = strWKT.substr(0,6);
	//gwSpatialReferenceSystemPtr pSpatial = gwSpatialReferenceSystemFactory::instance()->CreateSpatialReference(strWKt);
	
	OGRSpatialReference oSRS;
	
	char* szWKT = (char*)strWKT.data();

	OGRErr err = oSRS.importFromWkt(&szWKT);// oSR.importFromEPSG(m_pClassMetadate->srid);  //使用该方式效率相对要低，需要遍历gdal的坐标文件，但不需要依赖SpatialReference等库
	bool isPrj = true;
	
	/*if(strstr(strType.data(),"GEOGCS"))
	{
		isPrj = false;
	}*/
	if(err != OGRERR_NONE)
	{
		gsr::CSC_CRS_PropertyType gml_Pro = m_ieOpticalImage.CRS.append();
		gml::CProjectedCRSType gml_ProType = gml_Pro.ProjectedCRS.append();
	}
	else
	{
		oSRS.AutoIdentifyEPSG();
	/*	Eprj_Datum	        sDatum;
		Eprj_ProParameters  sPro;
		Eprj_MapInfo	sMapInfo;*/
		OGRSpatialReference *poGeogSRS = NULL;
		poGeogSRS = oSRS.CloneGeogCS();
		if(oSRS.IsProjected())
		{
			gsr::CSC_CRS_PropertyType gml_Pro = m_ieOpticalImage.CRS.append();
			gml::CProjectedCRSType gml_ProType = gml_Pro.ProjectedCRS.append();

			gml::CCodeWithAuthorityType ProInder = gml_ProType.identifier.append();
			std::string strProInder;
			char szProInder[100];
			sprintf(szProInder,"EPSG:%d",oSRS.GetEPSGGeogCS());
			wchar_t* wProInder = gwAddonFunction::CharToWchar(szProInder);

			xercesc::DOMNode* pProNde = ProInder.GetNode();
			pProNde->setTextContent(wProInder);
			delete[] wProInder;
			gml::CCodeType Proname = gml_ProType.name.append();
			xercesc::DOMNode* pProNameNde = Proname.GetNode();
			const char *pszPROJCS = poGeogSRS->GetAttrValue("PROJCS");
			wchar_t* wszProjcs = gwAddonFunction::CharToWchar(pszPROJCS);
			pProNameNde->setTextContent((XMLCh*)(pszPROJCS));
			delete[] wszProjcs;
			
			gml::CGeodeticCRSPropertyType geoCRSPro = gml_ProType.baseGeodeticCRS.append();
			gml::CGeodeticCRSType geoCRS = geoCRSPro.GeodeticCRS.append();
			//gwProjectionCoordinateSystemPtr pProject = gwRef_static_cast<gwProjectionCoordinateSystem>(pSpatial);
			if(poGeogSRS!=NULL)
			{
				/*memset( &sPro, 0, sizeof(sPro) );
				memset( &sDatum, 0, sizeof(sDatum) );
				memset( &sMapInfo, 0, sizeof(sMapInfo) );*/

				gml::CCodeWithAuthorityType GeoInder = geoCRS.identifier.append();
				string strGeoInder;
				char szGeoInder[100];
				sprintf(szGeoInder,"%d",poGeogSRS->GetEPSGGeogCS());
				wchar_t* wszGeoInder = gwAddonFunction::CharToWchar(szGeoInder);
				xercesc::DOMNode* pGeoInderNde = GeoInder.GetNode();
				pGeoInderNde->setTextContent(wszGeoInder);
				
				gie::gml::CCodeType Geoname = geoCRS.name.append();
				xercesc::DOMNode* pGeoNde = Geoname.GetNode();
				const char *pszGEoCrs= poGeogSRS->GetAttrValue("PROJCS");
				wchar_t* wsGeoName = gwAddonFunction::CharToWchar(pszGEoCrs);
				pGeoNde->setNodeValue(wsGeoName);
				delete[] wsGeoName;
				gml::CSphericalCSPropertyType spheriaclPro = geoCRS.sphericalCS.append();
				gml::CSphericalCSType shperiacl = spheriaclPro.SphericalCS.append();
				
				//sDatum.datumname = (char *) poGeogSRS->GetAttrValue( "GEOGCS|DATUM" );
                
				
				gml::CCodeWithAuthorityType shperiaclInder = shperiacl.identifier.append();
				xercesc::DOMNode* pshperiaclInder = shperiaclInder.GetNode();
				pshperiaclInder->setTextContent((XMLCh*)(wszGeoInder));
				gml::CCodeType shperiaclname = shperiacl.name.append();
				xercesc::DOMNode* pshperiaclname = shperiaclname.GetNode();
				wchar_t* wszshperiaclname = gwAddonFunction::CharToWchar(poGeogSRS->GetAttrValue( "GEOGCS|DATUM|SPHEROID" ));

				pshperiaclname->setTextContent((XMLCh*)(wszshperiaclname));
				delete[] wszshperiaclname;
				
				gml::CCoordinateSystemAxisPropertyType axisPro = shperiacl.axis.append();
				gml::CCoordinateSystemAxisType axis = axisPro.CoordinateSystemAxis.append();
				gml::CCodeWithAuthorityType pDir = axis.axisDirection.append();
				xercesc::DOMNode* ppDir = pDir.GetNode();
				ppDir->setTextContent(L"North");
				gml::CCodeType codetype = axis.axisAbbrev.append();
				xercesc::DOMNode* pcodetype = codetype.GetNode();
				pcodetype->setTextContent(L"X");
				
				gml::CCoordinateSystemAxisPropertyType axisPro1 = shperiacl.axis.append();
				gml::CCoordinateSystemAxisType axis1 = axisPro1.CoordinateSystemAxis.append();
				gml::CCodeWithAuthorityType pDir1 = axis1.axisDirection.append();
				xercesc::DOMNode* ppDir1 = pDir1.GetNode();
				ppDir1->setTextContent(L"East");
				gml::CCodeType codetype1 = axis1.axisAbbrev.append();
				xercesc::DOMNode* pcodetype1 = codetype1.GetNode();
				pcodetype1->setTextContent(L"Y");
				
				//Datum
				gml::CGeodeticDatumPropertyType geoDatumPro = geoCRS.usesGeodeticDatum.append();
				gml::CGeodeticDatumType geoDatum = geoDatumPro.GeodeticDatum.append();
				gml::CCodeWithAuthorityType DatumInder = geoDatum.identifier.append();
				xercesc::DOMNode* pDatumInder = DatumInder.GetNode();
				pDatumInder->setTextContent((XMLCh*)(wszGeoInder));
				delete[] wszGeoInder;
				gml::CCodeType Datumname = geoDatum.name.append();
				xercesc::DOMNode* pDatumname = Datumname.GetNode();
				wchar_t* wszName = gwAddonFunction::CharToWchar(poGeogSRS->GetAttrValue( "GEOGCS|DATUM" ));
				pDatumname->setTextContent(wszName);
				delete[] wszName;

				
			
				gml::CPrimeMeridianPropertyType MeridianPro = geoDatum.primeMeridian.append();
				gml::CPrimeMeridianType Meridian = MeridianPro.PrimeMeridian.append();
				
				double meriDian = oSRS.GetProjParm(SRS_PP_CENTRAL_MERIDIAN); 

				gml::CCodeWithAuthorityType merInder = Meridian.identifier.append();
				
				xercesc::DOMNode* pmerInder = merInder.GetNode();
				pmerInder->setTextContent(L"unknow");
				gml::CCodeType mername = Meridian.name.append();
				xercesc::DOMNode* pmername = mername.GetNode();
				pmername->setTextContent(L"unkonw");

				gml::CAngleType mer = Meridian.greenwichLongitude.append();
				mer = meriDian;
				gml::CAngleType angle = Meridian.greenwichLongitude.append();
				angle.uom = L"http://www.isotc211.org/2005/resources/uom/gmxUom.xsd#xpointer(//*[@gml:id='deg'])";

				gml::CEllipsoidPropertyType ellipsoidPro = geoDatum.usesEllipsoid.append();
				gml::CEllipsoidType ellipsoid = ellipsoidPro.Ellipsoid.append();
				
				gml::CCodeWithAuthorityType ellipsoidInder = ellipsoid.identifier.append();
				
				xercesc::DOMNode* pellipsoidInder = ellipsoidInder.GetNode();
				pellipsoidInder->setTextContent(L"unkown");
				//ellipsoidInder.codeSpace = strellipsoidInder.wsz();
				gml::CCodeType ellipsoidname = ellipsoid.name.append();
				xercesc::DOMNode* pellipsoidname = ellipsoidname.GetNode();
				wchar_t* wszpellipsoidname = gwAddonFunction::CharToWchar(poGeogSRS->GetAttrValue( "GEOGCS|DATUM|SPHEROID" ));
				pellipsoidname->setTextContent(wszpellipsoidname);

				gml::CMeasureType measure = ellipsoid.semiMajorAxis.append();
				measure.uom = L"http://www.isotc211.org/2005/resources/uom/gmxUom.xsd#xpointer(//*[@gml:id='m'])";
				measure = poGeogSRS->GetSemiMajor();
				gie2::CsecondDefiningParameterType2 seconPrama2 = ellipsoid.secondDefiningParameter.append();
				gie2::CSecondDefiningParameterType secondePrama = seconPrama2.SecondDefiningParameter.append();
				gml::CLengthType cLegth =  secondePrama.semiMinorAxis.append();
				cLegth.uom = L"http://www.isotc211.org/2005/resources/uom/gmxUom.xsd#xpointer(//*[@gml:id='m'])";
				cLegth = poGeogSRS->GetSemiMinor();
			}
			
		}
	}

	gie2::CIE_Georectified_PropertyType geoRectifiedPro = m_ieOpticalImage.georectifedSpatialInfo.append();
	gie2::CIE_Georectified_Type ieGeorectified = geoRectifiedPro.IE_Georectified.append();
	gco::CInteger_PropertyType num = ieGeorectified.numberOfDimensions.append();
	xs::CintegerType xsnum = num.Integer.append();
	if(m_gInfo.m_bDemIsXYZ == true)
		xsnum = 3;
	else
		xsnum = 2;
	
	gmd::CMD_CellGeometryCode_PropertyType CellGeoPro = ieGeorectified.cellGeometry.append();
	gco::CCodeListValue_Type CellGeo = CellGeoPro.MD_CellGeometryCode.append();
	CellGeo.codeList = L"http://standards.iso.org/ittf/PubliclyAvailableStandards/ISO_19139_Schemas/resources/Codelist/gmxCodelists.xml#MD_CellGeometryCode";
	CellGeo.codeListValue = L"Point";

	//CellGeo = L"Point";

	gco::CBoolean_PropertyType bTransPramaPro = ieGeorectified.transformationParameterAvailability.append();
	xs::CbooleanType bTransPrama = bTransPramaPro.Boolean.append();
	bTransPrama = false;

	gco::CBoolean_PropertyType bCheckPointPro = ieGeorectified.checkPointAvailability.append();
	xs::CbooleanType bCheckPoint= bCheckPointPro.Boolean.append();
	bCheckPoint = false;

	gmd::CMD_PixelOrientationCode_PropertyType PiexlPro = ieGeorectified.pointInPixel.append();
	gmd::CMD_PixelOrientationCode_TypeType Piexl = PiexlPro.MD_PixelOrientationCode.append();
	//gwRasterPosEnum PosEnum = m_gInfo.getRasterOrgPos();
	
	//if(PosEnum == gwRasterPosEnum_LeftTop_Corner)
		Piexl.SetEnumerationValue(2);//Piexl = L"2";
	//if(PosEnum == gwRasterPosEnum_LeftTop_Corner)
	//	Piexl.SetEnumerationValue(4);//Piexl = L"4";
	/*gie2::CIE_GeolocationSourceCode_PropertyType GeoLocationPro = ieGeorectified.geolocationSource.append();
	gie2::CCodeListValue_Type ieCodeList = GeoLocationPro.IE_GeolocationSourceCode.append();
	ieCodeList.codeList = "http://www.lmars.edu.cn/gie/Codelist/gieCodelists.xml#IE_GeolocationSourceCode";
	*/
	gco::CInteger_PropertyType bandsPro = m_ieOpticalImage.numberofBands.append();
	xs::CintegerType bands = bandsPro.Integer.append();
	bands = m_gInfo.m_nBandCount;
	//波段信息
	for(int i = 0;i < m_gInfo.m_nBandCount;i++)
	{
		gmi::CMI_Band_PropertyType BandInfoPro = m_ieOpticalImage.bandinformation.append();
		gmi::CMI_Band_Type BandInfo = BandInfoPro.MI_Band.append();
		gco::CReal_PropertyType resolutionPro = BandInfo.nominalSpatialResolution.append();
		xs::CdoubleType resolution = resolutionPro.Real.append();
		if(m_gInfo.m_eDataType == GDT_Byte)
		{
			resolution = 1;
		}
		if(m_gInfo.m_eDataType == GDT_UInt16)
		{
			resolution = 16;
		}
		if(m_gInfo.m_eDataType == GDT_Int16)
		{
			resolution = 16;
		}
		if(m_gInfo.m_eDataType == GDT_UInt32)
		{
			resolution = 32;
		}
		if(m_gInfo.m_eDataType == GDT_Int32)
		{
			resolution = 32;
		}
		if(m_gInfo.m_eDataType == GDT_Float32)
		{
			resolution = 32;
		}
		if(m_gInfo.m_eDataType == GDT_Float64)
		{
			resolution = 64;
		}
		
	}
	xercesc::DOMNode* root = m_ieOpticalImage.GetNode();
	m_strMetaData = gwAddonFunction::SaveXML(root,true);
	
}
void gwOpticalImageAnalysis::WriteDEMMetadata(const char* strPath)
{
	
	m_gie = gie2::Cgie::CreateDocument();
	gie2::CIE_ThematicGriddedData_Type ieThematicGriddedData = m_gie.IE_ThematicGriddedData.append();


	//domainExtent
	gie::gmd::CEX_Extent_PropertyType extent = ieThematicGriddedData.domainExtent.append();
	gie::gmd::CEX_Extent_Type extentType = extent.EX_Extent.append();
	gie::gmd::CEX_GeographicExtent_PropertyType exetentPro = extentType.geographicElement.append();
	gie::gmd::CEX_GeographicBoundingBox_Type box = exetentPro.EX_GeographicBoundingBox.append();
	gie::gco::CDecimal_PropertyType eastPro = box.eastBoundLongitude.append();
	gie::xs::CdecimalType realeast = eastPro.Decimal.append();
	gie::gco::CDecimal_PropertyType westPro = box.westBoundLongitude.append();
	gie::xs::CdecimalType realwest = westPro.Decimal.append();
	gie::gco::CDecimal_PropertyType northPro = box.northBoundLatitude.append();
	gie::xs::CdecimalType realnorth = northPro.Decimal.append();
	gie::gco::CDecimal_PropertyType southPro = box.southBoundLatitude.append();
	gie::xs::CdecimalType realsouth = southPro.Decimal.append();

//domainElement
	gcv::CCV_DomainObject_PropertyType domainPro = ieThematicGriddedData.domainElement.append();
	gcv::CCV_DomainObject_Type cvDomain = domainPro.CV_DomainObject.append();
	//temporalElement
	gcv::CTM_GeometricPrimitive_PropertyType cvObjectPro = cvDomain.temporalElement.append();
	gcv::CTM_GeometricPrimitive_Type cGeoPri = cvObjectPro.TM_GeometricPrimitive.append();
	gml::CMetaDataPropertyType cGeoPro = cGeoPri.metaDataProperty.append();
	gml::CGenericMetaDataType mltmName = cGeoPro.GenericMetaData.append();
	gml::CGenericMetaDataType mltmDW1 = cGeoPro.GenericMetaData.append();
	gml::CGenericMetaDataType mltmDW2 = cGeoPro.GenericMetaData.append();
	gml::CGenericMetaDataType mltmDW3 = cGeoPro.GenericMetaData.append();
	gml::CGenericMetaDataType mltmKey= cGeoPro.GenericMetaData.append();
	gml::CGenericMetaDataType mltmSecret = cGeoPro.GenericMetaData.append();
	gml::CGenericMetaDataType mltmCode = cGeoPro.GenericMetaData.append();
	gml::CGenericMetaDataType mltmExt = cGeoPro.GenericMetaData.append();
	gml::CGenericMetaDataType mlMetaCode = cGeoPro.GenericMetaData.append();
	gml::CGenericMetaDataType mlMetaDW = cGeoPro.GenericMetaData.append();
	gml::CGenericMetaDataType mlMetaName = cGeoPro.GenericMetaData.append();
	gml::CGenericMetaDataType mlMetaVersion = cGeoPro.GenericMetaData.append();
	//relatedTime
	gml::CRelatedTimeType mlRelateTimePro = cGeoPri.relatedTime.append();
	gml::CTimePeriodType mlRelateTime =  mlRelateTimePro.TimePeriod.append();
	gml::CTimeInstantType timeinse = mlRelateTimePro.TimeInstant.append();
	gml::CTimePositionType timepos = timeinse.timePosition.append();
	gml::CTimePositionType tmPoe = timeinse.timePosition.append();
	gml::CTimePositionType tmBegin = mlRelateTime.beginPosition.append();
	gml::CTimePositionType tmEnd = mlRelateTime.beginPosition.append();
	//CRS
	gsr::CSC_CRS_PropertyType gml_Pro = ieThematicGriddedData.CRS.append();
	gml::CProjectedCRSType gml_ProType = gml_Pro.ProjectedCRS.append();
	gml::CCodeType Proname = gml_ProType.name.append();
	xercesc::DOMNode* pProNameNde = Proname.GetNode();

	gml::CGeodeticCRSPropertyType geoCRSPro = gml_ProType.baseGeodeticCRS.append();
	gml::CGeodeticCRSType geoCRS = geoCRSPro.GeodeticCRS.append();
	gie::gml::CCodeType Geoname = geoCRS.name.append();
	xercesc::DOMNode* pGeoNde = Geoname.GetNode();
	
	gml::CSphericalCSPropertyType spheriaclPro = geoCRS.sphericalCS.append();
	gml::CSphericalCSType shperiacl = spheriaclPro.SphericalCS.append();
	
	gml::CCodeType shperiaclname = shperiacl.name.append();
	xercesc::DOMNode* pshperiaclname = shperiaclname.GetNode();
	
	gml::CCoordinateSystemAxisPropertyType axisPro = shperiacl.axis.append();
	gml::CCoordinateSystemAxisType axis = axisPro.CoordinateSystemAxis.append();
	gml::CCodeWithAuthorityType pDir = axis.axisDirection.append();
	xercesc::DOMNode* ppDir = pDir.GetNode();
	ppDir->setTextContent(L"North");
	gml::CCodeType codetype = axis.axisAbbrev.append();
	xercesc::DOMNode* pcodetype = codetype.GetNode();
	pcodetype->setTextContent(L"X");
	
	gml::CCoordinateSystemAxisPropertyType axisPro1 = shperiacl.axis.append();
	gml::CCoordinateSystemAxisType axis1 = axisPro1.CoordinateSystemAxis.append();
	gml::CCodeWithAuthorityType pDir1 = axis1.axisDirection.append();
	xercesc::DOMNode* ppDir1 = pDir1.GetNode();
	ppDir1->setTextContent(L"East");
	gml::CCodeType codetype1 = axis1.axisAbbrev.append();
	xercesc::DOMNode* pcodetype1 = codetype1.GetNode();
	pcodetype1->setTextContent(L"Y");
	
	//Datum
	gml::CGeodeticDatumPropertyType geoDatumPro = geoCRS.usesGeodeticDatum.append();
	gml::CGeodeticDatumType geoDatum = geoDatumPro.GeodeticDatum.append();
	gml::CCodeType Datumname = geoDatum.name.append();
	xercesc::DOMNode* pDatumname = Datumname.GetNode();

	gml::CPrimeMeridianPropertyType MeridianPro = geoDatum.primeMeridian.append();
	gml::CPrimeMeridianType Meridian = MeridianPro.PrimeMeridian.append();
	
	gml::CCodeType mername = Meridian.name.append();
	xercesc::DOMNode* pmername = mername.GetNode();
	pmername->setTextContent(L"unkonw");
	gml::CAngleType mer = Meridian.greenwichLongitude.append();
	
	gml::CAngleType angle = Meridian.greenwichLongitude.append();
	angle.uom = L"http://www.isotc211.org/2005/resources/uom/gmxUom.xsd#xpointer(//*[@gml:id='deg'])";

	gml::CEllipsoidPropertyType ellipsoidPro = geoDatum.usesEllipsoid.append();
	gml::CEllipsoidType ellipsoid = ellipsoidPro.Ellipsoid.append();
	gml::CCodeType ellipsoidname = ellipsoid.name.append();
	xercesc::DOMNode* pellipsoidname = ellipsoidname.GetNode();
	gml::CMeasureType measure = ellipsoid.semiMajorAxis.append();
	measure.uom = L"http://www.isotc211.org/2005/resources/uom/gmxUom.xsd#xpointer(//*[@gml:id='m'])";
	
	gie2::CsecondDefiningParameterType2 seconPrama2 = ellipsoid.secondDefiningParameter.append();
	gie2::CSecondDefiningParameterType secondePrama = seconPrama2.SecondDefiningParameter.append();
	gml::CLengthType cLegth =  secondePrama.semiMinorAxis.append();
	cLegth.uom = L"http://www.isotc211.org/2005/resources/uom/gmxUom.xsd#xpointer(//*[@gml:id='m'])";

	gie2::CIE_Georectified_PropertyType geoRectifiedPro = ieThematicGriddedData.georectifedSpatialInfo.append();
	gie2::CIE_Georectified_Type ieGeorectified = geoRectifiedPro.IE_Georectified.append();
	gco::CInteger_PropertyType num = ieGeorectified.numberOfDimensions.append();
	xs::CintegerType xsnum = num.Integer.append();
	xsnum = 3;
	
	gmd::CMD_CellGeometryCode_PropertyType CellGeoPro = ieGeorectified.cellGeometry.append();
	gco::CCodeListValue_Type CellGeo = CellGeoPro.MD_CellGeometryCode.append();
	CellGeo.codeList = L"http://standards.iso.org/ittf/PubliclyAvailableStandards/ISO_19139_Schemas/resources/Codelist/gmxCodelists.xml#MD_CellGeometryCode";
	CellGeo.codeListValue = L"Line";

	//CellGeo = L"Point";

	gco::CBoolean_PropertyType bTransPramaPro = ieGeorectified.transformationParameterAvailability.append();
	xs::CbooleanType bTransPrama = bTransPramaPro.Boolean.append();
	bTransPrama = false;

	gco::CBoolean_PropertyType bCheckPointPro = ieGeorectified.checkPointAvailability.append();
	xs::CbooleanType bCheckPoint= bCheckPointPro.Boolean.append();
	bCheckPoint = false;

	gmd::CMD_PixelOrientationCode_PropertyType PiexlPro = ieGeorectified.pointInPixel.append();
	gmd::CMD_PixelOrientationCode_TypeType Piexl = PiexlPro.MD_PixelOrientationCode.append();
	Piexl.SetEnumerationValue(2);//Piexl = L"2";

	 //datainfo
	gmd::CMD_CoverageDescription_PropertyType imageDescriptionPro = ieThematicGriddedData.dataInfo.append();
	gmi::CMI_ImageDescription_Type imageDes = imageDescriptionPro.MI_ImageDescription.append();
	gmd::CMD_Identifier_PropertyType imageIdenPro =  imageDes.imageQualityCode.append();
	gmd::CRS_Identifier_Type imageIden = imageIdenPro.RS_Identifier.append();
	gmd::CCI_Citation_PropertyType citaionPro = imageIden.authority.append();
	gmd::CCI_Citation_Type citation = citaionPro.CI_Citation.append();
	gco::CCharacterString_PropertyType title = citation.title.append();
	xs::CstringType strtitle = title.CharacterString.append();
	gco::CCharacterString_PropertyType alternateTitle = citation.alternateTitle.append();
	xs::CstringType stralternateTitle = alternateTitle.CharacterString.append();
	gco::CDate_PropertyType editionDate = citation.editionDate.append();
	gco::CDate_TypeType Date = editionDate.Date.append();
	xercesc::DOMNode* DateNode = Date.GetNode();


	gmd::CCI_ResponsibleParty_PropertyType ResponsiblePartyPro = citation.citedResponsibleParty.append();
	gmd::CCI_ResponsibleParty_Type ResponsibleParty = ResponsiblePartyPro.CI_ResponsibleParty.append();
	gco::CCharacterString_PropertyType individualName = ResponsibleParty.individualName.append();
	xs::CstringType strindividualName = individualName.CharacterString.append();
	gco::CCharacterString_PropertyType organisationName = ResponsibleParty.organisationName.append();
	xs::CstringType strorgnastionName = organisationName.CharacterString.append();
	//contactInfo
	gmd::CCI_Contact_PropertyType ContactPro = ResponsibleParty.contactInfo.append();
	gmd::CCI_Contact_Type contact = ContactPro.CI_Contact.append();
	gmd::CCI_Telephone_PropertyType phonePro = contact.phone.append();
	gmd::CCI_Telephone_Type phone = phonePro.CI_Telephone.append();
	gco::CCharacterString_PropertyType ccphone = phone.facsimile.append();
	xs::CstringType strphone = ccphone.CharacterString.append();
	gmd::CCI_Address_PropertyType addressPro = contact.address.append();
	gmd::CCI_Address_Type address = addressPro.CI_Address.append();
	gco::CCharacterString_PropertyType ccdeliveryPoint = address.deliveryPoint.append();
	xs::CstringType strdelivery = ccdeliveryPoint.CharacterString.append();
	gco::CCharacterString_PropertyType cccityPoint = address.city.append();
	xs::CstringType strcity = cccityPoint.CharacterString.append();
	gco::CCharacterString_PropertyType ccpostalCodePoint = address.postalCode.append();
	xs::CstringType strpostCode = ccpostalCodePoint.CharacterString.append();
	gco::CCharacterString_PropertyType cccountryPoint = address.country.append();
	xs::CstringType strCountry = cccountryPoint.CharacterString.append();
	strCountry = L"中国";
	gco::CCharacterString_PropertyType electronicMailAddress = address.electronicMailAddress.append();
	xs::CstringType strEMail = electronicMailAddress.CharacterString.append();
	gmd::CCI_OnlineResource_PropertyType onlinePro = contact.onlineResource.append();
	gmd::CCI_OnlineResource_Type online = onlinePro.CI_OnlineResource.append();
	gmd::CURL_PropertyType urlPro = online.linkage.append();
	xs::CanyURIType strurl = urlPro.URL.append();
	
	//geographicFeature
	gss::CGM_Object_PropertyType gmFeature = ieThematicGriddedData.geographicFeature.append();
	gml::CGridType grid = gmFeature.Grid.append();
	gml::CMetaDataPropertyType gridMetaData = grid.metaDataProperty.append();
	gml::CGenericMetaDataType gridDG = gridMetaData.GenericMetaData.append();
	gml::CGenericMetaDataType gridLX = gridMetaData.GenericMetaData.append();
	gml::CGenericMetaDataType gridSCFS = gridMetaData.GenericMetaData.append();
	gml::CGenericMetaDataType gridGCNC = gridMetaData.GenericMetaData.append();
	gml::CGenericMetaDataType gridXS= gridMetaData.GenericMetaData.append();
	gml::CGenericMetaDataType gridW = gridMetaData.GenericMetaData.append();
	gml::CGenericMetaDataType gridE = gridMetaData.GenericMetaData.append();
	gml::CGenericMetaDataType gridN = gridMetaData.GenericMetaData.append();
	gml::CGenericMetaDataType gridS = gridMetaData.GenericMetaData.append();
	gml::CGenericMetaDataType gridBXLX = gridMetaData.GenericMetaData.append();
	gml::CGridLimitsType gridlimit = grid.limits.append();
	gml::CGridEnvelopeType gridev = gridlimit.GridEnvelope.append();
	gml::CintegerListType strHeigh = gridev.high.append();
	gml::CintegerListType strLow = gridev.low.append();
	
	//sourceInfo
	gco::CCharacterString_PropertyType ccSJY = ieThematicGriddedData.sourceInfo.append();
	xs::CstringType strSJY = ccSJY.CharacterString.append();
	gco::CCharacterString_PropertyType ccXSX = ieThematicGriddedData.sourceInfo.append();
	xs::CstringType strXSX = ccXSX.CharacterString.append();
	gco::CCharacterString_PropertyType ccGCXTM = ieThematicGriddedData.sourceInfo.append();
	xs::CstringType strcxtm = ccGCXTM.CharacterString.append();
	gco::CCharacterString_PropertyType ccSJYS = ieThematicGriddedData.sourceInfo.append();
	xs::CstringType strSJYS = ccSJYS.CharacterString.append();
	
	wchar_t* wtTXT = gwAddonFunction::CharToWchar(strPath);
	std::ifstream in(wtTXT);  
	delete[] wtTXT;
	string filename;  
	string line;  
	string content;
	

	if(in) // 有该文件  
	{  
		int nLineIdx = 1;
		bool bisUTF8 = true;
		while (getline (in, line)) // line中不包括每行的换行符  
		{   
			wchar_t* wsContent  = gwAddonFunction::CharToWchar(line.data());

			std::wstring str = wsContent;
			int nIsGBK = -1; 
			if(nLineIdx == 1)
			{
				nIsGBK = str.find_first_of(L"元"); 
				if(nIsGBK != -1)
					bisUTF8 = false;
			}
			
			int nFirstIdx = -1; 
			//utf8
			if(bisUTF8)
			{
				char* szLine = gwAddonFunction::FromUTF8(line.data());
				wchar_t* wsContent1  = gwAddonFunction::CharToWchar(szLine);
				str = wsContent1;
				nFirstIdx = str.find_first_of(L"：");
				if(nFirstIdx == -1)
					nFirstIdx = str.find_first_of(L":");
				if(nFirstIdx == -1)
				{
					nLineIdx++;
					delete[] wsContent1;
					delete[] szLine;
					delete[] wsContent;
					continue;
				}
				delete[] wsContent1;
				delete[] szLine;
				
			}
			else
			{
				nFirstIdx =  str.find_first_of(L"：");
				if(nFirstIdx == -1)
					nFirstIdx = str.find_first_of(L":");
			}
			str = str.substr(nFirstIdx+1);
			wchar_t* wsline = (wchar_t*)str.data();
			delete[] wsContent;
			/*int nLastIdx  = line.size();
			line =line.substr(nFirstIdx );*/
			if(nLineIdx == 2)
			{
				
				//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
				mlMetaCode =wsline;
				//delete[] wsline;
			}
			if(nLineIdx == 4)
			{
				//line =line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
				mlMetaDW =wsline;
				//delete[] wsline;
				
			}

			if(nLineIdx == 7)
			{
				//line =line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
				mlMetaName =wsline;
				//delete[] wsline;
				
			}
			if(nLineIdx == 8)
			{
				//line =line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
				mlMetaVersion =wsline;
				//delete[] wsline;
				
			}
			if(nLineIdx == 15)
			{
				//line =line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
				timepos =wsline;
				//delete[] wsline;
			    
			}	
			if(nLineIdx == 59)
			{
				str.replace(str.find_first_of(L"°"),1,L".");
				str.erase(str.find_first_of(L"′"),1);
				str.erase(str.find_first_of(L"″"),1);
				realwest = wcstod(str.data(),NULL);
				//realwest = atof(line.data());


			}
			if(nLineIdx == 60)
			{
				str.replace(str.find_first_of(L"°"),1,L".");
				str.erase(str.find_first_of(L"′"),1);
				str.erase(str.find_first_of(L"″"),1);

				realeast = wcstod(str.data(),NULL);

				
			}
			if(nLineIdx == 61)
			{
				str.replace(str.find_first_of(L"°"),1,L".");
				str.erase(str.find_first_of(L"′"),1);
				str.erase(str.find_first_of(L"″"),1);
				realsouth = wcstod(str.data(),NULL);
			}
			if(nLineIdx == 62)
			{
				str.replace(str.find_first_of(L"°"),1,L".");
				str.erase(str.find_first_of(L"′"),1);
				str.erase(str.find_first_of(L"″"),1);
				realnorth = wcstod(str.data(),NULL);
			}
			if(nLineIdx == 97)
			{
				//line = line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wszProjcs = gwAddonFunction::CharToWchar(line.data());
				pProNameNde->setTextContent((XMLCh*)(wsline));
				//delete[] wszProjcs;
			}
			if(nLineIdx == 107)
			{
				//line = line.substr(nFirstIdx,nLastIdx);
			//	wchar_t* wsGeoName = gwAddonFunction::CharToWchar(line.data());
				pGeoNde->setNodeValue((XMLCh*)wsline);
				//delete[] wsGeoName;
			}
			if(nLineIdx == 102)
			{
				//line = line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wszshperiaclname = gwAddonFunction::CharToWchar(line.data());
				pshperiaclname->setTextContent((XMLCh*)(wsline));

				pellipsoidname->setTextContent((XMLCh*)(wsline));
				//delete[] wszshperiaclname;
			}
			if(nLineIdx == 109)
			{
				//line = line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wszName = gwAddonFunction::CharToWchar(line.data());
				pDatumname->setTextContent(wsline);
				//delete[] wszName;
			}
			if(nLineIdx == 101)
			{
				//line = line.substr(nFirstIdx,nLastIdx);
				mer = wcstod(wsline,NULL);
			}
			if(nLineIdx == 104)
			{
				//line = line.substr(nFirstIdx,nLastIdx);
				cLegth = wcstod(wsline,NULL);
			}
			if(nLineIdx == 106)
			{
				//line = line.substr(nFirstIdx,nLastIdx);
				measure = wcstod(wsline,NULL);
			}
			if(nLineIdx == 73)
			{
				//line = line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
				strtitle = wsline;
				//titleNode->setNodeValue((XMLCh*)wsline);
				//delete[] wsline;
			}
			if(nLineIdx == 74)
			{
				//line = line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
				//alternateTitleNode->setNodeValue((XMLCh*)wsline);
				stralternateTitle = wsline;
				//delete[] wsline;
			}
			if(nLineIdx == 86)
			{
				//line = line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
				DateNode->setNodeValue((XMLCh*)wsline);
				
				//delete[] wsline;
			}
			if(nLineIdx == 20)
			{
				//line =line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
				mltmDW1 =wsline;
				//delete[] wsline;

				
			}
			if(nLineIdx == 12)
			{
				//line =line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
				mltmName =wsline;
				//delete[] wsline;
				//
			}
			
			if(nLineIdx == 23)
			{
				//line =line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
				mltmDW2 =wsline;
				//delete[] wsline;

			}
			if(nLineIdx == 26)
			{
				//line =line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
				mltmDW3 =wsline;
				//delete[] wsline;
				
			}
			if(nLineIdx == 29)
			{
				//line =line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
				mltmKey =wsline;
				//delete[] wsline;
				
			}
			if(nLineIdx == 32)
			{
				//line =line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
				mltmSecret =wsline;
				//delete[] wsline;

			}
			if(nLineIdx == 33)
			{
				//line =line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
				mltmCode =wsline;
				//delete[] wsline;

			}
			if(nLineIdx == 38)
			{
				//line =line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
				gridDG =wsline;
				//delete[] wsline;

			}
			if(nLineIdx == 39)
			{
				//line =line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
				gridLX =wsline;
				//delete[] wsline;

			}
			if(nLineIdx == 40)
			{
				//line =line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
				gridSCFS =wsline;
				//delete[] wsline;

			}
			if(nLineIdx == 41)
			{
				//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
				gridGCNC =wsline;
				//delete[] wsline;

				
			}
			if(nLineIdx == 42)
			{
				int npointIdx = str.find_first_of(L"*");
				if(npointIdx == -1)
				{
					nLineIdx++;
					continue;
				}
				wstring h = str.substr(0,npointIdx-1);
				wstring l = str.substr(npointIdx+1,str.size()-1);

				strHeigh = h.data();
				strLow = l.data();


			}
			if(nLineIdx == 45)
			{
				//line =line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
				gridW =wsline;
				//delete[] wsline;


			}
			if(nLineIdx == 46)
			{
				//line =line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
				gridE =wsline;
				//delete[] wsline;


			}
			if(nLineIdx == 47)
			{
				//line =line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
				gridS =wsline;
				//delete[] wsline;


			}
			if(nLineIdx == 48)
			{
				//line =line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
				gridN =wsline;
				//delete[] wsline;


			}
			if(nLineIdx == 49)
			{
				//line =line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
				gridBXLX =wsline;
				//delete[] wsline;
			}
			if(nLineIdx == 64)
			{
				//line =line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
				strSJY =wsline;
				//delete[] wsline;
			}
			if(nLineIdx == 65)
			{
				//line =line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
				strXSX =wsline;
				//delete[] wsline;
			}
			if(nLineIdx == 71)
			{
				//line =line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
				strcxtm =wsline;
				//delete[] wsline;
			}
			if(nLineIdx == 6)
			{
				//line =line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
				tmPoe =wsline;
				//delete[] wsline;

			}
			if(nLineIdx == 15)
			{
				//line =line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
				tmBegin =wsline;
				//delete[] wsline;
				
			}
			if(nLineIdx == 92)
			{
				//line =line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
				tmEnd =wsline;
				//delete[] wsline;
			}
			if(nLineIdx == 73)
			{
				//line = line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
				//individualNode->setNodeValue((XMLCh*)wsline);
				strindividualName = wsline;
				//delete[] wsline;
			}
			if(nLineIdx == 77)
			{
				///line = line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
				//organisationNode->setNodeValue((XMLCh*)wsline);
				strorgnastionName = wsline;
				//delete[] wsline;
			}
			if(nLineIdx == 130)
			{
				//line = line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
				//phoneNode->setNodeValue((XMLCh*)wsline);
				strphone = wsline;
				//delete[] wsline;
			}
			if(nLineIdx == 124)
			{
				//line = line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
				//deliveryNode->setNodeValue((const XMLCh*)wsline);
				strdelivery = wsline;
				//delete[] wsline;
			}
			if(nLineIdx == 125)
			{
				//line = line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
			//	cityNode->setNodeValue((const XMLCh*)wsline);
				strcity = wsline;
				//delete[] wsline;
			}
			if(nLineIdx == 126)
			{
				//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
				
				strpostCode = wsline;
				//delete[] wsline;
			}
			if(nLineIdx == 127)
			{
				//line = line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
			//	electronicMailAddressNode->setNodeValue((XMLCh*)wsline);
				strEMail = wsline;
				//electronicMailAddress = (XMLCh*)wsline;		
				//delete[] wsline;
			}
			
			if(nLineIdx == 129)
			{
				//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
				strurl = wsline;
				//delete[] wsline;
			}
			nLineIdx++;
		}  
	}  
	else // 没有该文件  
	{  
		return;
	}  

	
	xercesc::DOMNode* root = ieThematicGriddedData.GetNode();
	m_strMetaData = gwAddonFunction::SaveXML(root,true);
	LocalFileFormatTarget target(m_XMLPath.c_str());
	bool bStatus = gwAddonFunction::WriteToTraget( &target, root, "UTF-8");
	//	delete[] path;
	
	
}
void gwOpticalImageAnalysis::WriteDOMMetadata(const char* strPath)
{
	
	m_gie = gie2::Cgie::CreateDocument();
	m_ieOpticalImage = m_gie.IE_OpticalImage.append();


	//domainExtent
	gie::gmd::CEX_Extent_PropertyType extent = m_ieOpticalImage.domainExtent.append();
	gie::gmd::CEX_Extent_Type extentType = extent.EX_Extent.append();
	gie::gmd::CEX_GeographicExtent_PropertyType exetentPro = extentType.geographicElement.append();
	gie::gmd::CEX_GeographicBoundingBox_Type box = exetentPro.EX_GeographicBoundingBox.append();
	gie::gco::CDecimal_PropertyType eastPro = box.eastBoundLongitude.append();
	gie::xs::CdecimalType realeast = eastPro.Decimal.append();
	gie::gco::CDecimal_PropertyType westPro = box.westBoundLongitude.append();
	gie::xs::CdecimalType realwest = westPro.Decimal.append();
	gie::gco::CDecimal_PropertyType northPro = box.northBoundLatitude.append();
	gie::xs::CdecimalType realnorth = northPro.Decimal.append();
	gie::gco::CDecimal_PropertyType southPro = box.southBoundLatitude.append();
	gie::xs::CdecimalType realsouth = southPro.Decimal.append();

//domainElement
	gcv::CCV_DomainObject_PropertyType domainPro = m_ieOpticalImage.domainElement.append();
	gcv::CCV_DomainObject_Type cvDomain = domainPro.CV_DomainObject.append();
	//temporalElement
	gcv::CTM_GeometricPrimitive_PropertyType cvObjectPro = cvDomain.temporalElement.append();
	gcv::CTM_GeometricPrimitive_Type cGeoPri = cvObjectPro.TM_GeometricPrimitive.append();
	gml::CMetaDataPropertyType cGeoPro = cGeoPri.metaDataProperty.append();
	gml::CGenericMetaDataType mlMetaCode = cGeoPro.GenericMetaData.append();
	gml::CGenericMetaDataType mlMetaDW = cGeoPro.GenericMetaData.append();
	gml::CGenericMetaDataType mlMetaName = cGeoPro.GenericMetaData.append();
	gml::CGenericMetaDataType mlMetaVersion = cGeoPro.GenericMetaData.append();
	gml::CRelatedTimeType mlRelateTime = cGeoPri.relatedTime.append();
	gml::CTimeInstantType timeinse = mlRelateTime.TimeInstant.append();
	gml::CTimePositionType timepos = timeinse.timePosition.append();
	//spatialelement
	gss::CGM_Object_PropertyType cvObjectPro1 = cvDomain.spatialElement.append();
	gml::CGridType grid = cvObjectPro1.Grid.append();
	gml::CMetaDataPropertyType gridMetaData = grid.metaDataProperty.append();
	gml::CGridLimitsType gridlimit = grid.limits.append();
	gml::CGridEnvelopeType gridev = gridlimit.GridEnvelope.append();
	gml::CintegerListType strHeigh = gridev.high.append();
	gml::CintegerListType strLow = gridev.low.append();
	//CRS
	gsr::CSC_CRS_PropertyType gml_Pro = m_ieOpticalImage.CRS.append();
	gml::CProjectedCRSType gml_ProType = gml_Pro.ProjectedCRS.append();
	gml::CCodeType Proname = gml_ProType.name.append();
	xercesc::DOMNode* pProNameNde = Proname.GetNode();

	gml::CGeodeticCRSPropertyType geoCRSPro = gml_ProType.baseGeodeticCRS.append();
	gml::CGeodeticCRSType geoCRS = geoCRSPro.GeodeticCRS.append();
	gie::gml::CCodeType Geoname = geoCRS.name.append();
	xercesc::DOMNode* pGeoNde = Geoname.GetNode();
	
	gml::CSphericalCSPropertyType spheriaclPro = geoCRS.sphericalCS.append();
	gml::CSphericalCSType shperiacl = spheriaclPro.SphericalCS.append();
	
	gml::CCodeType shperiaclname = shperiacl.name.append();
	xercesc::DOMNode* pshperiaclname = shperiaclname.GetNode();
	
	gml::CCoordinateSystemAxisPropertyType axisPro = shperiacl.axis.append();
	gml::CCoordinateSystemAxisType axis = axisPro.CoordinateSystemAxis.append();
	gml::CCodeWithAuthorityType pDir = axis.axisDirection.append();
	xercesc::DOMNode* ppDir = pDir.GetNode();
	ppDir->setTextContent(L"North");
	gml::CCodeType codetype = axis.axisAbbrev.append();
	xercesc::DOMNode* pcodetype = codetype.GetNode();
	pcodetype->setTextContent(L"X");
	
	gml::CCoordinateSystemAxisPropertyType axisPro1 = shperiacl.axis.append();
	gml::CCoordinateSystemAxisType axis1 = axisPro1.CoordinateSystemAxis.append();
	gml::CCodeWithAuthorityType pDir1 = axis1.axisDirection.append();
	xercesc::DOMNode* ppDir1 = pDir1.GetNode();
	ppDir1->setTextContent(L"East");
	gml::CCodeType codetype1 = axis1.axisAbbrev.append();
	xercesc::DOMNode* pcodetype1 = codetype1.GetNode();
	pcodetype1->setTextContent(L"Y");
	
	//Datum
	gml::CGeodeticDatumPropertyType geoDatumPro = geoCRS.usesGeodeticDatum.append();
	gml::CGeodeticDatumType geoDatum = geoDatumPro.GeodeticDatum.append();
	gml::CCodeType Datumname = geoDatum.name.append();
	xercesc::DOMNode* pDatumname = Datumname.GetNode();

	gml::CPrimeMeridianPropertyType MeridianPro = geoDatum.primeMeridian.append();
	gml::CPrimeMeridianType Meridian = MeridianPro.PrimeMeridian.append();
	
	gml::CCodeType mername = Meridian.name.append();
	xercesc::DOMNode* pmername = mername.GetNode();
	pmername->setTextContent(L"unkonw");
	gml::CAngleType mer = Meridian.greenwichLongitude.append();
	
	gml::CAngleType angle = Meridian.greenwichLongitude.append();
	angle.uom = L"http://www.isotc211.org/2005/resources/uom/gmxUom.xsd#xpointer(//*[@gml:id='deg'])";

	gml::CEllipsoidPropertyType ellipsoidPro = geoDatum.usesEllipsoid.append();
	gml::CEllipsoidType ellipsoid = ellipsoidPro.Ellipsoid.append();
	gml::CCodeType ellipsoidname = ellipsoid.name.append();
	xercesc::DOMNode* pellipsoidname = ellipsoidname.GetNode();
	

	gml::CMeasureType measure = ellipsoid.semiMajorAxis.append();
	measure.uom = L"http://www.isotc211.org/2005/resources/uom/gmxUom.xsd#xpointer(//*[@gml:id='m'])";
	
	gie2::CsecondDefiningParameterType2 seconPrama2 = ellipsoid.secondDefiningParameter.append();
	gie2::CSecondDefiningParameterType secondePrama = seconPrama2.SecondDefiningParameter.append();
	gml::CLengthType cLegth =  secondePrama.semiMinorAxis.append();
	cLegth.uom = L"http://www.isotc211.org/2005/resources/uom/gmxUom.xsd#xpointer(//*[@gml:id='m'])";

	gie2::CIE_Georectified_PropertyType geoRectifiedPro = m_ieOpticalImage.georectifedSpatialInfo.append();
	gie2::CIE_Georectified_Type ieGeorectified = geoRectifiedPro.IE_Georectified.append();
	gco::CInteger_PropertyType num = ieGeorectified.numberOfDimensions.append();
	xs::CintegerType xsnum = num.Integer.append();
	xsnum = 3;
	
	gmd::CMD_CellGeometryCode_PropertyType CellGeoPro = ieGeorectified.cellGeometry.append();
	gco::CCodeListValue_Type CellGeo = CellGeoPro.MD_CellGeometryCode.append();
	CellGeo.codeList = L"http://standards.iso.org/ittf/PubliclyAvailableStandards/ISO_19139_Schemas/resources/Codelist/gmxCodelists.xml#MD_CellGeometryCode";
	CellGeo.codeListValue = L"Line";

	//CellGeo = L"Point";

	gco::CBoolean_PropertyType bTransPramaPro = ieGeorectified.transformationParameterAvailability.append();
	xs::CbooleanType bTransPrama = bTransPramaPro.Boolean.append();
	bTransPrama = false;

	gco::CBoolean_PropertyType bCheckPointPro = ieGeorectified.checkPointAvailability.append();
	xs::CbooleanType bCheckPoint= bCheckPointPro.Boolean.append();
	bCheckPoint = false;

	gmd::CMD_PixelOrientationCode_PropertyType PiexlPro = ieGeorectified.pointInPixel.append();
	gmd::CMD_PixelOrientationCode_TypeType Piexl = PiexlPro.MD_PixelOrientationCode.append();
	Piexl.SetEnumerationValue(2);//Piexl = L"2";
	
	//acquisitionTime
	gcv::CTM_Period_PropertyType tmPerPro = m_ieOpticalImage.acquisitionTime.append();

	gcv::CTM_Period_Type tmPer =  tmPerPro.TM_Period.append();
	gml::CRelatedTimeType mlrelaTm = tmPer.relatedTime.append();
	gml::CTimeInstantType tmInse = mlrelaTm.TimeInstant.append();
	gml::CMetaDataPropertyType metaPro = tmInse.metaDataProperty.append();
	
	gml::CGenericMetaDataType mltmName = metaPro.GenericMetaData.append();
	gml::CGenericMetaDataType mltmDW1 = metaPro.GenericMetaData.append();
	gml::CGenericMetaDataType mltmDW2 = metaPro.GenericMetaData.append();
	//gml::CGenericMetaDataType mltmDW3 = metaPro.GenericMetaData.append();
	gml::CGenericMetaDataType mltmKey= metaPro.GenericMetaData.append();
	gml::CGenericMetaDataType mltmSecret = metaPro.GenericMetaData.append();
	/*gml::CGenericMetaDataType mltmCode = metaPro.GenericMetaData.append();*/
	gml::CGenericMetaDataType mltmExt = metaPro.GenericMetaData.append();
	gml::CTimePositionType tmPoe = tmInse.timePosition.append();
	gml::CTimePositionType tmBegin = tmPer.beginPosition.append();
	gml::CTimePositionType tmEnd = tmPer.beginPosition.append();
	 
	//imageDescription
	gmd::CMD_ImageDescription_PropertyType imageDescriptionPro = m_ieOpticalImage.imageDescription.append();
	gmi::CMI_ImageDescription_Type imageDes = imageDescriptionPro.MI_ImageDescription.append();
	gmd::CMD_Identifier_PropertyType imageIdenPro =  imageDes.imageQualityCode.append();
	gmd::CRS_Identifier_Type imageIden = imageIdenPro.RS_Identifier.append();
	gmd::CCI_Citation_PropertyType citaionPro = imageIden.authority.append();
	gmd::CCI_Citation_Type citation = citaionPro.CI_Citation.append();
	gco::CCharacterString_PropertyType title = citation.title.append();
	xs::CstringType strtitle = title.CharacterString.append();
	gco::CCharacterString_PropertyType alternateTitle = citation.alternateTitle.append();
	xs::CstringType stralternateTitle = alternateTitle.CharacterString.append();
	gco::CDate_PropertyType editionDate = citation.editionDate.append();
	gco::CDate_TypeType Date = editionDate.Date.append();
	xercesc::DOMNode* DateNode = Date.GetNode();

	gmd::CCI_ResponsibleParty_PropertyType ResponsiblePartyPro = citation.citedResponsibleParty.append();
	gmd::CCI_ResponsibleParty_Type ResponsibleParty = ResponsiblePartyPro.CI_ResponsibleParty.append();
	gco::CCharacterString_PropertyType individualName = ResponsibleParty.individualName.append();
	xs::CstringType strindividualName = individualName.CharacterString.append();
	gco::CCharacterString_PropertyType organisationName = ResponsibleParty.organisationName.append();
	xs::CstringType strorgnastionName = organisationName.CharacterString.append();
	//contactInfo
	gmd::CCI_Contact_PropertyType ContactPro = ResponsibleParty.contactInfo.append();
	gmd::CCI_Contact_Type contact = ContactPro.CI_Contact.append();
	gmd::CCI_Telephone_PropertyType phonePro = contact.phone.append();
	gmd::CCI_Telephone_Type phone = phonePro.CI_Telephone.append();
	gco::CCharacterString_PropertyType ccphone = phone.facsimile.append();
	xs::CstringType strphone = ccphone.CharacterString.append();
	gmd::CCI_Address_PropertyType addressPro = contact.address.append();
	gmd::CCI_Address_Type address = addressPro.CI_Address.append();
	gco::CCharacterString_PropertyType ccdeliveryPoint = address.deliveryPoint.append();
	xs::CstringType strdelivery = ccdeliveryPoint.CharacterString.append();
	gco::CCharacterString_PropertyType cccityPoint = address.city.append();
	xs::CstringType strcity = cccityPoint.CharacterString.append();
	gco::CCharacterString_PropertyType ccpostalCodePoint = address.postalCode.append();
	xs::CstringType strpostCode = ccpostalCodePoint.CharacterString.append();
	gco::CCharacterString_PropertyType cccountryPoint = address.country.append();
	xs::CstringType strCountry = cccountryPoint.CharacterString.append();
	strCountry = L"中国";
	gco::CCharacterString_PropertyType electronicMailAddress = address.electronicMailAddress.append();
	xs::CstringType strEMail = electronicMailAddress.CharacterString.append();
	gmd::CCI_OnlineResource_PropertyType onlinePro = contact.onlineResource.append();
	gmd::CCI_OnlineResource_Type online = onlinePro.CI_OnlineResource.append();
	gmd::CURL_PropertyType urlPro = online.linkage.append();
	xs::CanyURIType strurl = urlPro.URL.append();
	
	//sensorInfo
	gmi::CMI_Instrument_PropertyType instrumentPro = m_ieOpticalImage.sensorInfo.append();
	gmi::CMI_Instrument_Type instrument = instrumentPro.MI_Instrument.append();
	gmd::CCI_Citation_PropertyType citationPro = instrument.citation.append();
	gmd::CCI_Citation_Type sensorCitation = citationPro.CI_Citation.append();
	gco::CCharacterString_PropertyType sensorTitle = sensorCitation.title.append();
	xs::CstringType strSensortitle = sensorTitle.CharacterString.append();
	gmd::CCI_Date_PropertyType sensorDataPro = sensorCitation.date.append();
	gmd::CCI_Date_Type sensorDate = sensorDataPro.CI_Date.append();
	gco::CDate_PropertyType cosensorDate = sensorDate.date.append();
	gco::CDate_TypeType coDateType = cosensorDate.Date.append();
	xercesc::DOMNode* sensorDateNode = coDateType.GetNode();
	gmd::CMD_Identifier_PropertyType sensorIdenPr = sensorCitation.identifier.append();
	gmd::CRS_Identifier_Type sensorIdn = sensorIdenPr.RS_Identifier.append();
	gco::CCharacterString_PropertyType sensorCode = sensorIdn.code.append();
	xs::CstringType strSensorCode = sensorCode.CharacterString.append();
	gmd::CCI_ResponsibleParty_PropertyType sensorResponsPro = sensorCitation.citedResponsibleParty.append();
	gmd::CCI_ResponsibleParty_Type sensorResponse = sensorResponsPro.CI_ResponsibleParty.append();
	gco::CCharacterString_PropertyType ccSensororganisationName = sensorResponse.organisationName.append();
	xs::CstringType strSensororganisationName = ccSensororganisationName.CharacterString.append();
	gco::CCharacterString_PropertyType ccSensorDescription = instrument.description.append();
	xs::CstringType strSensorDes = ccSensorDescription.CharacterString.append();
	

	//numberofBands
	gco::CInteger_PropertyType bandsPro = m_ieOpticalImage.numberofBands.append();
	xs::CintegerType bands = bandsPro.Integer.append();
	bands = 1;
	//bandinformation
	gmi::CMI_Band_PropertyType BandInfoPro = m_ieOpticalImage.bandinformation.append();
	gmi::CMI_Band_Type BandInfo = BandInfoPro.MI_Band.append();
	gco::CReal_PropertyType resolutionPro = BandInfo.nominalSpatialResolution.append();
	xs::CdoubleType resolution = resolutionPro.Real.append();
	gco::CInteger_PropertyType intperValue = BandInfo.bitsPerValue.append();
	xs::CintegerType sxIntValue = intperValue.Integer.append();
	gco::CReal_PropertyType factor = BandInfo.scaleFactor.append();
	xs::CdoubleType dfact = factor.Real.append();

	wchar_t* wtTXT = gwAddonFunction::CharToWchar(strPath);
	std::ifstream in(wtTXT);  
	delete[] wtTXT;
	string filename;  
	string line;  
	string strForm ;
	if(in) // 有该文件  
	{  
		int nLineIdx = 1;
		bool bisUTF8 = true;
		while (getline (in, line)) // line中不包括每行的换行符  
		{   
			if(nLineIdx == 52)
				int s = 0;
			wchar_t* wsContent  = gwAddonFunction::CharToWchar(line.data());

			int nIsGBK = -1; 
			std::wstring str = wsContent;
			if(nLineIdx == 1)
			{
				nIsGBK = str.find_first_of(L"元"); 
				if(nIsGBK != -1)
					bisUTF8 = false;
			}

			
			int nFirstIdx = -1;
			if(bisUTF8)
			{
				char* szLine = gwAddonFunction::FromUTF8(line.data());
				wchar_t* wsContent1  = gwAddonFunction::CharToWchar(szLine);
				str = wsContent1;
				nFirstIdx = str.find_first_of(L"：");
				if(nFirstIdx == -1)
					nFirstIdx = str.find_first_of(L":");
				if(nFirstIdx == -1)
				{
					nLineIdx++;
					delete[] wsContent1;
					delete[] szLine;
					delete[] wsContent;
					continue;
				}
				delete[] wsContent1;
				delete[] szLine;
			}
			else
			{
				nFirstIdx = str.find_first_of(L"：");
				if(nFirstIdx == -1)
					nFirstIdx = str.find_first_of(L":");
			}
			str = str.substr(nFirstIdx+1);
			wchar_t* wsline = (wchar_t*)str.data();
			delete[] wsContent;
			if(nLineIdx == 2)
			{
				//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
				mlMetaCode =wsline;
				//delete[] wsline;
			}
			if(nLineIdx == 4)
			{
				//line =line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
				mlMetaDW =wsline;
				//delete[] wsline;
				
			}

			if(nLineIdx == 7)
			{
				//line =line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
				mlMetaName =wsline;
				//delete[] wsline;
				
			}
			if(nLineIdx == 8)
			{
				//line =line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
				mlMetaVersion =wsline;
				//delete[] wsline;
				
			}
			if(nLineIdx == 15)
			{
				//line =line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
				timepos =wsline;
				//delete[] wsline;
			    
			}	
			if(nLineIdx == 35)
			{
				sxIntValue =wcstod(wsline,NULL);;

			}	
			if(nLineIdx == 39)
			{
				dfact =wcstod(wsline,NULL);;

			}	
			if(nLineIdx == 47)
			{
				str.replace(str.find_first_of(L"°"),1,L".");
				str.erase(str.find_first_of(L"′"),1);
				str.erase(str.find_first_of(L"″"),1);
				realwest = wcstod(str.data(),NULL);
			}
			if(nLineIdx == 48)
			{
				str.replace(str.find_first_of(L"°"),1,L".");
				str.erase(str.find_first_of(L"′"),1);
				str.erase(str.find_first_of(L"″"),1);
				realeast = wcstod(str.data(),NULL);
			}
			if(nLineIdx == 49)
			{
				str.replace(str.find_first_of(L"°"),1,L".");
				str.erase(str.find_first_of(L"′"),1);
				str.erase(str.find_first_of(L"″"),1);
				realsouth = wcstod(str.data(),NULL);
			}
			if(nLineIdx == 50)
			{
				str.replace(str.find_first_of(L"°"),1,L".");
				str.erase(str.find_first_of(L"′"),1);
				str.erase(str.find_first_of(L"″"),1);
				realnorth = wcstod(str.data(),NULL);
			}
			if(nLineIdx == 91)
			{
				//line = line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wszProjcs = gwAddonFunction::CharToWchar(line.data());
				pProNameNde->setTextContent((XMLCh*)(wsline));
				//delete[] wszProjcs;
			}
			if(nLineIdx == 101)
			{
				//line = line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wsGeoName = gwAddonFunction::CharToWchar(line.data());
				pGeoNde->setNodeValue((XMLCh*)wsline);
				//delete[] wsGeoName;
			}
			if(nLineIdx == 96)
			{
				//line = line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wszshperiaclname = gwAddonFunction::CharToWchar(line.data());
				pshperiaclname->setTextContent((XMLCh*)(wsline));

				pellipsoidname->setTextContent((XMLCh*)(wsline));
				//delete[] wszshperiaclname;
			}
			if(nLineIdx == 103)
			{
				//line = line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wszName = gwAddonFunction::CharToWchar(line.data());
				pDatumname->setTextContent(wsline);
				//delete[] wszName;
			}
			if(nLineIdx == 95)
			{
				//line = line.substr(nFirstIdx,nLastIdx);
				mer = wcstod(wsline,NULL);
			}
			if(nLineIdx == 98)
			{
				//line = line.substr(nFirstIdx,nLastIdx);
				cLegth = wcstod(wsline,NULL);
			}
			if(nLineIdx == 100)
			{
				//line = line.substr(nFirstIdx,nLastIdx);
				measure =wcstod(wsline,NULL);
			}
			if(nLineIdx == 12)
			{
				//line = line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
				strtitle = wsline;
				stralternateTitle = wsline;
				mltmName =wsline;
				strindividualName = wsline;
				//titleNode->setNodeValue((XMLCh*)wsline);
				//delete[] wsline;
			}
			if(nLineIdx == 86)
			{
				//line = line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
				DateNode->setNodeValue((XMLCh*)wsline);
				
				//delete[] wsline;
			}
			if(nLineIdx == 20)
			{
				//line =line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
				mltmDW1 =wsline;
				//delete[] wsline;

				
			}
			if(nLineIdx == 23)
			{
				//line =line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
				mltmDW2 =wsline;
				//delete[] wsline;

			}
			if(nLineIdx == 26)
			{
				//line =line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
				mltmKey =wsline;
				//delete[] wsline;
				
			}
			if(nLineIdx == 29)
			{
				//line =line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
				mltmSecret =wsline;
				//delete[] wsline;

			}
			if(nLineIdx == 31)
			{
				//line =line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
				mltmExt =wsline;
				//delete[] wsline;
			}
			if(nLineIdx == 37)
			{
				int npointIdx = str.find_first_of(L"*");
				if(npointIdx == -1)
				{
					nLineIdx++;
					continue;
				}
				wstring h = str.substr(0,npointIdx-1);
				wstring l = str.substr(npointIdx+1,str.size()-1);;
				strHeigh = h.data();
				strLow = l.data();
			}
			if(nLineIdx == 6)
			{
				//line =line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
				tmPoe =wsline;
				//delete[] wsline;

			}
			if(nLineIdx == 15)
			{
				//line =line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
				tmBegin =wsline;
				//delete[] wsline;
				
			}
			if(nLineIdx == 86)
			{
				//line =line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
				tmEnd =wsline;
				//delete[] wsline;
			}
			if(nLineIdx == 4)
			{
				///line = line.substr(nFirstIdx,nLastIdx);
			//	wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
				//organisationNode->setNodeValue((XMLCh*)wsline);
				strorgnastionName = wsline;
				//delete[] wsline;
			}
			if(nLineIdx == 120)
			{
				//line = line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
				//phoneNode->setNodeValue((XMLCh*)wsline);
				strphone = wsline;
				//delete[] wsline;
			}
			if(nLineIdx == 114)
			{
				//line = line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
				//deliveryNode->setNodeValue((const XMLCh*)wsline);
				strdelivery = wsline;
				//delete[] wsline;
			}
			if(nLineIdx == 115)
			{
				//line = line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
			//	cityNode->setNodeValue((const XMLCh*)wsline);
				strcity = wsline;
				//delete[] wsline;
			}
			if(nLineIdx == 116)
			{
				//line = line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
				//postalCodeNode->setNodeValue((XMLCh*)wsline);
				strpostCode = wsline;
				//delete[] wsline;
			}
			if(nLineIdx == 117)
			{
				//line = line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
			//	electronicMailAddressNode->setNodeValue((XMLCh*)wsline);
				strEMail = wsline;
				//electronicMailAddress = (XMLCh*)wsline;		
				//delete[] wsline;
			}
			
			if(nLineIdx == 119)
			{
				//line = line.substr(nFirstIdx,nLastIdx);
				//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
				//urlNode->setNodeValue((XMLCh*)wsline);
				strurl = wsline;
				//delete[] wsline;
			}
			if(nLineIdx == 41)
			{
				//line = line.substr(nFirstIdx,nLastIdx);
				resolution = wcstod(wsline,NULL);
			}
			
			if(nLineIdx == 52)
			{
				/*wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
				strpresentationForm = wsline;*/
				char* czline = gwAddonFunction::WcharToChar(wsline);
				strForm = czline;
				delete[] czline;
				//delete[] wsline;
			}
			if(stricmp(strForm.data(),"航片")==0)
			{
				if(nLineIdx == 55)
				{
					//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
					strSensortitle = wsline;
					//delete[] wsline;
				}
				if(nLineIdx == 59)
				{
					//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
					sensorDateNode->setNodeValue(wsline);
					//delete[] wsline;
				}
				if(nLineIdx == 55)
				{
					//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
					strSensorCode = wsline;
					//delete[] wsline;
				}
				if(nLineIdx == 57)
				{
					//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
					strSensororganisationName = wsline;
					//delete[] wsline;
				}
				if(nLineIdx == 64)
				{
					//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
					strSensorDes = wsline;
					//delete[] wsline;
				}
			}
			else
			{
				if(nLineIdx == 66)
				{
					//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
					strSensortitle = wsline;
					//delete[] wsline;
				}
				if(nLineIdx == 71)
				{
					//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
					sensorDateNode->setNodeValue(wsline);
					//delete[] wsline;
				}
				if(nLineIdx == 70)
				{
					//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
					strSensorCode = wsline;
					//delete[] wsline;
				}
				if(nLineIdx == 79)
				{
					//wchar_t* wsline = gwAddonFunction::CharToWchar(line.data());
					strSensorDes = wsline;
					//delete[] wsline;
				}
			}
			
			nLineIdx++;
		}  
	}  
	else // 没有该文件  
	{  
		return;
	}  

	
	xercesc::DOMNode* root = m_ieOpticalImage.GetNode();
	m_strMetaData = gwAddonFunction::SaveXML(root,true);
	LocalFileFormatTarget target(m_XMLPath.c_str());
	bool bStatus = gwAddonFunction::WriteToTraget( &target, root, "UTF-8");
}
bool gwOpticalImageAnalysis::SaveMetaData()
{
	//wchar_t* path = gwAddonFunction::CharToWchar(m_XMLPath.c_str());
	/*XMLFormatTarget * Targe;
	Targe = new LocalFileFormatTarget( m_XMLPath.c_str());*/
	LocalFileFormatTarget target(m_XMLPath.c_str());
	bool bStatus = gwAddonFunction::WriteToTraget( &target, m_ieOpticalImage.GetNode(), "UTF-8");
//	delete[] path;
	return bStatus;
}
void gwOpticalImageAnalysis::ReadStanardMetadata()
{

}
const string& gwOpticalImageAnalysis::getMetaData()
{
	return m_strMetaData;
}
const ieSimpleRasterInfo gwOpticalImageAnalysis::getRasterInfo()
{
	ieSimpleRasterInfo s;
	return s;
}
void gwOpticalImageAnalysis::setRasterInfo(const ieSimpleRasterInfo& rInfo)
{
	//m_gInfo = rInfo;
}
void gwOpticalImageAnalysis::setStandardMetaDataFilePath(const string& strPath)
{
	m_XMLPath = strPath;
}