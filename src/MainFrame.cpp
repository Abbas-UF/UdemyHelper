#include "MainFrame.h"
#include <wx/wx.h>
#include <wx/gbsizer.h>

MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
	// Read/Make Lists
	udemyData.readCSV("Files/Udemy_Clean.csv");
	wxArrayString categories = udemyData.getCategories();
	wxArrayString filters;
	filters.Add("Alphabetic");
	filters.Add("Price");
	filters.Add("Rating");

	// Create main panel
	wxPanel* panel = new wxPanel(this, wxID_ANY);

	// Create input fields
	categoriesList = new wxListBox(panel, wxID_ANY);
	categoriesList->Set(categories);
	ratingsSlider = new wxSlider(panel, wxID_ANY, 3, 0, 5, wxDefaultPosition, wxSize(100, -1));
	filterList = new wxChoice(panel, wxID_ANY, wxDefaultPosition, wxSize(100, -1), filters);
	applyButton = new wxButton(panel, wxID_ANY, "Apply", wxDefaultPosition, wxSize(-1, 50));

	// Create output fields
	courseList = new wxListCtrl(panel, wxID_ANY);
	courseInfo.title = new wxStaticText(panel, wxID_ANY, "");
	courseInfo.topic = new wxStaticText(panel, wxID_ANY, "");
	courseInfo.category = new wxStaticText(panel, wxID_ANY, "");
	courseInfo.subcategory = new wxStaticText(panel, wxID_ANY, "");
	courseInfo.numRatings = new wxStaticText(panel, wxID_ANY, "");
	courseInfo.rating = new wxStaticText(panel, wxID_ANY, "");
	courseInfo.hiRating = new wxStaticText(panel, wxID_ANY, "");
	courseInfo.loRating = new wxStaticText(panel, wxID_ANY, "");
	courseInfo.instructor = new wxStaticText(panel, wxID_ANY, "");
	courseInfo.language = new wxStaticText(panel, wxID_ANY, "");
	courseInfo.numArticles = new wxStaticText(panel, wxID_ANY, "");
	courseInfo.numPracticeTests = new wxStaticText(panel, wxID_ANY, "");
	courseInfo.numCodingExercises = new wxStaticText(panel, wxID_ANY, "");
	courseInfo.additionalResources = new wxStaticText(panel, wxID_ANY, "");
	courseInfo.videoHours = new wxStaticText(panel, wxID_ANY, "");
	courseInfo.bestSeller = new wxStaticText(panel, wxID_ANY, "");
	courseInfo.price = new wxStaticText(panel, wxID_ANY, "");

	// Temp Headers
	wxFont* boldFont = new wxFont();
	boldFont->MakeBold();
	wxStaticText* categoriesHeader = new wxStaticText(panel, wxID_ANY, "Categories:");
	categoriesHeader->SetFont(*boldFont);
	wxStaticText* coursesHeader = new wxStaticText(panel, wxID_ANY, "Courses:");
	coursesHeader->SetFont(*boldFont);
	wxStaticText* ratingsHeader = new wxStaticText(panel, wxID_ANY, "Rating:");
	ratingsHeader->SetFont(*boldFont);
	wxStaticText* filterHeader = new wxStaticText(panel, wxID_ANY, "Sort By:");
	filterHeader->SetFont(*boldFont);
	wxStaticText* titleHeader = new wxStaticText(panel, wxID_ANY, "Course Title:");
	titleHeader->SetFont(*boldFont);
	wxStaticText* topicHeader = new wxStaticText(panel, wxID_ANY, "Topic:");
	topicHeader->SetFont(*boldFont);
	wxStaticText* categoryHeader = new wxStaticText(panel, wxID_ANY, "Category:");
	categoryHeader->SetFont(*boldFont);
	wxStaticText* subcategoryHeader = new wxStaticText(panel, wxID_ANY, "Subcategory:");
	subcategoryHeader->SetFont(*boldFont);
	wxStaticText* numRatingsHeader = new wxStaticText(panel, wxID_ANY, "Number of Ratings:");
	numRatingsHeader->SetFont(*boldFont);
	wxStaticText* avgRatingHeader = new wxStaticText(panel, wxID_ANY, "Average Rating:");
	avgRatingHeader->SetFont(*boldFont);
	wxStaticText* hiRatingHeader = new wxStaticText(panel, wxID_ANY, "Highest Rating:");
	hiRatingHeader->SetFont(*boldFont);
	wxStaticText* loRatingHeader = new wxStaticText(panel, wxID_ANY, "Lowest Rating:");
	loRatingHeader->SetFont(*boldFont);
	wxStaticText* instructorHeader = new wxStaticText(panel, wxID_ANY, "Instructor:");
	instructorHeader->SetFont(*boldFont);
	wxStaticText* languageHeader = new wxStaticText(panel, wxID_ANY, "Language:");
	languageHeader->SetFont(*boldFont);
	wxStaticText* numArticlesHeader = new wxStaticText(panel, wxID_ANY, "Number of Articles:");
	numArticlesHeader->SetFont(*boldFont);
	wxStaticText* numPracticeTestsHeader = new wxStaticText(panel, wxID_ANY, "Number of Practice Tests:");
	numPracticeTestsHeader->SetFont(*boldFont);
	wxStaticText* numCodingExercisesHeader = new wxStaticText(panel, wxID_ANY, "Number of Coding Exercises:");
	numCodingExercisesHeader->SetFont(*boldFont);
	wxStaticText* additionalResourcesHeader = new wxStaticText(panel, wxID_ANY, "Additional Resources:");
	additionalResourcesHeader->SetFont(*boldFont);
	wxStaticText* videoHoursHeader = new wxStaticText(panel, wxID_ANY, "Hours of Videos:");
	videoHoursHeader->SetFont(*boldFont);
	wxStaticText* bestSellerHeader = new wxStaticText(panel, wxID_ANY, "Best Seller:");
	bestSellerHeader->SetFont(*boldFont);
	wxStaticText* priceHeader = new wxStaticText(panel, wxID_ANY, "Price:");
	priceHeader->SetFont(*boldFont);

	// Sizer (Layout)
	wxBoxSizer* sizerM = new wxBoxSizer(wxVERTICAL);
	wxGridBagSizer* gridSizer = new wxGridBagSizer(10, 20);

	gridSizer->Add(categoriesHeader, wxGBPosition(0, 0), wxGBSpan(1, 1), wxALIGN_LEFT);
	gridSizer->Add(categoriesList, wxGBPosition(1, 0), wxGBSpan(4, 2), wxEXPAND);

	gridSizer->Add(filterHeader, wxGBPosition(5, 0), wxGBSpan(1, 1), wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL);
	gridSizer->Add(filterList, wxGBPosition(6, 0), wxGBSpan(1, 1), wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL);

	gridSizer->Add(ratingsHeader, wxGBPosition(7, 0), wxGBSpan(1, 1), wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL);
	gridSizer->Add(ratingsSlider, wxGBPosition(8, 0), wxGBSpan(1, 1), wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL);

	gridSizer->Add(applyButton, wxGBPosition(5, 1), wxGBSpan(4, 1), wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL);

	gridSizer->Add(coursesHeader, wxGBPosition(0, 2), wxGBSpan(1, 1), wxALIGN_LEFT);
	gridSizer->Add(courseList, wxGBPosition(1, 2), wxGBSpan(8, 3), wxEXPAND);

	// TODO: Split the output between bottom left and bottom right
	gridSizer->Add(titleHeader, wxGBPosition(9, 0), wxGBSpan(1, 1), wxALIGN_LEFT);
	gridSizer->Add(topicHeader, wxGBPosition(10, 0), wxGBSpan(1, 1), wxALIGN_LEFT);
	gridSizer->Add(categoryHeader, wxGBPosition(11, 0), wxGBSpan(1, 1), wxALIGN_LEFT);
	gridSizer->Add(subcategoryHeader, wxGBPosition(12, 0), wxGBSpan(1, 1), wxALIGN_LEFT);
	gridSizer->Add(numRatingsHeader, wxGBPosition(13, 0), wxGBSpan(1, 1), wxALIGN_LEFT);
	gridSizer->Add(avgRatingHeader, wxGBPosition(14, 0), wxGBSpan(1, 1), wxALIGN_LEFT);
	gridSizer->Add(hiRatingHeader, wxGBPosition(15, 0), wxGBSpan(1, 1), wxALIGN_LEFT);
	gridSizer->Add(loRatingHeader, wxGBPosition(16, 0), wxGBSpan(1, 1), wxALIGN_LEFT);
	gridSizer->Add(instructorHeader, wxGBPosition(17, 0), wxGBSpan(1, 1), wxALIGN_LEFT);
	gridSizer->Add(languageHeader, wxGBPosition(18, 0), wxGBSpan(1, 1), wxALIGN_LEFT);
	gridSizer->Add(numArticlesHeader, wxGBPosition(19, 0), wxGBSpan(1, 1), wxALIGN_LEFT);
	gridSizer->Add(numPracticeTestsHeader, wxGBPosition(20, 0), wxGBSpan(1, 1), wxALIGN_LEFT);
	gridSizer->Add(numCodingExercisesHeader, wxGBPosition(21, 0), wxGBSpan(1, 1), wxALIGN_LEFT);
	gridSizer->Add(additionalResourcesHeader, wxGBPosition(22, 0), wxGBSpan(1, 1), wxALIGN_LEFT);
	gridSizer->Add(videoHoursHeader, wxGBPosition(23, 0), wxGBSpan(1, 1), wxALIGN_LEFT);
	gridSizer->Add(bestSellerHeader, wxGBPosition(24, 0), wxGBSpan(1, 1), wxALIGN_LEFT);
	gridSizer->Add(priceHeader, wxGBPosition(25, 0), wxGBSpan(1, 1), wxALIGN_LEFT);

	gridSizer->AddGrowableRow(1);
	gridSizer->AddGrowableCol(2);
	gridSizer->AddGrowableCol(3);

	sizerM->Add(gridSizer, 1, wxEXPAND | wxALL, 20);
	panel->SetSizerAndFit(sizerM);

	SetMinSize(wxSize(600, 500));
}

void MainFrame::updateCourseInfo(Course course)
{
	// TODO: Test to see if output is correct.
	courseInfo.title->SetLabel(course.title);
	courseInfo.topic->SetLabel(course.topic);
	courseInfo.category->SetLabel(course.category);
	courseInfo.subcategory->SetLabel(course.subcategory);
	courseInfo.numRatings->SetLabel(to_string(course.numRatings));
	courseInfo.rating->SetLabel(to_string(course.rating));
	courseInfo.hiRating->SetLabel(to_string(course.hiRating));
	courseInfo.loRating->SetLabel(to_string(course.loRating));
	courseInfo.instructor->SetLabel(course.instructor);
	courseInfo.language->SetLabel(course.language);
	courseInfo.numArticles->SetLabel(to_string(course.numArticles));
	courseInfo.numPracticeTests->SetLabel(to_string(course.numPracticeTests));
	courseInfo.numCodingExercises->SetLabel(to_string(course.numCodingExercises));
	courseInfo.additionalResources->SetLabel(to_string(course.additionalResources));
	courseInfo.videoHours->SetLabel(to_string(course.videoHours));
	courseInfo.bestSeller->SetLabel(to_string(course.bestSeller));
	courseInfo.price->SetLabel(to_string(course.price));
}