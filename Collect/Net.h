#pragma once

#include "RawThread.h"
#include "RawCriSection.h"

class CWebServer;
class __declspec(dllexport) CNet
{
public:
	CNet();
	~CNet();

	void Start();
	void Pause();
	void Stop();
	void AddTask(const string& url, const wstring& savePath);
	void SaveUnfinishedTask();
	void LoadUnfinishedTask();
	bool UpdateProcess();

protected:
	static void ThreadFunc( void* aParam );
	void DoWork();

private:
	vector<TPicTaskInfo> taskInfoVec;
	vector<TPicTaskInfo>::iterator iter;

	CWebServer* webServ;

	bool onWork;
	CRawThread     rawThread;
	// 
	CRawCriSection rawCrisection;

	// ��¼����������������ʾ�����ܽ���
	uint16  taskCount;           
	uint16  taskFinishedCount;   // ȫ���������ʱ��0
};