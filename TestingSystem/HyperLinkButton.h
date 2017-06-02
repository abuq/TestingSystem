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
	CFont m_fontUnderline;   //����ƶ�����ť��ʱ������
	HCURSOR m_hCurHand;      //����ƶ�����ť��ʱ�Ĺ��
	BOOL m_bLBtnDown;        //�������Ƿ���
	BOOL m_bMouseOver;       //����Ƿ��ڰ�ť�Ϸ�
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
};


