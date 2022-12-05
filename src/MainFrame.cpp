#include "MainFrame.h"
#include <wx/wx.h>
#include <wx/gbsizer.h>

// Private Helpers
void MainFrame::updateCourseInfo(Course course)
{
	courseInfo.title->SetLabel(course.title);
	courseInfo.topic->SetLabel(course.topic);
	courseInfo.category->SetLabel(course.category);
	courseInfo.subcategory->SetLabel(course.subcategory);
	courseInfo.numRatings->SetLabel(to_string(course.numRatings));
	courseInfo.rating->SetLabel(wxString::Format("%0.2f", course.rating));
	courseInfo.hiRating->SetLabel(wxString::Format("%0.2f", course.hiRating));
	courseInfo.loRating->SetLabel(wxString::Format("%0.2f", course.loRating));
	courseInfo.instructor->SetLabel(course.instructor);
	courseInfo.language->SetLabel(course.language);
	courseInfo.numArticles->SetLabel(to_string(course.numArticles));
	courseInfo.numPracticeTests->SetLabel(to_string(course.numPracticeTests));
	courseInfo.numCodingExercises->SetLabel(to_string(course.numCodingExercises));
	courseInfo.additionalResources->SetLabel(to_string(course.additionalResources));
	courseInfo.videoHours->SetLabel(wxString::Format("%0.2f", course.videoHours));
	courseInfo.bestSeller->SetLabel(course.strBestSeller);
	courseInfo.price->SetLabel("$" + wxString::Format("%0.2f", course.price));
}

vector<string> MainFrame::getSelectedCategories()
{
	wxArrayInt selectedIndexes;
	categoriesList->GetSelections(selectedIndexes);

	vector<string> result;

	for (auto i = selectedIndexes.begin(); i != selectedIndexes.end(); i++)
	{
		result.push_back(categoriesList->GetString(*i).ToStdString());
	}

	return result;
}

SORT_FILTER MainFrame::getSelectedFilter()
{
	if (filterList->GetStringSelection() == "Rating")
	{
		return SORT_FILTER::RATING;
	}
	else if (filterList->GetStringSelection() == "Price")
	{
		return SORT_FILTER::PRICE;
	}
	else if (filterList->GetStringSelection() == "Number of Ratings")
	{
		return SORT_FILTER::NUM_RATING;
	}
	else
	{
		return SORT_FILTER::ALPHA;
	}
}

// Private Binds
void MainFrame::onSortPressed(wxCommandEvent& evt)
{
	if (sortType == SORT_TYPE::SHELL)
	{
		sortButton->SetLabel("Sort: Merge");
		sortType = SORT_TYPE::MERGE;
	}
	else
	{
		sortButton->SetLabel("Sort: Shell");
		sortType = SORT_TYPE::SHELL;
	}
}

void MainFrame::onApplyPressed(wxCommandEvent& evt)
{
	vector<string> selectedCategories = getSelectedCategories();

	if (!selectedCategories.empty())
	{
		coursesList.coursesVector = udemyData.getCoursesByRating(selectedCategories, ratingsSlider->GetValue());

		chrono::steady_clock::time_point beg;
		chrono::steady_clock::time_point end;

		if (sortType == SORT_TYPE::SHELL)
		{
			beg = chrono::high_resolution_clock::now();
			udemyData.shellSort(coursesList.coursesVector, getSelectedFilter());
			end = chrono::high_resolution_clock::now();
		}
		else
		{
			beg = chrono::high_resolution_clock::now();
			udemyData.mergeSort(coursesList.coursesVector, 0, coursesList.coursesVector.size() - 1, getSelectedFilter());
			end = chrono::high_resolution_clock::now();
		}

		wxLogStatus("Sort Time: " + (wxString) to_string(chrono::duration_cast<chrono::milliseconds>(end - beg).count()) + "ms");

		wxArrayString output;
		for (int i = 0; i < coursesList.coursesVector.size(); i++)
		{
			output.Add(coursesList.coursesVector[i].title);
		}

		coursesList.listBox->Set(output);
	}
}

void MainFrame::onCourseSelected(wxCommandEvent& evt)
{
	updateCourseInfo(coursesList.coursesVector[coursesList.listBox->GetSelection()]);
}

// Constructor
MainFrame::MainFrame(const wxString& title) : wxFrame(nullptr, wxID_ANY, title)
{
	// Read/Make Lists
	udemyData.readCSV("Files/Udemy_Clean.csv");
	vector<wxString> filters = { "Alphabetic" , "Price", "Rating", "Number of Ratings" };
	vector<wxString> categories = udemyData.getWXCategories();

	// Create main panel
	wxPanel* panel = new wxPanel(this, wxID_ANY);

	// Create input fields
	categoriesList = new wxListBox(panel, wxID_ANY, wxDefaultPosition, wxSize(400, -1), categories.size(), &categories[0], wxLB_MULTIPLE);
	ratingsSlider = new wxSlider(panel, wxID_ANY, 3, 0, 5, wxDefaultPosition, wxDefaultSize, wxSL_MIN_MAX_LABELS | wxSL_AUTOTICKS);
	filterList = new wxChoice(panel, wxID_ANY, wxDefaultPosition, wxDefaultSize, filters.size(), &filters[0]);
	filterList->SetSelection(0);
	applyButton = new wxButton(panel, wxID_ANY, "Apply", wxDefaultPosition, wxSize(-1, 50));

	// Sort Button & Data
	sortButton = new wxButton(panel, wxID_ANY, "Sort: Shell", wxDefaultPosition, wxDefaultSize);
	sortType = SORT_TYPE::SHELL;

	// Create output fields
	coursesList.listBox = new wxListBox(panel, wxID_ANY, wxDefaultPosition, wxSize(750, -1));
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
	gridSizer->Add(coursesList.listBox, wxGBPosition(1, 2), wxGBSpan(8, 3), wxEXPAND);
	gridSizer->Add(sortButton, wxGBPosition(0, 4), wxGBSpan(1, 1), wxALIGN_RIGHT);

	gridSizer->Add(topicHeader, wxGBPosition(9, 0), wxGBSpan(1, 1), wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
	gridSizer->Add(categoryHeader, wxGBPosition(10, 0), wxGBSpan(1, 1), wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
	gridSizer->Add(subcategoryHeader, wxGBPosition(11, 0), wxGBSpan(1, 1), wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
	gridSizer->Add(titleHeader, wxGBPosition(9, 2), wxGBSpan(1, 1), wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
	gridSizer->Add(instructorHeader, wxGBPosition(10, 2), wxGBSpan(1, 1), wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
	gridSizer->Add(languageHeader, wxGBPosition(11, 2), wxGBSpan(1, 1), wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
	gridSizer->Add(numRatingsHeader, wxGBPosition(13, 2), wxGBSpan(1, 1), wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
	gridSizer->Add(avgRatingHeader, wxGBPosition(14, 2), wxGBSpan(1, 1), wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
	gridSizer->Add(hiRatingHeader, wxGBPosition(15, 2), wxGBSpan(1, 1), wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
	gridSizer->Add(loRatingHeader, wxGBPosition(16, 2), wxGBSpan(1, 1), wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
	gridSizer->Add(numArticlesHeader, wxGBPosition(13, 0), wxGBSpan(1, 1), wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
	gridSizer->Add(numPracticeTestsHeader, wxGBPosition(14, 0), wxGBSpan(1, 1), wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
	gridSizer->Add(numCodingExercisesHeader, wxGBPosition(15, 0), wxGBSpan(1, 1), wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
	gridSizer->Add(additionalResourcesHeader, wxGBPosition(16, 0), wxGBSpan(1, 1), wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
	gridSizer->Add(videoHoursHeader, wxGBPosition(17, 0), wxGBSpan(1, 1), wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
	gridSizer->Add(bestSellerHeader, wxGBPosition(18, 2), wxGBSpan(1, 1), wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
	gridSizer->Add(priceHeader, wxGBPosition(18, 0), wxGBSpan(1, 1), wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);

	gridSizer->Add(courseInfo.topic, wxGBPosition(9, 1), wxGBSpan(1, 1), wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
	gridSizer->Add(courseInfo.category, wxGBPosition(10, 1), wxGBSpan(1, 1), wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
	gridSizer->Add(courseInfo.subcategory, wxGBPosition(11, 1), wxGBSpan(1, 1), wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
	gridSizer->Add(courseInfo.title, wxGBPosition(9, 3), wxGBSpan(1, 1), wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
	gridSizer->Add(courseInfo.instructor, wxGBPosition(10, 3), wxGBSpan(1, 1), wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
	gridSizer->Add(courseInfo.language, wxGBPosition(11, 3), wxGBSpan(1, 1), wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
	gridSizer->Add(courseInfo.numRatings, wxGBPosition(13, 3), wxGBSpan(1, 1), wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
	gridSizer->Add(courseInfo.rating, wxGBPosition(14, 3), wxGBSpan(1, 1), wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
	gridSizer->Add(courseInfo.hiRating, wxGBPosition(15, 3), wxGBSpan(1, 1), wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
	gridSizer->Add(courseInfo.loRating, wxGBPosition(16, 3), wxGBSpan(1, 1), wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
	gridSizer->Add(courseInfo.numArticles, wxGBPosition(13, 1), wxGBSpan(1, 1), wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
	gridSizer->Add(courseInfo.numPracticeTests, wxGBPosition(14, 1), wxGBSpan(1, 1), wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
	gridSizer->Add(courseInfo.numCodingExercises, wxGBPosition(15, 1), wxGBSpan(1, 1), wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
	gridSizer->Add(courseInfo.additionalResources, wxGBPosition(16, 1), wxGBSpan(1, 1), wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
	gridSizer->Add(courseInfo.videoHours, wxGBPosition(17, 1), wxGBSpan(1, 1), wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
	gridSizer->Add(courseInfo.bestSeller, wxGBPosition(18, 3), wxGBSpan(1, 1), wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);
	gridSizer->Add(courseInfo.price, wxGBPosition(18, 1), wxGBSpan(1, 1), wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL);

	gridSizer->AddGrowableRow(1);
	gridSizer->AddGrowableCol(3);

	sizerM->Add(gridSizer, 1, wxEXPAND | wxALL, 20);
	panel->SetSizerAndFit(sizerM);

	SetMinSize(wxSize(1600, 800));

	// Binds
	sortButton->Bind(wxEVT_BUTTON, &MainFrame::onSortPressed, this);
	applyButton->Bind(wxEVT_BUTTON, &MainFrame::onApplyPressed, this);
	coursesList.listBox->Bind(wxEVT_LISTBOX, &MainFrame::onCourseSelected, this);

	CreateStatusBar();
}