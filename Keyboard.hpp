
#include <array>        // for std::array
#include <cstring>      // for memcpy
#include <iostream>     // for std::cerr
#include <fstream>      // for std::ifstream
#include <linux/input.h>

#include "Keymap.hpp"


namespace Ctankep
{
    
    class Keyboard
    {
    private:
        enum class KEYSTATE {KEYPRESS, KEYRELEASE, KEYDOWN, KEYUP, KEYHOLD};
        KEYSTATE _keyhold;
        int _keyholdvalue;
        const Keymap _keymap;
        struct input_event _event;                  // to capture keyboard node
        std::array<char,sizeof(_event)> _data;      // to capture keyvoard data
        std::ifstream _file;                        // to open keyboard node as
                                                    // a file

    private:
        int init();
    public:
        Keyboard(const char* path);
        ~Keyboard();
        int keyPress();
        int keyRelease();
        int keyHold();
        int test();

        

    };



}