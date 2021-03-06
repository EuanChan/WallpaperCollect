#pragma once

class CUtil
{
public:
	CUtil(void);
	~CUtil(void);
};

wstring splitFirstString(const wstring& longStr);  // 取出第一段不包含空格的字符串
BOOL MakeSurePathExists(const CString &path, bool fileNameIncluded);

string GB2UTF8(const string& sSrc);
string UTF82GB(const string& szSrc);
unsigned int UTF8Length(const wchar_t *uptr, unsigned int tlen);
void UTF8FromUCS2(const wchar_t *uptr, unsigned int tlen, char *putf, unsigned int len);
unsigned int UCS2Length(const char *s, unsigned int len);
unsigned int UCS2FromUTF8(const char *s, unsigned int len, wchar_t *tbuf, unsigned int tlen);
unsigned int ascii_to_utf8(const char * pszASCII, unsigned int lenASCII, char * pszUTF8);
int utf8_to_ascii(const char * pszUTF8, unsigned int lenUTF8, char * pszASCII);

//获取系统当前时间
TTime __declspec(dllexport) GetLocalTime(void);