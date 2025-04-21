#include <app_cajero.hpp>
#include <lib_cypher_decipher.hpp>
#include <app.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdint.h>
#include <sstream>

#define ADMIN_FILE "sudo.txt"
#define USERS_FILE "users.txt"
#define CYPHER_METHOD "c1"
#define DECIPHER_METHOD "d1"
#define SEMILLA 6
#define BITS_ON_BYTES 8
#define NULL_STR ""
#define NO_DATA "0"
int main_app()
{
    u_int16_t opc;
    std::string user_data = NO_DATA;
    std::string admin_file = read_data(ADMIN_FILE, decipher_1, SEMILLA);
    std::string users_file = read_data(USERS_FILE, decipher_1, SEMILLA);

    if (admin_file.empty()) {
        std::cout << "Error al leer el archivo de administradores" << std::endl;
        return 1;
    }

    if (admin_file == NO_DATA)
        admin_file = NULL_STR;

    if (users_file.empty()) {
        std::cout << "Error al leer el archivo de usuarios" << std::endl;
        return 1;
    }

    if (users_file == NO_DATA)
        users_file = NULL_STR;
    
    
    do {
        std::cout << "1. Administrador\n2. Usuario\n3. Salir\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opc;
        if (std::cin.fail()) {
            std::cin.clear();
            while (std::cin.get() != '\n');
            opc = 0;
        }
        switch (opc) {
            case 1:
                std::cout << "Administrador\n";
                if (validar_usuario(admin_file, true, user_data))
                    app_administrador(users_file);
                break;
            case 2:
                std::cout << "Usuario\n";
                if (validar_usuario(users_file, false, user_data))
                    app_user(users_file, user_data);
                break;
            case 3:
                std::cout << "Salir\n";
                break;
            default:
                std::cout << "Opción no válida. Intente de nuevo.\n";
        }
    } while (opc != 3);
    return 0;
}

bool validar_usuario(const std::string& file_string, bool is_admin, std::string& user_data)
{
    if (file_string.empty()) {
        std::cout << "Error al leer el archivo" << std::endl;
        return false;
    }

    std::string user_cedula;
    std::string pass;

    if (is_admin) {
        std::cout << "Ingrese usuario: ";
        std::cin >> user_cedula;
    }
    else{
        std::cout << "Ingrese cedula: ";
        std::cin >> user_cedula;
    }

    std::cout << "Ingrese contraseña: ";
    std::cin >> pass;

    if (validate_user_pass(user_cedula, pass, file_string, is_admin, user_data)) {
        std::cout << "Autenticación exitosa\n";
        return true;
    } else {
        std::cout << "Error de autenticación\n";
        return false;
    }
}

std::string read_data(const char* file, method_ptr metodo, uint32_t semilla)
{
    uint8_t * memory_block;
    uint8_t ** binary_matrix;
    int32_t rows; 
    std::string user_file = NO_DATA;

    rows = read_file(file, &memory_block);

    if (rows == -1) {
        std::cout << "No se pudo abrir el archivo" << std::endl;
        return NULL_STR;
    }

    if (rows == 0) {
        return user_file;
    }

    if (!assign_matrix_bytes(&binary_matrix, rows)) {
        std::cout << "No se pudo asignar memoria dinámica" << std::endl;
        return NULL_STR;
    }

    if (!int_to_binary_matrix(memory_block, binary_matrix, rows)) {
        std::cout << "Error al convertir a binario" << std::endl;
        delete[] memory_block;
        delete_matrix(&binary_matrix, rows);
        return NULL_STR;
    }

    delete[] memory_block;

    if (!metodo(binary_matrix, semilla, rows, BITS_ON_BYTES)) {
        std::cout << "Error al aplicar la operación" << std::endl;
        delete_matrix(&binary_matrix, rows);
        return NULL_STR;
    }

    memory_block = new uint8_t[rows];
    
    if (memory_block == NULL) {
        std::cout << "Error. Sin memoria" << std::endl;
        delete_matrix(&binary_matrix, rows);
        return NULL_STR;
    }

    bin_to_char(binary_matrix, rows, memory_block);
    delete_matrix(&binary_matrix, rows);
    user_file = std::string((char *)memory_block);

    delete[] memory_block;
    
    return user_file;
}

bool validate_user_pass(std::string &user_cedula, std::string &password, const std::string& file_string, bool is_admin, std::string& user_data)
{
    std::istringstream stream(file_string);
    std::string line, new_line;

    while (std::getline(stream, line)) {
        new_line = line;
        if (!is_admin)
            line = line.substr(0, line.find_last_of(','));

        if (line == user_cedula + "," + password) {
            user_data = new_line;
            return true;
        }
    }
    return false;
}

bool crear_usuario(std::string& users_file)
{
    std::string cedula;
    std::string pass;
    std::string str_saldo;
    std::string new_user;
    int32_t saldo; 

   
    std::cout << "Ingrese cedula: ";
    std::cin >> cedula;
    std::cout << "Ingrese contraseña: ";
    std::cin >> pass;
    std::cout << "Ingrese saldo: ";
    std::cin >> saldo;

    if (std::cin.fail()) {
        std::cin.clear();
        while (std::cin.get() != '\n');
        std::cout << "Error. Todos los campos son obligatorios.\n";
        return false;
    }

    if (saldo < 0) {
        std::cout << "Error. El saldo no puede ser negativo.\n";
        return false;
    }

    if (cedula.empty() || pass.empty()) {
        std::cout << "Error. Todos los campos son obligatorios.\n";
        return false;
    }

    if (!is_number(cedula)) {
        std::cout << "Error. Cedula y saldo deben ser números.\n";
        return false;
    }

    if (!validate_new_user(users_file, cedula)) {
        std::cout << "Error. El usuario ya existe.\n";
        return false;
    }
    
    new_user =  cedula + ',' + pass + ',' + std::to_string(saldo) + '\n'; 
    users_file += new_user;

    if (!write_data(USERS_FILE, cypher_1, SEMILLA, users_file)) {
        std::cout << "Error al escribir el archivo de usuarios" << std::endl;
        return false;
    }

    std::cout << "Usuario creado exitosamente\n";
    return true;
}

bool write_data(const char* data_file, method_ptr metodo, uint32_t semilla,  const std::string& file_string)
{
    uint8_t * memory_block;
    uint8_t ** binary_matrix;
    int32_t rows = file_string.size();

    
    if (rows == 0) {
        std::cout << "Nada que escribir" << std::endl;
        return false;
    }
    
    memory_block = new uint8_t[rows];
    if (memory_block == NULL) {
        std::cout << "Error. Sin memoria" << std::endl;
        return false;
    }

    std::copy(file_string.begin(), file_string.end(), memory_block);
    
    if (!assign_matrix_bytes(&binary_matrix, rows)) {
        std::cout << "No se pudo asignar memoria dinámica" << std::endl;
        return false;
    }

    if (!int_to_binary_matrix(memory_block, binary_matrix, rows)) {
        std::cout << "Error al convertir a binario" << std::endl;
        delete[] memory_block;
        delete_matrix(&binary_matrix, rows);
        return false;
    }

    delete[] memory_block;

    if (!metodo(binary_matrix, semilla, rows, BITS_ON_BYTES)) {
        std::cout << "Error al aplicar la operación" << std::endl;
        delete_matrix(&binary_matrix, rows);
        return false;
    }

    memory_block = new uint8_t[rows];
    
    if (memory_block == NULL) {
        std::cout << "Error. Sin memoria" << std::endl;
        delete_matrix(&binary_matrix, rows);
        return false;
    }

    bin_to_char(binary_matrix, rows, memory_block);
    delete_matrix(&binary_matrix, rows);

    std::ofstream file_out(data_file, std::ios::binary | std::ios::trunc);

    if (!file_out.is_open()) {
        std::cout << "Error al abrir el archivo" << std::endl;
        delete[] memory_block;
        return false;
    }

    file_out.write((char *)memory_block, rows);
    
    delete[] memory_block;
    file_out.close();
    
    return true;
}

bool validate_new_user(const std::string user_data, std::string& cedula)
{
    std::istringstream stream(user_data);
    std::string line;
    while (std::getline(stream, line)) {
        if (line.substr(0, line.find(',')) == cedula) {
            std::cout << "Error. El usuario ya existe.\n";
            return false;
        }
    }
    return true;
}

bool is_number(const std::string& str_number) 
{
    for (char c : str_number)
        if (!isdigit(c))
            return false;
    return true;
}

void consultar_saldo(std::string& file_string, std::string& user)
{
    std::string cedula = user.substr(0, user.find(','));
    std::string pass = user.substr(user.find(',') + 1, user.find_last_of(',') - user.find(',') - 1);
    uint32_t saldo = std::stoi(user.substr(user.find_last_of(',') + 1));

    if (saldo < 1000) {
        std::cout << "El saldo es menor a 1000. No se puede consultar\n";
    } else {
        saldo -= 1000;
        std::cout << "Saldo: " << saldo << std::endl;
    }

    std::string new_user = cedula + "," + pass + "," + std::to_string(saldo);
    file_string.replace(file_string.find(user), user.length(), new_user);
    write_data(USERS_FILE, cypher_1, SEMILLA, file_string);
    user = new_user;
    std::cout << "Saldo actualizado\n";
}

void retirar(std::string& file_string, std::string& user)
{
    std::string cedula = user.substr(0, user.find(','));
    std::string pass = user.substr(user.find(',') + 1, user.find_last_of(',') - user.find(',') - 1);
    int32_t saldo = std::stoi(user.substr(user.find_last_of(',') + 1));
    int32_t retiro;
    std::cout << "Ingrese monto a retirar: ";
    std::cin >> retiro;

    if (std::cin.fail()) {
        std::cin.clear();
        while (std::cin.get() != '\n');
        retiro = 0;
    }

    if (retiro <= 0) {
        std::cout << "Error. El monto a retirar debe ser mayor a 0.\n";
        return;
    }

    if (retiro > saldo) {
        std::cout << "Error. El monto a retirar es mayor al saldo.\n";
        return;
    }

    std::cout << "Retirado " << retiro << " de su cuenta" << std::endl;
    saldo -= retiro;
    std::string new_user = cedula + "," + pass + "," + std::to_string(saldo);
    file_string.replace(file_string.find(user), user.length(), new_user);
    write_data(USERS_FILE, cypher_1, SEMILLA, file_string);
    user = new_user;
    std::cout << "Saldo actualizado\n";
}

void app_user(std::string& file_string, std::string& user)
{
    std::cout << "Bienvenido al usuario\n";
    uint16_t opc;
    do {
        std::cout << "1. Consultar saldo\n2. Retirar\n3. Salir\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opc;
        if (std::cin.fail()) {
            std::cin.clear();
            while (std::cin.get() != '\n');
            opc = 0;
        }
        switch (opc) {
            case 1:
                std::cout << "Consultar saldo\n";
                consultar_saldo(file_string, user);
                break;
            case 2:
                std::cout << "Retirar\n";
                retirar(file_string, user);
                break;
            case 3:
                std::cout << "Salir\n";
                break;
            default:
                std::cout << "Opción no válida. Intente de nuevo.\n";
        }
    } while (opc != 3);
}

void app_administrador(std::string& users_file)
{
    std::cout << "Bienvenido al administrador\n";
    uint16_t opc;

    do {
        std::cout << "1. Crear usuario\n2. Salir\n";
        std::cout << "Seleccione una opción: ";
        std::cin >> opc;
        if (std::cin.fail()) {
            std::cin.clear();
            while (std::cin.get() != '\n');
            opc = 0;
        }
        switch (opc) {
            case 1:
                std::cout << "Crear usuario\n";
                if(crear_usuario(users_file))
                    std::cout << "Usuario creado exitosamente\n";
                else
                    std::cout << "Error al crear el usuario\n";
                break;
            case 2:
                std::cout << "Salir\n";
                break;
            default:
                std::cout << "Opción no válida. Intente de nuevo.\n";
        }
    } while (opc != 2);
}