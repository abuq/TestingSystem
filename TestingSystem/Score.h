#pragma once
// CScore �Ի���

class CScore : public CDialogEx
{
	DECLARE_DYNAMIC(CScore)

public:
	CScore(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CScore();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	CString m_edit1;
	CString m_user;
	CString m_admission;
	CString m_id;
	CString m_question;
	CString m_true;
	CString m_speed;
	CString m_time;
	CString m_score;
	virtual BOOL OnInitDialog();
//	afx_msg void OnStnClickedStatic3();
	CString m_filename;
};
