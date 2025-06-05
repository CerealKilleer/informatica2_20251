#ifndef BODY_ITEM_H
#define BODY_ITEM_H

#include <QGraphicsEllipseItem>
#include <QBrush>
#include <QPen>
#include "body.h"
constexpr float fixed_size = 12.0f;

class body_item : public QGraphicsEllipseItem {
public:
    body_item(Body* body, QColor color, QGraphicsItem* parent = nullptr);

    void update_position(float scale_factor);

private:
    Body* m_body;
};

#endif


