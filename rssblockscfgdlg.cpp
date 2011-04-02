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
#include <wx/filepicker.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/spinctrl.h>
#include <wx/checkbox.h>
#include <wx/uri.h>

const long RssBlocksCfgDlg::ID_URL = wxNewId();
const long RssBlocksCfgDlg::ID_CTPL = wxNewId();
const long RssBlocksCfgDlg::ID_ITPL = wxNewId();
const long RssBlocksCfgDlg::ID_SAVETMP = wxNewId();
const long RssBlocksCfgDlg::ID_UPTIME = wxNewId();

BEGIN_EVENT_TABLE(RssBlocksCfgDlg,cbConfigurationPanel)

END_EVENT_TABLE()


RssBlocksCfgDlg::RssBlocksCfgDlg(wxEvtHandler* evt,wxWindow* parent,wxWindowID id)
{
	//create dialog
	Create(parent,id);
	//create sizer
	wxFlexGridSizer* topSizer = new wxFlexGridSizer(2,10,10);
	topSizer->AddGrowableCol(1);
	//add controls
	topSizer->Add(new wxStaticText(this,wxID_ANY,_("Channel's URL")),1,wxALIGN_CENTER_VERTICAL);
	topSizer->Add(new wxTextCtrl(this,ID_URL),1,wxEXPAND);
	topSizer->Add(new wxStaticText(this,wxID_ANY,_("Channel template file")),1,wxALIGN_CENTER_VERTICAL);
	topSizer->Add(new wxFilePickerCtrl(this,ID_CTPL),1,wxEXPAND);
	topSizer->Add(new wxStaticText(this,wxID_ANY,_("Item template file")),1,wxALIGN_CENTER_VERTICAL);
	topSizer->Add(new wxFilePickerCtrl(this,ID_ITPL),1,wxEXPAND);
	topSizer->Add(new wxStaticText(this,wxID_ANY,_("Update every(minutes)")),1,wxALIGN_CENTER_VERTICAL);
	topSizer->Add(new wxSpinCtrl(this,ID_UPTIME),1,wxEXPAND);
	topSizer->Add(new wxCheckBox(this,ID_SAVETMP,_("Save temporary files")),1,wxEXPAND);
	//set sizer
	SetSizer(topSizer);
	topSizer->Fit(this);
	//read config
	ConfigManager* cfg = Manager::Get()->GetConfigManager(rssblocksdef::rss_namespace);
	//url
	wxString str;
	str = cfg->Read(rssblocksdef::url,rssblocksdef::url_def);
	wxDynamicCast(FindWindow(ID_URL),wxTextCtrl)->SetValue(str);
	//channel template
	str = cfg->Read(rssblocksdef::channeltp,rssblocksdef::channeltp_def);
	wxDynamicCast(FindWindow(ID_CTPL),wxFilePickerCtrl)->SetPath(str);
	//item template
	str = cfg->Read(rssblocksdef::itemtp,rssblocksdef::itemtp_def);
	wxDynamicCast(FindWindow(ID_ITPL),wxFilePickerCtrl)->SetPath(str);
	//update time
	int updatetime = rssblocksdef::updatetime_def;
	cfg->Read(rssblocksdef::updatetime,&updatetime);
	wxDynamicCast(FindWindow(ID_UPTIME),wxSpinCtrl)->SetValue(updatetime);
	//save temp
	bool savetmp = rssblocksdef::savetmp_def;
	savetmp = cfg->ReadBool(rssblocksdef::savetmp,rssblocksdef::savetmp_def);
	wxDynamicCast(FindWindow(ID_SAVETMP),wxCheckBox)->SetValue(savetmp);
	//tooltips
	FindWindow(ID_URL)->SetToolTip(_("The url to the rss data, like http://agender.sf.net/rss.xml"));
	FindWindow(ID_CTPL)->SetToolTip(_("The rbc file of your preference"));
	FindWindow(ID_ITPL)->SetToolTip(_("The rbi file of your preference"));
	FindWindow(ID_UPTIME)->SetToolTip(_("How often would you like that Rss::Blocks refreshes the channel(in minutes)"));
	FindWindow(ID_SAVETMP)->SetToolTip(_("Save the data to temp folder, making it available offline"));
	p_evt = evt;
}

RssBlocksCfgDlg::~RssBlocksCfgDlg()
{
	//dtor -- nothing todo
}

/** @brief OnCancel
  *
  * @todo: document this function
  */
void RssBlocksCfgDlg::OnCancel()
{
}

/** @brief OnApply
  *
  * @todo: document this function
  */
void RssBlocksCfgDlg::OnApply()
{
	ConfigManager* cfg = Manager::Get()->GetConfigManager(rssblocksdef::rss_namespace);
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
