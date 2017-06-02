#pragma once


// CHyperLinkButton

class CHyperLinkButton : public CButton
{
	DECLARE_DYNAMIC(CHyperLinkButton)

public:
	CHyperLinkButton();
	virtual ~CHyperLinkButton();

protected:
	DECLARE_MESSAGE_MAP()
public:
	CFont m_fontUnderline;   //鼠标移动到按钮上时的字体
	HCURSOR m_hCurHand;      //鼠标移动到按钮上时的光标
	BOOL m_bLBtnDown;        //鼠标左键是否按下
	BOOL m_bMouseOver;       //鼠标是否处于按钮上方
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
};


