/***************************************************************
 * Name:      rssitem.cpp
 * Purpose:   rssitem class implementation
 * Author:    Gabriel Espinoza
 * Created:   2011-02-26
 * Copyright: Gabriel Espinoza
 * License: GPLv3+
 **************************************************************/
#include "rssitem.h"

rssitem::rssitem(wxXmlNode* node)
{
	m_node = node;
	if (m_node->GetName() != wxT("item"))
	{
		// TODO (gabriel#1#): throw error
		throw -1;
	}
	//read
	wxXmlNode* child_node = m_node->GetChildren();
	while (child_node != NULL)
	{
		if (child_node->GetName() == wxT("title"))
		{
			Settitle(child_node->GetNodeContent());
		}
		else if(child_node->GetName() == wxT("link"))
		{
			Setlink(child_node->GetNodeContent());
		}
		else if (child_node->GetName() == wxT("description"))
		{
			Setdesc(child_node->GetNodeContent());
		}
		child_node = child_node->GetNext();
	}
}

rssitem::~rssitem()
{
	//dtor
}
