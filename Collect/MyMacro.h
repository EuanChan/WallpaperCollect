#ifndef MYMACRO_H
#define MYMACRO_H

// ��������Ԫ�ظ���
#define COUNTOF(array) (sizeof(array) / sizeof(array[0]))

#define MEMSTZERO(x,y) memset(x,0x00,sizeof(y))
#define MEMBUFZERO(x)  memset(x,0x00,sizeof(x))

// ��ȫ���ַ�����
#define SAFESTRNCPY(x,y)  strncpy(x,y,sizeof(x)); x[sizeof(x) -1] =0x00;

// ��ȫ�ͷ�ָ��
#define SAFE_RELEASE(p) {if ((p)) { (p)->Release(); (p) = NULL; }}

// ��ȫɾ��ָ��(������ָ��)
#define SAFE_DELETE(p) {if ((p) != NULL) { delete (p); (p) = NULL; }}

// ��ȫ���ٴ���
#define SAFE_DESTROYWINDOW(hwnd) {if (::IsWindow((hwnd))){::DestroyWindow(hwnd);}}

// ���ʽ������ֵ
#define IFTF(b,setf1) {if (!(b)){(setf1) = 0;}}


//////////////////////////////////////////////////////////////////////////
void*& GetPtrByName( const char* aName );

#define MakeObjPtrFun( name, fun ) \
	inline void*& fun() \
{ \
	static void*& ptr = GetPtrByName( #name ); \
	return ptr; \
}

#endif