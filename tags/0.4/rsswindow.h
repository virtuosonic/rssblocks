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
#include "virtuosonic.hpp"

namespace rssblocks {
using virtuosonic::rsschannel;
using virtuosonic::wxException;
/**@brief Rss::Blocks window
  *
  * This is simply a html window,
  * this class also manages the
  * timer, downloads the
  * xml data and generates the html
  * from the @ref tpl_p
  */
class rsswindow : public wxHtmlWindow
{
	public:
		rsswindow(wxWindow* parent,wxWindowID id);
		~rsswindow();
		void InitUpdateTime();

	private:
		//event handlers
		void OnSearchUpdates(wxTimerEvent& event);
		//void OnNewFeed(wxCommandEvent& event);
		void OnLink(wxHtmlLinkEvent& event);
		void OnKey(wxKeyEvent& event);
		//private methods
		//downloads rss data
		void GetRss(const wxString& url);
		//update window
		void Update(rsschannel* channel);
		//generate html code
		wxString BuildHtml(rsschannel* channel) throw (wxException);
		//const
		static const long ID_RSSTIMER;
		static const long ID_RSSLINK;
		//
		rsschannel* m_channel;
		wxTimer timer1;
	DECLARE_EVENT_TABLE();
};
}//namespace rssblocks

#endif // RSSWINDOW_H
