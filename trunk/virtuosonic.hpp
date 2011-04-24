/***************************************************************
 * Name:      virtuosonic.hpp
 * Purpose:   common utility functions
 * Author:    Gabriel Espinoza
 * Created:   11-Abr-2011
 * Copyright: Gabriel Espinoza
 * License: GPLv3+
 **************************************************************/
#ifndef VIRTUOSONIC_HPP
#define VIRTUOSONIC_HPP

/**the powerful virtuosonic namespace*/
namespace virtuosonic
{
	#ifdef __WXWINDOWS__
	#include <exception>
	#include <wx/string.h>
	/**@brief exception class for wxWidgets applications
	  * this function wraps the standard exceptions, can be
	  * useful for use with multiple herence
	  */
	class wxException : public std::exception
	{
		public:
			wxException(const std::exception& e){m_str=wxString::Format(_T("%s"),e.what());}
			wxException(const wxString& arg){m_str = arg;}
			void operator = (const wxException& rhs) {m_str = rhs.m_str;}
			void operator = (const std::exception& rhs) {m_str=wxString::Format(_T("%s"),rhs.what());}
			~wxException() throw(){}
			wxString what()
			{
				if (!m_str.IsEmpty())
					return m_str;
				//ELSE
				return wxString::Format(_T("%s"),exception::what());
			}
		private:
			wxString m_str;
	};
	/** combines std::invalid_argument and wxException*/
	class wxInvalidArg :
		public std::invalid_argument, public wxException{};
	#endif//__WXWINDOWS__
	//gettext
	#ifndef _
		#define _(x) x
	#endif


}//namespace virtuosonic

#endif // VIRTUOSONIC_HPP
