#include "Farbe.hpp"
#include <iostream>

int main()
{
    // Test default constructor
    Farbe defaultFarbe;
    std::cout << "Default Farbe: " << defaultFarbe << std::endl;

    // Test parameterized constructor
    Farbe customFarbe(123, 45, 67);
    std::cout << "Custom Farbe: " << customFarbe << std::endl;

    // Test array access operator ([])
    try
    {
        std::cout << "Custom Farbe Red: " << static_cast<int>(customFarbe[0]) << std::endl;
        std::cout << "Custom Farbe Green: " << static_cast<int>(customFarbe[1]) << std::endl;
        std::cout << "Custom Farbe Blue: " << static_cast<int>(customFarbe[2]) << std::endl;
    }
    catch (const std::out_of_range &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    // Modify colors using array access operator
    customFarbe[0] = 200;
    customFarbe[1] = 150;
    customFarbe[2] = 100;
    std::cout << "Modified Custom Farbe: " << customFarbe << std::endl;

    // Test toString method
    std::cout << "Custom Farbe toString: " << customFarbe.toString() << std::endl;

    // Test LONG_OUTPUT functionality
    Farbe::LONG_OUTPUT = true;
    std::cout << "Custom Farbe (LONG_OUTPUT): " << std::endl;
    std::cout << customFarbe << std::endl;

    Farbe::LONG_OUTPUT = false;
    std::cout << "Custom Farbe (short output): " << customFarbe << std::endl;

    return 0;
}
