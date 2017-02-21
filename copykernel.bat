robocopy /s D:\02-Work\8888-GeoStarKernel\03-source\include\utility .\src\Addons\GeoStar\include\utility
robocopy /s D:\02-Work\8888-GeoStarKernel\03-source\include\kernel .\src\Addons\GeoStar\include\kernel
robocopy /s D:\02-Work\8888-GeoStarKernel\03-source\include\geomathse .\src\Addons\GeoStar\include\geomathd

robocopy D:\02-Work\8888-GeoStarKernel\03-source\debugx86  .\src\debug\x86  gdal201.dll geostar.kernel.dll geostar.kernel.xml gsgeodatabased.dll gsgeomathdd.dll gsgeomathse.dll gsgeometryd.dll gsmapd.dll gsspatialreferenced.dll gssymbold.dll gsutilityd.dll gswin32portd.dll

robocopy D:\02-Work\8888-GeoStarKernel\03-source\releasex86  .\src\release\x86  gdal201.dll geostar.kernel.dll geostar.kernel.xml gsgeodatabase.dll gsgeomathd.dll gsgeomathse.dll gsgeometry.dll gsmap.dll gsspatialreference.dll gssymbol.dll gsutility.dll gswin32port.dll

robocopy D:\02-Work\8888-GeoStarKernel\03-source\debugx86  .\src\Addons\GeoStar\debuglibx86  gdal_i.lib  gsgeodatabased.lib gsgeomathdd.lib gsgeomathse.lib gsgeometryd.lib gsmapd.lib gsspatialreferenced.lib gssymbold.lib gsutilityd.lib gswin32portd.lib

robocopy D:\02-Work\8888-GeoStarKernel\03-source\releasex86  .\src\Addons\GeoStar\releaselibx86  gdal_i.lib  gsgeodatabase.lib gsgeomathd.lib gsgeomathse.lib gsgeometry.lib gsmap.lib gsspatialreference.lib gssymbol.lib gsutility.lib gswin32port.lib

pause