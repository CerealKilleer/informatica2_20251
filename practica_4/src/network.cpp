#include "network.hpp"
#define LOG_ERROR(fn, msg) std::cerr << "[Network/" << fn << "]: " << msg << std::endl
#define LOG_SUCESS(fn, msg) std::cout << "[Network/" << fn << "]: " << msg << std::endl

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
        LOG_ERROR("add_network_router", "Router: " + router_id + " ya existe");
        return false;
    }
    routers[router_id] = std::make_unique<Router>(router_id);
    calculate_all_routing_tables();
    LOG_SUCESS("add_network_router", "Router: " + router_id + " - Creado");
    return true;
}

bool Network::remove_network_router(const std::string &router_id)
{
    std::vector<std::string> to_delete;
    if (!router_exists(router_id)) {
        LOG_ERROR("remove_network_router", "Router: " + router_id + " - No existe");
        return false;
    }

    for (auto &[id_neigh, _] : routers[router_id]->get_neighbors())
        to_delete.push_back(id_neigh);

    for (auto &id_neigh : to_delete)
        remove_link_router(router_id, id_neigh);

    LOG_SUCESS("remove_network_router", "Router: " + router_id + " eliminado");
    routers.erase(router_id);
    calculate_all_routing_tables();

    return true;
}

bool Network::connect_router(const std::string &router_1_id, 
                            const std::string &router_2_id, 
                            int32_t cost)
{
    if (!router_exists(router_1_id) || !router_exists(router_2_id)) {
        LOG_ERROR("connect_router", "Ambos routers deben existir para conectarse");
        return false;
    }

    if (cost < 1) {
        LOG_ERROR("connect_router", "El costo del enlace debe ser positivo");
        return false;
    }

    if(!routers[router_1_id]->add_link(router_2_id, cost))
        return false;

    if(!routers[router_2_id]->add_link(router_1_id, cost))
        return false;

    calculate_all_routing_tables();
    LOG_SUCESS("connect_router", "Enlace establecido");
    return true;
}

bool Network::update_link_router(const std::string &router_1_id, 
                            const std::string &router_2_id, 
                            int32_t cost)
{
    if (!router_exists(router_1_id) || !router_exists(router_2_id)) {
        LOG_ERROR("update_link_router", "Ambos routers deben existir para actualizarse");
        return false;
    }

    if (cost < 1) {
        LOG_ERROR("update_link_router", "El nuevo costo del enlace debe ser positivo");
        return false;
    }

    if(!routers[router_1_id]->update_link(router_2_id, cost))
        return false;

    if(!routers[router_2_id]->update_link(router_1_id, cost))
        return false;

    calculate_all_routing_tables();
    LOG_SUCESS("update_link_router", "Enlace actualizado");
    return true;
}

bool Network::remove_link_router(const std::string &router_1_id, 
                                const std::string &router_2_id)
{
    if (!router_exists(router_1_id) || !router_exists(router_2_id)) {
        LOG_ERROR("remove_link_router", "Ambos routers deben existir para eliminar el enlace");
        return false;
    }

    if(!routers[router_1_id]->remove_link(router_2_id))
        return false;

    if(!routers[router_2_id]->remove_link(router_1_id))
        return false;

    calculate_all_routing_tables();
    LOG_SUCESS("remove_link_router", "Enlace eliminado");
    return true;
}

std::vector<std::string> Network::find_shortest_path(const std::string &start, 
                                                    const std::string &end,
                                                    std::unordered_map<std::string, int> &distance)
{
    //Definición de cola de prioridad
    using queue_entry = std::pair<int, std::string>; //Le doy un alias :)
    //Creo una cola de prioridad de elementos tipo queue_entry, almacenados en un vector
    //y que en el top siempre esté la menor distancia
    std::priority_queue<queue_entry, std::vector<queue_entry>, std::greater<queue_entry>> queue;
    
    //Limpiemos todas las distancias del router
    distance.clear();

    //Y mantener el último router visitado
    std::unordered_map<std::string, std::string> previous;

    //Para mantener el path
    std::vector<std::string> path;

    // Todas las distancias se inicializan "infinitas"
    for (const auto& [id, _] : routers) {
        distance[id] = INT32_MAX;
    }

    //Excepto la primera que es nula :)
    distance[start] = 0;
    //El primer router a evaluar es el inicio
    queue.push({0, start});
    
    while (!queue.empty()) {
        //Mientras existan routers en el camino habrá que seguir buscando cuál da la mejor distancia 
        auto [dist, current] = queue.top();
        queue.pop();

        //Ahora hay que evaluar tooodos los vecinos del router actual y ver cuál es la mejor distancia a los vecinos

        for (const auto &[neighbor, cost] : routers[current]->get_neighbors()) {
            uint32_t new_dist = dist + cost;
            //Si la nueva distancia desde el router mejora la distancia actual hasta el vecino
            if (new_dist < distance[neighbor]) {
                distance[neighbor] = new_dist;
                previous[neighbor] = current;
                queue.push({new_dist, neighbor});
                //Ahora está actualizada la nueva menor distancia hasta el vecino actual
            }
        }
    }

    for (std::string at=end; at != ""; at = previous[at]) {
        path.push_back(at);
        if (at == start)
            break;
    }

    if (path.back() != start)
        return {};

    std::reverse(path.begin(), path.end());
    return path;
}

void Network::calculate_all_routing_tables(void)
{
    for (auto &[router_id, router] : routers) {
        find_shortest_path(router_id, router_id, router->get_routing_table());
    }
}

bool Network::show_routing_table(const std::string &router_id)
{
    if (!router_exists(router_id)) {
        LOG_ERROR("show_routing_table", "No existe el router" + router_id);
        return false;
    }

    routers[router_id]->show_routing_table();
    return true;
}

bool Network::calculate_min_path(const std::string &start, const std::string &end)
{
    if (!router_exists(start) || !router_exists(end)) {
        LOG_ERROR("calculate_min_path", "Ambos routers deben existir");
        return false;
    }

    std::vector<std::string> path;
    path = find_shortest_path(start, end, routers[start]->get_routing_table());
    
    if (path.empty()) {
        LOG_ERROR("calculate_min_path", "No hay camino entre: " + start + " y " + end);
        return false;
    }

    for (auto router_id : path) {
        std::cout << "->" << router_id;
    }

    std::cout << std::endl;
    return true;
}

int32_t Network::calculate_cost(const std::string &start, const std::string &end)
{
    if (!router_exists(start) || !router_exists(end)) {
        LOG_ERROR("calculate_cost", "Ambos routers deben existir");
        return -1;
    }

    return (routers[start]->get_routing_table())[end];
}