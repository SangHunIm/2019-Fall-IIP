﻿
// IIPDoc.h: CIIPDoc 클래스의 인터페이스
//


#pragma once
#include "Sample.h"
#include "Classifier.h"

class CIIPDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CIIPDoc() noexcept;
	DECLARE_DYNCREATE(CIIPDoc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CIIPDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	unsigned int height, width;
	unsigned char *m_InImage;
	unsigned char *m_OutImage;
	afx_msg void OnArithmetic();
	afx_msg void OnHistogram();
	afx_msg void OnBinarization();
	unsigned char m_Threshold;
	afx_msg void OnGonzalez();
	afx_msg void OnOtsu();
	afx_msg void OnLowpassfilter();
	afx_msg void OnHighpassfilter();
	afx_msg void OnMedianfilter();
	afx_msg void OnFdct();
	double* m_Dct;
	afx_msg void OnIdct();

	Sample samples[16];
	double weight[16];
	int turn;
	Classifier classifierList[100];
	afx_msg void OnAdaboostInit();
	double AdaboostResult();
	afx_msg void OnAdaboostNext();
	afx_msg void OnAdaboosttest();
	afx_msg void OnPrewitt();
	afx_msg void OnSobel();
	afx_msg void OnDerivativeofgaussian();
	afx_msg void OnZoomin();
	afx_msg void OnZoomout();
	afx_msg void OnRotation();
	afx_msg void OnBindilate();
	afx_msg void OnBineros();
	afx_msg void OnBinopen();
	afx_msg void OnBinclose();
	afx_msg void OnGraydilate();
	afx_msg void OnGrayeros();
	afx_msg void OnHarriscorner();
	afx_msg void OnMad();
	unsigned char m_RefImage[20][20];
	afx_msg void OnMadsurface();
};
