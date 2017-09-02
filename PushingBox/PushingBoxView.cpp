
// PushingBoxView.cpp : implementation of the CPushingBoxView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "PushingBox.h"
#endif

#include "PushingBoxDoc.h"
#include "PushingBoxView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPushingBoxView

IMPLEMENT_DYNCREATE(CPushingBoxView, CView)

BEGIN_MESSAGE_MAP(CPushingBoxView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CPushingBoxView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_KEYDOWN()
	ON_WM_CREATE()
	ON_WM_TIMER()
END_MESSAGE_MAP()

// CPushingBoxView construction/destruction

CPushingBoxView::CPushingBoxView()
{
	// TODO: add construction code here

	m_RowCount=10;	//10��
	m_ColCount=10;	//10��

	//��ʼ����˸��ť
	//shanshuo��ʼΪ8,��һ��ʼȫ��������t_shanshuoһ��ʼ����shanshuo
	t_shanshuo=shanshuo=8;

	//��ʼ��Ԫ��λͼ���飬��Ʒλͼ���飬��ťλͼ����
	for(int i=0;i<3;i++)
		m_Bitmap[i].LoadBitmap(IDB_BITMAP1+i);
	for(int j=0;j<3;j++)
		m_Thing[j].LoadBitmap(IDB_THING1+j);

	//��ʼ��LOGOλͼ
	m_Title.LoadBitmap(IDB_TITLE);
	//��ʼ��������λͼ
	m_Anniu.LoadBitmap(IDB_ANNIU);
	//��ʼ����˸�İ�ť
	m_AnniuShan.LoadBitmap(IDB_ANNIUSHAN);
	//��ʼ����ͣλͼ
	m_Pause.LoadBitmap(IDB_PAUSE);
	//��ʼ��ʤ��λͼ
	m_Win.LoadBitmap(IDB_WIN);
	//��ʼ������λͼ
	m_Regret.LoadBitmap(IDB_REGRET);

	//��ʼ�����
	Start();

}

CPushingBoxView::~CPushingBoxView()
{
}

BOOL CPushingBoxView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CPushingBoxView drawing

void CPushingBoxView::OnDraw(CDC* pDC)
{
	CPushingBoxDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here

	//������
	CBrush myBrush1;
	myBrush1.CreateSolidBrush(RGB(0,30,50));
	CRect myRect1(0,0,370,420);
	pDC->FillRect(myRect1,&myBrush1);

	//���Ʋ���
	//���Ʋ����ĺ�ɫ��Ļ
	CBrush myBrush2;
	myBrush2.CreateSolidBrush(RGB(0,0,0));
	CRect myRect2(20,20,70,50);
	pDC->FillRect(myRect2,&myBrush2);
	//���Ʋ����İ�ɫ�߿�
	CPen myPen1;
	CPen *myOldPen1;
	myPen1.CreatePen(PS_SOLID,2,RGB(255,255,255));
	myOldPen1=pDC->SelectObject(&myPen1);
	pDC->MoveTo(20,50);
	pDC->LineTo(70,50);
	pDC->LineTo(70,20);
	pDC->SelectObject(&myOldPen1);
	//���Ʋ����ĺ�ɫ�߿�
	CPen myPen2;
	CPen *myOldPen2;
	myPen2.CreatePen(PS_SOLID,2,RGB(200,0,0));
	myOldPen2=pDC->SelectObject(&myPen2);
	pDC->MoveTo(19,51);
	//pDC->LineTo(71,51);
	//pDC->LineTo(71,19);
	pDC->LineTo(19,19);
	pDC->LineTo(71,19);
	pDC->SelectObject(&myOldPen2);
	//���Ʋ���������
	int nOldDc=pDC->SaveDC();
	pDC->SetTextColor(RGB(255,0,0));
	pDC->SetBkColor(RGB(0,0,0));
	CFont myFont1;
	if(myFont1.CreatePointFont(153,_T("Comic Sans MS"))==0)
	{
		AfxMessageBox(_T("Can't Create Font!"));
	}
	pDC->SelectObject(&myFont1);
	//λ������
	CString str;
	if(foot<10)
		str.Format(_T("00%d"),foot);
	else if(foot<100)
		str.Format(_T("0%d"),foot);
	else
		str.Format(_T("%d"),foot);
	pDC->TextOut(27,20,str);
	pDC->RestoreDC(nOldDc);

	//����Ϸ�����weitu
	//
	//����weitu:
	//����ȡֵ��ͬ��ʾ��ͬ��λͼ
	//ȡ0����յ�
	//ȡ1����ǽ��
	//ȡ2�����ŵ�
	CDC Dc;
	if(Dc.CreateCompatibleDC(pDC)==FALSE)
		AfxMessageBox(_T("Can't Create DC!"));
	for(int i=0;i<m_RowCount;i++)
		for(int j=0;j<m_ColCount;j++)
		{
			if(cell[i][j].weitu==0)
			{
				Dc.SelectObject(m_Bitmap[0]);
				pDC->BitBlt(i*35+10,j*35+60,160,160,&Dc,0,0,SRCCOPY);
			}
			if(cell[i][j].weitu==1)
			{
				Dc.SelectObject(m_Bitmap[1]);
				pDC->BitBlt(i*35+10,j*35+60,160,160,&Dc,0,0,SRCCOPY);
			}
			if(cell[i][j].weitu==2)
			{
				Dc.SelectObject(m_Bitmap[2]);
				pDC->BitBlt(i*35+10,j*35+60,160,160,&Dc,0,0,SRCCOPY);
			}
		}

	//
	//����thing:
	//ȡ0ʱ����û�����ڣ��յػ��ŵ㣩����
	//ȡ1ʱ��������
	//ȡ2ʱ����������
	for(int i=0;i<m_RowCount;i++)
		for(int j=0;j<m_ColCount;j++)
		{
			if(cell[i][j].thing==1)
			{
				Dc.SelectObject(m_Thing[0]);
				pDC->BitBlt(i*35+10,j*35+60,160,160,&Dc,0,0,SRCCOPY);
			}
			if(cell[i][j].thing==2)
			{
				Dc.SelectObject(m_Thing[1]);
				pDC->BitBlt(i*35+10,j*35+60,160,160,&Dc,0,0,SRCCOPY);
			}
			if(cell[i][j].weitu==2 && cell[i][j].thing==2)
			{
				Dc.SelectObject(m_Thing[2]);
				pDC->BitBlt(i*35+10,j*35+60,160,160,&Dc,0,0,SRCCOPY);
			}
		};

	//��LOGO
	Dc.SelectObject(m_Title);
	pDC->BitBlt(85,5,1600,160,&Dc,0,0,SRCCOPY);

	////������������
	//CBrush myBrush3;
	//myBrush3.CreateSolidBrush(RGB(172,172,172));
	//CRect myRect3(5,420,365,645);
	//pDC->FillRect(myRect3,&myBrush3);

	////����������
	////���Ź���0~8�ֱ����ȷ�ϡ��ϡ����塢���ޡ��ҡ���ͣ���¡�����
	//Dc.SelectObject(m_Anniu);
	//pDC->BitBlt(20,430,350,350,&Dc,0,0,SRCCOPY);
	//Dc.SelectObject(m_AnniuShan);
	//switch(shanshuo)
	//{
	//	case 0:
	//		pDC->BitBlt(20,430,160,160,&Dc,0,0,SRCCOPY);break;
	//	case 1:
	//		pDC->BitBlt(130,430,160,160,&Dc,0,0,SRCCOPY);break;
	//	case 2:
	//		pDC->BitBlt(240,430,160,160,&Dc,0,0,SRCCOPY);break;
	//	case 3:
	//		pDC->BitBlt(20,500,160,160,&Dc,0,0,SRCCOPY);break;
	//	case 4:
	//		pDC->BitBlt(130,500,160,160,&Dc,0,0,SRCCOPY);break;
	//	case 5:
	//		pDC->BitBlt(240,500,160,160,&Dc,0,0,SRCCOPY);break;
	//	case 6:
	//		pDC->BitBlt(20,570,160,160,&Dc,0,0,SRCCOPY);break;
	//	case 7:
	//		pDC->BitBlt(130,570,160,160,&Dc,0,0,SRCCOPY);break;
	//	case 8:
	//		pDC->BitBlt(240,570,160,160,&Dc,0,0,SRCCOPY);break;
	//	default:break;
	//}

	//��������ʾ
	if(huiqi==1)
	{
		Dc.SelectObject(m_Regret);
		pDC->BitBlt(78,152,250,250,&Dc,0,0,SRCCOPY);
	}

	//����ͣ��ʾ
	if(zanting==-1)
	{
		Dc.SelectObject(m_Pause);
		pDC->BitBlt(78,152,250,250,&Dc,0,0,SRCCOPY);
	}
	
	//��������ʾ
	if(jieshu==1)
	{
		Dc.SelectObject(m_Win);
		pDC->BitBlt(78,152,250,250,&Dc,0,0,SRCCOPY);
	}

}


// CPushingBoxView printing


void CPushingBoxView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CPushingBoxView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPushingBoxView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPushingBoxView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CPushingBoxView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	//ע�͵�����ֹ����Ҽ�����
	//ClientToScreen(&point);
	//OnContextMenu(this, point);
}

void CPushingBoxView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CPushingBoxView diagnostics

#ifdef _DEBUG
void CPushingBoxView::AssertValid() const
{
	CView::AssertValid();
}

void CPushingBoxView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPushingBoxDoc* CPushingBoxView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPushingBoxDoc)));
	return (CPushingBoxDoc*)m_pDocument;
}
#endif //_DEBUG


// CPushingBoxView message handlers

//OnKeyDown���̿��ƺ���
void CPushingBoxView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	//����ദҪ��ͼ�����ں�����ͷд���⼸��
	//��ȡָ��pDC
	CDC *pDC=GetDC();
	CDC Dc;
	if(Dc.CreateCompatibleDC(pDC)==FALSE)
		AfxMessageBox(_T("Can't Create DC!"));

	//�����F2����������Ϸ
	if(nChar==VK_F2)
	{
		Start();
		Invalidate();
	}

	//�ж���Ϸ�Ƿ��Ѿ�����
	if(jieshu == 1)
		return;

	//����Ѿ������ˡ��Ѿ�����һ�Ρ�����ʾ�򣬴�ʱ���س����ɻص���Ϸ
	if(nChar==VK_RETURN)
	{
		huiqi=0;
		//AfxMessageBox(_T("Test"));
		CRect rect;
		rect.left=78;
		rect.right=rect.left+220;
		rect.top=152;
		rect.bottom=rect.top+150;
		InvalidateRect(&rect);
	}
	
	//����Ѿ�����һ�Σ��Ͳ����ٻ�����
	if(huiqi==1)
		return;

	//������ո񣬾���ͣ��Ϸ�����ڻ�������ʾ
	if(nChar==VK_SPACE)
	{
		zanting=pause(zanting);
	}
	//�ж���Ϸ�Ƿ��Ѿ���ͣ
	if(zanting==-1)
		return;

	//���÷��������������ػ���ǰ�������3������
	switch(nChar)
	{
		case VK_UP:
		{
			t_nChar=nChar;
			if(reny > 0 && cell[renx][reny-1].weitu != 1)
			{
				if(cell[renx][reny-1].thing==2 && reny-1==0)
					break;
				if(cell[renx][reny-1].thing==2 && cell[renx][reny-2].weitu==1)
					break;
				if(cell[renx][reny-1].thing==2 && cell[renx][reny-2].thing==2)
					break;
				reny--;
				foot++;
				cell[t_renx][t_reny].thing=0;
				if(cell[renx][reny].thing==2 && reny>0)
				{
					cell[renx][reny-1].thing=2;
					t_xiang=1;
				}
				else
					t_xiang=0;
				cell[renx][reny].thing=1;
				//�ػ�
				CRect rect;
				rect.left=renx*35+10;
				rect.right=renx*35+10+35;
				rect.top=(reny-1)*35+60;
				rect.bottom=(reny+2)*35+60;
				InvalidateRect(&rect);
				//����t_renx��t_reny
				t_renx=renx;
				t_reny=reny;
				//huiqi�ָ�Ϊ0
				huiqi=0;
			}
			break;
		}
		case VK_DOWN:
		{
			t_nChar=nChar;
			if(reny < m_RowCount-1 && cell[renx][reny+1].weitu != 1)
			{
				if(cell[renx][reny+1].thing==2 && reny+1==m_RowCount-1)
					break;
				if(cell[renx][reny+1].thing==2 && cell[renx][reny+2].weitu==1)
					break;
				if(cell[renx][reny+1].thing==2 && cell[renx][reny+2].thing==2)
					break;
				reny++;
				foot++;
				cell[t_renx][t_reny].thing=0;
				if(cell[renx][reny].thing==2 && reny<m_RowCount-1)
				{
					cell[renx][reny+1].thing=2;
					t_xiang=1;
				}
				else
					t_xiang=0;
				cell[renx][reny].thing=1;
				//�ػ�
				CRect rect;
				rect.left=renx*35+10;
				rect.right=renx*35+10+35;
				rect.top=(reny-1)*35+60;
				rect.bottom=(reny+2)*35+60;
				InvalidateRect(&rect);
				//����t_renx��t_reny
				t_renx=renx;
				t_reny=reny;
				//huiqi�ָ�Ϊ0
				huiqi=0;
			}
			break;
		}
		case VK_LEFT:
		{
			t_nChar=nChar;
			if(renx > 0 && cell[renx-1][reny].weitu != 1)
			{
				
				if(cell[renx-1][reny].thing==2 && renx-1==0)
					break;
				if(cell[renx-1][reny].thing==2 && cell[renx-2][reny].weitu==1)
					break;
				if(cell[renx-1][reny].thing==2 && cell[renx-2][reny].thing==2)
					break;
				renx--;
				foot++;
				cell[t_renx][t_reny].thing=0;
				if(cell[renx][reny].thing==2 && renx>0)
				{
					cell[renx-1][reny].thing=2;
					t_xiang=1;
				}
				else
					t_xiang=0;
				cell[renx][reny].thing=1;
				//�ػ�
				CRect rect;
				rect.left=(renx-1)*35+10;
				rect.right=(renx+2)*35+10;
				rect.top=reny*35+60;
				rect.bottom=reny*35+60+35;
				InvalidateRect(&rect);
				//����t_renx��t_reny
				t_renx=renx;
				t_reny=reny;
				//huiqi�ָ�Ϊ0
				huiqi=0;
			}
			break;			 
		}
		case VK_RIGHT:
		{
			t_nChar=nChar;
			if(renx < m_ColCount-1 && cell[renx+1][reny].weitu != 1)
			{
				if(cell[renx+1][reny].thing==2 && renx+1==m_ColCount-1)
					break;
				if(cell[renx+1][reny].thing==2 && cell[renx+2][reny].weitu==1)
					break;
				if(cell[renx+1][reny].thing==2 && cell[renx+2][reny].thing==2)
					break;
				renx++;
				foot++;
				cell[t_renx][t_reny].thing=0;
				if(cell[renx][reny].thing==2 && renx<m_ColCount-1)
				{
					cell[renx+1][reny].thing=2;
					t_xiang=1;
				}
				else
					t_xiang=0;
				cell[renx][reny].thing=1;
				//�ػ�
				CRect rect;
				rect.left=(renx-1)*35+10;
				rect.right=(renx+2)*35+10;
				rect.top=reny*35+60;
				rect.bottom=reny*35+60+35;
				InvalidateRect(&rect);
				//����t_renx��t_reny
				t_renx=renx;
				t_reny=reny;
				//huiqi�ָ�Ϊ0
				huiqi=0;
			}
			break;			  
		}
		case 0x52:
		{
			switch(t_nChar)
			{
				//�ж��Ƿ��Ѿ�����һ�Σ�����ǣ��Ͳ����ٻ�����
				case 0x52:
				{
					//������ֻ�ܻ���һ�Ρ�����ʾ������OnDraw��Ԥ�Ȱ�ʤ����ʾλͼ������
					//AfxMessageBox(_T("�Ѿ�����һ��"));
					huiqi=1;
					CRect rect;
					rect.left=78;
					rect.right=rect.left+220;
					rect.top=152;
					rect.bottom=rect.top+150;
					InvalidateRect(&rect);
					break;
				}
				case VK_UP:
				{
					reny++;
					foot++;
					cell[t_renx][t_reny].thing=0;
					if(t_xiang==1)
					{
						cell[t_renx][t_reny-1].thing=0;
						cell[t_renx][t_reny].thing=2;
					}
					cell[renx][reny].thing=1;
					//�ػ�
					CRect rect;
					rect.left=renx*35+10;
					rect.right=renx*35+10+35;
					rect.top=(reny-2)*35+60;
					rect.bottom=(reny+1)*35+60;
					InvalidateRect(&rect);
					//����t_renx��t_reny
					t_renx=renx;
					t_reny=reny;
					//��¼����һ�����ļ�ΪR��������Ϸֻ�ܻ���һ��
					t_nChar=nChar;
					//��t_xiang��ԭΪ0���ڿ��Ʒ���ʱ�����¸�ֵ
					t_xiang=0;
					break;
				}
				case VK_DOWN:
				{
					reny--;
					foot++;
					cell[t_renx][t_reny].thing=0;
					if(t_xiang==1)
					{
						cell[t_renx][t_reny+1].thing=0;
						cell[t_renx][t_reny].thing=2;
					}
					cell[renx][reny].thing=1;
					//�ػ�
					CRect rect;
					rect.left=renx*35+10;
					rect.right=renx*35+10+35;
					rect.top=reny*35+60;
					rect.bottom=(reny+3)*35+60;
					InvalidateRect(&rect);
					//����t_renx��t_reny
					t_renx=renx;
					t_reny=reny;
					//��¼����һ�����ļ�ΪR��������Ϸֻ�ܻ���һ��
					t_nChar=nChar;
					//��t_xiang��ԭΪ0���ڿ��Ʒ���ʱ�����¸�ֵ
					t_xiang=0;
					break;
				}
				case VK_LEFT:
				{
					renx++;
					foot++;
					cell[t_renx][t_reny].thing=0;
					if(t_xiang==1)
					{
						cell[t_renx-1][t_reny].thing=0;
						cell[t_renx][t_reny].thing=2;
					}
					cell[renx][reny].thing=1;
					//�ػ�
					CRect rect;
					rect.left=(renx-2)*35+10;
					rect.right=(renx+1)*35+10;
					rect.top=reny*35+60;
					rect.bottom=reny*35+60+35;
					InvalidateRect(&rect);
					//����t_renx��t_reny
					t_renx=renx;
					t_reny=reny;
					//��¼����һ�����ļ�ΪR��������Ϸֻ�ܻ���һ��
					t_nChar=nChar;
					//��t_xiang��ԭΪ0���ڿ��Ʒ���ʱ�����¸�ֵ
					t_xiang=0;
					break;
				}
				case VK_RIGHT:
				{
					renx--;
					foot++;
					cell[t_renx][t_reny].thing=0;
					if(t_xiang==1)
					{
						cell[t_renx+1][t_reny].thing=0;
						cell[t_renx][t_reny].thing=2;
					}
					cell[renx][reny].thing=1;
					//�ػ�
					CRect rect;
					rect.left=renx*35+10;
					rect.right=(renx+3)*35+10;
					rect.top=reny*35+60;
					rect.bottom=reny*35+60+35;
					InvalidateRect(&rect);
					//����t_renx��t_reny
					t_renx=renx;
					t_reny=reny;
					//��¼����һ�����ļ�ΪR��������Ϸֻ�ܻ���һ��
					t_nChar=nChar;
					//��t_xiang��ԭΪ0���ڿ��Ʒ���ʱ�����¸�ֵ
					t_xiang=0;
					break;	
				}
				default: break;
			}
		}
		default:break;
	}

	//�ػ��Ʋ���
	CRect rect;
	rect.left=20;
	rect.right=90;
	rect.top=20;
	rect.bottom=50;
	InvalidateRect(&rect);

	//�ж��Ƿ��Ѿ���Ϸ����
	jieshu = win();
	if(jieshu == 1)
		return;

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

//����ʤ���жϺ���win()
int CPushingBoxView::win()
{
	for(int i=0;i<m_RowCount;i++)
		for(int j=0;j<m_ColCount;j++)
			if(cell[i][j].weitu==2)
				if(cell[i][j].thing!=2)
					return 0;
	//����ʤ����ʾ������OnDraw��Ԥ�Ȱ�ʤ����ʾλͼ������
	CRect rect;
	rect.left=78;
	rect.right=rect.left+220;
	rect.top=152;
	rect.bottom=rect.top+150;
	InvalidateRect(&rect);
	return 1;
}

//�����ʼ����ֵĺ���
void CPushingBoxView::Start()
{
	jieshu=0;	//��ʼ��Ϊ0��������Ϸδ����
	zanting=1;	//��ʼ��Ϊ1��������Ϸ������
	huiqi=0;	//��ʼ��Ϊ0������ûʹ�û������

	foot=0;	//�Ʋ�

	t_nChar=0;	//��¼��һ������
	t_xiang=0;	//����˸����������Ƿ���Ҫ��ԭ��ȡ���ʾ����Ҫ

	//��ʼ����˸��ť
	//shanshuo��ʼΪ9,��һ��ʼȫ��������t_shanshuoһ��ʼ����shanshuo
	t_shanshuo=shanshuo=9;

	//������һ�������õ���֣����Էǳ��򵥣���ʽ�����Ҫע�͵�
	
	//��ʼ��cell�����weituԪ��
	//����ȡֵ��ͬ��ʾ��ͬ��λͼ
	//ȡ0����յ�
	//ȡ1����ǽ��
	//ȡ2�����ŵ�
	//�Ƚ�����Ԫ����Ϊ�յ�
	for(int i=0;i<m_RowCount;i++)
		for(int j=0;j<m_ColCount;j++)
			cell[i][j].weitu=0;
	//�趨��ЩԪ����ǽ��
	for(int i=0;i<3;i++)
		for(int j=0;j<3;j++)
			cell[i][j].weitu=1;
	for(int i=7;i<10;i++)
		for(int j=6;j<10;j++)
			cell[i][j].weitu=1;
	//�趨��ЩԪ���Ǵ�ŵ�
	cell[1][5].weitu=2;
	cell[4][7].weitu=2;
	cell[7][2].weitu=2;

	//��ʼ��cell�����thingԪ��
	//����ȡֵ��ͬ��ʾ��������������岻ͬ
	//ȡ0ʱ����û�����ڣ��յػ��ŵ㣩����
	//ȡ1ʱ��������
	//ȡ2ʱ����������
	//ȡ3ʱ���������ȷ������
	//�ȼ�������Ԫ�ض�û�з�����
	for(int i=0;i<m_RowCount;i++)
		for(int j=0;j<m_ColCount;j++)
			cell[i][j].thing=0;
	//�趨��Щ�յ������������
	cell[4][2].thing=2;
	cell[3][4].thing=2;
	cell[4][4].thing=2;

	//��ʼ���˵�λ��
	renx=t_renx=4;
	reny=t_reny=1;

	//�����ڵ�cell����thing=1���������������һ����
	cell[renx][reny].thing=1;
	

	//������һ����ʽ�õ����
	/*
	//��ʼ��game���飬Ҳ��������
	int game[10][10]=
	{
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 0, 0, 0, 1, 1, 1, 1, 1},
		{1, 1, 0, 1, 0, 0, 0, 1, 1, 1},
		{1, 0, 2, 2, 0, 2, 0, 1, 1, 1},
		{1, 0, 0, 0, 0, 0, 1, 1, 1, 1},
		{1, 1, 1, 0, 1, 2, 1, 1, 1, 1},
		{1, 1, 1, 0, 0, 0, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};
	//��ʼ��cell�����weituԪ�أ�Ҳ����gameת�ø�cell.weitu��
	for(int i=0;i<m_RowCount;i++)
		for(int j=0;j<m_ColCount;j++)
		cell[i][j].weitu=game[j][i];
	
	//��ʼ��cell�����thingԪ��
	//����ȡֵ��ͬ��ʾ��������������岻ͬ
	//ȡ0ʱ����û�����ڣ��յػ��ŵ㣩����
	//ȡ1ʱ��������
	//ȡ2ʱ����������
	//ȡ3ʱ���������ȷ������
	//�ȼ�������Ԫ�ض�û�з�����
	for(int i=0;i<m_RowCount;i++)
		for(int j=0;j<m_ColCount;j++)
			cell[i][j].thing=0;
	//�趨��Щ�յ������������
	cell[2][2].thing=2;
	cell[4][2].thing=2;
	cell[3][4].thing=2;
	cell[4][4].thing=2;

	//��ʼ���˵�λ��
	renx=t_renx=4;
	reny=t_reny=1;

	//�����ڵ�cell����thing=1���������������һ����
	cell[renx][reny].thing=1;
	*/
}

//OnCreate����
int CPushingBoxView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	//���ɼ�ʱ����1.5s��ʱһ��
	SetTimer(1,1500,NULL);

	return 0;
}

//OnTimer����
void CPushingBoxView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	//��ʱ��Ϊ�������������
	srand((unsigned)time(NULL));
	//�������0~8��ʾ9����ť˭���ڸ���״̬
	shanshuo=(rand())%9;
	//�ػ�������ť��������һ��������ť�ָ�
	shuaxin(t_shanshuo);
	shuaxin(shanshuo);
	t_shanshuo=shanshuo;	//��¼��ǰ��˸��ť�ı��

	CView::OnTimer(nIDEvent);
}

//ˢ�º���
void CPushingBoxView::shuaxin(int num)
{
	CRect rect;
	switch(num)
	{
		//ȷ��
		case 0:
			rect.left=20;
			rect.right=rect.left+110;
			rect.top=430;
			rect.bottom=rect.top+70;
			InvalidateRect(&rect);
			break;
		//��
		case 1:
			rect.left=130;
			rect.right=rect.left+110;
			rect.top=430;
			rect.bottom=rect.top+70;
			InvalidateRect(&rect);
			break;
		//����
		case 2:
			rect.left=240;
			rect.right=rect.left+110;
			rect.top=430;
			rect.bottom=rect.top+70;
			InvalidateRect(&rect);
			break;
		//��
		case 3:
			rect.left=20;
			rect.right=rect.left+110;
			rect.top=500;
			rect.bottom=rect.top+70;
			InvalidateRect(&rect);
			break;
		//��
		case 4:
			rect.left=130;
			rect.right=rect.left+110;
			rect.top=500;
			rect.bottom=rect.top+70;
			InvalidateRect(&rect);
			break;
		//��
		case 5:
			rect.left=240;
			rect.right=rect.left+110;
			rect.top=500;
			rect.bottom=rect.top+70;
			InvalidateRect(&rect);
			break;
		//��ͣ
		case 6:
			rect.left=20;
			rect.right=rect.left+110;
			rect.top=570;
			rect.bottom=rect.top+70;
			InvalidateRect(&rect);
			break;
		//��
		case 7:
			rect.left=130;
			rect.right=rect.left+110;
			rect.top=570;
			rect.bottom=rect.top+70;
			InvalidateRect(&rect);
			break;
		//����
		case 8:
			rect.left=240;
			rect.right=rect.left+110;
			rect.top=570;
			rect.bottom=rect.top+70;
			InvalidateRect(&rect);
			break;
		default:break;
	}
}

int CPushingBoxView::pause(int t_zanting)
{
	//������ո񣬾���ͣ��Ϸ�����ڻ�������ʾ
	t_zanting=t_zanting*(-1);
	CRect rect;
	rect.left=78;
	rect.right=rect.left+220;
	rect.top=152;
	rect.bottom=rect.top+150;
	InvalidateRect(&rect);
	return t_zanting;
}