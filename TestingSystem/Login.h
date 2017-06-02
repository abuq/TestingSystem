#pragma once
#include "HyperLinkButton.h"
#include "NewUser.h"
#include "ForgetPW.h"
#include "afxwin.h"

// CLogin �Ի���

class CLogin : public CDialogEx
{
	DECLARE_DYNAMIC(CLogin)

public:
	CLogin(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLogin();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CHyperLinkButton m_b1;
	CHyperLinkButton m_b2;
	CHyperLinkButton m_b3;
	afx_msg void OnClickedButton1();
	afx_msg void OnClickedButton2();
	virtual BOOL OnInitDialog();
	CString m_user;
	afx_msg void OnBnClickedOk();
	BOOL m_check;
	CComboBox m_combo1;
	afx_msg void OnCbnSelchangeCombo2();
	CString m_password;
	CString m_user1;
	CString m_user2;
	CString m_user3;
	afx_msg void OnCloseupCombo1();
	afx_msg void OnBnClickedButton3();
	int m_usernum;
};
