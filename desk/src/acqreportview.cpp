#ifdef __GNUG__
// #pragma implementation
#endif

// For compilers that support precompilation, includes "wx/wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#if !wxUSE_DOC_VIEW_ARCHITECTURE
#error You must set wxUSE_DOC_VIEW_ARCHITECTURE to 1 in setup.h!
#endif

#include "pfdevice.h"
#include "acqreportdoc.h"
#include "acqreportview.h"


IMPLEMENT_DYNAMIC_CLASS(wxAcqReportView, wxView)

	bool wxAcqReportView::OnCreate(wxDocument * doc, long WXUNUSED(flags))
{
	frame = wxGetApp().CreateChildFrame(doc, this, FALSE);

	int width, height;

	frame->GetClientSize(&width, &height);
	textsw =
		new wxAcqVis(this, frame, wxPoint(0, 0), wxSize(width, height),
					 wxTE_MULTILINE);
//textsw=new wxManageText(frame,8999,wxString(""),wxPoint(30,30),wxSize(200,200),*wxBLACK,wxTE_READONLY|wxSUNKEN_BORDER|wxTE_MULTILINE);


	frame->SetTitle(_T("wxAcqReportView"));

#ifdef __X__
	// X seems to require a forced resize
	int x, y;

	frame->GetSize(&x, &y);
	frame->SetSize(-1, -1, x, y);
#endif
	if (GetCount() == 0)
		GetReportFrame()->Show();
	frame->Show(TRUE);
	IncCount();

	Activate(TRUE);

	return TRUE;
}

// Handled by wxTextWindow
void wxAcqReportView::OnDraw(wxDC * WXUNUSED(dc))
{
}

void wxAcqReportView::OnUpdate(wxView * WXUNUSED(sender),
							   wxObject * WXUNUSED(hint))
{
}

bool wxAcqReportView::OnClose(bool deleteWindow)
{
	if (!GetDocument()->Close())
		return FALSE;

	Activate(FALSE);

	if (deleteWindow) {
		DecCount();
		delete frame;

		if (GetCount() == 0)
			GetReportFrame()->Hide();
		return TRUE;
	}

	return TRUE;
}

/*
 * Window implementations
 */


wxAcqVis::wxAcqVis(wxView * v, wxMDIChildFrame * frame, const wxPoint & pos, const wxSize & size, long style):
wxTextCtrl(frame, -1, _T(""), pos, size, style)
{
	fprintf(stderr, "This doc\n");
	view = v;
}
