// ForgetPW.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestingSystem.h"
#include "ForgetPW.h"
#include "afxdialogex.h"


// CForgetPW �Ի���

IMPLEMENT_DYNAMIC(CForgetPW, CDialogEx)

CForgetPW::CForgetPW(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG4, pParent)
	, m_edit1(_T(""))
	, m_edit2(_T(""))
	, m_edit3(_T(""))
	, m_user(_T(""))
	, m_password(_T(""))
	, m_question1(_T(""))
	, m_question2(_T(""))
	, m_question3(_T(""))
{

}

CForgetPW::~CForgetPW()
{
}

void CForgetPW::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_STATIC1, m_edit1);
	DDX_Text(pDX, IDC_STATIC2, m_edit2);
	DDX_Text(pDX, IDC_STATIC3, m_edit3);
	DDX_Text(pDX, IDC_EDIT6, m_user);
	DDX_Text(pDX, IDC_EDIT4, m_password);
	DDX_Text(pDX, IDC_EDIT1, m_question1);
	DDX_Text(pDX, IDC_EDIT2, m_question2);
	DDX_Text(pDX, IDC_EDIT3, m_question3);
}


BEGIN_MESSAGE_MAP(CForgetPW, CDialogEx)
	
	ON_EN_KILLFOCUS(IDC_EDIT6, &CForgetPW::OnKillfocusEdit6)
	ON_BN_CLICKED(IDOK, &CForgetPW::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT6, &CForgetPW::OnChangeEdit6)
END_MESSAGE_MAP()


// CForgetPW ��Ϣ�������


BOOL CForgetPW::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	ModifyStyleEx(WS_EX_TOOLWINDOW, WS_EX_APPWINDOW);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}



void CForgetPW::OnKillfocusEdit6()
{
	
}


void CForgetPW::OnBnClickedOk()
{
	UpdateData(true);
	UpdateData(true);
	CString str;
	if (GetPrivateProfileString(_T("Info"), _T("User"), NULL, str.GetBuffer(30), 30, _T("..\\Users\\") + m_user + _T("\\config.ini")) == 0)
	{
		MessageBox(_T("������û�������ȷ�����ʵ��"), _T("��ʾ"), MB_ICONINFORMATION);
		return;
	}
	UpdateData(false);
	CString temp1, temp2, temp3;
	GetPrivateProfileString(_T("PWD"), _T("password1"), NULL, temp1.GetBuffer(30), 30, _T("..\\Users\\") + m_user + _T("\\config.ini"));
	GetPrivateProfileString(_T("PWD"), _T("password2"), NULL, temp2.GetBuffer(30), 30, _T("..\\Users\\") + m_user + _T("\\config.ini"));
	GetPrivateProfileString(_T("PWD"), _T("password3"), NULL, temp3.GetBuffer(30), 30, _T("..\\Users\\") + m_user + _T("\\config.ini"));
	if (m_question1 != temp1||m_question2 != temp2||m_question3 != temp3)
	{
		MessageBox(_T("�ܱ��𰸲���ȷ��"), _T("��ʾ"), MB_ICONINFORMATION);
		return;
	}
	else
	{
		if (m_password.IsEmpty())
		{
			MessageBox(_T("���벻��Ϊ�գ�"), _T("��ʾ"), MB_ICONINFORMATION);
			return;
		}
		else
		{
			::WritePrivateProfileString(_T("Info"), _T("PWD"), m_password, _T("..\\Users\\") + m_user + _T("\\config.ini"));
			MessageBox(_T("�����޸ĳɹ���"), _T("��ʾ"), MB_ICONINFORMATION);
		}
	}
	CDialogEx::OnOK();
}


void CForgetPW::OnChangeEdit6()
{
	UpdateData(true);
	CString str;
	if (GetPrivateProfileString(_T("Info"), _T("User"), NULL, str.GetBuffer(30), 30, _T("..\\Users\\") + m_user + _T("\\config.ini")) == 0)
	{
		m_edit1.Empty();
		m_edit2.Empty();
		m_edit3.Empty();
		UpdateData(false);
		return;
	}
	else
	{
		GetPrivateProfileString(_T("Question"), _T("question1"), NULL, m_edit1.GetBuffer(30), 30, _T("..\\Users\\") + m_user + _T("\\config.ini"));
		GetPrivateProfileString(_T("Question"), _T("question2"), NULL, m_edit2.GetBuffer(30), 30, _T("..\\Users\\") + m_user + _T("\\config.ini"));
		GetPrivateProfileString(_T("Question"), _T("question3"), NULL, m_edit3.GetBuffer(30), 30, _T("..\\Users\\") + m_user + _T("\\config.ini"));
	}
	UpdateData(false);
}
