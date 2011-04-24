/***************************************************************
 * Name:      rsschannel.h
 * Purpose:   rsschannel class definition
 * Author:    Gabriel Espinoza
 * Created:   2011-02-26
 * Copyright: Gabriel Espinoza
 * License: LGPLv3+
 **************************************************************/
#ifndef RSSCHANNEL_H
#define RSSCHANNEL_H

#include "rssitem.h"
#include <wx/xml/xml.h>
#include <stdexcept>

namespace virtuosonic {
/**@brief A rss channel
  *
  * This class represents a rss channel,
  * created from an wxInputStream with
  * valid rss+xml data
  */
class rsschannel
{
	public:
		rsschannel(wxInputStream& rssdoc) throw (std::invalid_argument);
		virtual ~rsschannel();
		//accessors
		/**Returns an array containing the items in this channel*/
		const rssitemsarray& GetItems() {return items;}
		/**Returns the description of the channel*/
		const wxString& Getdesc() {return m_desc;}
		/**Returns the title of the channel*/
		const wxString& Gettitle() {return m_title;}
		/**Returns the link of the channel*/
		const wxString& Getlink() {return m_link;}
	private:
		wxXmlDocument m_doc;
		rssitemsarray items;
		wxString m_title;
		wxString m_desc;
		wxString m_link;
		//this functions are inline only to avoid
		//to much identation
		inline void FindChannel(wxXmlNode* node);
		inline void FindItems(wxXmlNode* node);
		inline void AddItem(wxXmlNode* node);
};
}//namespace virtuosonic

#endif // RSSCHANNEL_H
