#include "cMain.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
EVT_BUTTON(10001, OnButtonClicked)
wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "MINESWEEPER!", wxPoint(500, 200), wxSize(800, 600))
{
	btn = new wxButton * [nFieldWi * nFieldHe];
	wxGridSizer* grid = new wxGridSizer(nFieldWi, nFieldHe, 0, 0);

	nField = new int[nFieldWi * nFieldHe];

	wxFont font(24, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD, false);

	for (int x = 0; x < nFieldWi; x++)
	{
		for (int y = 0; y < nFieldHe; y++)
		{
			btn[y * nFieldWi + x] = new wxButton(this, 10000 + (y * nFieldWi + x));
			btn[y * nFieldWi + x]->SetFont(font);
			grid->Add(btn[y * nFieldWi + x], 1, wxEXPAND | wxALL);

			btn[y * nFieldWi + x]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnButtonClicked, this);
			nField[y * nFieldWi + x] = 0;
		}
	}

	this->SetSizer(grid);
	grid->Layout();
}

cMain::~cMain()
{
	delete[]btn;
}

void cMain::OnButtonClicked(wxCommandEvent& evt)
{
	int x = (evt.GetId() - 10000) % nFieldWi;
	int y = (evt.GetId() - 10000) / nFieldWi;

	if (bFirstCl)
	{
		int mines = 30;

		while (mines)
		{
			int rx = rand() % nFieldWi;
			int ry = rand() % nFieldHe;

			if (nField[ry * nFieldWi + rx] == 0 && rx != x && ry != y)
			{
				nField[ry * nFieldWi + rx] = -1;
				mines--;
			}
		}
		bFirstCl = false;
	}

	//Disable button
	btn[y * nFieldWi + x]->Enable(false);

	//if hit a mine
	if (nField[y * nFieldWi + x] == -1)
	{
		wxMessageBox("BOOOOM! You dead!");
		//reset game
		bFirstCl = true;
		for (int x = 0; x < nFieldWi; x++)
		{
			for (int y = 0; y < nFieldHe; y++)
			{
				nField[y * nFieldWi + x] = 0;
				btn[y * nFieldWi + x]->SetLabel("");
				btn[y * nFieldWi + x]->Enable(true);
			}
		}
	}
	else
	{
		//count neighbouring mines
		int mines_alive = 0;
		for (int i = -1; i < 2; i++)
		{
			for (int j = -1; j < 2; j++)
			{
				if (x + i >= 0 && x + 1 < nFieldWi && y + j >= 0 && y + j < nFieldHe)
				{
					if (nField[(y + j) * nFieldWi + (x + i)] == -1)
					{
						mines_alive++;
					}
				}
			}
		}

		//Show mine count if > 0
		if (mines_alive > 0)
		{
			btn[y * nFieldWi + x]->SetLabel(std::to_string(mines_alive));
		}
	}
	evt.Skip();
}