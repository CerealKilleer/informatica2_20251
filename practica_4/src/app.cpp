#include <iostream>
#include <fstream>
#include <memory>
#include <limits>
#include "network.hpp"
#include "app.hpp"

constexpr uint8_t num_digis_opc = 4;
constexpr uint8_t zero = 0;
constexpr uint8_t num_digis_cost = 10;
constexpr uint8_t min_cost = 0;
#define LOG_ERROR(fn, msg) std::cerr << "[App/" << fn << "]: " << msg << std::endl

void main_app(const std::string &file_path)
{
    auto net = std::make_unique<Network>();

    if (create_network(file_path, *net))
        app(*net);
}

void app(Network &net)
{
    std::string str_opc;
    uint8_t opc;

    do {
        std::cout << "1. Agregar Router\n2. Eliminar Router\n3. Agregar enlace\n" 
        << "4. Actualizar enlace\n5. Eliminar enlace\n6. Consultar tabla de enrutamiento\n" <<
        "7. Consultar costo paquete\n8. Consultar camino mas corto\n9. Salir" << std::endl;
        std::cin >> str_opc;
        opc = get_opc(str_opc);
        switch (opc) {
            case 1:
                add_router(net);
                break;
            case 2:
                remove_router(net);
                break;
            case 3:
                add_link(net);
                break;
            case 4:
                update_link(net);
                break;
            case 5:
                delete_link(net);
                break;
            case 6:
                consult_routing_table(net);
                break;
            case 7:
                consult_package_cost(net);
                break;
            case 8:
                consult_shortest_route(net);
                break;
            case 9:
                std::cout << "Adiós" << std::endl;
                break;
            default:
                std::cout << "Opción no válida" << std::endl;
                break;
        }
    } while (opc != 9);
}

bool get_link(std::string &r1, std::string &r2, int32_t &cost)
{
    std::string str_cost;
    std::cout << "Ingrese los routers a enlazar" << std::endl;

    if (!get_router_id(r1))
        return false;
    if (!get_router_id(r2))
        return false;
    
    std::cout << "Costo del enlace: ";
    std::cin >> str_cost;

    cost = get_cost(str_cost);
    return true;
}

void consult_shortest_route(Network &net)
{
    std::string router_id_1, router_id_2;
    
    std::cout << "Ingrese los routers de inicio y finalizacion." << std::endl;

    if (!get_router_id(router_id_1))
        return;
    if (!get_router_id(router_id_2))
        return;

    net.calculate_min_path(router_id_1, router_id_2);
}

void consult_package_cost(Network &net)
{
    std::string router_id_1, router_id_2;
    
    std::cout << "Ingrese los routers de inicio y finalizacion." << std::endl;

    if (!get_router_id(router_id_1))
        return;
    if (!get_router_id(router_id_2))
        return;

    int32_t cost = net.calculate_cost(router_id_1, router_id_2);
    if (cost < min_cost)
        return;
    std::cout << "Enviar un paquete desde " << router_id_1 << " a " 
              << router_id_2 << " cuesta: " << cost << std::endl; 
}

void consult_routing_table(Network &net)
{
    std::cout << "Router ID a consultar" << std::endl;
    std::string router_id;
    if (!get_router_id(router_id))
        return;
    net.show_routing_table(router_id);
}

void delete_link(Network &net)
{
    std::string router_id_1, router_id_2;
    
    std::cout << "Ingrese los enlaces a eliminar" << std::endl;

    if (!get_router_id(router_id_1))
        return;
    if (!get_router_id(router_id_2))
        return;

    net.remove_link_router(router_id_1, router_id_2);
}

void update_link(Network &net)
{
    std::string router_id_1, router_id_2;
    int32_t cost;
    if (!get_link(router_id_1, router_id_2, cost))
        return;
    net.update_link_router(router_id_1, router_id_2, cost);
}

void add_link(Network &net)
{   
    std::string router_id_1, router_id_2;
    int32_t cost;
    if (!get_link(router_id_1, router_id_2, cost))
        return;
    net.connect_router(router_id_1, router_id_2, cost);
}

void remove_router(Network &net)
{
    std::string router_id;
    if (!get_router_id(router_id))
        return;
    net.remove_network_router(router_id);
}

void add_router(Network &net)
{
    std::string router_id;
    if (!get_router_id(router_id))
        return;
    net.add_network_router(router_id);
}

bool get_router_id(std::string &router_id)
{
    std::cout << "ID del router: ";
    std::cin >> router_id;
    if (router_id.length() > 8) {
        LOG_ERROR("get_router_id", "ID del router demasiado grande > 8 caracteres");
        return false;
    }

    if (router_id.empty()) {
        LOG_ERROR("get_router_id", "ID del router NULA");
        return false;
    }
    return true;
}

uint32_t get_cost(std::string &str_cost)
{
    int64_t number;

    if (str_cost.length() > num_digis_cost)
        return zero;
    
    try {
        number = std::stoll(str_cost);
    } catch (std::invalid_argument &e) {
        return 0;
    } 

    if (number < INT32_MIN || number > INT32_MAX)
        return zero;

    return number;
}

uint8_t get_opc(std::string &str_opc)
{
    int16_t number;

    if (str_opc.length() > num_digis_opc)
        return zero;
    
    try {
        number = std::stoi(str_opc);
    } catch (const std::invalid_argument &e) {
        return 0;
    }
    
    if (number < zero || number > UINT8_MAX)
        return zero;

    return number;
}

bool create_network(const std::string &file_path, Network &net)
{
    std::string r1, r2;
    int32_t cost;

    std::ifstream archivo(file_path);
    if (!archivo.is_open()) {
        std::cerr << "[create_network]: No se pudo abrir el archivo " << file_path << std::endl;
        return false;
    }

    while (archivo >> r1) {
        if (r1 == "-")
            break;
        if (!net.add_network_router(r1)) {
            archivo.close();
            return false;
        }
            
    }

    while (archivo >> r1 >> r2 >> cost) {
        if(!net.connect_router(r1, r2, cost)) {
            archivo.close();
            return false;
        }
    }

    archivo.close();

    return true;
}