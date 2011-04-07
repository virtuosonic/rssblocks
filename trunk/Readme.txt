/******************************************************************************
*                   Rss::Blocks, a rss reader for Code::Blocks
******************************************************************************/

Web:
====
	http://rssblocks.sf.net

Intro:
======
    Thanks for trying this software, Rss::Blocks is a codeblocks plugin
    that shows rss feeds from the channel of your choice in a window
    that can easily be customized using html, to read the online
    documentation visit the website or read the source code.

Licence:
========
    Rss::Blocks is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Rss::Blocks is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    If you dont have a copy of the GNU General Public License
    visit <http://www.gnu.org/licenses/>.

ChangeLog:
==========
    0.4 - Abr 2011:
    -Added link to documentation in config panel
    -Fixed the bitmap for the cfg panel
    -Grouped controls inside static boxes

    0.3 - 1 Abr 2011:
    -F5 forces update inmediatedly
    -feeds are stored in temp folder
    -unvalid url characters are scaped
    -if opening the requested url fails it uses the temp
    -fixed warnings
    -timer changes after changing settings

    0.2 - 28 Mar 2011:
    -changed default url
    -fixed: now the update time is really in minutes
    -links are open in the default web browser
    -Documented with doxygen

    0.1 - 16 Mar 2011:
    -first release

TODO:
=====
    -wxWebConnect support
    -https support
    -show saveral channels
    -notify of new feeds
    -better exceptions handling
    -fix bugs

Bugs:
=====
    -If you disable or uninstall this plugin or quit CodeBlocks
    while the plugin's window is floating it surely will crash
    Code::Blocks, give it a try.
    -If you have Rss::Blocks installed to update you must
    uninstall it restart codeblocks and then install the new
    version, else it crashes codeblocks

Author:
=======
Gabriel Espinoza
	virtuosonic@users.sourceforge.net
Thanks for reading :) EOF
