#include "StdAfx.h"
#include "EButton.h"

void CEButton::DrawFrame(HDC& hdc, LPRECT rect)
{
	CPen pen;
	CBrush brush;
	int btnState = GetState();
	if ((btnState & BST_PUSHED) == BST_PUSHED)
	{
		pen.CreatePen(PS_SOLID, 1, frameColorPress);
		brush.CreateSolidBrush(frameColorPress);
	}
	else if (bHover)
	{
		pen.CreatePen(PS_SOLID, 1, frameColorNormal);
		brush.CreateSolidBrush(frameColorHover);		
	}
	else
	{
		pen.CreatePen(PS_SOLID, 1, frameColorHover);
		brush.CreateSolidBrush(frameColorNormal);
	}
	HPEN oldPen = (HPEN)SelectObject(hdc, (HGDIOBJ)pen);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, (HGDIOBJ)brush);
	::RoundRect(hdc, rect->left, rect->top, rect->right, rect->bottom, 5, 3);
	
	//FillRect(hdc, rect, brush);
	SelectObject(hdc, (HGDIOBJ)oldBrush);
	SelectObject(hdc, (HGDIOBJ)oldPen);
	DeleteObject(pen);
	DeleteObject(brush);
}

void CEButton::DrawText(HDC& hdc, LPRECT rect)
{
	//CFont *font = dc.GetCurrentFont();
	ATL::CString strText;
	GetWindowText(strText);
	SetBkMode(hdc, TRANSPARENT);
	::DrawText(hdc, strText, strText.GetLength(), rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER | DT_END_ELLIPSIS);
}