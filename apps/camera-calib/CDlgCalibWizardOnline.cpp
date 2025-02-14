/* +------------------------------------------------------------------------+
   |                     Mobile Robot Programming Toolkit (MRPT)            |
   |                          https://www.mrpt.org/                         |
   |                                                                        |
   | Copyright (c) 2005-2024, Individual contributors, see AUTHORS file     |
   | See: https://www.mrpt.org/Authors - All rights reserved.               |
   | Released under BSD License. See: https://www.mrpt.org/License          |
   +------------------------------------------------------------------------+ */

#include "CDlgCalibWizardOnline.h"

#include <mrpt/vision/chessboard_find_corners.h>

#include "camera_calib_guiMain.h"

//(*InternalHeaders(CDlgCalibWizardOnline)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/settings.h>
#include <wx/string.h>
//*)
#include <mrpt/gui/wx28-fixes.h>

#include <chrono>
#include <thread>

using namespace std;
using namespace mrpt;
using namespace mrpt::obs;
using namespace mrpt::img;

//(*IdInit(CDlgCalibWizardOnline)
const long CDlgCalibWizardOnline::ID_CUSTOM2 = wxNewId();
const long CDlgCalibWizardOnline::ID_STATICTEXT1 = wxNewId();
const long CDlgCalibWizardOnline::ID_SPINCTRL1 = wxNewId();
const long CDlgCalibWizardOnline::ID_STATICTEXT2 = wxNewId();
const long CDlgCalibWizardOnline::ID_SPINCTRL2 = wxNewId();
const long CDlgCalibWizardOnline::ID_RADIOBOX1 = wxNewId();
const long CDlgCalibWizardOnline::ID_STATICTEXT3 = wxNewId();
const long CDlgCalibWizardOnline::ID_TEXTCTRL1 = wxNewId();
const long CDlgCalibWizardOnline::ID_STATICTEXT4 = wxNewId();
const long CDlgCalibWizardOnline::ID_TEXTCTRL3 = wxNewId();
const long CDlgCalibWizardOnline::ID_CHECKBOX1 = wxNewId();
const long CDlgCalibWizardOnline::ID_STATICTEXT5 = wxNewId();
const long CDlgCalibWizardOnline::ID_SPINCTRL3 = wxNewId();
const long CDlgCalibWizardOnline::ID_STATICTEXT6 = wxNewId();
const long CDlgCalibWizardOnline::ID_STATICTEXT7 = wxNewId();
const long CDlgCalibWizardOnline::ID_TEXTCTRL2 = wxNewId();
const long CDlgCalibWizardOnline::ID_BUTTON1 = wxNewId();
const long CDlgCalibWizardOnline::ID_BUTTON2 = wxNewId();
const long CDlgCalibWizardOnline::ID_BUTTON3 = wxNewId();
const long CDlgCalibWizardOnline::ID_CUSTOM1 = wxNewId();
const long CDlgCalibWizardOnline::ID_TIMER1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(CDlgCalibWizardOnline, wxDialog)
//(*EventTable(CDlgCalibWizardOnline)
//*)
END_EVENT_TABLE()

CDlgCalibWizardOnline::CDlgCalibWizardOnline(
	wxWindow* parent, wxWindowID id, const wxPoint& pos, const wxSize& size)
{
	m_threadMustClose = false;
	m_threadResultsComputed = false;
	m_threadIsClosed = true;

	//(*Initialize(CDlgCalibWizardOnline)
	wxStaticBoxSizer* StaticBoxSizer2;
	wxFlexGridSizer* FlexGridSizer2;
	wxStaticBoxSizer* StaticBoxSizer5;
	wxFlexGridSizer* FlexGridSizer17;
	wxFlexGridSizer* FlexGridSizer7;
	wxFlexGridSizer* FlexGridSizer4;
	wxStaticBoxSizer* StaticBoxSizer3;
	wxFlexGridSizer* FlexGridSizer6;
	wxFlexGridSizer* FlexGridSizer3;
	wxStaticBoxSizer* StaticBoxSizer4;
	wxFlexGridSizer* FlexGridSizer18;
	wxFlexGridSizer* FlexGridSizer5;
	wxStaticBoxSizer* StaticBoxSizer1;

	Create(
		parent, id, _("Grab chessboard calibration pattern"), wxDefaultPosition,
		wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("id"));
	SetClientSize(wxDefaultSize);
	Move(wxDefaultPosition);
	FlexGridSizer1 = new wxFlexGridSizer(0, 3, 0, 0);
	FlexGridSizer1->AddGrowableCol(0);
	FlexGridSizer1->AddGrowableRow(0);
	FlexGridSizer2 = new wxFlexGridSizer(0, 1, 0, 0);
	FlexGridSizer4 = new wxFlexGridSizer(0, 1, 0, 0);
	StaticBoxSizer1 =
		new wxStaticBoxSizer(wxHORIZONTAL, this, _("Select your camera: "));
	m_panelCamera = new mrpt::gui::CPanelCameraSelection(this, ID_CUSTOM2);
	StaticBoxSizer1->Add(
		m_panelCamera, 1,
		wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer4->Add(StaticBoxSizer1, 1, wxEXPAND, 5);
	FlexGridSizer2->Add(FlexGridSizer4, 1, wxEXPAND, 0);
	StaticBoxSizer3 = new wxStaticBoxSizer(
		wxHORIZONTAL, this, _("Checkerboard detection parameters"));
	FlexGridSizer6 = new wxFlexGridSizer(2, 2, 0, 0);
	FlexGridSizer6->AddGrowableCol(0);
	FlexGridSizer6->AddGrowableCol(1);
	StaticBoxSizer4 = new wxStaticBoxSizer(
		wxHORIZONTAL, this, _("Number of inner corners: "));
	FlexGridSizer17 = new wxFlexGridSizer(1, 4, 0, 0);
	StaticText1 = new wxStaticText(
		this, ID_STATICTEXT1, _("In X:"), wxDefaultPosition, wxDefaultSize, 0,
		_T("ID_STATICTEXT1"));
	FlexGridSizer17->Add(
		StaticText1, 1,
		wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
	edSizeX = new wxSpinCtrl(
		this, ID_SPINCTRL1, _T("5"), wxDefaultPosition, wxSize(50, -1), 0, 1,
		200, 5, _T("ID_SPINCTRL1"));
	edSizeX->SetValue(_T("5"));
	FlexGridSizer17->Add(
		edSizeX, 1, wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL,
		5);
	StaticText2 = new wxStaticText(
		this, ID_STATICTEXT2, _("In Y:"), wxDefaultPosition, wxDefaultSize, 0,
		_T("ID_STATICTEXT2"));
	FlexGridSizer17->Add(
		StaticText2, 1,
		wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
	edSizeY = new wxSpinCtrl(
		this, ID_SPINCTRL2, _T("8"), wxDefaultPosition, wxSize(50, -1), 0, 1,
		200, 8, _T("ID_SPINCTRL2"));
	edSizeY->SetValue(_T("8"));
	FlexGridSizer17->Add(
		edSizeY, 1, wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL,
		5);
	StaticBoxSizer4->Add(FlexGridSizer17, 1, wxEXPAND, 0);
	FlexGridSizer6->Add(
		StaticBoxSizer4, 1, wxALL | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 2);
	StaticBoxSizer5 =
		new wxStaticBoxSizer(wxHORIZONTAL, this, _(" Size of quads (in mm): "));
	FlexGridSizer18 = new wxFlexGridSizer(1, 4, 0, 0);
	StaticText3 = new wxStaticText(
		this, ID_STATICTEXT3, _("In X:"), wxDefaultPosition, wxDefaultSize, 0,
		_T("ID_STATICTEXT3"));
	FlexGridSizer18->Add(
		StaticText3, 1,
		wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
	edLengthX = new wxTextCtrl(
		this, ID_TEXTCTRL1, _("40.0"), wxDefaultPosition, wxSize(40, -1), 0,
		wxDefaultValidator, _T("ID_TEXTCTRL1"));
	FlexGridSizer18->Add(
		edLengthX, 1,
		wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
	StaticText4 = new wxStaticText(
		this, ID_STATICTEXT4, _("In Y:"), wxDefaultPosition, wxDefaultSize, 0,
		_T("ID_STATICTEXT4"));
	FlexGridSizer18->Add(
		StaticText4, 1,
		wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
	edLengthY = new wxTextCtrl(
		this, ID_TEXTCTRL3, _("40.0"), wxDefaultPosition, wxSize(40, -1), 0,
		wxDefaultValidator, _T("ID_TEXTCTRL3"));
	FlexGridSizer18->Add(
		edLengthY, 1,
		wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer5->Add(FlexGridSizer18, 1, wxEXPAND, 0);
	FlexGridSizer6->Add(
		StaticBoxSizer5, 1, wxALL | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 2);
	cbNormalize = new wxCheckBox(
		this, ID_CHECKBOX1, _("Normalize image"), wxDefaultPosition,
		wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
	cbNormalize->SetValue(true);
	FlexGridSizer6->Add(
		cbNormalize, 1,
		wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer3->Add(FlexGridSizer6, 1, wxEXPAND, 0);
	FlexGridSizer2->Add(
		StaticBoxSizer3, 1,
		wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer2 =
		new wxStaticBoxSizer(wxHORIZONTAL, this, _("Capture limits"));
	FlexGridSizer7 = new wxFlexGridSizer(0, 2, 0, 0);
	FlexGridSizer7->AddGrowableCol(0);
	StaticText5 = new wxStaticText(
		this, ID_STATICTEXT5, _("Frames to grab:"), wxDefaultPosition,
		wxDefaultSize, 0, _T("ID_STATICTEXT5"));
	FlexGridSizer7->Add(
		StaticText5, 1, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, 5);
	edNumCapture = new wxSpinCtrl(
		this, ID_SPINCTRL3, _T("15"), wxDefaultPosition, wxDefaultSize, 0, 5,
		100, 15, _T("ID_SPINCTRL3"));
	edNumCapture->SetValue(_T("15"));
	FlexGridSizer7->Add(
		edNumCapture, 1,
		wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
	StaticText6 = new wxStaticText(
		this, ID_STATICTEXT6, _("Grabbed so far:"), wxDefaultPosition,
		wxDefaultSize, 0, _T("ID_STATICTEXT6"));
	FlexGridSizer7->Add(
		StaticText6, 1, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, 5);
	lbProgress = new wxStaticText(
		this, ID_STATICTEXT7, _("0"), wxDefaultPosition, wxDefaultSize, 0,
		_T("ID_STATICTEXT7"));
	FlexGridSizer7->Add(
		lbProgress, 1, wxALL | wxALIGN_LEFT | wxALIGN_CENTER_VERTICAL, 5);
	StaticBoxSizer2->Add(FlexGridSizer7, 1, wxEXPAND, 0);
	FlexGridSizer2->Add(StaticBoxSizer2, 1, wxEXPAND, 5);
	txtLog = new wxTextCtrl(
		this, ID_TEXTCTRL2, _("(debug output)"), wxDefaultPosition,
		wxSize(239, 78), wxTE_MULTILINE | wxTE_READONLY | wxHSCROLL | wxVSCROLL,
		wxDefaultValidator, _T("ID_TEXTCTRL2"));
	wxFont txtLogFont = wxSystemSettings::GetFont(wxSYS_OEM_FIXED_FONT);
	if (!txtLogFont.Ok())
		txtLogFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
	txtLogFont.SetPointSize(9);
	txtLog->SetFont(txtLogFont);
	FlexGridSizer2->Add(txtLog, 1, wxEXPAND, 5);
	FlexGridSizer1->Add(FlexGridSizer2, 1, wxEXPAND, 0);
	FlexGridSizer3 = new wxFlexGridSizer(2, 1, 0, 0);
	FlexGridSizer3->AddGrowableCol(0);
	FlexGridSizer3->AddGrowableRow(1);
	FlexGridSizer5 = new wxFlexGridSizer(0, 3, 0, 0);
	FlexGridSizer5->AddGrowableCol(2);
	btnStart = new wxButton(
		this, ID_BUTTON1, _("Start"), wxDefaultPosition, wxDefaultSize, 0,
		wxDefaultValidator, _T("ID_BUTTON1"));
	wxFont btnStartFont(
		-1, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
	btnStart->SetFont(btnStartFont);
	FlexGridSizer5->Add(
		btnStart, 1,
		wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL, 5);
	btnStop = new wxButton(
		this, ID_BUTTON2, _("Stop"), wxDefaultPosition, wxDefaultSize, 0,
		wxDefaultValidator, _T("ID_BUTTON2"));
	btnStop->Disable();
	FlexGridSizer5->Add(
		btnStop, 1, wxALL | wxALIGN_CENTER_HORIZONTAL | wxALIGN_CENTER_VERTICAL,
		5);
	btnClose = new wxButton(
		this, ID_BUTTON3, _("Close"), wxDefaultPosition, wxDefaultSize, 0,
		wxDefaultValidator, _T("ID_BUTTON3"));
	FlexGridSizer5->Add(
		btnClose, 1, wxALL | wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL, 5);
	FlexGridSizer3->Add(FlexGridSizer5, 1, wxEXPAND, 0);
	m_realtimeview = new mrpt::gui::wxMRPTImageControl(
		this, ID_CUSTOM1, wxDefaultPosition.x, wxDefaultPosition.y,
		wxSize(468, 286).GetWidth(), wxSize(468, 286).GetHeight());
	FlexGridSizer3->Add(
		m_realtimeview, 1, wxALL | wxALIGN_LEFT | wxALIGN_TOP, 0);
	FlexGridSizer1->Add(FlexGridSizer3, 1, wxEXPAND, 0);
	SetSizer(FlexGridSizer1);
	timCapture.SetOwner(this, ID_TIMER1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);
	Center();

	Bind(
		wxEVT_BUTTON, &CDlgCalibWizardOnline::OnbtnStartClick, this,
		ID_BUTTON1);
	Bind(
		wxEVT_BUTTON, &CDlgCalibWizardOnline::OnbtnStopClick, this, ID_BUTTON2);
	Bind(
		wxEVT_BUTTON, &CDlgCalibWizardOnline::OnbtnCloseClick, this,
		ID_BUTTON3);
	Bind(
		wxEVT_TIMER, &CDlgCalibWizardOnline::OntimCaptureTrigger, this,
		ID_TIMER1);
	//*)

	redire = std::make_unique<CMyRedirector>(txtLog, true, 10);
}

CDlgCalibWizardOnline::~CDlgCalibWizardOnline()
{
	//(*Destroy(CDlgCalibWizardOnline)
	//*)
}

void CDlgCalibWizardOnline::OnbtnCloseClick(wxCommandEvent& event)
{
	m_video.reset();
	m_threadMustClose = true;
	if (m_threadCorners.joinable()) m_threadCorners.join();

	EndModal(wxID_CANCEL);
}

void CDlgCalibWizardOnline::OnbtnStartClick(wxCommandEvent& event)
{
	// Try to open the camera:
	if (m_video) m_video.reset();

	m_video = mrpt::hwdrivers::prepareVideoSourceFromPanel(m_panelCamera);
	if (!m_video) return;

	// Launch thread:
	// --------------------------
	m_threadImgToProcess.reset();
	m_threadMustClose = false;
	m_threadResults.clear();
	m_threadResultsComputed = true;	 // To start a new detection
	m_threadIsClosed = false;

	m_calibFrames.clear();

	m_threadCorners =
		std::thread(&CDlgCalibWizardOnline::threadProcessCorners, this);

	lbProgress->SetLabel(_("0"));

	btnStart->Disable();
	btnStop->Enable();
	this->m_panelCamera->Disable();

	// start processing:
	timCapture.Start(2, true);	// One shot
}

void CDlgCalibWizardOnline::OnbtnStopClick(wxCommandEvent& event)
{
	m_video.reset();

	btnStart->Enable();
	btnStop->Disable();
	this->m_panelCamera->Enable();

	m_threadMustClose = true;
	if (m_threadCorners.joinable()) m_threadCorners.join();
}

void CDlgCalibWizardOnline::OntimCaptureTrigger(wxTimerEvent& event)
{
	static mrpt::system::TTimeStamp last_valid = INVALID_TIMESTAMP;

	try
	{
		if (!btnStop->IsEnabled())
		{
			timCapture.Stop();
			return;
		}

		ASSERT_(m_video);

		m_check_size_x = this->edSizeX->GetValue();
		m_check_size_y = this->edSizeY->GetValue();
		m_normalize_image = this->cbNormalize->GetValue();

		CObservation::Ptr obs = m_video->getNextFrame();
		ASSERT_(obs);
		ASSERT_(
			IS_CLASS(*obs, CObservationImage) ||
			IS_CLASS(*obs, CObservation3DRangeScan));

		// Convert to an image:
		if (IS_CLASS(*obs, CObservation3DRangeScan))
		{
			CObservation3DRangeScan::Ptr obs3D =
				std::dynamic_pointer_cast<CObservation3DRangeScan>(obs);

			CObservationImage::Ptr obsImg =
				std::make_shared<CObservationImage>();
			obsImg->timestamp = obs3D->timestamp;
			ASSERT_(obs3D->hasIntensityImage);
			obsImg->image = obs3D->intensityImage;

			// Ale hoop!
			obs = obsImg;
		}

		CImage img_to_show;

		// get the observation:
		CObservationImage::Ptr obs_img =
			std::dynamic_pointer_cast<CObservationImage>(obs);

		// Is there a detection??
		bool blankTime = (last_valid != INVALID_TIMESTAMP) &&
			mrpt::system::timeDifference(last_valid, mrpt::system::now()) < 2.0;

		if (!blankTime && m_threadResultsComputed && !m_threadResults.empty())
		{
			// Save image to the list:
			string newImgName =
				format("frame_%03u", (unsigned int)m_calibFrames.size());
			m_calibFrames[newImgName].img_original =
				m_calibFrames[newImgName].img_checkboard =
					m_calibFrames[newImgName].img_rectified =
						m_threadImgToProcess->image;

			// Counter:
			lbProgress->SetLabel(
				format("%u", (unsigned int)m_calibFrames.size()).c_str());

			last_valid = mrpt::system::now();

			// Display now:
			m_threadImgToProcess->image.colorImage(img_to_show);

			// Draw the corners:
			img_to_show.drawChessboardCorners(
				m_threadResults, m_check_size_x, m_check_size_y);
		}
		else
		{
			// Show current image:
			img_to_show = obs_img->image;
		}

		// Process a new image to detect checkerboard:
		if (m_threadResultsComputed)
		{
			m_threadImgToProcess = obs_img;
			m_threadResultsComputed = false;
			// cout << "new image sent"<<endl;
		}

		// Progress:
		const auto nFramesToGrab = (unsigned)edNumCapture->GetValue();
		img_to_show.textOut(
			10, 10,
			format(
				"%u out of %u grabbed", (unsigned int)m_calibFrames.size(),
				nFramesToGrab),
			TColor::white());

		m_realtimeview->AssignImage(img_to_show);
		m_realtimeview->Refresh(false);
		wxTheApp->Yield();

		// Resize the display area, if needed:
		if (std::abs(
				(int)(mrpt::gui::GetScaledClientSize(m_realtimeview)
						  .GetWidth()) -
				int(img_to_show.getWidth())) > 30)
		{
			this->m_realtimeview->SetSize(
				img_to_show.getWidth(), img_to_show.getHeight());
			this->m_realtimeview->SetMinSize(
				wxSize(img_to_show.getWidth(), img_to_show.getHeight()));
			this->FlexGridSizer1->Layout();
			this->Fit();
		}

		// Are we done?
		// --------------------
		if (m_calibFrames.size() >= nFramesToGrab)
		{
			wxCommandEvent dum;
			this->OnbtnStopClick(dum);
			wxTheApp->Yield();

			// Run calibration itself:
			if (wxOK ==
				wxMessageBox(
					_("The desired number of frames have been "
					  "grabbed.\nOkay to accept these frames?"),
					_("Done"), wxCANCEL | wxOK, this))
			{
				EndModal(wxID_OK);
			}
			else
			{
				try
				{
					wxCommandEvent dummy;
					this->OnbtnStopClick(dummy);
				}
				catch (...)
				{
				}
			}
		}
		else
		{
			// Get on...
			timCapture.Start(5, true);
		}
	}
	catch (const std::exception& e)
	{
		try
		{
			wxCommandEvent dum;
			this->OnbtnStopClick(dum);
		}
		catch (...)
		{
		}
		cerr << endl << mrpt::exception_to_str(e) << endl;
		wxMessageBox(
			mrpt::exception_to_str(e), _("Error"), wxICON_INFORMATION, this);
		return;
	}
}

// ---------------------------------------------------------------------------------------------------
// The thread for parallel detection of edges. This is needed since from OpenCV
// 1.1.0,
//  chessboard corner detection runs very slow, so it cannot be done in
//  real-time properly:
// ---------------------------------------------------------------------------------------------------
void CDlgCalibWizardOnline::threadProcessCorners()
{
	CDlgCalibWizardOnline* obj = this;
	try
	{
		while (!obj->m_threadMustClose)
		{
			if (!obj->m_threadResultsComputed)
			{
				try
				{
					// Detect corners:
					bool foundCorners = mrpt::vision::findChessboardCorners(
						obj->m_threadImgToProcess->image, obj->m_threadResults,
						obj->m_check_size_x, obj->m_check_size_y,
						obj->m_normalize_image);

					// cout << "corners: " << obj->m_threadResults.size() <<
					// endl;

					if (!foundCorners) obj->m_threadResults.clear();

					obj->m_threadResultsComputed = true;
				}
				catch (const std::exception& e)
				{
					cerr << mrpt::exception_to_str(e) << endl;
				}
				catch (...)
				{
				}
			}
			else
			{
				// Nothing to do:
				std::this_thread::sleep_for(5ms);
			}
		}

		// Signal we're done
		obj->m_threadIsClosed = true;
	}
	catch (const std::exception& e)
	{
		cerr << mrpt::exception_to_str(e) << endl;
		// Signal we're done
		obj->m_threadIsClosed = true;
	}
	catch (...)
	{
		// Signal we're done
		obj->m_threadIsClosed = true;
	}
}
