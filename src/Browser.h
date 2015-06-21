/*-------------------------------------------------------------------
* Purpose:
*         This file defines the structures, values, macros, and functions
* Time:
*         2011��9��18�� 21:37:41
* Author:
*         ������
--------------------------------------------------------------------*/

#ifndef _BROWSER_H_2011_9_18_lisency
#define _BROWSER_H_2011_9_18_lisency

#include <stdlib.h>
#include <vector>
#include <string>

#include "Util.h"

EF_NAMESPACE_BEGIN

class   CBrowseDir
{
protected:
	//��ų�ʼĿ¼�ľ���·������'\'��β
	char   m_szInitDir[_MAX_PATH];

public:
	//ȱʡ������
	CBrowseDir();

	//���ó�ʼĿ¼Ϊdir���������false����ʾĿ¼������
	bool   SetInitDir(const   char   *dir);

	//��ʼ������ʼĿ¼������Ŀ¼����filespecָ�����͵��ļ�
	//filespec����ʹ��ͨ���   *   ?�����ܰ���·����
	//�������false����ʾ�������̱��û���ֹ
	bool   BeginBrowse(const   char   *filespec);

protected:
	//����Ŀ¼dir����filespecָ�����ļ�
	//������Ŀ¼,���õ����ķ���
	//�������false,��ʾ��ֹ�����ļ�
	bool   BrowseDir(const   char   *dir,const   char   *filespec);

	//����BrowseDirÿ�ҵ�һ���ļ�,�͵���ProcessFile
	//�����ļ�����Ϊ�������ݹ�ȥ
	//�������false,��ʾ��ֹ�����ļ�
	//�û����Ը�д�ú���,�����Լ��Ĵ������
	virtual   bool   ProcessFile(const   char   *filename);

	//����BrowseDirÿ����һ��Ŀ¼,�͵���ProcessDir
	//�������ڴ����Ŀ¼������һ��Ŀ¼����Ϊ�������ݹ�ȥ
	//������ڴ�����ǳ�ʼĿ¼,��parentdir=NULL
	//�û����Ը�д�ú���,�����Լ��Ĵ������
	//�����û�����������ͳ����Ŀ¼�ĸ���
	virtual   void   ProcessDir(const   char
		*currentdir,const   char   *parentdir);
};


class BrowseFiles
	:public CBrowseDir
{
public:
	BrowseFiles();
	~BrowseFiles();
	std::vector<std::string> getFileList();
protected:
	std::vector<std::string> file_list;
	virtual bool ProcessFile(const   char   *filename);
	virtual void ProcessDir(const char *currentdir,const char *parentdir);
private:
};


EF_NAMESPACE_END

#endif // _BROWSER_H_2011_9_18_lisency

