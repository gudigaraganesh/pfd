/////////////////////////////////////////////////////////////////////////////
// Name:        view.h
// Purpose:     View classes
// Author:      Julian Smart
// Modified by:
// Created:     04/01/98
// RCS-ID:      $Id: view.h,v 1.8 2003/03/17 11:43:57 JS Exp $
// Copyright:   (c) Julian Smart
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifdef __GNUG__
// #pragma interface
#endif

#ifndef __VIEWSAMPLEH__
#define __VIEWSAMPLEH__

#include "wx/docview.h"
#include "managetext.h"

class wxAcqVis:public wxTextCtrl {
  public:
	wxView * view;

	wxAcqVis(wxView * v, wxMDIChildFrame * frame, const wxPoint & pos,
			 const wxSize & size, long style);
};


class wxAcqReportView:public wxView {
  private:
	unsigned int counter;
	void IncCount() {
		counter++;
	} void DecCount() {
		counter--;
	}
	unsigned int GetCount() {
		fprintf(stderr, "Execute me\n");
		return counter;
	}
  public:
	wxMDIChildFrame * frame;
	wxAcqVis *textsw;

  wxAcqReportView():wxView() {
		counter = 0;
		frame = (wxMDIChildFrame *) NULL;
		textsw = (wxAcqVis *) NULL;
	}
	~wxAcqReportView() {
	}

	bool OnCreate(wxDocument * doc, long flags);
	void OnDraw(wxDC * dc);
	void OnUpdate(wxView * sender, wxObject * hint = (wxObject *) NULL);
	bool OnClose(bool deleteWindow = TRUE);

  private:
	DECLARE_DYNAMIC_CLASS(wxAcqReportView)
};

#endif
