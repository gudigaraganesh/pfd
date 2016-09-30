/////////////////////////////////////////////////////////////////////////////
// Name:        doc.h
// Purpose:     Document classes
// Author:      Julian Smart
// Modified by:
// Created:     04/01/98
// RCS-ID:      $Id: doc.h,v 1.6 2003/03/17 11:43:57 JS Exp $
// Copyright:   (c) Julian Smart
// Licence:     wxWindows license
/////////////////////////////////////////////////////////////////////////////

#ifdef __GNUG__
// #pragma interface
#endif

#ifndef __DOCSAMPLEH__
#define __DOCSAMPLEH__

#include "wx/docview.h"
#include "wx/cmdproc.h"


class wxAcqReportDoc:public wxDocument {
	DECLARE_DYNAMIC_CLASS(wxAcqReportDoc)
  private:
  public:
/*
  wxSTD ostream& SaveObject(wxSTD ostream& stream);
  wxSTD istream& LoadObject(wxSTD istream& stream);
*/
	virtual bool OnSaveDocument(const wxString & filename);
	virtual bool OnOpenDocument(const wxString & filename);
	virtual bool IsModified(void) const;
	virtual void Modify(bool mod);

	 wxAcqReportDoc(void) {
		fprintf(stderr, "Called for doc init\n");
	} ~wxAcqReportDoc(void) {
	}
};


#endif
