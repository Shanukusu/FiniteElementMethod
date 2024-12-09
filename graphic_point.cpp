#include "graphic_point.h"

GraphicPoint::GraphicPoint(int x, int y) : QGraphicsEllipseItem(x, y, CIRCLE_RADIUS, CIRCLE_RADIUS)
{
    this->x = x;
    this->y = y;
    this->setPen(*new QPen(*new QColor("red")));
}

int GraphicPoint::getX() { return this->x; }

int GraphicPoint::getY() { return this->y; }
