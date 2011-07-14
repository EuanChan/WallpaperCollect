// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#include "MainDlg.h"
#include "PathInfo.h"


void CMainDlg::Init()
{
	TTime t = GetLocalTime();	
	char pOut[128] = {0};
	sprintf( pOut, "--------------------[%d-%02d-%02d]--------------", 
		t.wYear, t.wMonth, t.wDay );
	tTestLog( pOut );

	SetMsgRecvWindowH(this->m_hWnd);

	channelAtt = new TChannelInfo();

	//wstring cachePath = gPathInfo->CachePath();
	wpCol.SetSite("http://www.deskcity.com/");
	wpCol.ColChannelTree(channelAtt);
}

void CMainDlg::Release()
{
	delete channelAtt;
	
	size_t size = collectInfoVec.size();
	while (size-- > 0)
	{
		delete collectInfoVec[0];
		collectInfoVec.erase(collectInfoVec.begin());
	}
}

LRESULT CMainDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// ��ʼ��Ƶ����
	Init();

	//////////////////////////////////////////////////////////////////////////
	// center the dialog on the screen
	CenterWindow();

	// set icons
	HICON hIcon = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), 
		IMAGE_ICON, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON), LR_DEFAULTCOLOR);
	SetIcon(hIcon, TRUE);
	HICON hIconSmall = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), 
		IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
	SetIcon(hIconSmall, FALSE);
	
	dlgBkBrush.CreateSolidBrush(DLG_BK_COLOR);    // 
		
	//////////////////////////////////////////////////////////////////////////
	// channelTree
	channelTree.SubclassWindow(GetDlgItem(IDC_CHANNEL_TREE));
	channelTree.InitWithChannelAtt(channelAtt);

	// 
	picWallView.SubclassWindow(GetDlgItem(IDC_LIST_PIC));
	picWallView.SetExtendedListViewStyle(LVS_EX_CHECKBOXES);

	// Menu
	menuChannelTree.Attach(LoadMenu( _Module.GetResourceInstance(),MAKEINTRESOURCE(IDR_MENU_CHANNEL)));

	// Edit Ctrl
	savePathEdit.Attach(GetDlgItem(IDC_EDIT_SAVEDIR));

	// Progress bar
	progressTotal.Attach(GetDlgItem(IDC_PROGRESS_TOTAL));
	progressTotal.SetRange(0, 100);
	progressCur.Attach(GetDlgItem(IDC_PROGRESS_CUR));
	progressCur.SetRange(0, 100);

	// Button
	btnChangeDir.SubclassWindow(GetDlgItem(IDC_BTN_CHANGE_DIR));
	btnPause.SubclassWindow(GetDlgItem(IDC_BTN_PAUSE));
	long style;
	style = btnPause.GetWindowLong(GWL_STYLE);
	style |= WS_DISABLED;
	btnPause.SetWindowLong(GWL_STYLE, style);

	// SavePath
	wstring str = gPathInfo->GetSavePathRoot();
	savePathRoot = str.c_str();
	DoDataExchange(false);

	return TRUE;
}

LRESULT CMainDlg::OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CSimpleDialog<IDD_ABOUTBOX, FALSE> dlg;
	dlg.DoModal();
	return 0;
}

LRESULT CMainDlg::OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	EndDialog(0);
	return 0;
}

// �޸ı�ֽ�����·��
LRESULT CMainDlg::OnBnClickedBtnChangeDir(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	BROWSEINFO bi;
	wchar Buffer[MAX_PATH];
	bi.hwndOwner = NULL;
	bi.pidlRoot =NULL;    
	bi.pszDisplayName = Buffer;
	bi.lpszTitle = _T("�޸ı�ֽ��Ÿ�·��");
	bi.ulFlags = BIF_NEWDIALOGSTYLE | BIF_EDITBOX;
	bi.lpfn = NULL;
	bi.iImage = IDR_MAINFRAME;
	LPITEMIDLIST pIDList = SHBrowseForFolder(&bi);
	if(pIDList)
	{
		SHGetPathFromIDList(pIDList, Buffer);
		savePathRoot = Buffer;
		gPathInfo->SetSavePathRoot(savePathRoot.GetString());
		
		// TODO: �ƶ��������ļ���

		DoDataExchange(false);
	}
	LPMALLOC lpMalloc;
	if(FAILED(SHGetMalloc(&lpMalloc))) return 0;

	lpMalloc->Free(pIDList);
	lpMalloc->Release();

	RefreshControl(IDC_EDIT_SAVEDIR);

	return 0;
}

LRESULT CMainDlg::OnBnClickedBtnPause(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	return 0;
}

// ѡ���µ����ڵ㣬���¼��б�
LRESULT CMainDlg::OnTvnSelchangedChannelTree(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& bHandled)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);

 	if (pNMTreeView->itemNew.lParam == 0)
 		return 0;

	HTREEITEM selItem = pNMTreeView->itemNew.hItem;
	string url = (char*)pNMTreeView->itemNew.lParam;

	// ��ѯ�Ƿ񱾵����л���
	for (int i = 0; i < collectInfoVec.size(); i++)
	{
		if (url == collectInfoVec[i]->url)
		{
			picWallView.InitWithCollectInfo(collectInfoVec[i]);
			return 0;
		}
	}

	// 
	TPackagePageInfo *collectInfo = new TPackagePageInfo();
	collectInfo->url = url;
	if (wpCol.GetPackagePagesInfo(url, collectInfo))
	{
		collectInfoVec.push_back(collectInfo);
		picWallView.InitWithCollectInfo(collectInfo);
		netThumbnail.Start();
	}
	else
	{
		delete collectInfo;
		return 0;
	}

	// Add thumbnail to download task
	vector<TCollectInfo>::iterator iter = collectInfo->collectInfoVec.begin();
	for (; iter != collectInfo->collectInfoVec.end(); ++iter)
	{
		// TODO: ��Ϊ hash��ӿ��ѯ
		if (INVALID_FILE_ATTRIBUTES != GetFileAttributes(iter->thumbSavePath.c_str()))
			continue;
		netThumbnail.AddTask(iter->thumbUrl, iter->thumbSavePath);
		SetWallpaperCollectEvent();
	}

	return 0;
}

// �޸�ѡ��״̬
LRESULT CMainDlg::OnNMClickListPic(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& /*bHandled*/)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if(pNMListView->iItem != -1)
	{
		bool checked = picWallView.GetCheckState(pNMListView->iItem);
		picWallView.SetCheckState(pNMListView->iItem, checked ? false : true);
	}

	return 0;
}

// �������ز˵�
LRESULT CMainDlg::OnNMRclickListPic(int /*idCtrl*/, LPNMHDR pNMHDR, BOOL& /*bHandled*/)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	POINT point = pNMListView->ptAction; 
	GetCursorPos(&point); 
	ScreenToClient(&point);
	CMenu menu;
	if (menu.LoadMenu(IDR_MENU_LIST_OUT))
	{
		CMenuHandle menuH = menu.GetSubMenu(0);
		ClientToScreen(&point);
		if(pNMListView->iItem != -1)  
		{
			menu.EnableMenuItem(ID_DOWNLOAD_PICS, MF_ENABLED);
		}
		else
		{
			menu.EnableMenuItem(ID_DOWNLOAD_PICS, MF_DISABLED);
		}
		menuH.TrackPopupMenu(TPM_RIGHTBUTTON, point.x, point.y, this->m_hWnd);
	}
	return 0;
}

// ���ص�ǰ��
LRESULT CMainDlg::OnDownloadPackage(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	wstring savePath = GetSavePathByChannelTreeState();

	// Get Item Data.
	int index = picWallView.GetHotItem();
	if (index == -1)
		return 0;
	TCollectInfo* pInfo = (TCollectInfo*)picWallView.GetItemData(index);
	if (pInfo)
	{
		//tTestLog("Add Task:" << pInfo->linkUrl.c_str() << "  ---  " << pInfo->displayName.c_str());
		wpCol.AddTask(pInfo->linkUrl, savePath, ECmdColPicListPage);
		wpCol.Start();
		bool ret = SetWallpaperCollectEvent();
		picWallView.DeleteItem(index);
	}

	return 0;
}

// ��������ѡ�м�
LRESULT CMainDlg::OnDownloadSelectPackage(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: ������ѡ���޷�һ���Լ������
	size_t itemCount = picWallView.GetItemCount();
	wstring savePath = GetSavePathByChannelTreeState();

	for (size_t i = 0; i < itemCount; i++)
	{
		if (picWallView.GetCheckState(i))
		{
			TCollectInfo* pInfo = (TCollectInfo*)picWallView.GetItemData(i);
			if (pInfo)
			{
				wpCol.AddTask(pInfo->linkUrl, savePath, ECmdColPicListPage);
				picWallView.DeleteItem(i);
			}
		}
	}
	wpCol.Start();
	SetWallpaperCollectEvent();

	return 0;
}

// ���������ϼ�
LRESULT CMainDlg::OnDownloadCollect(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	// TODO: �ڴ���������������
	CTreeItem item = channelTree.GetSelectedItem();
	DWORD_PTR ptr = (DWORD_PTR)item.GetData();
	if (!ptr) return 0;

	string url = (char*)(item.GetData());
	wchar lpStr[MAX_PATH];
	memset(lpStr, 0, MAX_PATH);
	item.GetParent().GetText((LPTSTR)lpStr, MAX_PATH);
	wcscat(lpStr, _T("\\"));
	wstring rootPath = gPathInfo->GetSavePathRoot();
	rootPath.append(lpStr);

	// ���÷����̷߳�������
	wpCol.AddTask(url, rootPath, ECmdColPackagePages);
	wpCol.Start();
	SetWallpaperCollectEvent();
	return 0;
}

LRESULT CMainDlg::OnSelectAll(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	size_t itemCount = picWallView.GetItemCount();
	for (size_t i = 0; i < itemCount; i++)
	{
		picWallView.SetCheckState(i, true);
	}

	return 0;
}

LRESULT CMainDlg::OnSelectInvert(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	size_t itemCount = picWallView.GetItemCount();
	for (size_t i = 0; i < itemCount; i++)
	{
		bool checked = picWallView.GetCheckState(i);
		picWallView.SetCheckState(i, checked ? false : true);
	}

	return 0;
}

wstring CMainDlg::GetSavePathByChannelTreeState()
{
	wstring path = gPathInfo->GetSavePathRoot();

	CTreeItem item = channelTree.GetSelectedItem();
	if (item.GetData() == 0)  // ��ǰѡ��Ϊ���ڵ�
	{
		// TODO: ѡ�������ڵ�ʱ��Ҫ�������ط���ȡ����·��
		// TODO: ���� picWallView.collectName ��channelTree���ҵ����ڵ�
		MessageBox(_T("TODO: ·��δ���壬���浽��Ŀ¼��'unknown'Ŀ¼��"));
		path.append(_T("unknown\\"));
		return path;
	}
	else
	{
		wchar lpStr[MAX_PATH];
		memset(lpStr, 0, MAX_PATH);
		item.GetParent().GetText((LPTSTR)lpStr, MAX_PATH);
		wcscat(lpStr, _T("\\"));
		path.append(lpStr);
		item.GetText((LPTSTR)lpStr, MAX_PATH);
		wcscat(lpStr, _T("\\"));
		path.append(lpStr);
		return path;
	}
}

LRESULT CMainDlg::OnUpdateTotalProgress(UINT /*uMsg*/, WPARAM wParam, LPARAM lParam, BOOL& /*bHandled*/)
{
	if (progressTotal.m_hWnd)
		progressTotal.SetPos((float)wParam / (float)lParam * 100);

	ATL::CString str;
	str.Format(_T("%d / %d"), wParam, lParam);
	GetDlgItem(IDC_PROGRESS_TOTAL_TXT).SetWindowText(str);
	RefreshControl(IDC_PROGRESS_TOTAL_TXT);

	return 0;
}

LRESULT CMainDlg::OnUpdateCurProgress(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	if (progressTotal.m_hWnd)
		progressCur.SetPos(wParam);
	return 0;
}

LRESULT CMainDlg::OnUpdateCurPicName(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	ATL::CString str = (wchar*)wParam;
	GetDlgItem(IDC_CUR_PIC_NAME).SetWindowText(str);
	RefreshControl(IDC_CUR_PIC_NAME);
	return 0;
}

LRESULT CMainDlg::ONNotifyThumbPicFinished(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// TODO: ��Ҫ�����ַ������ͷš�
	char http[5];
	memset(http, 0, 5);
	memcpy(http, (void *)wParam, 4);
	if (strcmp("http", http) != 0)
		return 0;

	string url = (char*)wParam;
	picWallView.UpdateItem(url);
	return 0;
}

LRESULT CMainDlg::OnCtlColorStatic(UINT /*uMsg*/, WPARAM wParam, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// ����static�ؼ�͸��
	SetBkMode((HDC)wParam, TRANSPARENT);

	// return a null brush so image behind static isn't erased
	return (LRESULT)::GetStockObject(NULL_BRUSH);
}

LRESULT CMainDlg::OnCtlColorDlg(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	return (LRESULT)(HGDIOBJ)dlgBkBrush;  
}

void CMainDlg::RefreshControl(UINT uCtlID)
{
	RECT rc;
	GetDlgItem(uCtlID).GetWindowRect(&rc);   
	ScreenToClient(&rc);     
	InvalidateRect(&rc); 
}
