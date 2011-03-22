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
#include <wx/textfile.h>
#include <wx/filesys.h>

const long rsswindow::ID_RSSTIMER = wxNewId();

BEGIN_EVENT_TABLE(rsswindow,wxHtmlWindow)
	EVT_TIMER(ID_RSSTIMER,rsswindow::OnSearchUpdates)
END_EVENT_TABLE()


/** @brief rsswindow
  *
  * @todo: document this function
  */
rsswindow::rsswindow(wxWindow* parent,wxWindowID id)
{
	Create(parent,id);
	timer1.SetOwner(this,ID_RSSTIMER);
	ConfigManager* cfg = Manager::Get()->GetConfigManager(rssblocks::rss_namespace);
	int updatetime = cfg->ReadInt(rssblocks::updatetime,rssblocks::updatetime_def);
	// TODO (gabriel#1#): cambiar a 60000 para el release
	updatetime *= 1000;
	timer1.Start(updatetime);
	GetRss(cfg->Read(rssblocks::url,rssblocks::url_def));
}

/** @brief ~rsswindow
  *
  * @todo: document this function
  */
rsswindow::~rsswindow()
{

}

/** @brief OnSearchUpdates
  *
  * @todo: document this function
  */


void rsswindow::OnSearchUpdates(wxTimerEvent& event)
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
	wxFSFile* rss_data = fs->OpenFile(url);
	if (rss_data)
	{
		wxInputStream* is = rss_data->GetStream();
		try {
			rsschannel* n_channel = new rsschannel(*is);
			Update(n_channel);
			delete n_channel;
		}
		catch (...)
		{
		}
		delete rss_data;
	}
	else{}
	delete fs;
}

wxString rsswindow::BuildHtml(rsschannel* channel)
{
	ConfigManager* cfg = Manager::Get()->GetConfigManager(rssblocks::rss_namespace);
	//
	if (!channel)
		throw -3;
	//open file
    wxTextFile item_text_file;
    wxString item_file = cfg->Read(rssblocks::itemtp,rssblocks::itemtp_def);
    wxFileName fname = item_file;
    if (fname.IsRelative())
		fname = cfg->LocateDataFile(item_file);
    if (!item_text_file.Open(fname.GetFullPath()))
		throw -4;
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
		throw -6;
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

