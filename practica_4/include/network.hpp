#ifndef __NETWORK_HPP__
#define __NETWORK_HPP__
#include <iostream>
#include <unordered_map>
#include <map>
#include <memory>
#include <string>
#include <stdint.h>
#include <vector>
#include <set>
#include <queue>
#include <limits>
#include <algorithm>
#include "router.hpp"

class Network
{
    private:
        std::unordered_map<std::string, std::unique_ptr<Router>> routers;
        bool router_exists(const std::string &router_id);
        std::vector<std::string> find_shortest_path(const std::string& start, 
                                                    const std::string& end,
                                                    std::unordered_map<std::string, int> &distance);
    
    public:
        bool add_network_router(const std::string &router_id);
        bool connect_router(const std::string &router_1_id, 
                            const std::string &router_2_id, int32_t cost);
        bool update_link_router(const std::string &router_1_id, 
                            const std::string &router_2_id, 
                            int32_t cost);
        bool remove_link_router(const std::string &router_1_id, 
                            const std::string &router_2_id);
        void show_connections(void);
        void calculate_all_routing_tables(void);
        bool show_routing_table(const std::string &router_id);
        bool calculate_min_path(const std::string &router_id_1, 
            const std::string &router_id_2);
        int32_t calculate_cost(const std::string &start, 
                                        const std::string &end);
        bool remove_network_router(const std::string &router_id);
};
#endif