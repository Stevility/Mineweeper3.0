#include "cApp.h"
#include "cMain.h"


cApp::cApp()
{

}


cApp::~cApp()
{

}

bool cApp::onInit()
{
	m_frame1 = new cMain();
	m_frame1->Show(true);

	return true;
}

