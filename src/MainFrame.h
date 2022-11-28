#pragma once

#include "UdemyData.h"
#include <wx/wx.h>
#include <wx/listctrl.h>

class MainFrame : public wxFrame
{
	private:
		// Data
		UdemyData udemyData;

		// Controls
		wxListCtrl* categoriesList;
		wxSlider* ratingsSlider;
		wxButton* applyButton;

	public:
		MainFrame(const wxString& title);
};