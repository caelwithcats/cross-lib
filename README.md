# CrossLib
CrossLib is a C++ API specificly made for compiling using a cross compiler. This will allow you to compile your code on multiple operating systems (linux and windows). For more infomation go to [link to be decided].

The source code for CrossLib can be found in `src/cross.h`.
To install CrossLib, you will need to install the dependencies

    sudo apt-get install mingw-w64 g++ gcc build-essential libx11-dev
## Creating your first graphical application
Clone the CrossLib repository by typing in your terminal

    git clone https://github.com/caelwithcats/cross-lib.git
Copy the the `cross.h` file into project. 
To import CrossLib into your C++ project add this line to your C++ file

    #include <cross.h>
And that's it you now have CrossLib installed in your C++ project.
CrossLib has a GUI framework called CrossGUI. This is what we will be using to create the hello world project. Create a new C++ file and add the following code to it:

    #include <cross.h>
    int main() {
        return 0;
    }

## Additional infomation about CrossLib

### CrossGUI
CrossGUI uses GTK (linux GUI framework) and the win32 api. Using these two it has compatibility for Linux and Windows.
