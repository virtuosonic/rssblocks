/***************************************************************
 * Name:      rsswindow.cpp
 * Purpose:   rsswindow class implementation
 * Author:    Gabriel Espinoza
 * Created:   2011-02-27
 * Copyright: Gabriel Espinoza
 * License: GPLv3+
 **************************************************************/

#include "rsswindow.h"
#include "rssblocksdef.h"
#include <logmanager.h>
#include <wx/textfile.h>
#include <wx/filesys.h>
#include <wx/wfstream.h>


/**@page tpl_p Html Templates
  * Rss::Blocks can be customized by using html,
  * to customize the Rss::Blocks window you
  * need two files one .rbc file and one .rbi file.
  * The .rbc is a Rss::Blocks channel template and the
  * .rbi is a Rss::Blocks item template, basicly they are
  * html but with some variables that are expanded
  * by Rss::Blocks.
  * @section rbc_sec rbc file
  * The rbc file is a html file that contain some
  * of this optional variables:
  *   @li <b>@$(CHANNEL_TITLE):</b> the channel's title
  *   @li <b>@$(CHANNEL_LINK):</b> the channel's link
  *   @li <b>@$(CHANNEL_DESCRIPTION):</b> a description for the channel
  *   @li <b>@$(FEEDS):</b> the feeds, this are generated from the rbi file
  * @section rbi_sec rbi file
  * The rbi file is the one used to
  * generate each one of the feeds
  * shown in the window,
  * it isn't a html file but contains
  * html tags and can contain some
  * of this optional variables:
  *   @li <b>@$(TITLE):</b> the feed's title
  *   @li <b>@$(LINK):</b> the feed's link
  *   @li <b>@$(DESCRIPTION):</b> a description for the feed
  * @section tplex_sec Examples
  * For examples you can see default.rbc and
  * default.rbi from the distribution. Rss::Blocks
  * uses wxHtmlWindow to display the generated
  * html and because of that it is very limited, no
  * css, javascript etc. Adding support for wxWebConnect
  * is planned for future releases, so then it will
  * support all that modern features.
  */

namespace rssblocks {
using virtuosonic::rsschannel;
//using virtuosonic::rssitem;

const long rsswindow::ID_RSSTIMER = wxNewId();
const long rsswindow::ID_RSSLINK = wxNewId();

BEGIN_EVENT_TABLE(rsswindow,wxHtmlWindow)
	//timer
	EVT_TIMER(ID_RSSTIMER,rsswindow::OnSearchUpdates)
	//handle external links
	EVT_HTML_LINK_CLICKED(ID_RSSLINK,rsswindow::OnLink)
	//for update
	EVT_KEY_DOWN(rsswindow::OnKey)
END_EVENT_TABLE()


/**@brief Constructor
  * Creates an object
  * @param parent the parent for this window
  * @param id the id for this window
  */
rsswindow::rsswindow(wxWindow* parent,wxWindowID id)
{
	Create(parent,id);
	timer1.SetOwner(this,ID_RSSTIMER);
	ConfigManager* cfg = Manager::Get()->GetConfigManager(rssblocks::rss_namespace);
	InitUpdateTime();
	GetRss(cfg->Read(rssblocks::url,rssblocks::url_def));
	Connect(GetId(),wxEVT_COMMAND_HTML_LINK_CLICKED,
			(wxObjectEventFunction)&rsswindow::OnLink);
}

/** @brief Destructor
  *
  * Destroys this object, does nothing
  */
rsswindow::~rsswindow()
{

}

/** @brief OnSearchUpdates
  *
  * @todo: document this function
  */


void rsswindow::OnSearchUpdates(wxTimerEvent& WXUNUSED(event))
{
	ConfigManager* cfg = Manager::Get()->GetConfigManager(rssblocks::rss_namespace);
	GetRss(cfg->Read(rssblocks::url,rssblocks::url_def));
}

/** @brief Update
  *
  * @todo: document this function
  */
void rsswindow::Update(rsschannel* channel)
{
	try {
	SetPage(BuildHtml(channel));
	}
	catch (...)
	{
		SetPage(_T("missing template file?"));
	}
}

void rsswindow::GetRss(const wxString& url)
{
	wxFileSystem* fs = new wxFileSystem;
	wxFSFile* rss_data = fs->OpenFile(url,wxFS_READ | wxFS_SEEKABLE);
	ConfigManager* cfg = Manager::Get()->GetConfigManager(rssblocks::rss_namespace);
	if (rss_data)
	{
		wxInputStream* is = rss_data->GetStream();
		try {
			rsschannel n_channel(*is);
			Update(&n_channel);
			//write temp data
			if (cfg->ReadBool(rssblocks::savetmp,rssblocks::savetmp_def))
			{
				//path
				wxFileName rsstmp;
				rsstmp.AssignDir(cfg->GetFolder(sdTemp));
				rsstmp.AppendDir(wxT("rssblocks"));
				//create dir
				if (!wxDirExists(rsstmp.GetPath()))
					wxMkDir(rsstmp.GetPath());
				//name
				rsstmp.SetName(n_channel.Gettitle());
				rsstmp.SetExt(wxT("xml"));
				wxFileOutputStream rssout(rsstmp.GetFullPath());
				//must return to start or
				//won't copy anything
				is->SeekI(0);
				rssout.Write(*is);
				//log
				Manager::Get()->GetLogManager()->Log(
					wxString::Format(_T("saved rss temp to: %s"),
					rsstmp.GetFullPath().c_str()));
				cfg->Write(rssblocks::lasttmp,rsstmp.GetFullPath());
			}
			//delete n_channel;
		}
		catch (std::invalid_argument& e)
		{
			virtuosonic::wxException ex(e);
			Manager::Get()->GetLogManager()->LogError(ex.what());
		}
		delete rss_data;
	}
	else
	{
		bool usetemp = cfg->ReadBool(rssblocks::savetmp,
				rssblocks::savetmp_def);
		wxString tempfile(cfg->Read(rssblocks::lasttmp,
				wxEmptyString));
		if (usetemp && wxFileExists(tempfile))
		{
			Manager::Get()->GetLogManager()->Log(_("Rss::Blocks: using temporary data"));
			wxFileInputStream is(tempfile);
			try {
				rsschannel n_channel(is);
				Update(&n_channel);
			}catch (...){}
		}
		else
			SetPage(_("The channel you selected may be invalid or unreachable."));
	}
	delete fs;
}

wxString rsswindow::BuildHtml(rsschannel* channel) throw (wxException)
{
	ConfigManager* cfg = Manager::Get()->GetConfigManager(rssblocks::rss_namespace);
	//
	if (!channel)
		throw wxException(_T("channel must not be null"));
	//open file
    wxTextFile item_text_file;
    wxString item_file = cfg->Read(rssblocks::itemtp,rssblocks::itemtp_def);
    wxFileName fname = item_file;
    if (fname.IsRelative())
		fname = cfg->LocateDataFile(item_file);
    if (!item_text_file.Open(fname.GetFullPath()))
		throw wxException(_T("couldn't open file ") +
					fname.GetFullPath());
    //read
    wxString item_preset;
    for (unsigned k=0;k < item_text_file.GetLineCount();k++)
    {
    	item_preset << item_text_file[k];
    }
    wxString feeds_str;
    for (unsigned i = 0;i <channel->GetItems().GetCount();i++)
    {
		wxString item_text(item_preset);
		item_text.Replace(_T("$(LINK)"),
				channel->GetItems()[i]->Getlink());
		item_text.Replace(_T("$(TITLE)"),
				channel->GetItems()[i]->Gettitle());
		item_text.Replace(_T("$(DESCRIPTION)"),
				channel->GetItems()[i]->Getdesc());
		feeds_str << item_text;
    }
    //open channel preset
    wxTextFile channel_text_file;
    wxString channel_file = cfg->Read(rssblocks::channeltp,rssblocks::channeltp_def);
    fname = channel_file ;
    if (fname.IsRelative())
		fname = cfg->LocateDataFile(channel_file );
    if (!channel_text_file.Open(fname.GetFullPath()))
		throw wxException(_("couldn't open file %s")+
				fname.GetFullPath());
    //read it
    wxString channel_preset;
    for (unsigned j =0;j < channel_text_file.GetLineCount();j++)
    {
    	channel_preset << channel_text_file[j];
    }
    channel_preset.Replace(_T("$(FEEDS)"),
			feeds_str);
	channel_preset.Replace(_T("$(CHANNEL_DESCRIPTION)"),channel->Getdesc());
	channel_preset.Replace(_T("$(CHANNEL_TITLE)"),channel->Gettitle());
	channel_preset.Replace(_T("$(CHANNEL_LINK)"),channel->Getlink());
	return channel_preset;
}

/** @brief OnLink
  *
  * @todo: document this function
  */
void rsswindow::OnLink(wxHtmlLinkEvent& event)
{
	wxLaunchDefaultBrowser(event.GetLinkInfo().GetHref());
}

/** @brief OnKey
  *
  * handles F5, for Refresh
  */
void rsswindow::OnKey(wxKeyEvent& event)
{
	//process F5
	if (event.GetKeyCode() == WXK_F5)
	{
		ConfigManager* cfg = Manager::Get()->GetConfigManager(
				rssblocks::rss_namespace);
		GetRss(cfg->Read(rssblocks::url,rssblocks::url_def));
	}
	else
		event.Skip();//pass to parent
}

/** read timer settings from config */
void rsswindow::InitUpdateTime()
{
	ConfigManager* cfg = Manager::Get()->GetConfigManager(rssblocks::rss_namespace);
	//read how much minutes
	int updatetime = cfg->ReadInt(rssblocks::updatetime,rssblocks::updatetime_def);
	//convert to minutes
	updatetime *= 60000;
	timer1.Start(updatetime);
	Manager::Get()->GetLogManager()->Log(
	wxString::Format(_T("Update time set to: %i"),updatetime));
}
}//namespace rssblocks
