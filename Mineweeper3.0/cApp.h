#pragma once
#include "wx/wx.h"
#include "cMain.h"

class cApp : public wxApp
{
public:
	cApp();
	~cApp();

private:
	cMain* m_frame1 = nullptr;

public:
	bool OnInit() override
	{
		m_frame1 = new cMain();
		m_frame1->Show(true);

		return true;
	}
};