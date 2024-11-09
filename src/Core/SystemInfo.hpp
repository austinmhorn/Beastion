#ifndef SystemInfo_hpp
#define SystemInfo_hpp

#if WIN32 || WIN64
#include <windows.h>
#elif LINUX || linux || __linux__
#include <X11/Xlib.h>
#elif __APPLE__ || __MACH__
#include <CoreGraphics/CGDisplayConfiguration.h>
#else
#endif

#include <string>
#include <sys/stat.h>

/////////////////////////////////////////////////
/// @brief Fetch computer screen resolution
/////////////////////////////////////////////////
static void fetchScreenResolution(unsigned int& width, unsigned int& height) 
{
#if WIN32 || WIN64
    width = (int)GetSystemMetrics(SM_CXSCREEN);
    height = (int)GetSystemMetrics(SM_CYSCREEN);
#elif LINUX || linux || __linux__
    Display* d = XOpenDisplay(NULL);
    Screen*  s = DefaultScreenOfDisplay(d);
    width = s->width;
    height = s->height;
#elif __APPLE__ || __MACH__
    auto mainDisplayId = CGMainDisplayID();
    width = static_cast<unsigned int>(CGDisplayPixelsWide(mainDisplayId));
    height = static_cast<unsigned int>(CGDisplayPixelsHigh(mainDisplayId));
#else
#endif
}

////////////////////////////////////////////////////////////
/// @brief Determine if a file exists 
/// @return True if file exists, false if no match found
////////////////////////////////////////////////////////////
static bool fileExistenceCheck(const std::string& name) 
{
    struct stat buffer;
    return (stat(name.c_str(), &buffer) == 0);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief Count the number of files matching a pattern in a directory exist
/// @return True if file exists, false if no match found
////////////////////////////////////////////////////////////////////////////////
static int directoryFileCount(std::string dir, std::string prefix, std::string extension)
{
    int count = 0;

    for (int i = 1; i < 5000000; ++i) // Limit count to five million files
    {
        std::string filename = "";
        filename.append(dir);
        filename.append(prefix);
        filename.append(std::to_string(i));
        filename.append(extension);
        bool status = fileExistenceCheck(filename);

        if (!status)
            break;
        else
            count = i;
    }

    return count;
}

#endif /* SystemInfo_hpp */
