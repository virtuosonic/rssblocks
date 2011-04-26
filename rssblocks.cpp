/***************************************************************
 * Name:      rsschannel.cpp
 * Purpose:   rsschannel class implementation
 * Author:    Gabriel Espinoza
 * Created:   2011-02-26
 * Copyright: Gabriel Espinoza
 * License: GPLv3+
 **************************************************************/
#include <sdk.h> // Code::Blocks SDK
#include <configurationpanel.h>
#include "rssblocks.h"
#include "rsswindow.h"

// Register the plugin with Code::Blocks.
// We are using an anonymous namespace so we don't litter the global one.
namespace
{
PluginRegistrant<rssblocks> reg(_T("rssblocks"));
}

const long rssblocks::ID_RSSMENU = wxNewId();
// events handling
BEGIN_EVENT_TABLE(rssblocks, cbPlugin)
	EVT_MENU(ID_RSSMENU,rssblocks::OnMenuRss)
	// add any events you want to handle here
END_EVENT_TABLE()

// constructor
rssblocks::rssblocks()
{
	// Make sure our resources are available.
	// In the generated boilerplate code we have no resources but when
	// we add some, it will be nice that this code is in place already ;)
	if(!Manager::LoadResource(_T("rssblocks.zip")))
	{
		NotifyMissingFile(_T("rssblocks.zip"));
	}
}

// destructor
rssblocks::~rssblocks()
{
}

void rssblocks::OnAttach()
{
	m_window = new rsswindow(Manager::Get()->GetAppWindow(),wxID_ANY);
	CodeBlocksDockEvent evt(cbEVT_ADD_DOCK_WINDOW);
    evt.name = _T("RssPane");
    evt.title = _("Rss::Blocks");
    evt.pWindow = m_window;
    evt.shown = true;
    evt.dockSide = CodeBlocksDockEvent::dsFloating;
    evt.desiredSize.Set(350, 250);
    evt.floatingSize.Set(350, 250);
    evt.minimumSize.Set(150, 150);
    Manager::Get()->ProcessEvent(evt);
	// do whatever initialization you need for your plugin
	// NOTE: after this function, the inherited member variable
	// m_IsAttached will be TRUE...
	// You should check for it in other functions, because if it
	// is FALSE, it means that the application did *not* "load"
	// (see: does not need) this plugin...
}

void rssblocks::OnRelease(bool appShutDown)
{
	// do de-initialization for your plugin
	// if appShutDown is true, the plugin is unloaded because Code::Blocks is being shut down,
	// which means you must not use any of the SDK Managers
	// NOTE: after this function, the inherited member variable
	// m_IsAttached will be FALSE...
	CodeBlocksDockEvent evt(cbEVT_REMOVE_DOCK_WINDOW);
    //evt.name = _T("RssPane");
    evt.pWindow = m_window;
	m_window->Destroy();
}

int rssblocks::Configure()
{
	//create and display the configuration dialog for your plugin
	cbConfigurationDialog dlg(Manager::Get()->GetAppWindow(), wxID_ANY, _("Your dialog title"));
	cbConfigurationPanel* panel = GetConfigurationPanel(&dlg);
	if (panel)
	{
		dlg.AttachConfigurationPanel(panel);
		PlaceWindow(&dlg);
		return dlg.ShowModal() == wxID_OK ? 0 : -1;
	}
	return -1;
}

void rssblocks::BuildMenu(wxMenuBar* menuBar)
{
	wxMenu* helpMenu = menuBar->GetMenu(menuBar->GetMenuCount() - 1);
	helpMenu->Insert(2,ID_RSSMENU,_("RSS Feeds"),
		_("Read your favorite RSS channel"))->SetBitmap(
			wxXmlResource::Get()->LoadBitmap(wxT("rssmenu")));
	//The application is offering its menubar for your plugin,
	//to add any menu items you want...
	//Append any items you need in the menu...
	//NOTE: Be careful in here... The application's menubar is at your disposal.
}

void rssblocks::BuildModuleMenu(const ModuleType type, wxMenu* menu, const FileTreeData* data)
{
	/**Not supported**/
	//Some library module is ready to display a pop-up menu.
	//Check the parameter \"type\" and see which module it is
	//and append any items you need in the menu...
	//TIP: for consistency, add a separator as the first item...
	NotImplemented(_T("rssblocks::BuildModuleMenu()"));
}

bool rssblocks::BuildToolBar(wxToolBar* toolBar)
{
	//The application is offering its toolbar for your plugin,
	//to add any toolbar items you want...
	//Append any items you need on the toolbar...
	//NotImplemented(_T("rssblocks::BuildToolBar()"));
//	toolBar->AddTool(wxID_ANY,wxEmptyString,
//					wxXmlResource::Get()->LoadBitmap(_T("rss")));

	// return true if you add toolbar items
	return false;
}
//
//void rssblocks::OnNewFeed(wxCommandEvent& event)
//{
//	InfoWindow::Display(wxT("Rss::Blocks"),
//		wxT("New feed found on channel: %s\n%s\n%s"));
//}

/** @brief OnMenuRss
  *
  * @todo: document this function
  */
void rssblocks::OnMenuRss(wxCommandEvent& event)
{
	if (m_window)
	{

		CodeBlocksDockEvent evt(cbEVT_SHOW_DOCK_WINDOW);
		//evt.name = _T("RssPane");
		evt.pWindow = m_window;
		Manager::Get()->ProcessEvent(evt);
	}
}
