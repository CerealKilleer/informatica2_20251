#ifndef __APP_H__
#define __APP_H__
#include "network.hpp"
#include "string"
bool create_network(const std::string &file_path, Network &net);
void app(Network &net);
uint8_t get_opc(std::string &str_opc);
void add_router(Network &net);
bool get_router_id(std::string &router_id);
void remove_router(Network &net);
uint32_t get_cost(std::string &str_opc);
bool get_link(std::string &r1, std::string &r2, int32_t &cost);
void add_link(Network &net);
void update_link(Network &net);
void delete_link(Network &net);
void consult_routing_table(Network &net);
void consult_package_cost(Network &net);
void consult_shortest_route(Network &net);
void main_app(const std::string &file_path);
#endif