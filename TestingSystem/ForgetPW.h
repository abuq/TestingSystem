#pragma once


// CForgetPW �Ի���

class CForgetPW : public CDialogEx
{
	DECLARE_DYNAMIC(CForgetPW)

public:
	CForgetPW(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CForgetPW();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG4 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString m_edit1;
	CString m_edit2;
	CString m_edit3;
//	afx_msg void OnStnClickedStatic3();
	CString m_user;
	CString m_password;
	CString m_question1;
	CString m_question2;
	CString m_question3;
	afx_msg void OnKillfocusEdit6();
	afx_msg void OnBnClickedOk();
	afx_msg void OnChangeEdit6();
};
