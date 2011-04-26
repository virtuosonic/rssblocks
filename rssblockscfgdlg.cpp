/***************************************************************
 * Name:      rssblokscfgdlg.cpp
 * Purpose:   config dialog class implementation
 * Author:    Gabriel Espinoza
 * Created:   2011-03-06
 * Copyright: Gabriel Espinoza
 * License: GPLv3+
 **************************************************************/
#include "rssblockscfgdlg.h"
#include "rssblocksdef.h"
#include <wx/sizer.h>
#include <wx/gbsizer.h>
#include <wx/filepicker.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/spinctrl.h>
#include <wx/checkbox.h>
#include <wx/uri.h>
#include <wx/hyperlink.h>

namespace rssblocks{
/**WindowID's*/
const long RssBlocksCfgDlg::ID_URL = wxNewId();
const long RssBlocksCfgDlg::ID_CTPL = wxNewId();
const long RssBlocksCfgDlg::ID_ITPL = wxNewId();
const long RssBlocksCfgDlg::ID_SAVETMP = wxNewId();
const long RssBlocksCfgDlg::ID_UPTIME = wxNewId();
const long RssBlocksCfgDlg::ID_LINK = wxNewId();

BEGIN_EVENT_TABLE(RssBlocksCfgDlg,cbConfigurationPanel)

END_EVENT_TABLE()


RssBlocksCfgDlg::RssBlocksCfgDlg(wxEvtHandler* evt,wxWindow* parent,wxWindowID id)
{
	//create dialog
	Create(parent,id);
	//create sizer
	wxFlexGridSizer* topSizer = new wxFlexGridSizer(1,10,10);
	topSizer->AddGrowableCol(0);
	topSizer->AddGrowableRow(3);
	//url
	wxFlexGridSizer* urlSizer= new wxFlexGridSizer(2,10,10);
	urlSizer->AddGrowableCol(1);
	urlSizer->Add(new wxStaticText(this,wxID_ANY,_("Channel's URL")),
			1,wxALIGN_CENTER_VERTICAL);
	urlSizer->Add(new wxTextCtrl(this,ID_URL),1,wxEXPAND);
	urlSizer->Add(new wxStaticText(this,wxID_ANY,_("Update every(minutes)")),
			wxALIGN_CENTER_VERTICAL);
	urlSizer->Add(new wxSpinCtrl(this,ID_UPTIME),1,wxEXPAND);
	urlSizer->Add(new wxCheckBox(this,ID_SAVETMP,_("Save temporary files")),
			1,wxEXPAND);
	wxSizer* urlBox = new wxStaticBoxSizer(wxVERTICAL,this,_("Channel"));
	urlBox->Add(urlSizer,1,wxEXPAND);
	topSizer->Add(urlBox,1,wxEXPAND);
	//tpl
	wxFlexGridSizer* tplSizer= new wxFlexGridSizer(2,10,10);
	tplSizer->AddGrowableCol(1);
	tplSizer->Add(new wxStaticText(this,wxID_ANY,_("Channel template file")),1,wxALIGN_CENTER_VERTICAL);
	tplSizer->Add(new wxFilePickerCtrl(this,ID_CTPL),1,wxEXPAND);
	tplSizer->Add(new wxStaticText(this,wxID_ANY,_("Item template file")),1,wxALIGN_CENTER_VERTICAL);
	tplSizer->Add(new wxFilePickerCtrl(this,ID_ITPL),1,wxEXPAND);
	wxSizer* tplBox = new wxStaticBoxSizer(wxVERTICAL,this,_("Html Templates"));
	tplBox->Add(tplSizer,1,wxEXPAND);
	topSizer->Add(tplBox,1,wxEXPAND);
	//link, please click it!!!
	topSizer->Add(new wxHyperlinkCtrl(this,ID_LINK,
			_("Learn how to use and create html templates."),
			_T("http://rssblocks.sourceforge.net")),1);
	//set sizer
	SetSizer(topSizer);
	topSizer->Fit(this);
	//read config
	ConfigManager* cfg = Manager::Get()->GetConfigManager(rssblocks::rss_namespace);
	//url
	wxString str;
	str = cfg->Read(rssblocks::url,rssblocks::url_def);
	wxDynamicCast(FindWindow(ID_URL),wxTextCtrl)->SetValue(str);
	//channel template
	str = cfg->Read(rssblocks::channeltp,rssblocks::channeltp_def);
	wxDynamicCast(FindWindow(ID_CTPL),wxFilePickerCtrl)->SetPath(str);
	//item template
	str = cfg->Read(rssblocks::itemtp,rssblocks::itemtp_def);
	wxDynamicCast(FindWindow(ID_ITPL),wxFilePickerCtrl)->SetPath(str);
	//update time
	int updatetime = rssblocks::updatetime_def;
	cfg->Read(rssblocks::updatetime,&updatetime);
	wxDynamicCast(FindWindow(ID_UPTIME),wxSpinCtrl)->SetValue(updatetime);
	//save temp
	bool savetmp = rssblocks::savetmp_def;
	savetmp = cfg->ReadBool(rssblocks::savetmp,rssblocks::savetmp_def);
	wxDynamicCast(FindWindow(ID_SAVETMP),wxCheckBox)->SetValue(savetmp);
	//tooltips
	FindWindow(ID_URL)->SetToolTip(_("The url to the rss data, like http://agender.sf.net/rss.xml"));
	FindWindow(ID_CTPL)->SetToolTip(_("The rbc file of your preference"));
	FindWindow(ID_ITPL)->SetToolTip(_("The rbi file of your preference"));
	FindWindow(ID_UPTIME)->SetToolTip(_("How often would you like that Rss::Blocks refreshes the channel(in minutes)"));
	FindWindow(ID_SAVETMP)->SetToolTip(_("Save the data to temp folder, making it available offline"));
	FindWindow(ID_LINK)->SetToolTip(_("Read the online documentation available at rssblocks.sf.net"));
	p_evt = evt;
}

RssBlocksCfgDlg::~RssBlocksCfgDlg()
{
	//dtor -- nothing todo
}

void RssBlocksCfgDlg::OnCancel()
{
}

void RssBlocksCfgDlg::OnApply()
{
	ConfigManager* cfg = Manager::Get()->GetConfigManager(rssblocks::rss_namespace);
	//url
	wxURI uri_check(wxDynamicCast(
			FindWindow(ID_URL),wxTextCtrl)->GetValue());
	cfg->Write(wxT("url"),uri_check.BuildURI());
	cfg->Write(wxT("channeltp"),wxDynamicCast(
		FindWindow(ID_CTPL),wxFilePickerCtrl)->GetPath());
	cfg->Write(wxT("itemtp"),wxDynamicCast(
		FindWindow(ID_ITPL),wxFilePickerCtrl)->GetPath());
	cfg->Write(wxT("updatetime"),wxDynamicCast(
		FindWindow(ID_UPTIME),wxSpinCtrl)->GetValue());
	cfg->Write(wxT("savetmp"),wxDynamicCast(
		FindWindow(ID_SAVETMP),wxCheckBox)->IsChecked());
	//send an event
	wxCommandEvent event(wxEVT_COMMAND_MENU_SELECTED,GetId());
	event.SetEventObject(this);
	wxPostEvent(p_evt,event);
}
}//namespace rssblocks
