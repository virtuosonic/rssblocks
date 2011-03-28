/***************************************************************
 * Name:      rssblocks.cpp
 * Purpose:   rssblocks plugin implementation
 * Author:    Gabriel Espinoza
 * Created:   2011-02-26
 * Copyright: Gabriel Espinoza
 * License: GPLv3+
 **************************************************************/
#include <sdk.h> // Code::Blocks SDK
#include <configurationpanel.h>
#include <wx/menu.h>
#include "rssblocks.h"
#include "rsswindow.h"

/**@mainpage Rss::Blocks Developer Documentation
  *
  * Thanks for trying this software, this is the documentation of
  * Rss::Blocks, Rss::Blocks is a codeblocks plugin
  * that shows rss feeds from the channel of your choice in a window
  * that can easily be customized using @ref tpl_p
  *
  * - @ref install_p
  * - @ref tpl_p
  *
  *@author Gabriel Espinoza <a href="http://virtuosonic.users.sourceforge.net">virtuosonic at  sf_net</a>
  */

// Register the plugin with Code::Blocks.
// We are using an anonymous namespace so we don't litter the global one.
namespace
{
PluginRegistrant<rssblocks> reg(_T("rssblocks"));
}

/**@page install_p Installation
  * To install Rss::Blocks follow this instructions
  *   - Download the latest release
  *   - Build Rss::Blocks with Code::Blocks
  *   - Copy default.rbc and default.rbi to the share/CodeBlocks/ folder
  *   - Copy rssblocks.png and rssblocks-off.png to the share/CodeBlocks/images/settings/ folder
  *   - Then install rssblocks.cbplugin with "Manage Plugins"
  */
const long rssblocks::ID_RSSMENU = wxNewId();
// events handling
BEGIN_EVENT_TABLE(rssblocks, cbPlugin)
	EVT_MENU(ID_RSSMENU,rssblocks::OnMenuRss)
	// add any events you want to handle here
END_EVENT_TABLE()

/**@brief constructor
  *
  * Called by Code::Blocks PluginManager
  */
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

/**@brief destructor
  *
  * Does nothing
  */
rssblocks::~rssblocks()
{
}

void rssblocks::OnAttach()
{
	m_window = new rsswindow(Manager::Get()->GetAppWindow(),wxNewId());
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
}

void rssblocks::BuildModuleMenu(const ModuleType type, wxMenu* menu, const FileTreeData* data)
{
	/**Not supported**/
	NotImplemented(_T("rssblocks::BuildModuleMenu()"));
}

bool rssblocks::BuildToolBar(wxToolBar* toolBar)
{
		/**Not supported**/
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
