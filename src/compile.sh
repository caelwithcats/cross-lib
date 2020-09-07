BUILDOSTARGET=$1
BUILDARCHTARGET=$2
firstFlag=$3
if [ $firstFlag == "--actions-build" ]
then
    mainfile=./src/example.cpp
else
    mainfile=crossExample.cpp
fi
# Windows
# 32-bit
echo "  Main file: $mainfile"
if [ $BUILDOSTARGET == "win32" ]
then
    echo "  Building for $BUILDOSTARGET"
    if [ $BUILDARCHTARGET == 32 ]
    then
        echo "  CPU architecture: x32"
    else
        echo "  CPU architecture: x64"
    fi
elif [ $BUILDOSTARGET == "linux" ]
then
    echo "  Building for $BUILDOSTARGET x64."
    if [ $BUILDARCHTARGET == 32 ]
    then
        echo "  Cannot compile for x32 bit because GTK does not support it (which crossLib is based on)"
    fi
else
    echo "  Unkown target \"$BUILDOSTARGET\""
fi
printf "\n  ---------------------\n"
if [ $BUILDOSTARGET == "win32" ]
then
    if [ $BUILDARCHTARGET == 32 ]
    then
        i686-w64-mingw32-g++ -ggdb -g3 -std=c++17 -static-libstdc++ -static-libgcc -o windows-out.exe $mainfile
    else
        # x64-bit windows
        x86_64-w64-mingw32-g++ -ggdb -g3 -std=c++17 -static-libstdc++ -static-libgcc -o windows-out.exe $mainfile
    fi
fi
# 0-bit
#moo

# linux
# 32-bit, might not work yet
# g++ -m32 -o out example.cpp -lX11 `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0`
# 64-bit linux
if [ $BUILDOSTARGET == "linux" ]
then
    g++ -std=c++17 -m64 -o out $mainfile -lX11 `pkg-config --cflags gtk+-3.0` `pkg-config --libs gtk+-3.0`
fi
