/***************************************************************
 * Name:      rssitem.h
 * Purpose:   rssitem class definition
 * Author:    Gabriel Espinoza
 * Created:   2011-02-26
 * Copyright: Gabriel Espinoza
 * License: GPLv3+
 **************************************************************/
#ifndef RSSITEM_H
#define RSSITEM_H

#include <wx/xml/xml.h>
#include <wx/dynarray.h>

/**@brief A rss item
  *
  * Represents a rss item
  */
class rssitem
{
	public:
		rssitem(wxXmlNode* node) throw (int);
		~rssitem();
		//accessors
		/**Returns the description of the item*/
		const wxString& Getdesc() {return m_desc;}
		/**Returns the title of the item*/
		const wxString& Gettitle() {return m_title;}
		/**Returns the link of the item*/
		const wxString& Getlink() {return m_link;}
	private:
		void Setlink(wxString val) {m_link = val;}
		void Settitle(wxString val) {m_title = val;}
		void Setdesc(wxString val) {m_desc = val;}
		//Members
		wxString m_desc;
		wxString m_title;
		wxString m_link;
		wxXmlNode* m_node;
};

WX_DEFINE_ARRAY(rssitem*,rssitemsarray);

#endif // RSSITEM_H
