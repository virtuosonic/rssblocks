/***************************************************************
 * Name:      rssitem.cpp
 * Purpose:   rssitem class implementation
 * Author:    Gabriel Espinoza
 * Created:   2011-02-26
 * Copyright: Gabriel Espinoza
 * License: LGPLv3+
 **************************************************************/
#include "rssitem.h"

namespace virtuosonic{

/**@brief Constructor
  *
  * Reads a rssitem object from a xml node,
  * the node usually is managed from a
  * wxXmlDocument so  it isn't deleted
  * or modified by rssitem
  *
  *@param node a xml node containing the item
  */
rssitem::rssitem(wxXmlNode* node) throw (int)
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

/**@brief Destructor
  * Does nothing
  */
rssitem::~rssitem()
{
	//dtor
}
}//namespace rssblocks
