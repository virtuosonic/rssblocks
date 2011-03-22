/***************************************************************
 * Name:      rsswindow.h
 * Purpose:   rsswindow class definition
 * Author:    Gabriel Espinoza
 * Created:   2011-02-27
 * Copyright: Gabriel Espinoza
 * License: GPLv3+
 **************************************************************/
#ifndef RSSWINDOW_H
#define RSSWINDOW_H

#include <wx/html/htmlwin.h>
#include <wx/timer.h>
#include "rsschannel.h"

class rsswindow : public wxHtmlWindow
{
	public:
		rsswindow(wxWindow* parent,wxWindowID id);
		~rsswindow();

	private:
		//event handlers
		void OnSearchUpdates(wxTimerEvent& event);
		void OnNewFeed(wxCommandEvent& event);
		void OnLink(wxHtmlLinkEvent& event);
		//private methods
		//downloads rss data
		void GetRss(const wxString& url);
		//update window
		void Update(rsschannel* channel);
		//generate html code
		wxString BuildHtml(rsschannel* channel);
		//const
		static const long ID_RSSTIMER;
		//
		rsschannel* m_channel;
		wxTimer timer1;
		wxString htmLog;
	DECLARE_EVENT_TABLE();
};

#endif // RSSWINDOW_H
