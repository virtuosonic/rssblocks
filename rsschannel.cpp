/***************************************************************
 * Name:      rsschannel.cpp
 * Purpose:   rsschannel class implementation
 * Author:    Gabriel Espinoza
 * Created:   2011-02-26
 * Copyright: Gabriel Espinoza
 * License: GPLv3+
 **************************************************************/
#include "rsschannel.h"

/** @brief Constructor
 *
 * This creates an rsschannel object
 *@param rssdoc an inputstream containing xml rss data
 */
rsschannel::rsschannel(wxInputStream& rssdoc) throw (int)
{
	//ctor
	m_doc.Load(rssdoc);
	wxXmlNode* root = m_doc.GetRoot();
	//no root!
	if (root == NULL)
		throw -1;
	//this is a rss
	if (root->GetName() == wxT("rss"))
	{
		FindChannel(root);
	}
	else {
		throw -2;
	}
}

/**@brief Destructor
 *
 * Does nothing
 */
rsschannel::~rsschannel()
{
	//dtor
}

/** @brief FindChannel
  *
  * Finds the channel node
  *@param node an xml node
  */
void rsschannel::FindChannel(wxXmlNode* node)
{
	//search for channel
	wxXmlNode* channel_node = node->GetChildren();
	while (channel_node != NULL)
	{
		if (channel_node->GetName() ==wxT("channel"))
		{
			FindItems(channel_node);
			channel_node = NULL;
		}
		else
		{
			channel_node = channel_node->GetNext();
		}
	}
}

/** @brief FindItems
  *
  * @todo: document this function
  */
void rsschannel::FindItems(wxXmlNode* node)
{
	wxXmlNode* child_node = node->GetChildren();
	while (child_node != NULL)
	{
		if (child_node->GetName() ==wxT("title"))
		{
			m_title = child_node->GetNodeContent();
		}
		else if (child_node->GetName() ==wxT("link"))
		{
			m_link = child_node->GetNodeContent();
		}
		else if (child_node->GetName() ==wxT("description"))
		{
			m_desc = child_node->GetNodeContent();
		}
		else if (child_node->GetName() ==wxT("item"))
		{
			AddItem(child_node);
		}
		child_node = child_node->GetNext();
	}
}

/** @brief AddItem
  *
  * @todo: document this function
  */
void rsschannel::AddItem(wxXmlNode* node)
{
	try {
		rssitem* n_item = new rssitem(node);
		items.Add(n_item);
	}
	catch(...)
	{
		// TODO (gabriel#1#): handle apropiatedly
	}
}

