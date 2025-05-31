#include <QKeyEvent>
#include "game_widget.h"
#include "pacman.h"
#include "constants.h"
#include <stdio.h>

game_widget::game_widget(QWidget *parent)
    : QWidget{parent}, map(map_data), score(0), actual_direction(Pacman::none)
{
    setFocusPolicy(Qt::StrongFocus);
    setFixedSize(map_width * cell_size, map_height * cell_size);
    cookie = QPixmap(":items/img/items/dot.png");
    power_cookie = QPixmap(":items/img/items/pellet.png");
    build_map_cached();
    connect(&move_timer, &QTimer::timeout, this, &game_widget::move_callback);
    move_timer.start(120);
}

void game_widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawPixmap(0,0, cached_map);
    pacman.draw(painter, cell_size);
    painter.setPen(Qt::white);
    painter.setFont(QFont("Liberation Sans", 14));
    painter.drawText(10, height() - 10, QString("Puntos: %1").arg(score));
}

void game_widget::update_score(int32_t x, int32_t y)
{
    switch (map[y][x]) {
    case 2:
        map[y][x] = 0;
        build_map_cached();
        score += 10;
        break;
    case 3:
        map[y][x] = 0;
        build_map_cached();
        score += 50;
        break;
    }
}

void game_widget::move_callback()
{
    int32_t x = pacman.position().rx();
    int32_t y = pacman.position().ry();

    switch(actual_direction) {
    case (Pacman::up):
        y--;
        break;
    case (Pacman::down):
        y++;
        break;
    case (Pacman::left):
        x--;
        break;
    case (Pacman::right):
        x++;
        break;
    }

    if (can_move_to(x, y)) {
        pacman.move(actual_direction);
        update_score(x,y);
        update();
    }

    pacman.update_animation();
}

void game_widget::keyPressEvent(QKeyEvent *event)
{

    switch (event->key()) {
    case Qt::Key_Up:
        actual_direction = Pacman::up;
        break;
    case Qt::Key_Down:
        actual_direction = Pacman::down;
        break;
    case Qt::Key_Left:
        actual_direction = Pacman::left;
        break;
    case Qt::Key_Right:
        actual_direction = Pacman::right;
        break;
    default:
        QWidget::keyPressEvent(event);
        return;
    }
}

QSize game_widget::sizeHint() const
{
    return QSize(400,500);
}

bool game_widget::can_move_to(int x, int y) const {
    if (x < 0 || y < 0)
        return false;

    if (x > map_width || y > map_height)
        return false;

    if (map[y][x] == 1)
        return false;

    return true;
}

void game_widget::build_map_cached(void) {
    cached_map = QPixmap(width(), height());
    cached_map.fill(Qt::black);
    QPainter p(&cached_map);

    for (int y = 0; y < map.size(); y++) {
        for (int x = 0; x < map[y].size(); x++) {
            QRect cell(x * cell_size, y * cell_size, cell_size, cell_size);
            switch (map[y][x]) {
            case 1: // muro
                p.setBrush(Qt::blue);
                p.setPen(Qt::NoPen);
                p.drawRect(cell);
                break;
            case 2: // frutita
                p.drawPixmap(cell.topLeft(), cookie.scaled(cell_size, cell_size, Qt::KeepAspectRatio, Qt::SmoothTransformation));
                break;
            case 3: // frutita de poder
                p.drawPixmap(cell.topLeft(), power_cookie.scaled(cell_size, cell_size, Qt::KeepAspectRatio, Qt::SmoothTransformation));
                break;
            }
        }
    }
}
