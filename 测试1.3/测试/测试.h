
// ����.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// C����App: 
// �йش����ʵ�֣������ ����.cpp
//

class C����App : public CWinApp
{
public:
	C����App();
	float m_teach;
	float m_plat;
	float m_audio;
	int   m_speaker;
	int   m_mic;
	int   m_camera;

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern C����App theApp;