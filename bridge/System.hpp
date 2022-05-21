#pragma once

#include <iostream>

// Két API (Interface) együttes működése.
// Az egyik (általában a platform specifikus) interface apróbb részfeladatokat határoz meg.
// A másik (kliens oldali) interface nagyobb (több metódust használva az előző API-ból) feladatokat határoz meg.
// Mindkét interface-nek lehetnek eltérő konkrét implementációi, bár gyakori variáns amikor a kliens oldali interface egyetlen egy implementáció.

struct System
{
    struct Window
    {
        // Nevermind this, azért kell, hogy complete type legyen a window
        unsigned id;
    };

    virtual auto enter_root_environment() -> void = 0;
    virtual auto open_window() -> Window = 0;
    virtual auto open_file(std::string path) -> unsigned char * = 0;
};

struct Windows : System
{
    virtual auto enter_root_environment() -> void override
    {
        std::cout << "Run as administrator... (or sth)\n";
    }
    virtual auto open_window() -> Window override
    {
        // 1. Create window class descriptor
        // 2. Register window class
        // 3. Instanciate window object
        std::cout << "Windows opened a window\n";

        return Window{1};
    }
    virtual auto open_file(std::string path) -> unsigned char * override
    {
        std::cout << "Opening file under Windows: " << path << std::endl;
        return nullptr; // vagy vmi ptr a file byte-jaira...
    }
};

struct Linux : System
{
    virtual auto enter_root_environment() -> void override
    {
        std::cout << "sudo / doas\n";
    }
    virtual auto open_window() -> Window override
    {
        std::cout << "Linux opened a window\n";

        return Window{1};
    }
    virtual auto open_file(std::string path) -> unsigned char * override
    {
        std::cout << "Opening file under Linux: " << path << std::endl;
        return nullptr; // vagy vmi ptr a file byte-jaira...
    }
};

struct Mac : System
{
    virtual auto enter_root_environment() -> void override
    {
        std::cout << "Root env under Mac (I have no idea how Mac works...)\n";
    }
    virtual auto open_window() -> Window override
    {
        std::cout << "Mac opened a window\n";

        return Window{1};
    }
    virtual auto open_file(std::string path) -> unsigned char * override
    {
        std::cout << "Opening file under Mac: " << path << std::endl;
        return nullptr; // vagy vmi ptr a file byte-jaira...
    }
};

struct GUI
{
    System *system;
    // Pointereknél illene vmi nullptr check, dee most az nem lényeg.
    GUI(System *sys) : system(sys){};
    auto init() -> bool
    {
        if (!system)
            return false;

        system->open_window();
        return true;
    }
    virtual auto button1_clicked() -> void = 0;
    virtual auto button2_clicked() -> void = 0;
    // ...
};

struct UserGUI : GUI
{
    UserGUI(System *sys) : GUI(sys){};

    virtual auto button1_clicked() -> void
    {
        system->open_file("./puppies.png");
        //...
    };
    virtual auto button2_clicked() -> void
    {
        system->open_file("./kitties.png");
        //...
    };
};

struct AdminGUI : GUI
{
    AdminGUI(System *sys) : GUI(sys){};

    virtual auto button1_clicked() -> void
    {
        system->open_file("./hardcore_puppies.png");
        //...
    };
    virtual auto button2_clicked() -> void
    {
        system->open_file("./hardcore_kitties.png");
        //...
    };
    auto admin_button_clicked() -> void
    {
        system->enter_root_environment();
        system->open_file("/admin_config.conf");
        //...
    }
};