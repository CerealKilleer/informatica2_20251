#include <iostream>
#include <fstream>
#include <app.h>

int main(int argc, char* argv[])
{
    
    if (argc != 5) {
        std::cerr << "Uso: " << argv[0] << " [origen] [destino] [metodo] [semilla]" << std::endl;
        return -1;
    }

    if (app_main(argv) == EXIT_FAILURE) {
        std::cerr << "Error en la aplicación" << std::endl;
        return -1;
    }
    
    return 0;
}