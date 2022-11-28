#include "MainFrame.h"
#include <wx/wx.h>
#include <wx/gbsizer.h>

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
	// Creat main panel
	wxPanel* panel = new wxPanel(this, wxID_ANY);

	// Create buttons
	categoriesList = new wxListCtrl(panel, wxID_ANY);
	ratingsSlider = new wxSlider(panel, wxID_ANY, 3, 0, 5);
	applyButton = new wxButton(panel, wxID_ANY, "Apply");

	// Sizer
	wxGridBagSizer* gridSizer = new wxGridBagSizer(5, 5);
	gridSizer->Add(categoriesList);
	gridSizer->Add(ratingsSlider);
	gridSizer->Add(applyButton);

	panel->SetSizerAndFit(gridSizer);
}