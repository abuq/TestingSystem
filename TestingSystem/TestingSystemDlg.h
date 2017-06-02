
// TestingSystemDlg.h : 头文件
//

#pragma once
#include"Score.h"
#include "afxwin.h"
#include "afxcmn.h"
#include "Mmsystem.h"

// CTestingSystemDlg 对话框
class CTestingSystemDlg : public CDialogEx
{
// 构造
public:
	CTestingSystemDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TestingSystem_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
//	afx_msg void OnEnChangeEdit4();
	afx_msg void OnCbnSelchangeCombo1();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
	POINT old;
	CComboBox m_combo1;
	int m_total_minutes;
	int m_total_questions;
	int m_max_speed;
	int m_second, m_minute, m_hour;
	CFont m_font;
	CBrush m_brush;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CString m_timer;
	CStatic m_edit1;
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void ReSize(void);
	// 身份证信息18位带X
	CString m_id;
	CString m_admission;
	CListCtrl m_ctrList;
	CString m_user;
	void OnPlay();
	void OnStop();
	MCI_OPEN_PARMS op;
	int GetInfo(UINT wDeviceID, DWORD item);
	afx_msg void OnCloseupCombo1();
	CString m_musicnum;
	void GetFileFromDir();
	int *m_musicstype;
	float Similarity(CString str1, CString str2);
	CString m_edit4;
	bool m_IsEnd;
	afx_msg void OnSetfocusEdit4();
	int m_use;
	int m_speed;
	double m_percentage_accuracy;
	double m_percentage_speed;
	float m_accuracy;
	CString ReadText(CString str);
	double m_score;
	afx_msg void OnChangeEdit1();
	afx_msg void OnDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
	bool Is;
	CString Exchange(CString str);
};
