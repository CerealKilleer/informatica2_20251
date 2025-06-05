#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <memory>
#include "system.h"

System::System(float g, const char *bodies_file)
    : m_G(g)
{
    create_bodies(bodies_file);
}

const std::vector<std::shared_ptr<Body>> System::get_bodies(void) const {
    return m_bodies;
}

void System::create_bodies(const char *bodies_file)
{
    QString resourcePath = QString(":/") + QString(bodies_file);
    QFile qfile(resourcePath);

    if (!qfile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "No se pudo abrir el archivo de bodies en resources:" << resourcePath;
        return;
    }

    QTextStream in(&qfile);

    while (!in.atEnd()) {
        float x, y, vx, vy, mass, radius;

        in >> x >> y >> mass >> radius >> vx >> vy;

        if (in.status() != QTextStream::Ok) {
            qWarning() << "Error leyendo datos, posible archivo mal formateado.";
            break;
        }

        auto new_body = std::make_shared<Body>(x, y, vx, vy, mass, radius);
        m_bodies.push_back(new_body);
    }

    qfile.close();
}

void System::update(float dt) {
    size_t n = m_bodies.size();
    std::vector<Vec_2D> accelerations(n, {0.0f, 0.0f});

    for (size_t i = 0; i < n; ++i) {
        Vec_2D pos_i = m_bodies[i]->get_pos();

        Vec_2D acc_i = {0.0f, 0.0f};

        for (size_t j = 0; j < n; ++j) {
            if (i == j)
                continue;

            Vec_2D pos_j = m_bodies[j]->get_pos();

            float mass_j = m_bodies[j]->get_mass();
            float dx = pos_j.x - pos_i.x;
            float dy = pos_j.y - pos_i.y;
            float dist_sq = dx * dx + dy * dy;
            float dist = std::sqrt(dist_sq);

            float force_mag = m_G * mass_j / dist_sq;

            acc_i.x += force_mag * dx / dist;
            acc_i.y += force_mag * dy / dist;
        }

        accelerations[i] = acc_i;
    }

    for (size_t i = 0; i < n; ++i) {
        Body* body = m_bodies[i].get();
        Vec_2D vel = body->get_vel();
        Vec_2D pos = body->get_pos();
        Vec_2D acc = accelerations[i];

        Vec_2D new_vel = {
            vel.x + acc.x * dt,
            vel.y + acc.y * dt
        };

        Vec_2D new_pos = {
            pos.x + new_vel.x * dt,
            pos.y + new_vel.y * dt
        };

        body->set_vel(new_vel);
        body->set_pos(new_pos);
        body->set_acc(acc);
    }
}


