#pragma once
#include "wx/wx.h"

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

public:
	int nFieldWi = 10;
	int nFieldHe = 10;
	wxButton** btn;
	int* nField = nullptr;
	bool bFirstCl = true;

	void OnButtonClicked(wxCommandEvent &evt);

	wxDECLARE_EVENT_TABLE();
};
