#pragma once

#include <iostream>

// Belső API (Implementáció interface)
struct Delivery
{
    virtual auto issue() -> void = 0;
};

// Konkrét implemenáció
struct Normal : Delivery
{
    virtual auto issue() -> void override
    {
        std::cout << "Normal delivery for two weeks\n";
    }
};

struct Express : Delivery
{
    virtual auto issue() -> void override
    {
        std::cout << "Super fast delivery for 3 days\n";
    }
};

// Kliens oldali API (Absztrakció)
struct Transport
{
    Delivery *delivery;
    Transport(Delivery *delivery) : delivery(delivery){};
    virtual auto load() -> void = 0;
    // Pointereknél illene vmi nullptr check, dee most az nem lényeg.
    auto set_delivery(Delivery *delivery) -> void { this->delivery = delivery; }
    virtual auto carry() -> void = 0;
    virtual auto unload() -> void = 0;
};

// Kiterjesztett (finomított) absztrakció
struct Plane : Transport
{
    Plane(Delivery *delivery) : Transport(delivery){};
    virtual auto load() -> void override
    {
        // Plane load impl.
        std::cout << "Loading plane\n";
    }
    virtual auto carry() -> void override
    {
        // Plane carry impl.
        delivery->issue();
        std::cout << "The plane flew off... Done!\n";
    }
    virtual auto unload() -> void override
    {
        // Plane unload impl.
        std::cout << "Unloading plane\n";
    }
};

struct Train : Transport
{
    Train(Delivery *delivery) : Transport(delivery){};
    virtual auto load() -> void override
    {
        // Train load impl.
        std::cout << "Loading train\n";
    }
    virtual auto carry() -> void override
    {
        // Train carry impl.
        delivery->issue();
        std::cout << "The train left... Done!\n";
    }
    virtual auto unload() -> void override
    {
        // Train unload impl.
        std::cout << "Unloading train\n";
    }
};