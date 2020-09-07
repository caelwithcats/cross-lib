//#pragma once

#ifdef __MINGW32__ || _WIN32
    #include <windows.h>
    #include <string.h>
    #include <tchar.h>
    #include <commctrl.h>
#else
    #include <time.h>
    #include <X11/Xlib.h>
    #include <gtk/gtk.h>
    #include <unistd.h>
    #include <thread>
#endif

// Put headers here that are not OS dependent and are used by both operating systems
#include "cross_features.h"
#include <cstddef>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <cstring>
#include <type_traits>
#include <random>
#include <cstdlib>
#include <ctime>
#include <math.h>