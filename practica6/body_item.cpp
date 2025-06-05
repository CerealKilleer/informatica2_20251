#include "body_item.h"

body_item::body_item(Body* body, QColor color, QGraphicsItem* parent)
    : QGraphicsEllipseItem(parent), m_body(body)
{
    setRect(-fixed_size/2, -fixed_size/2, fixed_size, fixed_size);

    setBrush(QBrush(color));
    setPen(Qt::NoPen);

    Vec_2D pos = m_body->get_pos();
    setPos(pos.x, pos.y);
}


void body_item::update_position(float scale_factor)
{
    Vec_2D pos = m_body->get_pos();
    setPos(pos.x * scale_factor, pos.y * scale_factor);
}

