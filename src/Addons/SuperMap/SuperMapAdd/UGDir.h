/*!
* Copyright (c) 2017,
* All Rights Reserved.
*
*
* \file UGDir.h
* \brief 类声明
*
* \author 
* \date 2017年04月28日
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
	//按path的指定创建所有目录和子目录
	static bool CreateDir(const string& strPath);

	//返回指定目录中的直接子文件/目录名称。不包括"."和".."
	static int GetSubPaths(std::vector<string>& vPathNames, const string& strPath);

	//返回指定目录中与指定搜索模式匹配的直接子文件/目录名称。不包括"."和".."
	static int GetSubPaths(std::vector<string>& vPathNames, const string& strPath, const string& strNameFilter);

	//返回指定目录中与指定搜索模式匹配的文件/目录名称，并使用某个值确定是否在子目录中搜索。不包括"."和".."
	static int GetSubPaths(std::vector<string>& vPathNames, const string& strPath, const string& strNameFilter, bool bRecursive);

	//返回指定目录中的直接子文件名称。不包括"."和".."
	static int GetFiles(std::vector<string>& vFileNames, const string& strPath);

	//返回指定目录中与指定搜索模式匹配的直接子文件名称。不包括"."和".."
	static int GetFiles(std::vector<string>& vFileNames, const string& strPath, const string& strNameFilter);

	//返回指定目录中与指定搜索模式匹配的文件名称，并使用某个值确定是否在子目录中搜索。不包括"."和".."
	static int GetFiles(std::vector<string>& vFileNames, const string& strPath, const string& strNameFilter, bool bRecursive);

	//返回指定目录中的直接子目录名称。不包括"."和".."
	static int GetDirectories(std::vector<string>& vDirNames, const string& strPath);

	//返回指定目录中与指定搜索模式匹配的直接子目录名称。不包括"."和".."
	static int GetDirectories(std::vector<string>& vDirNames, const string& strPath, const string& strNameFilter);

	//返回指定目录中与指定搜索模式匹配的目录，并使用某个值确定是否在子目录中搜索。不包括"."和".."
	static int GetDirectories(std::vector<string>& vDirNames, const string& strPath, const string& strNameFilter, bool bRecursive);
};


#endif //_UG_DIR_H
