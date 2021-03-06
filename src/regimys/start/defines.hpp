#ifndef DEFINES_HPP
#define DEFINES_HPP

#ifdef __GNUC__
#define OP_DEPRECATED __attribute__((deprecated))
#elif defined(_MSC_VER)
#define OP_DEPRECATED __declspec(deprecated)
#else
#define OP_DEPRECATED
#endif

/**
Shortcuts
*/
#define UNS using namespace std;
#define toStr(toStrP) #toStrP

/**
Linux only. If defined, the program will search for the resources on the local directory, instead of /usr/share/OpMon
*/
#define LOCAL_TEST
/**
Return how many time in milliseconds the program is open
*/
#define GET_TICKS ticks.getElapsedTime().asMilliseconds()

/**
 * Location of the resource folder
 */
#if defined(LOCAL_TEST) && !defined(_WIN32)
#define RESSOURCES_PATH std::string("data/")
#else
#define RESSOURCES_PATH std::string("/usr/share/OpMon/")
#endif

/* location of the save folder */
#define SAVE_PATH std::string("saves/")


#endif
