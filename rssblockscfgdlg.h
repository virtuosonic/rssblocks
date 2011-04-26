/***************************************************************
 * Name:      rssblokscfgdlg.h
 * Purpose:   config dialog class definition
 * Author:    Gabriel Espinoza
 * Created:   2011-03-06
 * Copyright: Gabriel Espinoza
 * License: GPLv3+
 **************************************************************/
 #ifndef RSSBLOCKSCFGDLG_H
#define RSSBLOCKSCFGDLG_H

#include <configurationpanel.h>


class RssBlocksCfgDlg : public cbConfigurationPanel
{
	public:
		RssBlocksCfgDlg(wxWindow* parent,wxWindowID id);
		virtual ~RssBlocksCfgDlg();
		virtual wxString GetTitle() const {return wxT("Rss::Blocks");}
        virtual wxString GetBitmapBaseName() const {return wxT("rssblocks");}
        virtual void OnApply();
        virtual void OnCancel();
	private:
		static const long ID_URL;
		static const long ID_CTPL;
		static const long ID_ITPL;
		static const long ID_UPTIME;
		static const long ID_SAVETMP;
	DECLARE_EVENT_TABLE();
};

#endif // RSSBLOCKSCFGDLG_H
