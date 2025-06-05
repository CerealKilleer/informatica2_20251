#ifndef SYSTEM_WIDGET_H
#define SYSTEM_WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QTimer>
#include <vector>


#include "system.h"
#include "body_item.h"

constexpr int range = 8000;

class System_Widget : public QWidget {
    Q_OBJECT

public:
    explicit System_Widget(QWidget* parent = nullptr);

private slots:
    void on_update();
    void draw_ticks(float scale_factor, int tick_length);

private:
    QGraphicsScene* scene;
    QGraphicsView* view;
    System m_system;
    std::vector<body_item*> m_body_items;
    QTimer* timer;
    float m_scale_factor = 0.055;
};

#endif


