// stdafx.cpp : ֻ������׼�����ļ���Դ�ļ�
// GeoStarAddon.pch ����ΪԤ����ͷ
// stdafx.obj ������Ԥ����������Ϣ

#include "stdafx.h"

// TODO: �� STDAFX.H ��
// �����κ�����ĸ���ͷ�ļ����������ڴ��ļ�������
//#pragma comment(lib,"gdal_i.lib")
#ifdef _DEBUG
#pragma comment(lib,"geodatabased.lib")
#pragma comment(lib,"spatialreferenced.lib")
#pragma comment(lib,"geometryd.lib")
#pragma comment(lib,"utilityd.lib")
#else
#pragma comment(lib,"geodatabase.lib")
#pragma comment(lib,"spatialreference.lib")
#pragma comment(lib,"geometry.lib")
#pragma comment(lib,"utility.lib")
#endif

#pragma comment(lib,"libgpkg.lib")