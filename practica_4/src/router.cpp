#include <iostream>
#include <string>
#include <stdint.h>
#include "router.hpp"

Router::Router(const std::string &id) 
        : m_id(id) 
{}

bool Router::link_exists(const std::string &neigh_id)
{
    return neighbors.count(neigh_id) > 0; 
}

bool Router::add_link(const std::string &id_neigh, int32_t cost) 
{
    if (cost < 1) {
        return false;
    }
    neighbors[id_neigh] = cost;
    std::cout << "[Router/add_link]: " << m_id << " -> " << id_neigh << " costo: " << cost << std::endl;
    return true;
}

bool Router::update_link(const std::string &id_neigh, int32_t cost)
{
    if (cost < 1) {
        std::cout << "[Router/update_link]: El nuevo costo no puede ser negativo";
        return false;
    }
    if (!link_exists(id_neigh)) {
        std::cout << "[Router/update_link]:" << m_id << "->" << id_neigh << ". No existe" << std::endl;
        return false;
    }
    neighbors[id_neigh] = cost;
    std::cout << "[Router/update_link]: " 
                    << m_id << " -> " << id_neigh << " costo: " << cost << std::endl;
    return true;
}

bool Router::remove_link(const std::string &id_neigh)
{
    if (!link_exists(id_neigh)) {
        std::cout << "[Router/update_link]:" << m_id << "->" << id_neigh << ". No existe" << std::endl;
        return false;
    }

    neighbors.erase(id_neigh);
    std::cout << "[Router/update_link]:" << m_id << "->" << id_neigh << ". Eliminado" << std::endl;
    return true;
}

void Router::show_neighbors(void)
{
    for (const auto&[id_neigh, cost] : neighbors) {
        std::cout << "[Router]: " << m_id << " -> " << id_neigh << " Costo: " << cost << std::endl; 
    }
}

const std::unordered_map<std::string, int> &Router::get_neighbors(void)
{
    return neighbors;
}

std::unordered_map<std::string, int> &Router::get_routing_table(void)
{
    return basic_routing_table;
}

const void Router::show_routing_table(void)
{
    std::vector<std::pair<std::string, int>> table (
        basic_routing_table.begin(),
        basic_routing_table.end()
    );

    std::sort(table.begin(), table.end());

    // Encabezado de la tabla
    std::cout << "+---------------------+---------------------+" << std::endl;
    std::cout << "| " << std::left << std::setw(20) << "Router ID" 
              << "| " << std::setw(20) << "Distancia" << "|" << std::endl;
    std::cout << "+---------------------+---------------------+" << std::endl;

    // Filas de datos
    for (const auto& [router_id, distance] : table) {
        if (distance == INT32_MAX)
            continue;
        std::cout << "| " << std::left << std::setw(20) << router_id 
                  << "| " << std::setw(20) << distance << "|" << std::endl;
    }

    // Pie de tabla
    std::cout << "+---------------------+---------------------+" << std::endl;
}