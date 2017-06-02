// Login.cpp : 实现文件
//

#include "stdafx.h"
#include "TestingSystem.h"
#include "Login.h"
#include "afxdialogex.h"


// CLogin 对话框

IMPLEMENT_DYNAMIC(CLogin, CDialogEx)

CLogin::CLogin(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG2, pParent)
	, m_user(_T(""))
	, m_password(_T(""))
	, m_check(FALSE)
	, m_user1(_T(""))
	, m_user2(_T(""))
	, m_user3(_T(""))
	, m_usernum(0)
{

}

CLogin::~CLogin()
{
}

void CLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON1, m_b1);
	DDX_Control(pDX, IDC_BUTTON2, m_b2);
	DDX_Control(pDX, IDC_BUTTON3, m_b3);
	DDX_CBString(pDX, IDC_COMBO1, m_user);
	DDX_Check(pDX, IDC_CHECK1, m_check);
	DDX_Control(pDX, IDC_COMBO1, m_combo1);
	DDX_Text(pDX, IDC_EDIT2, m_password);
}


BEGIN_MESSAGE_MAP(CLogin, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &CLogin::OnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CLogin::OnClickedButton2)
	ON_BN_CLICKED(IDOK, &CLogin::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO2, &CLogin::OnCbnSelchangeCombo2)
	ON_CBN_CLOSEUP(IDC_COMBO1, &CLogin::OnCloseupCombo1)
	ON_BN_CLICKED(IDC_BUTTON3, &CLogin::OnBnClickedButton3)
END_MESSAGE_MAP()


// CLogin 消息处理程序


void CLogin::OnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CNewUser dlg;
	dlg.DoModal();
}


void CLogin::OnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	CForgetPW dlg;
	dlg.DoModal();
}


BOOL CLogin::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	DWORD dwAttr = GetFileAttributes(_T("..\\Users"));
	if (dwAttr == 0xFFFFFFFF)
		CreateDirectory(_T("..\\Users"), NULL);
	else if (dwAttr & FILE_ATTRIBUTE_DIRECTORY) 
	{
	}
	CString str, str1;
	m_usernum = GetPrivateProfileInt(_T("RecentUser"), _T("usernum"), NULL, _T("..\\0131122589\\config.ini"));
	for (int i = 0; i < m_usernum; i++)
	{
		str.Empty();
		str1.Format(_T("user%d"), i + 1);
		if (GetPrivateProfileString(_T("RecentUser"), str1, NULL, str.GetBuffer(30), 30, _T("..\\0131122589\\config.ini")) == 0)
		{
			break;
		}
		GetPrivateProfileString(_T("RecentUser"), str1, NULL, str.GetBuffer(30), 30, _T("..\\0131122589\\config.ini"));
		str1.Empty();
		m_combo1.InsertString(i, str);
	}
	if (m_usernum > 0)
	{
		m_combo1.SetCurSel(0);
		m_combo1.GetLBText(0, m_user);
		if (GetPrivateProfileInt(_T("State"), _T("state1"), NULL, _T("..\\Users\\") + m_user + _T("\\config.ini")) == 1)
		{
			GetPrivateProfileString(_T("Info"), _T("PWD"), NULL, m_password.GetBuffer(30), 30, _T("..\\Users\\") + m_user + _T("\\config.ini"));
			m_check = TRUE;
		}
		UpdateData(false);
	}
	// TODO:  在此添加额外的初始化
	ModifyStyleEx(WS_EX_TOOLWINDOW, WS_EX_APPWINDOW);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CLogin::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	CString str;
	if (GetPrivateProfileString(_T("Info"), _T("User"), NULL, str.GetBuffer(30), 30, _T("..\\Users\\") + m_user + _T("\\config.ini")) == 0)
	{
		MessageBox(_T("输入的用户名不正确！请核实！"), _T("提示"), MB_ICONINFORMATION);
		return;
	}
	else
	{
		GetPrivateProfileString(_T("Info"), _T("PWD"), NULL, str.GetBuffer(30), 30, _T("..\\Users\\") + m_user + _T("\\config.ini"));
		if (str != m_password)
		{
			MessageBox(_T("输入的密码不正确！请核实！"), _T("提示"), MB_ICONINFORMATION);
			return;
		}
	}
	str.Empty();
	GetPrivateProfileString(_T("RecentUser"), _T("user1"), NULL, m_user1.GetBuffer(30), 30, _T("..\\0131122589\\config.ini"));
	GetPrivateProfileString(_T("RecentUser"), _T("user2"), NULL, m_user2.GetBuffer(30), 30, _T("..\\0131122589\\config.ini"));
	GetPrivateProfileString(_T("RecentUser"), _T("user3"), NULL, m_user3.GetBuffer(30), 30, _T("..\\0131122589\\config.ini"));
	if (m_user == m_user1 || m_user == m_user2 || m_user == m_user3)
	{

	}
	else
	{
		::WritePrivateProfileString(_T("RecentUser"), _T("user3"), m_user2, _T("..\\0131122589\\config.ini"));
		str.Empty();

		::WritePrivateProfileString(_T("RecentUser"), _T("user2"), m_user1, _T("..\\0131122589\\config.ini"));
		::WritePrivateProfileString(_T("RecentUser"), _T("user1"), m_user, _T("..\\0131122589\\config.ini"));
	}
	if (m_check == TRUE)
	{
		::WritePrivateProfileString(_T("State"), _T("state1"),_T("1") , _T("..\\Users\\") + m_user + _T("\\config.ini"));
	}
	else
	{
		::WritePrivateProfileString(_T("State"), _T("state1"), _T("0"), _T("..\\Users\\") + m_user + _T("\\config.ini"));
	} 
	if (m_usernum < 3)
	{
		m_usernum += 1;
		CString UserNum;
		UserNum.Format(_T("%d"),m_usernum);
		::WritePrivateProfileString(_T("RecentUser"), _T("usernum"), UserNum, _T("..\\0131122589\\config.ini"));
	}

	((CTestingSystemApp *)AfxGetApp())->m_user=m_user;
	CDialogEx::OnOK();
}


void CLogin::OnCbnSelchangeCombo2()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CLogin::OnCloseupCombo1()
{
	if (m_usernum > 0)
	{
		if (m_combo1.GetCurSel() != -1)
		{
			CString temp;
			m_combo1.GetLBText(m_combo1.GetCurSel(), temp);
			if (GetPrivateProfileInt(_T("State"), _T("state1"), NULL, _T("..\\Users\\") + temp + _T("\\config.ini")) == 1)
			{
				GetPrivateProfileString(_T("Info"), _T("PWD"), NULL, m_password.GetBuffer(30), 30, _T("..\\Users\\") + temp + _T("\\config.ini"));
				m_check = TRUE;
			}
			else
			{
				CString s;
				m_password = s;
				m_check = FALSE;
			}
			m_combo1.GetLBText(m_combo1.GetCurSel(), m_user);
			UpdateData(false);
		}
	}
}

void CLogin::OnBnClickedButton3()
{
	ShellExecute(NULL, "open","HTSL.CHM", NULL, NULL, SW_RESTORE);
}
