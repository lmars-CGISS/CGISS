
@rem ������ϸ˵��
@rem -Type ת����ʽ������ Inmdb OutMdb��Infgdb Outfgdb��Indb Outdb
@rem -Parameter �����ַ���
@echo off 
echo ת����ʼ..... 

D:\code\gwPlatformwss\bin\gwCore\win32\releaseBin\geowayTransformAPP.exe  -Parameter "<GIS><Parameter Key=\"DataType\"><Value>File</Value></Parameter><Parameter Key=\"Path\"><Value>d:\\TestData\\db\\ɽ��final.db</Value></Parameter><Parameter Key=\"Output\"><Value>d:\\TestData\\gpkg\\db2gpkgs121.gpkg</Value></Parameter></GIS>" -Type "Inmdb"

echo ת������!
echo. & pause 