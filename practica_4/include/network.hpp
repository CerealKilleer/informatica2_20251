#ifndef __NETWORK_HPP__
#define __NETWORK_HPP__
#include <iostream>
#include <unordered_map>
#include <memory>
#include <string>
#include <stdint.h>
#include "router.hpp"

class Network
{
    private:
        std::unordered_map<std::string, std::shared_ptr<Router>> routers;
        bool router_exists(const std::string &router_id);
    
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
};
#endif