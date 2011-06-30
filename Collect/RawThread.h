#if !defined(_CRAWTHREAD_H)
#define _CRAWTHREAD_H

typedef void (* RawThreadFunc)( void* );   //�߳�ִ�к���ָ��

class __declspec(dllexport) CRawThread
{
public:
	CRawThread();
	virtual ~CRawThread();

	bool Start( RawThreadFunc aFunc, void* aParam = NULL );
	void Stop();

protected:
	static DWORD WINAPI ThreadProc( void* aParam );	//�����̺߳���

	DWORD			iID;				//�߳�ID
	HANDLE			iHandle;			//�߳̾��
	RawThreadFunc	iThreadFunc;		//�û������̺߳���
	void*			iParam;				//�û��̲߳���
};

#endif  //_CRAWTHREAD_H
