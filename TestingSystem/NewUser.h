#pragma once
#include "afxwin.h"


// CNewUser �Ի���

class CNewUser : public CDialogEx
{
	DECLARE_DYNAMIC(CNewUser)

public:
	CNewUser(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CNewUser();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG3 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnEnChangeEdit2();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	CComboBox m_combo1;
	CComboBox m_combo2;
	CComboBox m_combo3;
	int m_num;
	CString m_question1;
	CString m_question2;
	CString m_question3;
	CString m_user;
	CString m_password;
};
