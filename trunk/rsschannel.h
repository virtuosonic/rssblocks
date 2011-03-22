/***************************************************************
 * Name:      rsschannel.h
 * Purpose:   rsschannel class definition
 * Author:    Gabriel Espinoza
 * Created:   2011-02-26
 * Copyright: Gabriel Espinoza
 * License: GPLv3+
 **************************************************************/
#ifndef RSSCHANNEL_H
#define RSSCHANNEL_H

#include "rssitem.h"
#include <wx/xml/xml.h>

class rsschannel
{
	public:
		rsschannel(wxInputStream& rssdoc);
		virtual ~rsschannel();
		//accessors
		rssitemsarray& GetItems() {return items;}
		const wxString& Getdesc() {return m_desc;}
		const wxString& Gettitle() {return m_title;}
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

#endif // RSSCHANNEL_H
