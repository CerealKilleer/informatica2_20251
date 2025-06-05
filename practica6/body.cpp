#include "body.h"

Body::Body(float x0, float y0, float vx0, float vy0, float mass, float radius)
    : m_pos{x0, y0}, m_vel{vx0, vy0}, m_mass(mass), m_radius(radius)
{}

void Body::set_pos(struct Vec_2D &pos) {
    m_pos = pos;
}

void Body::set_vel(struct Vec_2D &vel) {
    m_vel = vel;
}

void Body::set_acc(struct Vec_2D &acc) {
    m_acc = acc;
}

struct Vec_2D Body::get_pos(void) const {
    return m_pos;
}

struct Vec_2D Body::get_vel(void) const {
    return m_vel;
}

struct Vec_2D Body::get_acc(void) const {
    return m_acc;
}

float Body::get_mass(void) const {
    return m_mass;
}

float Body::get_radius(void) const {
    return m_radius;
}
