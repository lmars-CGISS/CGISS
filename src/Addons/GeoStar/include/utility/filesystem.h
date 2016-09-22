#pragma once
#include "preconfig.h" 
#include <stringhelp.h>
#include <vectorhelp.h>
UTILITY_NS 

/// \brief 文件路径相关的操作静态函数
class GS_API GsFileSystem
{
public:
	/// \brief 文件路径的的分隔符
	static char PathSeparator();
	/// \brief 判断文件路径、目录路径是否存在
	/// \param strFile 文件或者目录的路径
    ///\return 返回路径是或否存在
	static bool Exists(const char* strPath);

	/// \brief 工作目录
	static GsString WorkingFolder();

	/// \brief 当前执行文件所在的文件路径
	static GsString ModuleFileName();

	/// \brief 合并两个路径字符串
	/// \brief path1 第一个路径
	/// \brief path2 第二个路径
    ///\return 包含合并的路径的字符串。如果指定的路径之一是零长度字符串，则该方法返回其他路径。如果 path2 包含绝对路径，则该方法返回 path2
	static GsString Combine(const char* path1,const char* path2);

	
	/// \brief 从两个绝对路径计算相对路径
	/// \brief from 绝对路径，从这个绝对路径计算
	/// \brief to  绝对路径，计算该路径相对于from的相对路径
    ///\return 返回相对路径，如果输入路径无效则返回to
	static GsString PathRelativePathTo(const char* from,const char* to);


	
	/// \brief 判断一个路径是否是文件
	/// \brief path 路径
	///\return 返回路径是否是文件路径
	static bool IsFile(const char* strPath);


	/// \brief 获取一个值，该值指示指定的路径字符串是包含绝对路径信息还是包含相对路径信息。
	/// \brief path 要测试的路径
	///\return 如果 path 包含绝对路径，则为 true；否则为 false
	static bool IsPathRooted (const char* path);

};

class GsDir;

//// \brief 文件系统的文件
class GS_API GsFile
{
	GsString m_strPath;
public:
	
	/// \brief 拷贝构造函数
	/// \brief rhs拷贝的对象
	GsFile(const GsFile& rhs);

	/// \brief 文件的完整路径构造对象
	/// \brief strName文件完整路径
	GsFile(const char* strName);
	virtual ~GsFile();

	/// \brief 获取文件名称，不包含路径
    ///\return 返回文件的名称
	GsString Name(bool bHasExtension = true)const; 

	/// \brief 获取文件完整路径
    ///\return 返回文件的完整路径
	GsString FullPath()const;

	/// \brief 获取文件是否存在
    ///\return 返回文件是否存在
	bool Exists()const;
	
	/// \brief 获取文件的大小
    ///\return 返回文件大小，字节
	unsigned long long Size()const;
	 
	/// \brief 判断文件是否为同一个文件
	/// \brief rhs其他文件
    ///\return 传入文件是否和本文件为同一个文件
	bool operator == (const GsFile& rhs) const;

	/// \brief 赋值
	/// \brief rhs其他文件
    ///\return 自身
	GsFile& operator = (const GsFile& rhs) ;

	/// \brief 文件所在的目录
    ///\return 分返文件所在的目录
	GsDir Parent();


	/// \brief 文件的扩展名，(不带.)
    ///\return 返回文件的扩展名
	GsString Extension()const;
	
	/// \brief 改变文件路径的扩展名
	/// \details 注意并非修改文件的扩展名。
	/// \param strExt 新的扩展名，(不带.)
    /// \return 返回文件的扩展名
	GsString ChangeExtension(const char* strExt);

	/// \brief 将文件当作文本文件全部读取为字符串
	///\return 输出文件中读取的字符串
	GsString ReadAll() const;

	/// \brief 删除当前文件
	///\return 返回是否成功
	bool Delete();

	/// \brief 删除一个文件
	///\return 返回是否删除成功
	static bool Delete(const char* path);
};

/// \brief 文件系统的目录
class GS_API GsDir
{
	GsString m_strPath;
public:
	/// \brief 拷贝构造函数
	/// \brief rhs拷贝的对象
	GsDir(const GsDir& pDir);
	/// \brief 目录的完整路径构造对象
	/// \brief strName目录完整路径
	GsDir(const char* strDirPath);
	virtual ~GsDir();
	
	/// \brief 如果文件夹不存在则创建文件夹
	bool Create();

	/// \brief 目录的名称
    ///\return 返回目录的名称
	GsString Name() const; 

	/// \brief 目录的完整路径
    ///\return 返回目录的完整路径
	GsString FullPath()const;

	/// \brief 目录是否存在
    ///\return 返回目录是否存在
	bool Exists() const;
	
	/// \brief 是否为根目录
    ///\return 返回目录是否是跟目录
	bool IsRoot()  const;


	/// \brief 返回父目录
    ///\return 返回父目录
	GsDir Parent() const;

	/// \brief 目录下所有的文件
	/// \brief searchPattern搜索条件，比如*.txt
    ///\return 返回目录下的所有文件对象
	GsVector<GsFile> Files(const char* searchPattern = NULL)const;


	/// \brief 目录下所有的文件
	/// \brief files保存文件对象的集合
    ///\return 返回保存集合的指针
	GsVector<GsFile>* Files(GsVector<GsFile>& files)const;

	/// \brief 获取子目录
    ///\return 返回子目录对象
	GsDir  SubDir(const char* subName)const;
	
	/// \brief 获取目录下的文件
    ///\return 目录下的文件
	GsFile  File(const char* fileName)const;
	
	/// \brief 目录下所有的子目录
    ///\return 返回目录下的所有子目录对象
	GsVector<GsDir> Dirs()const;

	/// \brief 目录下所有的子目录
    ///\return 返回目录下的所有子目录对象
	GsVector<GsDir>* Dirs(GsVector<GsDir>& files)const;

	/// \brief 判断目录是否为同一个目录
	/// \brief rhs其他目录
    ///\return 传入目录是否和本目录为同一个文件
	bool operator == (const GsDir& rhs) const;

	/// \brief 赋值
	/// \brief rhs对象
    ///\return 自身
	GsDir& operator = (const GsDir& rhs) ;
	
	/// \brief 赋值
	/// \brief rhs对象
    ///\return 自身
	GsDir& operator = (const char* strDirPath) ;

	/// \brief 赋值
	/// \brief rhs对象
    ///\return 自身
	GsDir& operator = (const GsString& strDirPath) ;
 

	/// \brief 删除当前目录
	/// \brief param recursive 是否删除子目录
	///\return 返回是否成功
	bool Delete(bool recursive =true );

	/// \brief 删除一个目录
	///\return 返回是否删除成功
	static bool Delete(const char* path,bool recursive =true );
};
		

UTILITY_ENDNS