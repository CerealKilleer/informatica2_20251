#include <iostream>
#include "network.hpp"

int main(void)
{
    Network red;
    /*
    red.add_network_router("a");
    red.add_network_router("b");
    red.add_network_router("c");
    red.add_network_router("d");
    red.add_network_router("e");
    red.connect_router("b", "a", 1);
    red.connect_router("a", "c", 2);
    red.connect_router("a", "d", 3);
    red.connect_router("a", "e", 4);

    red.show_routing_table("b");
    */
    red.add_network_router("a");
    red.add_network_router("b");
    red.add_network_router("c");
    red.add_network_router("d");

    red.connect_router("a", "b", 1);
    red.connect_router("c", "d", 2);

    red.show_routing_table("a");
    red.calculate_min_path("a", "c");
    std::cout << "Costo: " << red.calculate_cost("a", "c") << std::endl;
    return 0;
}