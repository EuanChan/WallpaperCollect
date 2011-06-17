#ifndef CHTMLPARSE_H
#define CHTMLPARSE_H

#include "ComDef.h"

class CHtmlParse
{
public:
	CHtmlParse(const string& htmlSource);
	~CHtmlParse(void);
	void ResetSrc(const string& htmlSource);

	
	// ����������� page1 url����ҳԴ�� pageLevel2
	TPackagePageAttri GetWallpaperPagesUrl(const TSiteInfo& siteInfo);
	// �������� ��ֽͼƬurl�� ��ҳԴ�� pageLevel1
	TPicshowPageAttri GetWallpaperImgUrl(const TSiteInfo& siteInfo);

private:
	string   htmlSrc;
};

#endif