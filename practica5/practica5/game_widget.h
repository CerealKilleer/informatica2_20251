#ifndef GAME_WIDGET_H
#define GAME_WIDGET_H

#include <QWidget>
#include <QTimer>
#include <QPoint>
#include "pacman.h"
#include "map.h"

class game_widget : public QWidget
{
    Q_OBJECT
public:
    explicit game_widget(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    QSize sizeHint() const override;

private:
    QTimer move_timer;
    Pacman pacman;
    QVector<QVector<int>> map;
    QPixmap cookie;
    QPixmap power_cookie;
    int16_t score;
    QPixmap cached_map;
    Pacman::Direction actual_direction;
    void build_map_cached(void);
    bool can_move_to(int x, int y) const;
    void update_score(int32_t x, int32_t y);
    void move_callback();

signals:
};

#endif // GAME_WIDGET_H
