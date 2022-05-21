#include "Employee.hpp"
#include "Server.hpp"

int main()
{
    std::cout << "\nEmployee exapmle\n";

    // Mivel dinamikus polimorfizmus használunk, nem elegek temporális példényok. ( e("Terézia", 69, NormalSalery{}) nem működne sadly. )
    ManagerSalery msc;
    NormalSalery nsc;

    Employee e("Terézia", 69, nsc);
    std::cout << e.calculate_salery() << std::endl;

    Employee e2("Meow", 44, nsc);
    e.add_underling(e2);

    e.set_salery_calculator(msc);
    std::cout << e.calculate_salery() << std::endl;

    /*--------------------------------------------------------------------------------*/

    std::cout << "\nServer exapmle\n";
    RetryFiveTimes five;
    RetryForEver forever;
    std::cout << "Connecting to server...\n";
    std::cout << (connect(forever) ? "Succesfully connected to server" : "Could not connect to server") << std::endl;
}