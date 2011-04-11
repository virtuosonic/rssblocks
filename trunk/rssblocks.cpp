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

/**@mainpage Rss::Blocks
  *
  * @image html rss1.png
  * Rss::Blocks is a codeblocks plugin
  * that shows rss feeds from the channel of your choice in a window
  * that can easily be customized using @ref tpl_p
  *
  * - @ref install_p
  * - @ref tpl_p
  * @section Download
  * You can download Rss::Blocks
  * from the file manager at sourceforge.
  * There you should find a zip file
  * containing the source code, datafiles
  * and the Code::Blocks project to build it.
  *@author Gabriel Espinoza <a href="http://virtuosonic.users.sourceforge.net">virtuosonic at  sf_net</a>
  */

// Registere the plugin with Code::Blocks.
namespace rssblocks
{
PluginRegistrant<RssBlocksPlugin> reg(_T("rssblocks"));


/**@page install_p Installation
  * To install Rss::Blocks follow this instructions
  *   - Download the latest release
  *   - Uncompress it
  *   - open rssblocks.cbp
  *   - build the default target
  *   - build the install target
  *
  * NOTE: If you have Rss::Blocks installed, to update you must
  * uninstall it, restart codeblocks and then install the new
  * version.
  */


/**WindowID's*/
const long RssBlocksPlugin::ID_RSSMENU = wxNewId();
const long RssBlocksPlugin::ID_RSSCFGDLG = wxNewId();
// events handling
BEGIN_EVENT_TABLE(RssBlocksPlugin, cbPlugin)
	EVT_MENU(ID_RSSMENU,RssBlocksPlugin::OnMenuRss)
	EVT_MENU(ID_RSSCFGDLG,RssBlocksPlugin::OnUpdateCfg)
	// add any events you want to handle here
END_EVENT_TABLE()

/**@brief constructor
  *
  * Called by Code::Blocks PluginManager
  */
RssBlocksPlugin::RssBlocksPlugin()
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
RssBlocksPlugin::~RssBlocksPlugin()
{
}

void RssBlocksPlugin::OnAttach()
{
	m_window = new rsswindow(Manager::Get()->GetAppWindow(),wxNewId());
	CodeBlocksDockEvent evt(cbEVT_ADD_DOCK_WINDOW);
    evt.name = _T("RssPane");
    evt.title = _T("Rss::Blocks");
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

void RssBlocksPlugin::OnRelease(bool WXUNUSED(appShutDown))
{
	// do de-initialization for your plugin
	// if appShutDown is true, the plugin is unloaded because Code::Blocks is being shut down,
	// which means you must not use any of the SDK Managers
	// NOTE: after this function, the inherited member variable
	// m_IsAttached will be FALSE...
	CodeBlocksDockEvent evt(cbEVT_REMOVE_DOCK_WINDOW);
    evt.name = _T("RssPane");
    evt.pWindow = m_window;
	m_window->Destroy();
}

int RssBlocksPlugin::Configure()
{
	//create and display the configuration dialog for your plugin
	cbConfigurationDialog dlg(Manager::Get()->GetAppWindow(), wxID_ANY, _("Rss::Clocks settings"));
	cbConfigurationPanel* panel = GetConfigurationPanel(&dlg);
	if (panel)
	{
		dlg.AttachConfigurationPanel(panel);
		PlaceWindow(&dlg);
		return dlg.ShowModal() == wxID_OK ? 0 : -1;
	}
	return -1;
}

void RssBlocksPlugin::BuildMenu(wxMenuBar* menuBar)
{
	wxMenu* helpMenu = menuBar->GetMenu(menuBar->GetMenuCount() - 1);
	helpMenu->Insert(2,ID_RSSMENU,_("RSS Feeds"),
		_("Read your favorite RSS channel"))->SetBitmap(
			wxXmlResource::Get()->LoadBitmap(wxT("rssmenu")));
}

void RssBlocksPlugin::BuildModuleMenu(const ModuleType
		WXUNUSED(type), wxMenu* WXUNUSED(menu),
		const FileTreeData* WXUNUSED(data))
{
	/**Not supported**/
	NotImplemented(_T("RssBlocksPlugin::BuildModuleMenu()"));
}

bool RssBlocksPlugin::BuildToolBar(wxToolBar* WXUNUSED(toolBar))
{
		/**Not supported**/
		return false;
}

//void RssBlocksPlugin::OnNewFeed(wxCommandEvent& event)
//{
//	InfoWindow::Display(wxT("Rss::Blocks"),
//		wxT("New feed found on channel: %s\n%s\n%s"));
//}

/** @brief OnMenuRss
  *
  * @todo: document this function
  */
void RssBlocksPlugin::OnMenuRss(wxCommandEvent& WXUNUSED(event))
{
	if (m_window)
	{

		CodeBlocksDockEvent evt(cbEVT_SHOW_DOCK_WINDOW);
		//evt.name = _T("RssPane");
		evt.pWindow = m_window;
		Manager::Get()->ProcessEvent(evt);
	}
}

void RssBlocksPlugin::OnUpdateCfg(wxCommandEvent& WXUNUSED(event))
{
	m_window->InitUpdateTime();
}
}//namespace rssblocks
