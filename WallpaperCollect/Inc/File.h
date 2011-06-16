#ifndef ZMFILE_H
#define ZMFILE_H

//////////////////////////////////////////////////////////////////////////
//���������ļ���ZMFile�Ķ����ļ���ZMFile��һ���ļ������������
//���ߣ��γ�
//////////////////////////////////////////////////////////////////////////

// class ZMList;

class /*ZMDLL_EXPORT*/ FileOp
{
public:
	FileOp(void);
	virtual ~FileOp(void);

	//��ȡ����ʱ��(���غ���)
	static uint32 FileOp::GetTime(void);

	//��ȡϵͳ��ǰʱ��
	static ZMTIME ZMGetLocalTime(void);

	//��ȡ�ļ��޸�ʱ��:0 ����ʱ��;1 ����ʱ��;2 �޸�ʱ��
	ZMTIME ZMGetFileTime(uint8 type = 2);
	
	//���Զ����Ƿ�ɹ�����һ���ļ�
	BOOL IsOpened() { return m_pFILE != INVALID_HANDLE_VALUE ; }

	//��һ���ļ�,ȫ���Զ����Ʒ�ʽ��
	BOOL open(const wchar* pFileName,uint8 openMode,uint8 shareMode = ZM_SHARE_RW);
	enum 
	{
		ZM_CREATE_W			= 0x1,		//�������ļ���ԭ�����ڵ�ɾ��
		ZM_OPEN_R_EXIST		= 0x2,		//���ļ��������������������ɶ�
		ZM_OPEN_W_EXIST		= 0x3,		//���ļ���������������������д
		ZM_OPEN_RW_EXIST	= 0x4,		//���ļ��������������������ɶ�д
		ZM_OPEN_R_ALWAYS	= 0x5,		//���ļ����������򴴽���Ȼ���
		ZM_OPEN_W_ALWAYS	= 0x6,		//���ļ����������򴴽���Ȼ��д
		ZM_OPEN_RW_ALWAYS	= 0x7		//���ļ����������򴴽���Ȼ���д
	};
	enum
	{
		ZM_SHARE_R		= 0x01,			//�����ļ���
		ZM_SHARE_W		= 0x02,			//�����ļ�д
		ZM_SHARE_RW		= 0x03,			//�����ļ���д
		ZM_SHARE_NONE	= 0x04			//�������ļ���д
	};

	//�ر�һ���ļ�
	BOOL close();

	//���ļ�
	uint32 read(int8* pBuf,uint32 size);

	//д�ļ�
	uint32 write(int8* pBuf,uint32 size);

	//�ѻ�������д��洢��
	BOOL  flush();

	//��c���Ե�fputs����
	void fputs(int8* pString);
	//��c���Ե�fgets����
	void fgets(int8* pString,uint32 bufsize);

	//�õ��ļ�����
	uint32 GetLength();
	//�ƶ��ļ���дָ��,����ָ��ĵ�ǰλ��
	BOOL seek(uint32 pos,uint8 from);
	enum
	{
		ZMFILE_SEEK_BEGIN,
		ZMFILE_SEEK_END,
		ZMFILE_SEEK_CURRENT
	};
	//�õ��ļ���дָ��ĵ�ǰλ��
	uint32 GetPosition();

	//�õ��ļ���
	const wchar* GetFileName();

	//�����ļ�����
	static BOOL MoveFile( wchar* pSourFName, wchar* pdestFName );
	static BOOL CopyFile( wchar* pSourFName, wchar* pdestFName );
	static BOOL DelFile(const wchar* pFileName);
	static BOOL RenameFile(wchar* pOldName,wchar* pNewName);
	static BOOL CreateDirectory(wchar* pPath);
// 	static BOOL DelOldFile(wchar* pFileName,uint8 outofday );
// 	static BOOL DelDirectory(wchar * dir,uint8 outofday=0, int waittime = 0 );
// 	static uint64 GetDiskFreeSpace(wchar * pPath);

// 	static ZMList* FindFile( const wchar* pDir );//����Ŀ¼�ļ���ע��·������Ҫ��\\��
protected:
	HANDLE 	m_pFILE;				//�ļ�ָ��
	wstring iFullPath;
	wstring iPath;
};



#endif





