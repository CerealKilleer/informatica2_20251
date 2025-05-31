#include "pacman.h"
#include "constants.h"

Pacman::Pacman()
{
    pos = QPoint(1,1);
    direction = right;
    current_frame = 0;

    sprites.append(QPixmap(":/sprites/img/pacman/0.png"));
    sprites.append(QPixmap(":/sprites/img/pacman/1.png"));
    sprites.append(QPixmap(":/sprites/img/pacman/2.png"));
}

void Pacman::update_animation() {
    current_frame = (current_frame + 1) % sprites.size();
}

void Pacman::draw(QPainter &painter, int cell_size) {
    int x = pos.x() * cell_size;
    int y = pos.y() * cell_size;

    QPixmap sprite = sprites[current_frame];
    sprite = sprite.scaled(cell_size, cell_size, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    // Para girar el sprite según la dirección
    QTransform transform;
    switch(direction) {
    case up:
        transform.rotate(-90);
        break;
    case down:
        transform.rotate(90);
        break;
    case left:
        transform.rotate(180);
        break;
    case right:
        break;
    default:
        break;
    }
    sprite = sprite.transformed(transform);

    painter.drawPixmap(x, y, sprite);
}



void Pacman::move(Direction dir) {
    direction = dir;
    switch (dir) {
    case (up):
        pos.ry()--;
        break;
    case (down):
        pos.ry()++;
        break;
    case (left):
        pos.rx()--;
        break;
    case (right):
        pos.rx()++;
        break;
    }
}

QPoint Pacman::position() const {
    return pos;
}
