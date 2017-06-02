
// TestingSystemDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestingSystem.h"
#include "TestingSystemDlg.h"
#include "afxdialogex.h"
#include "Login.h"
#include "Encryption.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnHelpInfo(HELPINFO* pHelpInfo);
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)

END_MESSAGE_MAP()


// CTestingSystemDlg �Ի���



CTestingSystemDlg::CTestingSystemDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TestingSystem_DIALOG, pParent)
	, m_total_minutes(0)
	, m_total_questions(0)
	, m_max_speed(0)
	, m_timer(_T(""))
	, m_id(_T(""))
	, m_admission(_T(""))
	, m_user(_T(""))
	, m_musicnum(_T("1"))
	, m_musicstype(NULL)
	, m_edit4(_T(""))
	, m_IsEnd(false)
	, m_use(0)
	, m_speed(0)
	, m_score(0)
	, Is(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_percentage_accuracy = 0.0;
	m_percentage_speed = 0.0;
	m_accuracy = 0.0;
	m_score = 0.0;
}


void CTestingSystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_combo1);
	DDX_Text(pDX, IDC_STATIC1, m_timer);
	DDX_Control(pDX, IDC_STATIC1, m_edit1);
	DDX_Text(pDX, IDC_EDIT1, m_id);
	DDV_MaxChars(pDX, m_id, 18);
	DDX_Text(pDX, IDC_EDIT2, m_admission);
	DDV_MaxChars(pDX, m_admission, 15);
	DDX_Control(pDX, IDC_LIST1, m_ctrList);
	DDX_Text(pDX, IDC_EDIT4, m_edit4);
}

BEGIN_MESSAGE_MAP(CTestingSystemDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_CBN_SELCHANGE(IDC_COMBO1, &CTestingSystemDlg::OnCbnSelchangeCombo1)
	ON_BN_CLICKED(IDOK, &CTestingSystemDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &CTestingSystemDlg::OnBnClickedButton1)
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
	ON_CBN_CLOSEUP(IDC_COMBO1, &CTestingSystemDlg::OnCloseupCombo1)
	ON_EN_SETFOCUS(IDC_EDIT4, &CTestingSystemDlg::OnSetfocusEdit4)
	ON_EN_CHANGE(IDC_EDIT1, &CTestingSystemDlg::OnChangeEdit1)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CTestingSystemDlg::OnDblclkList1)
	ON_WM_HELPINFO()
END_MESSAGE_MAP()


// CTestingSystemDlg ��Ϣ�������

BOOL CTestingSystemDlg::OnInitDialog()
{

	CDialogEx::OnInitDialog();
	CLogin dlg;
	if (dlg.DoModal() == IDCANCEL)
		OnOK();
	m_user=dlg.m_user;
	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	ShowWindow(SW_SHOWMINIMIZED| SW_RESTORE);
	m_ctrList.InsertColumn(0, _T("����ʱ��"));
	m_ctrList.InsertColumn(1, _T("�����"));
	m_ctrList.InsertColumn(2, _T("׼ȷ��"));
	m_ctrList.InsertColumn(3, _T("�ٶ�"));
	m_ctrList.InsertColumn(4, _T("�÷�"));
	m_ctrList.InsertColumn(5, _T("��ʱ"));
	m_ctrList.SetColumnWidth(0, 61);
	m_ctrList.SetColumnWidth(1, 48);
	m_ctrList.SetColumnWidth(2, 47);
	m_ctrList.SetColumnWidth(3, 50);
	m_ctrList.SetColumnWidth(4, 40);
	m_ctrList.SetColumnWidth(5, 61);
	DWORD dwStyle = m_ctrList.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;
	dwStyle |= LVS_EX_GRIDLINES;
	m_ctrList.SetExtendedStyle(dwStyle);
	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_total_minutes= GetPrivateProfileInt(_T("ExamInfo"), _T("total_minutes"),NULL,_T("..\\0131122589\\config.ini"));
	m_total_questions= GetPrivateProfileInt(_T("ExamInfo"), _T("total_questions"),NULL, _T("..\\0131122589\\config.ini"));
	m_max_speed = GetPrivateProfileInt(_T("ExamInfo"), _T("max_speed"),NULL, _T("..\\0131122589\\config.ini"));
	CString percentage_speed, percentage_accuracy;
	GetPrivateProfileString(_T("ExamInfo"), _T("percentage_speed"), NULL,percentage_speed.GetBuffer(30),30, _T("..\\0131122589\\config.ini"));
	GetPrivateProfileString(_T("ExamInfo"), _T("percentage_accuracy"), NULL, percentage_accuracy.GetBuffer(30),30, _T("..\\0131122589\\config.ini"));
	m_second = 0;
	m_minute = m_total_minutes;
	m_hour = 0;
	for (int i = 0; i < m_total_questions;i++)
	{
		CString str;
		str.Format(_T("%d"),i+1);
		m_combo1.InsertString(i, str);
	}
	m_percentage_accuracy = atof(percentage_accuracy);
	m_percentage_speed = atof(percentage_speed);
	m_brush.CreateSolidBrush(RGB(255, 0, 0));
	m_combo1.SetCurSel(0);
	m_font.CreatePointFont(150, _T("����"));
	m_edit1.SetFont(&m_font);
	m_musicstype = new int[m_total_questions];
	GetFileFromDir();
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CTestingSystemDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTestingSystemDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CTestingSystemDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTestingSystemDlg::OnCbnSelchangeCombo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CTestingSystemDlg::OnBnClickedOk()
{
	if(Is||(MessageBox(_T("�Ƿ�Ҫ�������Բ��ύ��"),_T("��ʾ"),MB_OKCANCEL | MB_ICONWARNING)==1))
	{
		Is = false;
		m_IsEnd = false;
		KillTimer(1);
		m_speed = m_edit4.GetLength()/double(m_use/60.0);
		if (m_speed > m_max_speed)
			m_speed = m_max_speed;
		OnStop();
		((CEdit*)GetDlgItem(IDC_EDIT4))->EnableWindow(false);
		((CButton*)GetDlgItem(IDOK))->EnableWindow(false);
		CFileFind finder;
		CString m_filename, UseTime, Speed, Accuracy, Score,Text;
		CTime CurrentTime;
		CurrentTime = CTime::GetCurrentTime();
		Speed.Format(_T("%d"), m_speed);
		m_accuracy = Similarity(ReadText(m_musicnum), Exchange(m_edit4));
		m_score = m_percentage_accuracy*m_accuracy*100 + m_percentage_speed*m_speed;
		Score.Format(_T("%.2f"),m_score);
		float m_cur100 = m_accuracy*100;
		Accuracy.Format(_T("%.2f"), m_cur100);
		UseTime.Format(_T("%d:%d:%d"), m_use/3600,m_use/60,m_use%60);
		m_filename.Format(_T("%d%d%d%d%d%d"), CurrentTime.GetYear(), CurrentTime.GetMonth(), CurrentTime.GetDay(), CurrentTime.GetHour(), CurrentTime.GetMinute(), CurrentTime.GetSecond());
		Text.Format(_T("%d-%d-%d-%d:%d:%d"), CurrentTime.GetYear(), CurrentTime.GetMonth(), CurrentTime.GetDay(), CurrentTime.GetHour(), CurrentTime.GetMinute(), CurrentTime.GetSecond());
		BOOL ifFind = finder.FindFile(_T("..\\Users\\") + m_user + _T("\\") + m_id + _T("\\") + m_filename + _T(".ini"));
		if (!ifFind)
		{
			WritePrivateProfileString(_T("Info"), _T("User"), m_user, _T("..\\Users\\") + m_user + _T("\\") + m_id + _T("\\") + m_filename + _T(".ini"));
			WritePrivateProfileString(_T("Info"), _T("ID"), m_id, _T("..\\Users\\") + m_user + _T("\\") + m_id + _T("\\") + m_filename + _T(".ini"));
			WritePrivateProfileString(_T("Info"), _T("Admission"), m_admission, _T("..\\Users\\") + m_user + _T("\\") + m_id + _T("\\") + m_filename + _T(".ini"));
			WritePrivateProfileString(_T("Info"), _T("Question"), m_musicnum, _T("..\\Users\\") + m_user + _T("\\") + m_id + _T("\\") + m_filename + _T(".ini"));
			WritePrivateProfileString(_T("Info"), _T("True"), Accuracy + _T("%"), _T("..\\Users\\") + m_user + _T("\\") + m_id + _T("\\") + m_filename + _T(".ini"));
			WritePrivateProfileString(_T("Info"), _T("Speed"), Speed+_T("����/����"), _T("..\\Users\\") + m_user + _T("\\") + m_id + _T("\\") + m_filename + _T(".ini"));
			WritePrivateProfileString(_T("Info"), _T("UseTime"),UseTime, _T("..\\Users\\") + m_user + _T("\\") + m_id + _T("\\") + m_filename + _T(".ini"));
			WritePrivateProfileString(_T("Info"), _T("Score"), Score, _T("..\\Users\\") + m_user + _T("\\") + m_id + _T("\\") + m_filename + _T(".ini"));
			WritePrivateProfileString(_T("Info"), _T("TextTime"), Text, _T("..\\Users\\") + m_user + _T("\\") + m_id + _T("\\") + m_filename + _T(".ini"));
			WritePrivateProfileString(_T("Text"), _T("Text"), m_edit4, _T("..\\Users\\") + m_user + _T("\\") + m_id + _T("\\") + m_filename + _T(".ini"));
		}
		((CTestingSystemApp *)AfxGetApp())->m_filename=m_filename;
		CScore dlg;
		dlg.DoModal();
		((CEdit*)GetDlgItem(IDC_EDIT1))->EnableWindow(true);
		((CEdit*)GetDlgItem(IDC_EDIT2))->EnableWindow(true);
		((CComboBox*)GetDlgItem(IDC_COMBO1))->EnableWindow(true);
		((CEdit*)GetDlgItem(IDC_EDIT4))->EnableWindow(false);
		((CButton*)GetDlgItem(IDOK))->EnableWindow(false);
		((CButton*)GetDlgItem(IDC_BUTTON1))->EnableWindow(true);
		OnChangeEdit1();
	}
}


void CTestingSystemDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	for (int i = 0; i < m_id.GetLength(); i++)
	{
		if (m_id[i]<'0' || m_id[i]>'9')
		{
			if (i==17&&m_id[i] == 'X')
			{
			}
			else
			{
				MessageBox(_T("��������֤���벻��ȷ�����ʵ��"), _T("��ʾ"), MB_ICONINFORMATION);
				return;
			}
		}
	}
	if (m_id.GetLength() != 18)
	{
		MessageBox(_T("��������֤����λ������ȷ�����ʵ��"), _T("��ʾ"), MB_ICONINFORMATION);
		return;
	}
	for (int i = 0; i < m_admission.GetLength(); i++)
	{
		if (m_admission[i]<'0' || m_admission[i]>'9')
		{
			MessageBox(_T("�����׼��֤�Ų���ȷ���������룡"), _T("��ʾ"), MB_ICONINFORMATION);
			return;
		}
	}
	if (m_admission.GetLength() > 15 || m_admission.GetLength() < 13)
	{
		MessageBox(_T("�����׼��֤�ų��Ȳ���ȷ�����飡"), _T("��ʾ"), MB_ICONINFORMATION);
		return;
	}
	((CEdit*)GetDlgItem(IDC_EDIT1))->EnableWindow(false);
	((CEdit*)GetDlgItem(IDC_EDIT2))->EnableWindow(false);
	((CComboBox*)GetDlgItem(IDC_COMBO1))->EnableWindow(false);
	((CEdit*)GetDlgItem(IDC_EDIT4))->EnableWindow(true);
	((CButton*)GetDlgItem(IDOK))->EnableWindow(true);
	((CButton*)GetDlgItem(IDC_BUTTON1))->EnableWindow(FALSE);
	UpdateData(false);
	SetTimer(1, 1000, 0);
	DWORD dwAttr = GetFileAttributes(_T("..\\Users\\") + m_user+_T("\\")+m_id);
	if (dwAttr == 0xFFFFFFFF)
		CreateDirectory(_T("..\\Users\\") + m_user + _T("\\") + m_id, NULL);
	else if (dwAttr & FILE_ATTRIBUTE_DIRECTORY)
	{
	}
	((CTestingSystemApp *)AfxGetApp())->m_id = m_id;
	SetDlgItemText(IDC_EDIT4,_T("���Կ�ʼ�ˣ����ڴ�¼������..."));
	OnPlay();
	ReadText(m_musicnum);
}
void CTestingSystemDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	UpdateData(true);
	if (m_second == 0 && m_minute == 0 && m_hour == 0)
	{
		Is = true;
		OnBnClickedOk();
	}
	else
	{
		m_use++;
		if (m_second == 0)
		{
			m_second = 59;
			if (m_minute == 0)
			{
				m_hour--;
				m_minute = 59;
			}
			else
			m_minute--;
		}
		else
			m_second--;
	}
	CString m_strsecond,m_strminute,m_strhour;
	if (m_hour <= 9)
		m_strhour.Format(_T("0%d"), m_hour);
	else
		m_strhour.Format(_T("%d"), m_hour);
	if (m_minute <= 9)
		m_strminute.Format(_T("0%d"), m_minute);
	else
		m_strminute.Format(_T("%d"), m_minute);
	if (m_second <= 9)
		m_strsecond.Format(_T("0%d"), m_second);
	else
		m_strsecond.Format(_T("%d"), m_second);
	m_timer.Format(_T("\r\n����ʣ��ʱ��\r\n\r\n") + m_strhour+_T(":") + m_strminute + _T(":") + m_strsecond);
	UpdateData(false);
	CDialogEx::OnTimer(nIDEvent);
}


HBRUSH CTestingSystemDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	// TODO:  �ڴ˸��� DC ���κ�����
	if (nCtlColor == CTLCOLOR_STATIC &&
		pWnd->GetDlgCtrlID() == IDC_STATIC1)//ע��˴��ģ�pWnd->��������ûЧ��
	{
		pDC->SetTextColor(RGB(255, 0, 0));
		pDC->SetBkColor(RGB(0, 0, 0));//�����ı�����ɫ
		pDC->SetBkMode(TRANSPARENT);//���ñ���͸��
		//hbr = (HBRUSH)m_brush;
	}
	return hbr;
}


void CTestingSystemDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	//ReSize();
	// TODO: �ڴ˴������Ϣ����������
}


void CTestingSystemDlg::ReSize(void)
{
	float fsp[2];
	POINT Newp; //��ȡ���ڶԻ���Ĵ�С
	CRect recta;
	GetClientRect(&recta);     //ȡ�ͻ�����С  
	Newp.x = recta.right - recta.left;
	Newp.y = recta.bottom - recta.top;
	fsp[0] = (float)Newp.x / old.x;
	fsp[1] = (float)Newp.y / old.y;
	CRect Rect;
	int woc;
	CPoint OldTLPoint, TLPoint; //���Ͻ�
	CPoint OldBRPoint, BRPoint; //���½�
	HWND  hwndChild = ::GetWindow(m_hWnd, GW_CHILD);  //�г����пؼ�  
	while (hwndChild)
	{
		woc = ::GetDlgCtrlID(hwndChild);//ȡ��ID
		GetDlgItem(woc)->GetWindowRect(Rect);
		ScreenToClient(Rect);
		OldTLPoint = Rect.TopLeft();
		TLPoint.x = long(OldTLPoint.x*fsp[0]);
		TLPoint.y = long(OldTLPoint.y*fsp[1]);
		OldBRPoint = Rect.BottomRight();
		BRPoint.x = long(OldBRPoint.x *fsp[0]);
		BRPoint.y = long(OldBRPoint.y *fsp[1]);
		Rect.SetRect(TLPoint, BRPoint);
		GetDlgItem(woc)->MoveWindow(Rect, TRUE);
		hwndChild = ::GetWindow(hwndChild, GW_HWNDNEXT);
	}
	old = Newp;
}


BOOL CAboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	return TRUE;  
}


void CTestingSystemDlg::OnPlay()
{
	DWORD cdlen;
	CString m_temp;
	if (m_musicstype[atoi(m_musicnum)] == 1)
		m_temp = _T("..\\0131122589\\music\\") + m_musicnum + _T(".mp3");
	else
		m_temp = _T("..\\0131122589\\music\\") + m_musicnum + _T(".wma");
	op.dwCallback = NULL;
	op.lpstrAlias = NULL;
	op.lpstrDeviceType = _T("MPEGAudio");
	op.lpstrElementName = m_temp; 
	op.wDeviceID = NULL;
	UINT rs;
	rs = mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT, (DWORD)&op);
	mciSendCommand(NULL, MCI_SET, MCI_SET_DOOR_OPEN, NULL);
	cdlen = GetInfo(op.wDeviceID, MCI_STATUS_LENGTH);
	if (rs == 0) 
	{
		MCI_PLAY_PARMS pp;
		pp.dwCallback = NULL;
		pp.dwFrom = 0;    
		mciSendCommand(op.wDeviceID, MCI_PLAY, MCI_NOTIFY, (DWORD)&pp);
	}
	else
	{
		MessageBox(_T("��ȡ�ļ�ʧ�ܣ�"), _T("��ʾ"), MB_ICONINFORMATION);
	}
}




void CTestingSystemDlg::OnStop()
{
	MCI_GENERIC_PARMS gp;
	gp.dwCallback = NULL;
	mciSendCommand(op.wDeviceID, MCI_CLOSE, MCI_WAIT, (DWORD)&gp);
}


int CTestingSystemDlg::GetInfo(UINT wDeviceID, DWORD item)
{
	MCI_STATUS_PARMS mcistatusparms;
	mcistatusparms.dwCallback = (DWORD)GetSafeHwnd();
	mcistatusparms.dwItem = item;
	mcistatusparms.dwReturn = 0;
	mciSendCommand(wDeviceID, MCI_STATUS, MCI_STATUS_ITEM, (DWORD)&mcistatusparms);
	return mcistatusparms.dwReturn;
}


void CTestingSystemDlg::OnCloseupCombo1()
{
	m_musicnum.Format(_T("%d"), m_combo1.GetCurSel()+1);
}


void CTestingSystemDlg::GetFileFromDir()
{
	CString csDirPath;
	csDirPath= "..\\0131122589\\music\\*.*";
	HANDLE file;
	WIN32_FIND_DATA fileData;
	file = FindFirstFile(csDirPath.GetBuffer(), &fileData);
	CString m_filename;
	m_filename = fileData.cFileName;
	if (m_filename.Find(_T("mp3")) != -1)
	{
		m_musicstype[atoi(m_filename.Left(m_filename.GetLength()-4))] = 1;
	}
	if (m_filename.Find(_T("wma")) != -1)
	{
		m_musicstype[atoi(m_filename.Left(m_filename.GetLength() - 4))] = 0;
	}
	BOOL bState = FALSE;
	bState = FindNextFile(file, &fileData);
	while (bState) {
		m_filename=fileData.cFileName;
		if (m_filename.Find(_T("mp3")) != -1)
		{
			m_musicstype[atoi(m_filename.Left(m_filename.GetLength() - 4))] = 1;
		}
		if (m_filename.Find(_T("wma")) != -1)
		{
			m_musicstype[atoi(m_filename.Left(m_filename.GetLength() - 4))] = 0;
		}
		bState = FindNextFile(file, &fileData);
	}
}


float CTestingSystemDlg::Similarity(CString str1, CString str2)
{
	//���������ַ����ĳ��ȡ� 
	int len1 = str1.GetLength();
	int len2 = str2.GetLength(); //�������飬���ַ����ȴ�һ���ռ� 
	int ** dif; //����ֵ������B�� 
	dif = new int*[len1 + 1];
	for (int i = 0; i < len1+1; i++)
	{
		dif[i] = new int[len2 + 1];
	}
	for (int a = 0; a <= len1; a++) 
	{ 
		dif[a][0] = a; 
	} 
	for (int a = 0; a <= len2; a++) 
	{ 
		dif[0][a] = a; 
	} //���������ַ��Ƿ�һ�����������ϵ�ֵ 
	int temp; 
	for (int i = 1; i <= len1; i++) 
	{ 
		for (int j = 1; j <= len2; j++) 
		{ 
			if (str1[i - 1] == str2[j - 1]) 
			{ 
				temp = 0; 
			} 
			else 
			{ 
				temp = 1; 
			} //ȡ����ֵ����С�� 
			dif[i][j] = min(dif[i - 1][j - 1] + temp,min(dif[i][j - 1] + 1, dif[i - 1][j] + 1));
		} 
	} 
	return 1 - (float) dif[len1][len2] / max(str1.GetLength(), str2.GetLength());
} 




void CTestingSystemDlg::OnSetfocusEdit4()
{
	if (!m_IsEnd)
	{
		m_edit4.Empty();
		UpdateData(false);
		m_IsEnd = true;
	}
}


CString CTestingSystemDlg::ReadText(CString str)
{
	CEncryption encode;
	CString pszFileName = _T("..\\0131122589\\answer\\") + str + _T(".txt");
	int flag = encode.filecryption((LPSTR)(LPCSTR)pszFileName, "songyaxu", 1);
	if (flag == 2)
	{
		MessageBox("��ȡ�ļ�����!");
		return "";
	}
	CStdioFile myFile;
	CString Text;
	CFileException fileException;
	if (myFile.Open(pszFileName, CFile::typeText | CFile::modeReadWrite), &fileException)
	{
		myFile.SeekToBegin();
		myFile.ReadString(Text);
	}
	else
	{
		TRACE("�޷����ļ�%s,����%u\n", pszFileName, fileException.m_cause);
	}
	CString a;
	for (int i = 0; i < Text.GetLength(); i++)
	{
		if (Text[i] != ' ')
			a += Text[i];
	}
	myFile.Close();
	encode.filecryption((LPSTR)(LPCSTR)pszFileName, "songyaxu", 0);
	return a;
}


void CTestingSystemDlg::OnChangeEdit1()
{
	m_ctrList.DeleteAllItems();
	UpdateData(true);
	CString str;
	DWORD dwAttr = GetFileAttributes(_T("..\\Users\\") + m_user + _T("\\") + m_id);
	if (dwAttr == 0xFFFFFFFF)
	{	}
	else if (dwAttr & FILE_ATTRIBUTE_DIRECTORY)
	{
		CString csDirPath;
		csDirPath = "..\\Users\\" + m_user + "\\" + m_id + "\\*.ini";
		HANDLE file;
		WIN32_FIND_DATA fileData;
		file = FindFirstFile(csDirPath.GetBuffer(), &fileData);
		CString m_filename,strTemp;
		CString str_test_time, str_question, str_accaurcy, str_speed, str_score, str_use_time;
		m_filename = fileData.cFileName;
		GetPrivateProfileString(_T("Info"), _T("TextTime"), NULL, str_test_time.GetBuffer(30), 30, _T("..\\Users\\") + m_user + _T("\\") + m_id + _T("\\") + m_filename);
		GetPrivateProfileString(_T("Info"), _T("Question"), NULL, str_question.GetBuffer(30), 30, _T("..\\Users\\") + m_user + _T("\\") + m_id + _T("\\") + m_filename);
		GetPrivateProfileString(_T("Info"), _T("True"), NULL, str_accaurcy.GetBuffer(30), 30, _T("..\\Users\\") + m_user + _T("\\") + m_id + _T("\\") + m_filename);
		GetPrivateProfileString(_T("Info"), _T("Speed"), NULL, str_speed.GetBuffer(30), 30, _T("..\\Users\\") + m_user + _T("\\") + m_id + _T("\\") + m_filename);
		GetPrivateProfileString(_T("Info"), _T("Score"), NULL, str_score.GetBuffer(30), 30, _T("..\\Users\\") + m_user + _T("\\") + m_id + _T("\\") + m_filename);
		GetPrivateProfileString(_T("Info"), _T("UseTime"), NULL, str_use_time.GetBuffer(30), 30, _T("..\\Users\\") + m_user + _T("\\") + m_id + _T("\\") + m_filename);
		int i = 0;
		m_ctrList.InsertItem(i, strTemp);
		m_ctrList.SetItemText(i, 0, str_test_time);
		m_ctrList.SetItemText(i, 1, str_question);
		m_ctrList.SetItemText(i, 2, str_accaurcy);
		m_ctrList.SetItemText(i, 3, str_speed);
		m_ctrList.SetItemText(i, 4, str_score);
		m_ctrList.SetItemText(i, 5, str_use_time);
		BOOL bState = FALSE;
		bState = FindNextFile(file, &fileData);
		while (bState) {
			i++;
			m_filename = fileData.cFileName;
			GetPrivateProfileString(_T("Info"), _T("TextTime"), NULL, str_test_time.GetBuffer(30), 30, _T("..\\Users\\") + m_user + _T("\\") + m_id + _T("\\") + m_filename);
			GetPrivateProfileString(_T("Info"), _T("Question"), NULL, str_question.GetBuffer(30), 30, _T("..\\Users\\") + m_user + _T("\\") + m_id + _T("\\") + m_filename);
			GetPrivateProfileString(_T("Info"), _T("True"), NULL, str_accaurcy.GetBuffer(30), 30, _T("..\\Users\\") + m_user + _T("\\") + m_id + _T("\\") + m_filename);
			GetPrivateProfileString(_T("Info"), _T("Speed"), NULL, str_speed.GetBuffer(30), 30, _T("..\\Users\\") + m_user + _T("\\") + m_id + _T("\\") + m_filename);
			GetPrivateProfileString(_T("Info"), _T("Score"), NULL, str_score.GetBuffer(30), 30, _T("..\\Users\\") + m_user + _T("\\") + m_id + _T("\\") + m_filename);
			GetPrivateProfileString(_T("Info"), _T("UseTime"), NULL, str_use_time.GetBuffer(30), 30, _T("..\\Users\\") + m_user + _T("\\") + m_id + _T("\\") + m_filename);
			m_ctrList.InsertItem(i, strTemp);
			m_ctrList.SetItemText(i, 0, str_test_time);
			m_ctrList.SetItemText(i, 1, str_question);
			m_ctrList.SetItemText(i, 2, str_accaurcy);
			m_ctrList.SetItemText(i, 3, str_speed);
			m_ctrList.SetItemText(i, 4, str_score);
			m_ctrList.SetItemText(i, 5, str_use_time);
			bState = FindNextFile(file, &fileData);
		}
	}
}


void CTestingSystemDlg::OnDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateData(true);
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (pNMListView->iItem != -1)
	{
		((CTestingSystemApp *)AfxGetApp())->m_filename.Empty();
		CString str;
		str= m_ctrList.GetItemText(pNMListView->iItem, 0);
		for (int i = 0; i < str.GetLength(); i++)
		{
			if (str[i] != '-' && str[i] != ':')
				((CTestingSystemApp *)AfxGetApp())->m_filename += str[i];
		}
		((CTestingSystemApp *)AfxGetApp())->m_id = m_id;
		CScore dlg;
		dlg.DoModal();
	}
	*pResult = 0;
}


BOOL CTestingSystemDlg::OnHelpInfo(HELPINFO* pHelpInfo)
{
	return CDialogEx::OnHelpInfo(pHelpInfo);
}


CString CTestingSystemDlg::Exchange(CString str)
{
	str.Replace("��", "");
	str.Replace("��", "");
	str.Replace("��", "");
	str.Replace("��", "");
	str.Replace(" ", "");
	str.Replace("��", "");
	str.Replace("��", "");
	str.Replace("��", "");
	str.Replace("{", "");
	str.Replace("}", "");
	str.Replace("��", "");
	str.Replace("��", "");
	str.Replace(" ", "");
	str.Replace(".", "");
	str.Replace("��", "");
	str.Replace("��", "");
	return str;
}
