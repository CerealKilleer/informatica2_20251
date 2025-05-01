#include <iostream>
#include "network.hpp"

int main(void)
{
    Network red;
    red.add_network_router("a");
    red.add_network_router("b");
    red.add_network_router("c");
    red.add_network_router("d");
    red.connect_router("a", "b", 4);
    red.connect_router("b", "d", 1);
    red.connect_router("d", "c", 2);
    red.connect_router("c", "a", 10);
    red.show_connections();
    red.update_link_router("b", "d", 16);
    red.update_link_router("a", "d", 3);
    red.show_connections();
    red.remove_link_router("a", "c");
    red.show_connections();
    return 0;
}