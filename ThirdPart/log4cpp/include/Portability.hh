/*
 * Portability.hh
 *
 * Copyright 2001, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2001, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#ifndef _LOG4CPP_PORTABILITY_HH
#define _LOG4CPP_PORTABILITY_HH

#if defined (_MSC_VER) || defined(__BORLANDC__)
#    if defined (LOG4CPP_STLPORT_AND_BOOST_BUILD)
#        include <config-win32-stlport-boost.h>
#    else
#        include "config-win32.h"
#    endif
#else
#if defined(__OPENVMS__)
#    include <log4cpp/config-openvms.h>
#else
#   if defined(__MINGW32__)
#       include <config-MinGW32.h>
#   else
#       include <config.h>
#   endif
#endif
#endif

#include "Export.hh"

#if defined(_MSC_VER)
#    pragma warning( disable : 4786 ) // 255 char debug symbol limit
#    pragma warning( disable : 4290 ) // throw specifier not implemented
#    pragma warning( disable : 4251 ) // "class XXX should be exported"
#endif

#ifndef LOG4CPP_HAVE_SSTREAM
#include <strstream>
namespace std {
    class LOG4CPP_EXPORT ostringstream : public ostrstream {
        public:
        std::string str();
    };
}
#endif

#endif
