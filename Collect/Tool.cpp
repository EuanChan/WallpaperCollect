#include "stdafx.h"
#include "Tool.h"
#include <io.h>

CUtil::CUtil(void)
{
}

CUtil::~CUtil(void)
{
}

wstring splitFirstString(const wstring& longStr)  // 取出第一段不包含空格的字符串
{
	CString str = longStr.c_str();
	str.TrimLeft();
	str = str.Left(str.Find(_T(" ")));
	return str.GetBuffer();
}

BOOL MakeSurePathExists(const CString &strPath, bool fileNameIncluded)
{
	int Pos=0;
	while ((Pos = strPath.Find('\\', Pos + 1)) != -1) 
		CreateDirectory(strPath.Left(Pos), NULL);
	if (!fileNameIncluded)
		CreateDirectory(strPath, NULL);

// 判断文件是否可读写
// 	return ((!fileNameIncluded) ? 
// 		!_access(strPath, 0) :
// 		!_access(strPath.Left(strPath.ReverseFind('\\')), 0));
	return true;
}

string GB2UTF8(const string& sSrc)
{
	string sRet;

	if(sSrc.length() > 0)
	{
		int iWLen = MultiByteToWideChar(936, 0, sSrc.c_str(), -1, NULL, 0);
		WCHAR* wc = new WCHAR[iWLen*sizeof(WCHAR)];
		MultiByteToWideChar(936, 0, sSrc.c_str(), -1, wc, iWLen);

		int iDesLen = WideCharToMultiByte(CP_UTF8, 0, wc, iWLen, NULL, 0, 0, 0);
		char* pBuf = new char[iDesLen+1];
		WideCharToMultiByte(CP_UTF8, 0, wc, iWLen, pBuf, iDesLen, 0, 0);
		sRet = pBuf;
		delete []pBuf;
		delete []wc;
	}

	return sRet;
}

// 将UTF8编码转化为GB2312
string UTF82GB(const string& szSrc)
{
	if(szSrc.length() > 0)
	{
		size_t iWLen = MultiByteToWideChar(CP_UTF8, 0, szSrc.c_str(), szSrc.length(), NULL, 0);
		WCHAR* wc = new WCHAR[iWLen + 1];
		MultiByteToWideChar(CP_UTF8, 0, szSrc.c_str(), szSrc.length(), wc, iWLen);
		wc[iWLen] = 0;

		int iDesLen = WideCharToMultiByte(936, 0, wc, -1, NULL, 0, 0, 0);
		char* pBuf = new char[iDesLen+1];
		WideCharToMultiByte(936, 0, wc, -1, pBuf, iDesLen, 0, 0);
		//pBuf[iDesLen] = 0;
		string sRet = pBuf;
		delete []pBuf;
		delete []wc;
		return sRet;
	}
	return NULL;
}


unsigned int UTF8Length(const wchar_t *uptr, unsigned int tlen) 
{
	unsigned int len = 0;
	for (unsigned int i = 0; i < tlen && uptr[i]; i++) {
		unsigned int uch = uptr[i];
		if (uch < 0x80)
			len++;
		else if (uch < 0x800)
			len += 2;
		else 
			len +=3;
	}
	return len;
}

void UTF8FromUCS2(const wchar_t *uptr, unsigned int tlen, char *putf, unsigned int len) 
{
	int k = 0;
	for (unsigned int i = 0; i < tlen && uptr[i]; i++) {
		unsigned int uch = uptr[i];
		if (uch < 0x80) {
			putf[k++] = static_cast<char>(uch);
		} else if (uch < 0x800) {
			putf[k++] = static_cast<char>(0xC0 | (uch >> 6));
			putf[k++] = static_cast<char>(0x80 | (uch & 0x3f));
		} else {
			putf[k++] = static_cast<char>(0xE0 | (uch >> 12));
			putf[k++] = static_cast<char>(0x80 | ((uch >> 6) & 0x3f));
			putf[k++] = static_cast<char>(0x80 | (uch & 0x3f));
		}
	}
	putf[len] = '\0';
}

unsigned int UCS2Length(const char *s, unsigned int len) 
{
	unsigned int ulen = 0;
	for (unsigned int i=0;i<len;i++) {
		UCHAR ch = static_cast<UCHAR>(s[i]);
		if ((ch < 0x80) || (ch > (0x80 + 0x40)))
			ulen++;
	}
	return ulen;
}

unsigned int UCS2FromUTF8(const char *s, unsigned int len, wchar_t *tbuf, unsigned int tlen)
{
	unsigned int ui=0;
	const UCHAR *us = reinterpret_cast<const UCHAR *>(s);
	unsigned int i=0;
	while ((i<len) && (ui<tlen)) {
		UCHAR ch = us[i++];
		if (ch < 0x80) {
			tbuf[ui] = ch;
		} else if (ch < 0x80 + 0x40 + 0x20) {
			tbuf[ui] = static_cast<wchar_t>((ch & 0x1F) << 6);
			ch = us[i++];
			tbuf[ui] = static_cast<wchar_t>(tbuf[ui] + (ch & 0x7F));
		} else {
			tbuf[ui] = static_cast<wchar_t>((ch & 0xF) << 12);
			ch = us[i++];
			tbuf[ui] = static_cast<wchar_t>(tbuf[ui] + ((ch & 0x7F) << 6));
			ch = us[i++];
			tbuf[ui] = static_cast<wchar_t>(tbuf[ui] + (ch & 0x7F));
		}
		ui++;
	}
	return ui;
}


unsigned int ascii_to_utf8(const char * pszASCII, unsigned int lenASCII, char * pszUTF8)
{
	// length of pszUTF8 must be enough; 
	// its maximum is (lenASCII*3 + 1)

	if (!lenASCII || !pszASCII)
	{
		pszUTF8[0] = 0;
		return 0; 
	}

	unsigned int lenUCS2;
	unsigned int lenUTF8;
	wchar_t *pszUCS2 = new wchar_t[lenASCII * 3 + 1];
	if (!pszUCS2)
	{
		pszUTF8[0] = 0;
		return 0; 
	}

	lenUCS2 = ::MultiByteToWideChar(CP_ACP, 0, pszASCII, lenASCII, pszUCS2, lenASCII + 1);
	lenUTF8 = UTF8Length(pszUCS2, lenUCS2);
	// length of pszUTF8 must be >= (lenUTF8 + 1)
	UTF8FromUCS2(pszUCS2, lenUCS2, pszUTF8, lenUTF8);
	delete [] pszUCS2;
	return lenUTF8;
}

int utf8_to_ascii(const char * pszUTF8, unsigned int lenUTF8, char * pszASCII)
{
	// length of pszASCII must be enough;
	// its maximum is (lenUTF8 + 1)

	if (!lenUTF8 || !pszUTF8)
	{
		pszASCII[0] = 0;
		return 0;
	} 

	unsigned int lenUCS2;
	wchar_t*     pszUCS2;

	pszUCS2 = new wchar_t[lenUTF8 + 1];
	if (!pszUCS2)
	{
		pszASCII[0] = 0;
		return 0;
	}

	lenUCS2 = UCS2FromUTF8(pszUTF8, lenUTF8, pszUCS2, lenUTF8);
	pszUCS2[lenUCS2] = 0;
	// length of pszASCII must be >= (lenUCS2 + 1)
	int nbByte = ::WideCharToMultiByte(CP_ACP, 0, pszUCS2, lenUCS2, pszASCII, lenUCS2 + 1, NULL, NULL);
	delete [] pszUCS2;
	return nbByte;
}

TTime GetLocalTime(void)	
{
	SYSTEMTIME systemtime;
	TTime time;
	::GetLocalTime(&systemtime);

	time.wYear	= systemtime.wYear;
	time.wMonth	= (uint8)systemtime.wMonth;
	time.wDay	= (uint8)systemtime.wDay;
	time.wHour	= (uint8)systemtime.wHour;
	time.wMinute	= (uint8)systemtime.wMinute;
	time.wSecond	= (uint8)systemtime.wSecond;
	time.wMilliseconds = systemtime.wMilliseconds;

	return time;
}
