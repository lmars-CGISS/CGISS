#include "stdafx.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include "Dir.h"
#include <io.h>
#include "gwAddonFunction.h"
int IsDirectory(const char *pszName,const string& FileFilter)
{
	FILE* pFile = fopen(pszName,"rb");
	if(pFile == NULL)
	{
		if(FileFilter == "*")
		{
			string strFile = pszName;
			//判断是否为GRID数据
			strFile = strFile + "\\w001001.adf";
			pFile = fopen(strFile.data(),"rb");
			if (pFile == NULL)
				return 0;
			else
			{
				fclose(pFile);
				return 3;
			}
		}
		if(FileFilter == "*.gdb")
		{
			string strFile = pszName;
			//判断是否为gdb数据
			strFile = strFile + "\\a00000000.gdbtable";
			pFile = fopen(strFile.data(),"rb");
			if (pFile == NULL)
				return 0;
			else
			{
				fclose(pFile);
				return 2;
			}
		}

	}
	else
	{
		fclose(pFile);
		return 1;
	}
}

bool IsDir(const string& strPath)
{
	FILE* pFile = fopen(strPath.data(),"rb");
	if(pFile == NULL)
	{
		string Ext = "";
		if(strPath.find_last_of(".")!=-1)
			Ext = strPath.substr(strPath.find_last_of("."),strPath.length()-strPath.find_last_of("."));
		if(Ext == "*.gdb")
		{
			return false;
		}
		return true;
	}
	else
	{
		fclose(pFile);
		return false;
	}
}

bool gwDir::CreateDir(const string& strPath)
{
	string strAbsolutePath = strPath;
	wchar_t* szPath = gwAddonFunction::CharToWchar(strAbsolutePath.data());

	int nSize = strAbsolutePath.size();
	for(int i = 0; i < nSize; i++)
	{
		if( (i == nSize-1)
			|| (i > 0 && i < nSize-1 && ('/' == szPath[i] || '\\' == szPath[i])) )
		{   
			if(i != nSize-1)
				szPath[i]   =   '\0';   

			if( _waccess(szPath, 0) !=0  ) 
			{
				if(_wmkdir(szPath) != 0)
				{
					delete[] szPath;
					szPath = NULL;
					return false;
				}
			}
			if(i != nSize-1)
				szPath[i]   =   '\\';
		} //end of if
	} //end of for
	delete[] szPath;
	szPath = NULL;
	return true;
}


class PathFuncObj
{
public:
	typedef enum
	{
		All,
		Dir,
		File,
	}PathType;

	explicit PathFuncObj(PathType t) : m_t(t) { }

	bool operator()(const string& strPath)
	{
		switch(m_t)
		{
		case Dir:
			return IsDir(strPath);
		case File:
			return !IsDir(strPath);
		default:
			return true;
		}
	}

private:
	PathType m_t;
};

template <typename F>
int GetDirectChildren(std::vector<string>& vChildren,
					  const string& strPath, const string& strNameFilter, F func)
{	
	if(IsDirectory(strPath.data(),strNameFilter)!=0)
	{
		return 0;
	}

	struct _wfinddata_t c_file;
	intptr_t hFile;
	string strFind = strPath;
	string strFinds = "";
	if(strPath.find_last_of("/") == strPath.length() - 1||
		strPath.find_last_of("\\") == strPath.length() - 1)
	{
		strFinds =strPath+ (char*)strNameFilter.data();
	}
	else
	{
		strFinds = strPath + "\\" + (char*)strNameFilter.data();
	}

	wchar_t* wcFind = gwAddonFunction::CharToWchar(strFinds.data());
	if( (hFile = _wfindfirst(wcFind, &c_file )) == -1L )
		return 0;
	delete[] wcFind;
	wcFind = NULL;
	do
	{
		//排除"."和".."
		if(wcscmp(L".", c_file.name) == 0 || wcscmp(L"..", c_file.name)==0)
			continue;
		string strFile = "";
		string strFileName = "";
		strFind = strPath;
		if(strPath.find_last_of("/") == strPath.length() - 1||
			strPath.find_last_of("\\") == strPath.length() - 1)
		{
			char* FileName = gwAddonFunction::WcharToChar(c_file.name);
			strFileName = FileName;
			strFile = strFind.append(FileName) ;
			delete[] FileName;
			FileName = NULL;
		}
		else
		{
			strFile = strFind.append("\\");
			char* FileName = gwAddonFunction::WcharToChar(c_file.name);
			strFileName = FileName;
			strFile = strFile.append(FileName) ;
			delete[] FileName;
			FileName = NULL;
		}
		if( func(strFile) )
		{
			vChildren.push_back( strFile );
		}

	} while( _wfindnext( hFile, &c_file ) == 0 );

	_findclose(hFile);
	return vChildren.size();
}

int gwDir::GetSubPaths(std::vector<string>& vPathNames, const string& strPath)
{
	return GetSubPaths(vPathNames, strPath, "*", false);
}

int gwDir::GetSubPaths(std::vector<string>& vPathNames, const string& strPath, const string& strNameFilter)
{
	return GetSubPaths(vPathNames, strPath, strNameFilter, false);
}

int gwDir::GetSubPaths(std::vector<string>& vPathNames, const string& strPath, const string& strNameFilter, bool bRecursive)
{
	GetDirectChildren<PathFuncObj>(vPathNames, strPath, strNameFilter, PathFuncObj(PathFuncObj::All) );
	if(!bRecursive)
		return vPathNames.size();

	std::vector<string> vDirs;
	GetDirectChildren<PathFuncObj>(vDirs, strPath, "*", PathFuncObj(PathFuncObj::Dir));
	int nDirCount = vDirs.size();
	for(int i = 0; i < nDirCount; i++)
	{
		const string& strDir = vDirs[i];
		GetSubPaths(vPathNames, strDir, strNameFilter, bRecursive);
	}

	return vPathNames.size();
}

int gwDir::GetFiles(std::vector<string>& vFileNames, const string& strPath)
{
	return GetFiles(vFileNames, strPath, "*", false);
}

int gwDir::GetFiles(std::vector<string>& vFileNames, const string& strPath, const string& strNameFilter)
{
	return GetFiles(vFileNames, strPath, strNameFilter, false);
}

int gwDir::GetFiles(std::vector<string>& vFileNames, const string& strPath, const string& strNameFilter, bool bRecursive)
{
	GetDirectChildren<PathFuncObj>(vFileNames, strPath, strNameFilter, PathFuncObj(PathFuncObj::File));
	if(!bRecursive)
		return vFileNames.size();

	std::vector<string> vDirs;
	GetDirectChildren<PathFuncObj>(vDirs, strPath, "*", PathFuncObj(PathFuncObj::Dir));
	int nDirCount = vDirs.size();
	for(int i = 0; i < nDirCount; i++)
	{
		const string& strDir = vDirs[i];
		GetFiles(vFileNames, strDir, strNameFilter, bRecursive);
	}

	return vFileNames.size();
}

int gwDir::GetDirectories(std::vector<string>& vDirNames, const string& strPath)
{
	return GetDirectories(vDirNames, strPath, "*", false);
}

int gwDir::GetDirectories(std::vector<string>& vDirNames, const string& strPath, const string& strNameFilter)
{
	return GetDirectories(vDirNames, strPath, strNameFilter, false	);
}

int gwDir::GetDirectories(std::vector<string>& vDirNames, const string& strPath, const string& strNameFilter, bool bRecursive)
{
	GetDirectChildren<PathFuncObj>(vDirNames, strPath, strNameFilter, PathFuncObj(PathFuncObj::Dir));
	if(!bRecursive)
		return vDirNames.size();

	int nDirCount = vDirNames.size();
	for(int i = 0; i < nDirCount; i++)
	{
		const string& strDir = vDirNames[i];
		GetDirectories(vDirNames, strDir, strNameFilter, bRecursive);
	}

	return vDirNames.size();
}
