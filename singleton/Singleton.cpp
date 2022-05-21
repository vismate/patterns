#include <iostream>
#include <array>

class Configuration
{

    // Ez is privát lenne, csak lusta vagyok gettereket írni megint...
public:
    std::pair<unsigned, unsigned> resolution;
    std::array<unsigned char, 4> text_color;
    // ...

private:
    // 2. verzióhoz
    static Configuration *instance;

    // A empty constructor privát, ezért nem tudunk az egyetlen instance-on kívül másikat kreálni.
    // Fontos viszont hogy legyen privát empty constructor, mert ha nincs, akkor automatikusan kapunk egy publikus default változatot.
    Configuration()
    {
        resolution = std::make_pair(1280, 720);
        text_color[0] = 0;
        text_color[1] = 230;
        text_color[2] = 120;
        text_color[3] = 255;

        //...
    }

public:
    inline auto read(std::istream &stream) -> void
    {
        // read config from stream...
    }

    // Lazy initialization (on stack)
    inline static auto get_instance() -> Configuration &
    {
        static Configuration conf;
        return conf;
    }

    // Ez is technically lazy inicializáció, de már a heap-en
    inline static auto get_treszka_instance() -> Configuration &
    {
        if (instance == nullptr)
        {
            instance = new Configuration();
        }

        return *instance;
    }

    // Technically működik enélkül is, de mi Jézus követői vagyunk...
    // pl.: delete &Configuration::get_treszka_instance() is perfect pl a main végén (ahol ezt is meghívod)
    inline static auto destroy_instance() -> void
    {
        delete instance;
        instance = nullptr;
    }
};

// Statikus változót csak out of line lehet inicializálni.
// Bár a statikus változók mindig nullára vannak inicializálva, deee jobb félni mint megijedni.
Configuration *Configuration::instance = nullptr;

int main()
{
    // Itt a bináris programban van hely "foglalva" az instance-nek.
    // Első híváskor (itt) inicializálódik.
    std::cout << (int)Configuration::get_instance().text_color[3] << std::endl;

    // Itt a heap-en inicializálódik a példány, amikor elősször meghívjuk a függvényt.
    std::cout << Configuration::get_treszka_instance().resolution.first << std::endl;

    // Viszont akkor törölni is kell, mert a heap-ről automatikus nem törlődnek objektumok. (vagy hát kinda igen, de hivatalosan nem.)
    // delete &Configuration::get_treszka_instance();
    Configuration::destroy_instance();
}