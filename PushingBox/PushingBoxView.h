
// PushingBoxView.h : interface of the CPushingBoxView class
//

#pragma once

//TODO
//�Զ�����cell��������ָ��һ�������ӣ�Ԫ�أ�
class Cell
{
public:
	int weitu;
	//����ȡֵ��ͬ��ʾ��ͬ��λͼ
	//ȡ0����յ�
	//ȡ1����ǽ��
	//ȡ2�����ŵ�
	
	int thing;
	//����ȡֵ��ͬ��ʾ��������������岻ͬ
	//ȡ0ʱ����û�����ڣ��յػ��ŵ㣩����
	//ȡ1ʱ��������
	//ȡ2ʱ����������

};

class CPushingBoxView : public CView
{
protected: // create from serialization only
	CPushingBoxView();
	DECLARE_DYNCREATE(CPushingBoxView)

// Attributes
public:
	CPushingBoxDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CPushingBoxView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()

//TODO
public:
	//���ݳ�Ա:
	int m_RowCount;	//��������
	int m_ColCount;	//��������
	Cell cell[10][10];	//�����淶Χ
	CBitmap m_Bitmap[3];	//Ԫ��λͼ����
	CBitmap m_Thing[3];	//��Ʒλͼ����
	int foot;	//����

	CBitmap m_Anniu;	//��ťλͼ��һ���Ź������
	CBitmap m_AnniuShan;	//��˸�İ�ť
	int shanshuo;	//���ȡ0~8�������ĸ���ť���ڸ���״̬
	int t_shanshuo;	//��¼��һ�������İ�ť���

	CBitmap m_Title;	//LOGOλͼ
	CBitmap m_Pause;	//��ͣλͼ
	CBitmap m_Win;	//ʤ��λͼ
	CBitmap m_Regret;	//����λͼ
	
	int renx;	//��¼�˵�λ��
	int reny;
	int t_renx;	//��¼�˵���һʱ�̵�λ��
	int t_reny;
	unsigned int t_nChar;	//��¼��һ�������������ʲô�������ʱ��Ҫ��
	int	t_xiang;	//����ʱ����Ҫ�����˸����������Ƿ�Ҫ��ԭ��ȡ0ʱ��ʾ���ã�1ʱ��ʾ�� 

	int jieshu;	//ȡ0ʱ������Ϸ��δ������ȡ1ʱ��ʾ����
	int zanting;	//ȡ1ʱ��Ϸ����,ȡ-1��Ϸ��ͣ
	int huiqi;	//ȡ0ʱ��Ϸ������ȡ1ʱ������ֻ�ܳ���һ�Ρ�����ʾ����Ϸ��ͣ

	//������Ա:
	int pause(int t_zanting);	//�ж��Ƿ���ͣ
	int win();	//�ж��Ƿ�ʤ��
	void Start();	//�趨ǽ�ڡ����Ӳ���
	void shuaxin(int num);	//ˢ�º������βδ���ˢ����һ����ť
	
	//��Ϣ��Ա:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};

#ifndef _DEBUG  // debug version in PushingBoxView.cpp
inline CPushingBoxDoc* CPushingBoxView::GetDocument() const
   { return reinterpret_cast<CPushingBoxDoc*>(m_pDocument); }
#endif