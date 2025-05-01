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

