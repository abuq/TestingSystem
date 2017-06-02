// NewUser.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestingSystem.h"
#include "NewUser.h"
#include "afxdialogex.h"


// CNewUser �Ի���

IMPLEMENT_DYNAMIC(CNewUser, CDialogEx)

CNewUser::CNewUser(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG3, pParent)
	, m_question1(_T(""))
	, m_question2(_T(""))
	, m_question3(_T(""))
	, m_num(0)
	, m_user(_T(""))
	, m_password(_T(""))
{

}

CNewUser::~CNewUser()
{
}

void CNewUser::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo1);
	DDX_Control(pDX, IDC_COMBO2, m_combo2);
	DDX_Control(pDX, IDC_COMBO3, m_combo3);
	DDX_Text(pDX, IDC_EDIT1, m_question1);
	DDX_Text(pDX, IDC_EDIT2, m_question2);
	DDX_Text(pDX, IDC_EDIT3, m_question3);
	DDX_Text(pDX, IDC_EDIT4, m_user);
	DDX_Text(pDX, IDC_EDIT5, m_password);
}


BEGIN_MESSAGE_MAP(CNewUser, CDialogEx)
	
	ON_BN_CLICKED(IDOK, &CNewUser::OnBnClickedOk)
END_MESSAGE_MAP()


// CNewUser ��Ϣ�������




BOOL CNewUser::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	ModifyStyleEx(WS_EX_TOOLWINDOW, WS_EX_APPWINDOW);
	m_num = GetPrivateProfileInt(_T("Questions"), _T("Num"), NULL, _T("..\\0131122589\\config.ini"));
	CString str,str1;
	for (int i = 0; i < m_num; i++)
	{

		str.Empty();
		str1.Format(_T("question%d"), i + 1);
		GetPrivateProfileString(_T("Questions"), str1, NULL, str.GetBuffer(30), 30, _T("..\\0131122589\\config.ini"));
		str1.Empty();
		m_combo1.InsertString(i, str);
		m_combo2.InsertString(i, str);
		m_combo3.InsertString(i, str);
	}
	m_combo1.SetCurSel(0);
	m_combo2.SetCurSel(1);
	m_combo3.SetCurSel(2);
	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	return TRUE;  // return TRUE unless you set the focus to a control
				  // �쳣: OCX ����ҳӦ���� FALSE
}


void CNewUser::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	if (m_question1.IsEmpty())
	{
		MessageBox(_T("�������ܱ�����1��"), _T("��ʾ"), MB_ICONINFORMATION);
		return;
	}
	if (m_question2.IsEmpty())
	{
		MessageBox(_T("�������ܱ�����2��"), _T("��ʾ"), MB_ICONINFORMATION);
		return;
	}
	if (m_question3.IsEmpty())
	{
		MessageBox(_T("�������ܱ�����3��"), _T("��ʾ"), MB_ICONINFORMATION);
		return;
	}
	if (m_combo1.GetCurSel() == m_combo2.GetCurSel() || m_combo1.GetCurSel() == m_combo3.GetCurSel() || m_combo2.GetCurSel() == m_combo3.GetCurSel())
	{
		MessageBox(_T("�ܱ����ⲻ����ͬ��"), _T("��ʾ"), MB_ICONINFORMATION);
		return;
	}
	if (m_user.IsEmpty() || m_password.IsEmpty())
	{
		MessageBox(_T("�û��������벻��Ϊ�գ�"), _T("��ʾ"), MB_ICONINFORMATION);
		return;
	}
	if (m_user.GetLength()>20)
	{
		MessageBox(_T("�û������ܳ���20λ��"), _T("��ʾ"), MB_ICONINFORMATION);
		return;
	}
	if (m_password.GetLength() > 20)
	{
		MessageBox(_T("���벻�ܳ���16λ��"), _T("��ʾ"), MB_ICONINFORMATION);
		return;
	}

	DWORD dwAttr = GetFileAttributes(_T("..\\Users\\")+m_user);
	if (dwAttr == 0xFFFFFFFF)
		CreateDirectory(_T("..\\Users\\"+m_user), NULL);
	else if (dwAttr & FILE_ATTRIBUTE_DIRECTORY)
	{
	}
	CFileFind finder;   
	BOOL ifFind = finder.FindFile(_T("..\\Users\\")+m_user+_T("\\config.ini"));
	if (!ifFind)
	{
		::WritePrivateProfileString(_T("Info"), _T("User"),m_user, _T("..\\Users\\") + m_user + _T("\\config.ini"));
		::WritePrivateProfileString(_T("Info"), _T("PWD"), m_password, _T("..\\Users\\") + m_user + _T("\\config.ini"));
		CString strnum;
		m_combo1.GetLBText(m_combo1.GetCurSel(),strnum);
		::WritePrivateProfileString(_T("Question"), _T("question1"),strnum, _T("..\\Users\\") + m_user + _T("\\config.ini"));
		m_combo1.GetLBText(m_combo2.GetCurSel(), strnum);
		::WritePrivateProfileString(_T("Question"), _T("question2"),strnum, _T("..\\Users\\") + m_user + _T("\\config.ini"));
		m_combo1.GetLBText(m_combo3.GetCurSel(), strnum);
		::WritePrivateProfileString(_T("Question"), _T("question3"),strnum, _T("..\\Users\\") + m_user + _T("\\config.ini"));
		::WritePrivateProfileString(_T("PWD"), _T("password1"), m_question1, _T("..\\Users\\") + m_user + _T("\\config.ini"));
		::WritePrivateProfileString(_T("PWD"), _T("password2"), m_question2, _T("..\\Users\\") + m_user + _T("\\config.ini"));
		::WritePrivateProfileString(_T("PWD"), _T("password3"), m_question3, _T("..\\Users\\") + m_user + _T("\\config.ini"));
	}
	MessageBox(_T("�û�ע��ɹ���"), _T("��ʾ"), MB_ICONINFORMATION);
	CDialogEx::OnOK();
}
