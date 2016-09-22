#pragma once
#include "preconfig.h"
#include "spatialindex.h"
#include "spatialreference.h"
#include "pyramid.h"
#include "geometry.h"
#include "symbol.h"
#include "pointsymbol.h"
#include "linesymbol.h"
#include "fillsymbol.h"
#include "geodatabase.h"
#include "map.h"
#include "mapdefine.h"
#ifdef QT_VERSION 
#include "qt/qtdevice.h"
#endif

#ifdef WIN32
#include "win32\windevice.h"
#endif
/*! \mainpage GeoStar Kernel （GeoStar基础GIS平台内核模块)
 *
 * \section intro_sec 介绍
 *
 * 介绍内容.
 *
 * \section install_sec 安装
 *
 * \subsection step1 Step 1: Opening the box
 *  
 * etc...
 */

KERNEL_NS 
/// \brief 内核初始化
class GsKernel
{
	static void RegisterSymbol()
	{
		//点
		REG_CLASS_CREATE(GsMultiPointSymbol);
		REG_CLASS_CREATE_ALIAS(GsMultiPointSymbol,"{F6E15656-6573-4B93-BF6F-0CD1A3B05426}");
		REG_CLASS_CREATE_ALIAS(GsMultiPointSymbol,"GeoStarCore.MultiPointSymbol.1");
		REG_CLASS_CREATE_ALIAS(GsMultiPointSymbol,"MultiPointSymbol");


		REG_CLASS_CREATE(GsSimplePointSymbol);
		REG_CLASS_CREATE_ALIAS(GsSimplePointSymbol,"{F6E15656-6573-4B93-BF6F-0CD1A3B05415}");
		REG_CLASS_CREATE_ALIAS(GsSimplePointSymbol,"GeoStarCore.SimplePointSymbol.1"); 
		REG_CLASS_CREATE_ALIAS(GsSimplePointSymbol,"SimplePoint");

		REG_CLASS_CREATE(GsLinePointSymbol);
		REG_CLASS_CREATE_ALIAS(GsLinePointSymbol,"{F6E15656-6573-4B93-BF6F-0CD1A3B05416}");
		REG_CLASS_CREATE_ALIAS(GsLinePointSymbol,"GeoStarCore.LinePointSymbol.1");
		REG_CLASS_CREATE_ALIAS(GsLinePointSymbol,"LinePoint");

		REG_CLASS_CREATE(GsPolylinePointSymbol);
		REG_CLASS_CREATE_ALIAS(GsPolylinePointSymbol,"{F6E15656-6573-4B93-BF6F-0CD1A3B05417}");
		REG_CLASS_CREATE_ALIAS(GsPolylinePointSymbol,"GeoStarCore.PolylinePointSymbol.1");
		REG_CLASS_CREATE_ALIAS(GsPolylinePointSymbol,"PolylinePoint");

		REG_CLASS_CREATE(GsPicturePointSymbol);
		REG_CLASS_CREATE_ALIAS(GsPicturePointSymbol,"{0C6D50E9-24CA-4D80-91AE-491C8053F0A5}");
		REG_CLASS_CREATE_ALIAS(GsPicturePointSymbol,"GeoStarCore.PicturePointSymbol.1");
		REG_CLASS_CREATE_ALIAS(GsPicturePointSymbol,"PicturePoint");

		REG_CLASS_CREATE(GsEllipsePointSymbol);
		REG_CLASS_CREATE_ALIAS(GsEllipsePointSymbol,"{F6E15656-6573-4B93-BF6F-0CD1A3B0541B}");
		REG_CLASS_CREATE_ALIAS(GsEllipsePointSymbol,"GeoStarCore.EllipsePointSymbol.1");
		REG_CLASS_CREATE_ALIAS(GsEllipsePointSymbol,"EllipsePoint");

		REG_CLASS_CREATE(GsArcPointSymbol);
		REG_CLASS_CREATE_ALIAS(GsArcPointSymbol,"{F6E15656-6573-4B93-BF6F-0CD1A3B05425}");
		REG_CLASS_CREATE_ALIAS(GsArcPointSymbol,"GeoStarCore.ArcPointSymbol.1");
		REG_CLASS_CREATE_ALIAS(GsArcPointSymbol,"ArcPoint");

		REG_CLASS_CREATE(GsTextPointSymbol);
		REG_CLASS_CREATE_ALIAS(GsTextPointSymbol,"{F6E15656-6573-4B93-BF6F-0CD1A3B05420}");
		REG_CLASS_CREATE_ALIAS(GsTextPointSymbol,"GeoStarCore.TextPointSymbol.1");
		REG_CLASS_CREATE_ALIAS(GsTextPointSymbol,"TextPoint");

		REG_CLASS_CREATE(GsCurvelinePointSymbol);
		REG_CLASS_CREATE_ALIAS(GsCurvelinePointSymbol,"{F6E15656-6573-4B93-BF6F-0CD1A3B05419}");
		REG_CLASS_CREATE_ALIAS(GsCurvelinePointSymbol,"GeoStarCore.CurvelinePointSymbol.1");
		REG_CLASS_CREATE_ALIAS(GsCurvelinePointSymbol,"CurvelinePoint");

		REG_CLASS_CREATE(GsCurvegonPointSymbol);
		REG_CLASS_CREATE_ALIAS(GsCurvegonPointSymbol,"{F6E15656-6573-4B93-BF6F-0CD1A3B0541A}");
		REG_CLASS_CREATE_ALIAS(GsCurvegonPointSymbol,"GeoStarCore.CurvegonPointSymbol.1");
		 REG_CLASS_CREATE_ALIAS(GsCurvegonPointSymbol,"CurvegonPoint");

		REG_CLASS_CREATE(GsAsteriskPointSymbol);
		REG_CLASS_CREATE_ALIAS(GsAsteriskPointSymbol,"{F6E15656-6573-4B93-BF6F-0CD1A3B0541F}");
		REG_CLASS_CREATE_ALIAS(GsAsteriskPointSymbol,"GeoStarCore.AsteriskPointSymbol.1");
		REG_CLASS_CREATE_ALIAS(GsAsteriskPointSymbol,"AsteriskPoint");

		REG_CLASS_CREATE(GsQRCodePointSymbol);
		REG_CLASS_CREATE_ALIAS(GsQRCodePointSymbol,"QRCodePoint"); 
		

		//PolygonPoint
		REG_CLASS_CREATE(GsPolygonPointSymbol);
		REG_CLASS_CREATE_ALIAS(GsPolygonPointSymbol,"{F6E15656-6573-4B93-BF6F-0CD1A3B05418}");
		REG_CLASS_CREATE_ALIAS(GsPolygonPointSymbol,"GeoStarCore.PolygonPointSymbol.1");
		REG_CLASS_CREATE_ALIAS(GsPolygonPointSymbol,"PolygonPoint");

		//ChordPoint
		REG_CLASS_CREATE(GsChordPointSymbol);
		REG_CLASS_CREATE_ALIAS(GsChordPointSymbol,"{F6E15656-6573-4B93-BF6F-0CD1A3B0541E}");
		REG_CLASS_CREATE_ALIAS(GsChordPointSymbol,"GeoStarCore.ChordPointSymbol.1");
		REG_CLASS_CREATE_ALIAS(GsChordPointSymbol,"ChordPoint");

		REG_CLASS_CREATE(GsPiePointSymbol);
		REG_CLASS_CREATE_ALIAS(GsPiePointSymbol,"{F6E15656-6573-4B93-BF6F-0CD1A3B0541D}");
		REG_CLASS_CREATE_ALIAS(GsPiePointSymbol,"GeoStarCore.GsPiePointSymbol.1");
		REG_CLASS_CREATE_ALIAS(GsPiePointSymbol,"PiePoint");

		//RectanglePoint
		REG_CLASS_CREATE(GsRectanglePointSymbol);
		REG_CLASS_CREATE_ALIAS(GsRectanglePointSymbol,"{F6E15656-6573-4B93-BF6F-0CD1A3B0541C}");
		REG_CLASS_CREATE_ALIAS(GsRectanglePointSymbol,"GeoStarCore.RectanglePointSymbol.1");
		REG_CLASS_CREATE_ALIAS(GsRectanglePointSymbol,"RectanglePoint");

		//线
		REG_CLASS_CREATE(GsMultiLineSymbol);
		REG_CLASS_CREATE_ALIAS(GsMultiLineSymbol,"{C6D520D5-6EC3-4C93-9C5A-9AFFAB0EED0F}");
		REG_CLASS_CREATE_ALIAS(GsMultiLineSymbol,"GeoStarCore.MultiLineSymbol.1");
		REG_CLASS_CREATE_ALIAS(GsMultiLineSymbol,"MultiLineSymbol");

		REG_CLASS_CREATE(GsSimpleLineSymbol);
		REG_CLASS_CREATE_ALIAS(GsSimpleLineSymbol,"{C6D520D5-6EC3-4C93-9C5A-9AFFAB0EED0E}");
		REG_CLASS_CREATE_ALIAS(GsSimpleLineSymbol,"GeoStarCore.SimpleLineSymbol.1");
		REG_CLASS_CREATE_ALIAS(GsSimpleLineSymbol,"SimpleLine");


		REG_CLASS_CREATE(GsPointLineSymbol);
		REG_CLASS_CREATE_ALIAS(GsPointLineSymbol,"{260F5830-5562-4D8F-BE80-6AB5805204E5}");
		REG_CLASS_CREATE_ALIAS(GsPointLineSymbol,"GeoStarCore.PointLineSymbol.1");
		REG_CLASS_CREATE_ALIAS(GsPointLineSymbol,"PointLine");

		REG_CLASS_CREATE(GsHashLineSymbol);
		REG_CLASS_CREATE_ALIAS(GsHashLineSymbol,"{8E427709-7B01-4580-9239-EFD176966615}");
		REG_CLASS_CREATE_ALIAS(GsHashLineSymbol,"GeoStarCore.HashLineSymbol.1");
		REG_CLASS_CREATE_ALIAS(GsHashLineSymbol,"HashLine");

		REG_CLASS_CREATE(GsCartographicLineSymbol);
		REG_CLASS_CREATE_ALIAS(GsCartographicLineSymbol,"{C6D520D5-6EC3-4C93-9C5A-9AFFAB0EED0D}");
		REG_CLASS_CREATE_ALIAS(GsCartographicLineSymbol,"GeoStarCore.CartographicLineSymbol.1");
		REG_CLASS_CREATE_ALIAS(GsCartographicLineSymbol,"CartographicLine");

		REG_CLASS_CREATE(GsLocatePointLineSymbol);
		REG_CLASS_CREATE_ALIAS(GsLocatePointLineSymbol,"{2474E6D1-8FE4-42E8-A20C-C07B68B9628D}");
		REG_CLASS_CREATE_ALIAS(GsLocatePointLineSymbol,"GeoStarCore.LocatePointLineSymbol.1");
		REG_CLASS_CREATE_ALIAS(GsLocatePointLineSymbol,"LocatePointLine");

		REG_CLASS_CREATE(GsLeadConnectedLineSymbol);
		REG_CLASS_CREATE_ALIAS(GsLeadConnectedLineSymbol,"{B44C3816-A707-441C-B8EC-EA5D890DBECE}");
		REG_CLASS_CREATE_ALIAS(GsLeadConnectedLineSymbol,"GeoStarCore.LeadConnectedLineSymbol.1");
		REG_CLASS_CREATE_ALIAS(GsLeadConnectedLineSymbol,"LeadConnectedLine");

		//面
		REG_CLASS_CREATE(GsMultiFillSymbol);
		REG_CLASS_CREATE_ALIAS(GsMultiFillSymbol,"{AF129AAF-F709-4F59-9E67-47904923B6A9}");
		REG_CLASS_CREATE_ALIAS(GsMultiFillSymbol,"GeoStarCore.MultiFillSymbol.1");
		REG_CLASS_CREATE_ALIAS(GsMultiFillSymbol,"MultiAreaSymbol");

		REG_CLASS_CREATE(GsSimpleFillSymbol);
		REG_CLASS_CREATE_ALIAS(GsSimpleFillSymbol,"{171538B1-4DAB-435D-9C48-8CBBF33307EA}");
		REG_CLASS_CREATE_ALIAS(GsSimpleFillSymbol,"GeoStarCore.SimpleFillSymbol.1");
		REG_CLASS_CREATE_ALIAS(GsSimpleFillSymbol,"SimpleArea");

		REG_CLASS_CREATE(GsPointFillSymbol);
		REG_CLASS_CREATE_ALIAS(GsPointFillSymbol,"{23D65545-D01A-4398-9DA7-0701AA896B32}");
		REG_CLASS_CREATE_ALIAS(GsPointFillSymbol,"GeoStarCore.PointFillSymbol.1");
		REG_CLASS_CREATE_ALIAS(GsPointFillSymbol,"PointArea");

		REG_CLASS_CREATE(GsLineFillSymbol);
		REG_CLASS_CREATE_ALIAS(GsLineFillSymbol,"{3A92B7B6-54C9-4D13-ABBA-A8118D740BD0}");
		REG_CLASS_CREATE_ALIAS(GsLineFillSymbol,"GeoStarCore.LineFillSymbol.1");
		REG_CLASS_CREATE_ALIAS(GsLineFillSymbol,"LineArea");

		REG_CLASS_CREATE(GsPictureFillSymbol);
		REG_CLASS_CREATE_ALIAS(GsPictureFillSymbol,"{7a0aa58b-2446-43dc-a282-0470d759de86}");
		REG_CLASS_CREATE_ALIAS(GsPictureFillSymbol,"GeoStarCore.PictureFillSymbol.1");
		REG_CLASS_CREATE_ALIAS(GsPictureFillSymbol,"PictureArea");

		REG_CLASS_CREATE(GsGradsFillSymbol);
		REG_CLASS_CREATE_ALIAS(GsGradsFillSymbol,"{55196cc6-effb-45df-a992-1e27167011d6}");
		REG_CLASS_CREATE_ALIAS(GsGradsFillSymbol,"GeoStarCore.GradsFillSymbol.1");
		REG_CLASS_CREATE_ALIAS(GsGradsFillSymbol,"GradsArea");

		REG_CLASS_CREATE(GsTextSymbol);
		REG_CLASS_CREATE_ALIAS(GsTextSymbol,"{F947691D-CED4-4600-A1EC-CBC0C01EB039}");
		REG_CLASS_CREATE_ALIAS(GsTextSymbol,"GeoStarCore.TextSymbol.1");
		REG_CLASS_CREATE_ALIAS(GsTextSymbol,"TextSymbol");

		//Canvas 注册
#ifdef QT_VERSION 
		REG_CLASS_CREATE_NS(GsQTCanvasFactory,QT);
#endif
		
#ifdef WIN32
		REG_CLASS_CREATE_NS(GsWin32CanvasFactory,Win32);
#endif
	}
	static void RegisterUser()
	{

	}
public:
	
	/// \brief 创建类的实例
	static Utility::GsString Version()
	{
		return Utility::GsString("1.0.0");
	}

	/// \brief 初始化
	static void Initialize()
	{
		static bool bInit = false;
		static Utility::GsLock lock;
		if(bInit)
			return;
		{
			Utility::GsAutoLocker l(lock);
			RegisterSymbol();
			RegisterUser();
			bInit = true;
		}
	}


};
KERNEL_ENDNS 
