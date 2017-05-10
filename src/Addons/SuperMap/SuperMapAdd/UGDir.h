/*!
* Copyright (c) 2017,
* All Rights Reserved.
*
*
* \file UGDir.h
* \brief ������
*
* \author 
* \date 2017��04��28��
* \version 1.0
*/

#ifndef _UG_DIR_H
#define _UG_DIR_H
#pragma once
#include "stdafx.h"

using namespace std;

class UGDir
{
public:	
	//��path��ָ����������Ŀ¼����Ŀ¼
	static bool CreateDir(const string& strPath);

	//����ָ��Ŀ¼�е�ֱ�����ļ�/Ŀ¼���ơ�������"."��".."
	static int GetSubPaths(std::vector<string>& vPathNames, const string& strPath);

	//����ָ��Ŀ¼����ָ������ģʽƥ���ֱ�����ļ�/Ŀ¼���ơ�������"."��".."
	static int GetSubPaths(std::vector<string>& vPathNames, const string& strPath, const string& strNameFilter);

	//����ָ��Ŀ¼����ָ������ģʽƥ����ļ�/Ŀ¼���ƣ���ʹ��ĳ��ֵȷ���Ƿ�����Ŀ¼��������������"."��".."
	static int GetSubPaths(std::vector<string>& vPathNames, const string& strPath, const string& strNameFilter, bool bRecursive);

	//����ָ��Ŀ¼�е�ֱ�����ļ����ơ�������"."��".."
	static int GetFiles(std::vector<string>& vFileNames, const string& strPath);

	//����ָ��Ŀ¼����ָ������ģʽƥ���ֱ�����ļ����ơ�������"."��".."
	static int GetFiles(std::vector<string>& vFileNames, const string& strPath, const string& strNameFilter);

	//����ָ��Ŀ¼����ָ������ģʽƥ����ļ����ƣ���ʹ��ĳ��ֵȷ���Ƿ�����Ŀ¼��������������"."��".."
	static int GetFiles(std::vector<string>& vFileNames, const string& strPath, const string& strNameFilter, bool bRecursive);

	//����ָ��Ŀ¼�е�ֱ����Ŀ¼���ơ�������"."��".."
	static int GetDirectories(std::vector<string>& vDirNames, const string& strPath);

	//����ָ��Ŀ¼����ָ������ģʽƥ���ֱ����Ŀ¼���ơ�������"."��".."
	static int GetDirectories(std::vector<string>& vDirNames, const string& strPath, const string& strNameFilter);

	//����ָ��Ŀ¼����ָ������ģʽƥ���Ŀ¼����ʹ��ĳ��ֵȷ���Ƿ�����Ŀ¼��������������"."��".."
	static int GetDirectories(std::vector<string>& vDirNames, const string& strPath, const string& strNameFilter, bool bRecursive);
};


#endif //_UG_DIR_H
