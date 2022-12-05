#pragma once

#include "UdemyData.h"
#include <wx/wx.h>
#include <wx/listctrl.h>

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

struct wxCoursesList
{
	wxListBox* listBox;
	vector<Course> coursesVector;
};

enum SORT_TYPE { SHELL = 02, MERGE = 00 };

class MainFrame : public wxFrame
{
	private:
		// Data
		UdemyData udemyData;
		SORT_TYPE sortType;

		// Input Fields
		wxListBox* categoriesList;
		wxSlider* ratingsSlider;
		wxChoice* filterList;
		wxButton* applyButton;

		// Output Fields
		wxCoursesList coursesList;
		wxCourseInfo courseInfo;

		// Sort Button
		wxButton* sortButton;

		// Private Helpers
		void updateCourseInfo(Course course);
		vector<string> getSelectedCategories();
		SORT_FILTER getSelectedFilter();

		// Private Binds
		void onSortPressed(wxCommandEvent& evt);
		void onApplyPressed(wxCommandEvent& evt);
		void onCourseSelected(wxCommandEvent& evt);

	public:
		// Constructor
		MainFrame(const wxString& title);
};