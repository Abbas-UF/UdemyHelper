#pragma once

#include "UdemyData.h"
#include <wx/wx.h>
#include <wx/listctrl.h>

struct wxCoursesList
{
	wxListBox* listBox;
	vector<Course> coursesVector;
};

struct wxCourseInfo
{
	wxStaticText* title;

	wxStaticText* topic;
	wxStaticText* category;
	wxStaticText* subcategory;

	wxStaticText* numRatings;
	wxStaticText* rating;
	wxStaticText* hiRating;
	wxStaticText* loRating;

	wxStaticText* instructor;
	wxStaticText* language;

	wxStaticText* numArticles;
	wxStaticText* numPracticeTests;
	wxStaticText* numCodingExercises;

	wxStaticText* additionalResources;
	// Different data type for duration?
	wxStaticText* videoHours;

	wxStaticText* bestSeller;

	wxStaticText* price;
};

class MainFrame : public wxFrame
{
	private:
		// Data
		UdemyData udemyData;

		// Input Fields
		wxListBox* categoriesList;
		wxSlider* ratingsSlider;
		wxChoice* filterList;
		wxButton* applyButton;

		// Output Fields
		wxCoursesList coursesList;
		wxCourseInfo courseInfo;

		// Private Helpers
		void updateCourseInfo(Course course);
		vector<string> getSelectedCategories();

		// Private Binds
		void onApplyPressed(wxCommandEvent& evt);
		void onCourseSelected(wxCommandEvent& evt);

	public:
		MainFrame(const wxString& title);
};