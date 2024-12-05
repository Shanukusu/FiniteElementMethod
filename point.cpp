#include "point.h"

Point::Point(int x, int y) : QGraphicsEllipseItem(x, y, CIRCLE_RADIUS, CIRCLE_RADIUS)
{
    this->x = x;
    this->y = y;
    this->setPen(*new QPen(*new QColor("red")));
}

int Point::getX() { return this->x; }

int Point::getY() { return this->y; }
