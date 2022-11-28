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

class MainFrame : public wxFrame
{
	private:
		// Data
		UdemyData udemyData;

		// Input Fields
		wxListCtrl* categoriesList;
		wxSlider* ratingsSlider;
		wxChoice* filterList;
		wxButton* applyButton;

		// Output Fields
		wxListCtrl* courseList;
		wxCourseInfo courseInfo;

		// Private Helpers
		void updateCourseInfo(Course course);

	public:
		MainFrame(const wxString& title);
};