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

const long RssBlocksCfgDlg::ID_URL = wxNewId();
const long RssBlocksCfgDlg::ID_CTPL = wxNewId();
const long RssBlocksCfgDlg::ID_ITPL = wxNewId();
const long RssBlocksCfgDlg::ID_SAVETMP = wxNewId();
const long RssBlocksCfgDlg::ID_UPTIME = wxNewId();

BEGIN_EVENT_TABLE(RssBlocksCfgDlg,cbConfigurationPanel)

END_EVENT_TABLE()


RssBlocksCfgDlg::RssBlocksCfgDlg(wxWindow* parent,wxWindowID id)
{
	//create dialog
	Create(parent,id);
	//create sizer
	wxFlexGridSizer* topSizer = new wxFlexGridSizer(2,10,10);
	topSizer->AddGrowableCol(1);
	//add controls
	topSizer->Add(new wxStaticText(this,wxID_ANY,_("Channel's URL")),1);
	topSizer->Add(new wxTextCtrl(this,ID_URL),1,wxEXPAND);
	topSizer->Add(new wxStaticText(this,wxID_ANY,_("Channel template file")),1);
	topSizer->Add(new wxFilePickerCtrl(this,ID_CTPL),1,wxEXPAND);
	topSizer->Add(new wxStaticText(this,wxID_ANY,_("Item template file")),1);
	topSizer->Add(new wxFilePickerCtrl(this,ID_ITPL),1,wxEXPAND);
	topSizer->Add(new wxStaticText(this,wxID_ANY,_("Update every(minutes)")),1);
	topSizer->Add(new wxSpinCtrl(this,ID_UPTIME),1,wxEXPAND);
	topSizer->Add(new wxCheckBox(this,ID_SAVETMP,_("Save temporary files")),1,wxEXPAND);
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
	cfg->ReadBool(rssblocks::savetmp,&savetmp);
	wxDynamicCast(FindWindow(ID_SAVETMP),wxCheckBox)->SetValue(savetmp);
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
	ConfigManager* cfg = Manager::Get()->GetConfigManager(rssblocks::rss_namespace);
	//url
	cfg->Write(wxT("url"),wxDynamicCast(
		FindWindow(ID_URL),wxTextCtrl)->GetValue());
	cfg->Write(wxT("channeltp"),wxDynamicCast(
		FindWindow(ID_CTPL),wxFilePickerCtrl)->GetPath());
	cfg->Write(wxT("itemtp"),wxDynamicCast(
		FindWindow(ID_ITPL),wxFilePickerCtrl)->GetPath());
	cfg->Write(wxT("updatetime"),wxDynamicCast(
		FindWindow(ID_UPTIME),wxSpinCtrl)->GetValue());
	cfg->Write(wxT("savetmp"),wxDynamicCast(
		FindWindow(ID_SAVETMP),wxCheckBox)->IsChecked());
}
