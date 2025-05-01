#include "network.hpp"

bool Network::router_exists(const std::string &router_id)
{
    return routers.count(router_id) > 0;
}

void Network::show_connections(void)
{
    for (const auto &[router_id, router] : routers) {
        router->show_neighbors();
    }
}

bool Network::add_network_router(const std::string &router_id)
{
    if (router_exists(router_id)) {
        std::cerr << "[Network/add_network_router]: Router: " << router_id << " ya existe" << std::endl;
        return false;
    }
    routers[router_id] = std::make_shared<Router>(router_id);
    return true;
}

bool Network::connect_router(const std::string &router_1_id, 
                            const std::string &router_2_id, 
                            int32_t cost)
{
    if (!router_exists(router_1_id) || !router_exists(router_2_id)) {
        std::cerr << "[Network/connect_router]: Ambos routers deben existir para conectarse" << std::endl;
        return false;
    }

    if (cost < 1) {
        std::cerr << "[Network/connect_router]: El costo del enlace debe ser positivo" << std::endl;
        return false;
    }

    if(!routers[router_1_id]->add_link(router_2_id, cost))
        return false;

    if(!routers[router_2_id]->add_link(router_1_id, cost))
        return false;

    std::cout << "[Network/connect_router]: Enlace establecido" << std::endl;
    return true;
}

bool Network::update_link_router(const std::string &router_1_id, 
                            const std::string &router_2_id, 
                            int32_t cost)
{
    if (!router_exists(router_1_id) || !router_exists(router_2_id)) {
        std::cerr << "[Network/connect_router]: Ambos routers deben existir para actualizarse" << std::endl;
        return false;
    }

    if (cost < 1) {
        std::cerr << "[Network/connect_router]: El costo del enlace debe ser positivo" << std::endl;
        return false;
    }

    if(!routers[router_1_id]->update_link(router_2_id, cost))
        return false;

    if(!routers[router_2_id]->update_link(router_1_id, cost));
        return false;

    std::cout << "[Network/connect_router]: Enlace actualizado" << std::endl;
    return true;
}

bool Network::remove_link_router(const std::string &router_1_id, 
                                const std::string &router_2_id)
{
    if (!router_exists(router_1_id) || !router_exists(router_2_id)) {
        std::cerr << "[Network/connect_router]: Ambos routers deben existir para actualizarse" << std::endl;
        return false;
    }

    if(!routers[router_1_id]->remove_link(router_2_id))
        return false;

    if(!routers[router_2_id]->remove_link(router_1_id));
        return false;

    std::cout << "[Network/connect_router]: Enlace eliminado" << std::endl;
    return true;
}