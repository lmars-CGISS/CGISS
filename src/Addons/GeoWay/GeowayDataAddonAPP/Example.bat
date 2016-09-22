
@rem 参数详细说明
@rem -Type 转换方式，包括 Inmdb OutMdb，Infgdb Outfgdb，Indb Outdb
@rem -Parameter 参数字符串
@echo off 
echo 转换开始..... 

D:\code\gwPlatformwss\bin\gwCore\win32\releaseBin\geowayTransformAPP.exe  -Parameter "<GIS><Parameter Key=\"DataType\"><Value>File</Value></Parameter><Parameter Key=\"Path\"><Value>d:\\TestData\\db\\山东final.db</Value></Parameter><Parameter Key=\"Output\"><Value>d:\\TestData\\gpkg\\db2gpkgs121.gpkg</Value></Parameter></GIS>" -Type "Inmdb"

echo 转换结束!
echo. & pause 