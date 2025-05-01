#ifndef __ROUTER_HPP__
#define __ROUTER_HPP__
#include <iostream>
#include <string>
#include <unordered_map>
#include <stdint.h>

class Router 
{
private:
    std::string m_id;
    std::unordered_map<std::string, int> neighbors;
    bool link_exists(const std::string &neigh_id);

public:
    Router(const std::string &id);
    bool add_link(const std::string &id_neigh, int32_t cost);
    bool update_link(const std::string &id_neigh, int32_t cost);
    void show_neighbors(void);
    bool remove_link(const std::string &id_neigh);
};
#endif