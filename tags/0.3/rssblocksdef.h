/***************************************************************
 * Name:      rssblocksdef.h
 * Purpose:   global constants
 * Author:    Gabriel Espinoza
 * Created:   2011-03-14
 * Copyright: Gabriel Espinoza
 * License: GPLv3+
 **************************************************************/
#ifndef RSSBLOCKSDEF_H
#define RSSBLOCKSDEF_H

#include <manager.h>
#include <configmanager.h>


/**@brief Rss::Blocks const's
  *
  * This are the paths to config settings
  * and the default values
  */
namespace rssblocksdef
{
	//configuration namespace
	const wxString rss_namespace = wxT("rssblocks");
	//configuration names
	const wxString url = wxT("url");
	const wxString channeltp = wxT("channeltp");
	const wxString itemtp = wxT("itemtp");
	const wxString updatetime = wxT("updatetime");
	const wxString savetmp = wxT("savetmp");
	const wxString lasttmp = wxT("lasttmp");
	//configuration default values;
	const wxString url_def = wxT("http://agender.sourceforge.net/rss.xml");
	// TODO (gabriel#1#): change to above value for release
	//const wxString url_def = wxT("http://127.0.0.1/rss.xml");
	const wxString channeltp_def = wxT("default.rbc");
	const wxString itemtp_def = wxT("default.rbi");
	const unsigned updatetime_def = 10;
	const bool savetmp_def = true;
}

#endif // RSSBLOCKSDEF_H
