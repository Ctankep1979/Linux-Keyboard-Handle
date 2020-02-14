# LINUX KEYBOARD
`Linux-Keyboard-Handle` is a C++ interface to access `Key Press`, `Key Hold`, and `Key Release` events. It is based on `/dev/input/` device folder's events.  
This interface is dependent on `#include <linux/input.h>` header file to access different keyboard events in shell.

---

# Sample Implemention
```javascript
#include "Keyboard.hpp"

int main()
{
    Ctankep::Keyboard _key("/dev/input/event12");
    std::map<int,int> key;
    int d;
    while(1)
    {
        d = _key.keyPress();
        if(d == KEY_A)
        {
            std::cout << "key a pressed: " << std::endl;
        }
    }
    return 0;
}
```
Methods `keyPress()`, `keyHold()`, and `keyRelease()` return the same value as values from `linux/input.h` header.  
> You need to have a root access in order to access `/dev/input/event*`