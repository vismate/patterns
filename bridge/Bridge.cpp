#include "System.hpp"
#include "Transport.hpp"

int main()
{
    // Eskü rossz erre a példa kódra ránézni...

    std::cout << "\nSystem exapmle\n";

    Windows win;
    Linux _linux;
    Mac mac;

    UserGUI winU{&win};
    UserGUI linuxU{&_linux};
    UserGUI macU{&mac};

    AdminGUI winA{&win};
    AdminGUI linuxA{&_linux};
    AdminGUI macA{&mac};

    std::cout << "\nUser GUI\n";

    winU.init();
    linuxU.init();
    macU.init();

    winU.button1_clicked();
    linuxU.button1_clicked();
    macU.button1_clicked();

    winU.button2_clicked();
    linuxU.button2_clicked();
    macU.button2_clicked();

    std::cout << "\nAdmin GUI\n";

    winA.init();
    linuxA.init();
    macA.init();

    winA.button1_clicked();
    linuxA.button1_clicked();
    macA.button1_clicked();

    winA.button2_clicked();
    linuxA.button2_clicked();
    macA.button2_clicked();

    winA.admin_button_clicked();
    linuxA.admin_button_clicked();
    macA.admin_button_clicked();

    /*--------------------------------------------------------------------*/

    std::cout << "\nTransport exapmle\n";

    Express express;
    Normal normal;

    Plane plane_express{&express};
    Train train_express{&express};

    Plane plane_normal{&normal};
    Train train_normal{&normal};

    plane_express.load();
    plane_express.carry();
    plane_express.unload();

    train_normal.load();
    train_normal.carry();
    train_normal.unload();
}