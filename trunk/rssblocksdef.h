/***************************************************************
 * Name:      rssblocksdef.h
 * Purpose:   global constants
 * Author:    Gabriel Espinoza
 * Created:   2011-03-14
 * Copyright: Gabriel Espinoza
 * License: GPLv3+
 **************************************************************/
#ifndef _RSSBLOCKSDEF_H_
#define _RSSBLOCKSDEF_H_

#include <manager.h>
#include <configmanager.h>

namespace rssblocks
{
	//configuration namespace
	const wxString rss_namespace = wxT("rss__Blocks");
	//configuration names
	const wxString url = wxT("url");
	const wxString channeltp = wxT("channeltp");
	const wxString itemtp = wxT("itemtp");
	const wxString updatetime = wxT("updatetime");
	const wxString savetmp = wxT("savetmp");
	//configuration default values;
	//const wxString url_def = wxT("http://agender.sourceforge.net/rss.xml");
	// TODO (gabriel#1#): change to above value for release
	const wxString url_def = wxT("http://127.0.0.1/rss.xml");
	const wxString channeltp_def = wxT("default.rbc");
	const wxString itemtp_def = wxT("default.rbi");
	const unsigned updatetime_def = 10;
	const bool savetmp_def = true;
}

#endif // _RSSBLOCKSDEF_H_
