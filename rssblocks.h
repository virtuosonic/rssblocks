/***************************************************************
 * Name:      rssblocks.h
 * Purpose:   Code::Blocks plugin
 * Author:    Gabriel Espinoza (virtuosonic@users.sourceforge.net)
 * Created:   2011-02-24
 * Copyright: Gabriel Espinoza
 * License:   GPLv3+
 **************************************************************/
#ifndef RSSBLOCKS_H
#define RSSBLOCKS_H

// For compilers that support precompilation, includes <wx/wx.h>
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <cbplugin.h> // for "class cbPlugin"
#include "rssblockscfgdlg.h"

class rsswindow;

/**@brief Rss::Blocks plugin class
  *
  * This is the where this plugin starts
  * running
  */
class rssblocks : public cbPlugin
{
	public:
		/** Constructor. */
		rssblocks();
		/** Destructor. */
		virtual ~rssblocks();

		virtual int Configure();
		virtual int GetConfigurationPriority() const {return 50;}
		virtual int GetConfigurationGroup() const {return cgUnknown;}
		/** Return plugin's configuration panel.
		  * @param parent The parent window.
		  * @return A pointer to the plugin's cbConfigurationPanel. It is deleted by the caller.
		  */
		virtual cbConfigurationPanel* GetConfigurationPanel(wxWindow* parent) {

			RssBlocksCfgDlg* dlg = new RssBlocksCfgDlg(this,parent,ID_RSSCFGDLG);
			return dlg;
		}

		/** This method is called by Code::Blocks and is used by the plugin
		  * to add any menu items it needs on Code::Blocks's menu bar.\n
		  * It is a pure virtual method that needs to be implemented by all
		  * plugins. If the plugin does not need to add items on the menu,
		  * just do nothing ;)
		  * @param menuBar the wxMenuBar to create items in
		  */
		virtual void BuildMenu(wxMenuBar* menuBar);
		virtual void BuildModuleMenu(const ModuleType type, wxMenu* menu, const FileTreeData* data = 0);
		virtual bool BuildToolBar(wxToolBar* toolBar);
	protected:
		/** Any descendent plugin should override this virtual method and
		  * perform any necessary initialization. This method is called by
		  * Code::Blocks (PluginManager actually) when the plugin has been
		  * loaded and should attach in Code::Blocks. When Code::Blocks
		  * starts up, it finds and <em>loads</em> all plugins but <em>does
		  * not</em> activate (attaches) them. It then activates all plugins
		  * that the user has selected to be activated on start-up.\n
		  * This means that a plugin might be loaded but <b>not</b> activated...\n
		  * Think of this method as the actual constructor...
		  */
		virtual void OnAttach();

		/** Any descendent plugin should override this virtual method and
		  * perform any necessary de-initialization. This method is called by
		  * Code::Blocks (PluginManager actually) when the plugin has been
		  * loaded, attached and should de-attach from Code::Blocks.\n
		  * Think of this method as the actual destructor...
		  * @param appShutDown If true, the application is shutting down. In this
		  *         case *don't* use Manager::Get()->Get...() functions or the
		  *         behaviour is undefined...
		  */
		virtual void OnRelease(bool appShutDown);

	private:
		rsswindow* m_window;
		static const long ID_RSSMENU;
		static const long ID_RSSCFGDLG;
		//handlers
		void OnMenuRss(wxCommandEvent& event);
		void OnUpdateCfg(wxCommandEvent& event);
		DECLARE_EVENT_TABLE();
};

#endif // RSSBLOCKS_H
