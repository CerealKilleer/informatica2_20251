#ifndef SYSTEM_H
#define SYSTEM_H
#include <vector>
#include "body.h"

class System {
public:
    System(float g, const char *bodies_file);
    const std::vector<std::shared_ptr<Body>> get_bodies(void) const;
    void update(float dt);

private:
    float m_G;
    std::vector<std::shared_ptr<Body>> m_bodies;
    void create_bodies(const char *bodies_file);
};

#endif
