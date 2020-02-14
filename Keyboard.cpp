#include "Keyboard.hpp"

namespace Ctankep
{
    Keyboard::~Keyboard()
    {
        if(_file.is_open())
        {
            _file.close();
        }
    }

    Keyboard::Keyboard(const char* path) 
    {
        _keyhold = KEYSTATE::KEYUP;
        _keyholdvalue = -2;
        try
        {
            _file.open(path);

        }
        catch(std::ifstream::failure e)
        {
            std::cerr << "Error opening file: " << path << '\n';
        }
    }

    int Keyboard::init()
    {
        if(_file.is_open())
        {
            try
            {
                _file.read(_data.begin(), sizeof(_event));
                memcpy(&_event, _data.begin(), sizeof(_event));
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
                return 0;
            }
            
        } else 
        {
            std::cerr << "Input is not open" << '\n';
            return 0;
        }
        return 1;
    }

    int Keyboard::keyPress()
    {
        KEYSTATE _STATE = KEYSTATE::KEYUP;
        int value = -2;

        if(init())
        {
            value = _keymap.keyCode.at(static_cast<int>(_event.value));
        } else
        {
            return -2;
        }

        while(1)
        {
            switch (_STATE)
            {
            case KEYSTATE::KEYUP:
                if(_event.value > 2)
                {
                    _STATE = KEYSTATE::KEYDOWN;
                    init();
                } else
                {
                    return -2;
                }
                break;

            case KEYSTATE::KEYDOWN:
                if(_event.value == 1)
                {

                    return value;

                } else
                {
                    return -2;
                }
                break;
            default:
                return -2;
                break;
            }
        }

        return -2;
    }

    int Keyboard::keyRelease()
    {
        KEYSTATE _STATE = KEYSTATE::KEYUP;
        int value = -2;

        if(init())
        {
            value = _keymap.keyCode.at(static_cast<int>(_event.value));
        } else
        {
            return -2;
        }
        
        while(1)
        {
            switch (_STATE)
            {
            case KEYSTATE::KEYUP:
                if(_event.value > 2)
                {
                    _STATE = KEYSTATE::KEYDOWN;
                    init();
                } else
                {
                    return -2;
                }
                break;

            case KEYSTATE::KEYDOWN:
                if(_event.value == 0)
                {
                    return value;

                 } else
                {
                    return -2;
                }
                break;
            
            default:
                break;
            }
        }

        return -2;
    }

    int Keyboard::keyHold()
    {

        KEYSTATE _STATE = KEYSTATE::KEYUP;
        int value = -2;

        if(_keyhold == KEYSTATE::KEYHOLD)
        {
            _STATE = KEYSTATE::KEYHOLD;
        }

        if(init())
        {
            value = _keymap.keyCode.at(static_cast<int>(_event.value));
        } else
        {
            return -2;
        }

        while(1)
        {
            switch (_STATE)
            {
            case KEYSTATE::KEYUP:
                _keyhold = KEYSTATE::KEYUP;
                if(_event.value > 2)
                {
                    _STATE = KEYSTATE::KEYDOWN;
                    _keyholdvalue = value;
                    init();
                } else
                {
                    _keyholdvalue = -2;
                    return -2;
                }
                break;
            case KEYSTATE::KEYDOWN:
                if(_event.value == 1)
                {
                    _STATE = KEYSTATE::KEYDOWN;
                    init();
                } else if(_event.value == 0)
                {
                    _STATE = KEYSTATE::KEYHOLD;
                    init();
                } else
                {
                    _keyholdvalue = -2;
                    return -2;
                }
                break;

            case KEYSTATE::KEYHOLD:
                if(_event.value == 2 || _event.value == 1)
                {
                    _keyhold = KEYSTATE::KEYHOLD;
                    return _keyholdvalue;
                } else
                {
                    _keyhold = KEYSTATE::KEYUP;
                    _keyholdvalue = -2;
                    return -2;
                }
                break;

            default:
                _keyholdvalue = -2;
                return -2;
                break;
            }
        }

        return -2;

    }

    
    int Keyboard::test()
    {
        if(init())
        {
            return _event.value;
        }
        return -2;
    }

}