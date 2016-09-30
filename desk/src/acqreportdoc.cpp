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
#include "wx/txtstrm.h"

#if !wxUSE_DOC_VIEW_ARCHITECTURE
#error You must set wxUSE_DOC_VIEW_ARCHITECTURE to 1 in setup.h!
#endif

#include "acqreportdoc.h"
#include "acqreportview.h"


IMPLEMENT_DYNAMIC_CLASS(wxAcqReportDoc, wxDocument)
// Since text windows have their own method for saving to/loading from files,
// we override OnSave/OpenDocument instead of Save/LoadObject
	bool wxAcqReportDoc::OnSaveDocument(const wxString & filename)
{
	wxAcqReportView *view = (wxAcqReportView *) GetFirstView();

	if (!view->textsw->SaveFile(filename))
		return FALSE;
	Modify(FALSE);
	return TRUE;
}

bool wxAcqReportDoc::OnOpenDocument(const wxString & filename)
{
	wxAcqReportView *view = (wxAcqReportView *) GetFirstView();

	fprintf(stderr, "opendoc:first\n");
	if (!view->textsw->LoadFile(filename))
		return FALSE;

	fprintf(stderr, "load file\n");
	SetFilename(filename, TRUE);
	Modify(FALSE);
	fprintf(stderr, "before update \n");
	UpdateAllViews();
	fprintf(stderr, "updated");
	return TRUE;
}

bool wxAcqReportDoc::IsModified(void) const 
{
	wxAcqReportView *view = (wxAcqReportView *) GetFirstView();

	if (view) {
		return (wxDocument::IsModified() || view->textsw->IsModified());
	} else
		return wxDocument::IsModified();
}

void wxAcqReportDoc::Modify(bool mod)
{
	wxAcqReportView *view = (wxAcqReportView *) GetFirstView();

	wxDocument::Modify(mod);

	if (!mod && view && view->textsw)
		view->textsw->DiscardEdits();
}
