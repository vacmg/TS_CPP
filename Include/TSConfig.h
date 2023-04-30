/*
 *
 * This header configures the level of verbosity of the TSManager module
 * Verbose level can range from TS_LEVEL_MUTE (No messages) to TS_LEVEL_DEBUG (All messages)
 * To set the level of verbosity, modify macro TS_PRINT_MESSAGES_LEVEL a few lines below
 *
 */

#ifndef TS_TSCONFIG_H
#define TS_TSCONFIG_H

namespace TS_CPP{

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)
#define AT " AT " __FILE__ ":" TOSTRING(__LINE__)

#define TS_LEVEL_DEBUG 3
#define TS_LEVEL_INFO 2
#define TS_LEVEL_ERROR 1
#define TS_LEVEL_MUTE 0

#ifndef TS_PRINT_MESSAGES_LEVEL
/// This macro set the level of verbosity of the TSManager to one of this values: TS_LEVEL_MUTE, TS_LEVEL_ERROR, TS_LEVEL_INFO, TS_LEVEL_DEBUG
#define TS_PRINT_MESSAGES_LEVEL TS_LEVEL_ERROR // CHANGE THIS LINE TO SET THE LEVEL OF PRINT MESSAGES
#endif

#ifndef TS_NULLSTRINGREPLACEMENT
/// If a nullptr is placed inside an attribute value of type string of an entry, this string will be used instead for better human readability
#define TS_NULLSTRINGREPLACEMENT "'-'"
#endif

#if TS_PRINT_MESSAGES_LEVEL == TS_LEVEL_DEBUG
#define tsdebug(message,...) fprintf(stderr,"TS_DEBUG: " message "\n",__VA_ARGS__); fflush(stderr)
#else
#define tsdebug(message,...)
#endif

#if TS_PRINT_MESSAGES_LEVEL >= TS_LEVEL_INFO
#define tsinfo(message,...) fprintf(stderr,"TS_INFO: " message "\n",__VA_ARGS__); fflush(stderr)
#else
#define tsinfo(message,...)
#endif

#if TS_PRINT_MESSAGES_LEVEL >= TS_LEVEL_ERROR
#define tserror(message,...) fprintf(stderr,"TS_ERROR:" AT "; " message "\n",__VA_ARGS__); fflush(stderr)
#else
#define tserror(message,...)
#endif

}

#endif //TS_TSCONFIG_H
