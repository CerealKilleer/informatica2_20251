#include "system_widget.h"
#include "system.h"
#include <QVBoxLayout>
#include <QGraphicsEllipseItem>

System_Widget::System_Widget(QWidget* parent)
    : QWidget(parent), m_system(1, "/bodies/bodies.txt")
{
    setFixedSize(960, 1080);

    scene = new QGraphicsScene(this);
    scene->setSceneRect(-8000, -8000, 20000, 20000);
    scene->setBackgroundBrush(Qt::white);

    view = new QGraphicsView(scene, this);
    view->setRenderHint(QPainter::Antialiasing);
    view->setBackgroundBrush(Qt::white);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->scale(1, -1);
    view->centerOn(0, 0);
    view->setFrameStyle(QFrame::NoFrame);

    QPen axis_pen(Qt::black);
    axis_pen.setWidth(1);
    scene->addLine(-scene->width()/2, 0, scene->width()/2, 0, axis_pen);
    scene->addLine(0, -scene->height()/2, 0, scene->height()/2, axis_pen);
    draw_ticks(m_scale_factor, 10);

    auto* layout = new QVBoxLayout(this);
    layout->addWidget(view);
    setLayout(layout);

    QVector<QColor> colors = { Qt::blue, Qt::red, Qt::green, Qt::yellow, Qt::magenta, Qt::cyan };

    int color_index = 0;
    for (auto& body : m_system.get_bodies()) {
        QColor color = colors[color_index % colors.size()];
        body_item* item = new body_item(body.get(), color);
        item->update_position(m_scale_factor);
        scene->addItem(item);
        m_body_items.push_back(item);
        color_index++;
    }

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &System_Widget::on_update);
    timer->start(16);
}

void System_Widget::on_update() {

    m_system.update(1);
    for (body_item* item : m_body_items) {
        item->update_position(m_scale_factor);
    }
}

void System_Widget::draw_ticks(float scale_factor, int tick_length) {
    QPen tick_pen(Qt::black);
    tick_pen.setWidth(1);

    QFont font;
    font.setPointSize(8);

    for (int y = -8000; y <= 12000; y += 1000) {
        if (y == 0)
            continue;
        QTransform transform;
        transform.scale(1, -1);
        double y_scaled = y * scale_factor;
        scene->addLine(-tick_length/2.0, y_scaled, tick_length/2.0, y_scaled, tick_pen);

        QGraphicsTextItem* text = scene->addText(QString::number(y), font);
        text->setDefaultTextColor(Qt::black);
        text->setTransform(transform);
        text->setPos(-tick_length - text->boundingRect().width(), y_scaled - text->boundingRect().height()/2);
    }

    for (int x = -8000; x <= 12000; x += 1000) {
        if (x == 0)
            continue;
        QTransform transform;
        transform.scale(1, -1);
        double x_scaled = x * scale_factor;
        scene->addLine(x_scaled, -tick_length/2.0, x_scaled, tick_length/2.0, tick_pen);

        QGraphicsTextItem* text = scene->addText(QString::number(x), font);
        text->setDefaultTextColor(Qt::black);
        text->setTransform(transform);
        text->setPos(x_scaled - text->boundingRect().width()/2, tick_length/2.0);
    }
}
