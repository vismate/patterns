#pragma once

#include <iostream>
#include <vector>

// Employee class elődeklarációja, hogy a SaleryCalculator tudja miről van szó.
class Employee;

struct SaleryCalulator
{
    // Sidenote: a pattern nem írja elő, hogy Employee-t kapjon paraméterül. It's just an example.
    virtual auto calculate(const Employee &employee) const -> unsigned = 0;
};

// 1. opció: paraméterként
/*
class Employee
{
public: // private lenne, de lusta vagyok gettereket használni.
    std::string name;
    unsigned hours_a_week;
    std::vector<Employee> underlings;

public:
    Employee(std::string name, unsigned hours_a_week) : name(name), hours_a_week(hours_a_week) {}
    inline auto add_underling(Employee &underling) -> void { underlings.push_back(underling);}
    inline auto calculate_salery(const SaleryCalulator &sc)
    {
        return sc.calculate(*this);
    }
};*/

// 2. opció: adattagként
class Employee
{
public: // private lenne, de lusta vagyok gettereket használni.
    std::string name;
    unsigned hours_a_week;
    std::vector<Employee *> underlings;

    SaleryCalulator *sc;

public:
    Employee(std::string name, unsigned hours_a_week, SaleryCalulator &sc) : name(name), hours_a_week(hours_a_week), sc(&sc) {}

    inline auto add_underling(Employee &underling) -> void { underlings.push_back(&underling); }

    inline auto set_salery_calculator(SaleryCalulator &sc) -> void { this->sc = &sc; }

    inline auto calculate_salery()
    {
        return sc->calculate(*this);
    }
};

struct NormalSalery : SaleryCalulator
{
    virtual auto calculate(const Employee &employee) const -> unsigned override
    {
        return employee.hours_a_week * 3000;
    }
};

struct EmployeeOfTheMothSalery : SaleryCalulator
{
    virtual auto calculate(const Employee &employee) const -> unsigned override
    {
        NormalSalery sc;
        return sc.calculate(employee) * 1.5;
    }
};

struct ManagerSalery : SaleryCalulator
{
    virtual auto calculate(const Employee &employee) const -> unsigned override
    {
        NormalSalery sc;
        return sc.calculate(employee) + employee.underlings.size() * 1500;
    }
};