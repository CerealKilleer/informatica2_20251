#ifndef PACMAN_H
#define PACMAN_H

#include <QPoint>
#include <QPainter>
#include <stdint.h>

class Pacman {
public:
    enum Direction {up, down, left, right, none};
    Pacman();
    void draw(QPainter &p, int32_t cell_size);
    void move(Direction dir);
    QPoint position() const;
    void update_animation();

private:
    QPoint pos;
    Direction direction;
    QVector<QPixmap> sprites;
    int32_t current_frame;
};

#endif
