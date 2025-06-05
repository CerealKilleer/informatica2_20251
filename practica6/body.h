#ifndef BODY_H
#define BODY_H

struct Vec_2D {
    float x;
    float y;
};

class Body {
public:
    Body(float x0, float y0, float vx0, float vy0, float mass, float radius);
    void set_pos(struct Vec_2D &pos);
    void set_vel(struct Vec_2D &vel);
    void set_acc(struct Vec_2D &acc);
    struct Vec_2D get_pos(void) const;
    struct Vec_2D get_vel(void) const;
    struct Vec_2D get_acc(void) const;
    float get_mass(void) const;
    float get_radius(void) const;

private:
    struct Vec_2D m_pos;
    struct Vec_2D m_vel;
    struct Vec_2D m_acc;
    float m_mass;
    float m_radius;
};

#endif // BODY_H
