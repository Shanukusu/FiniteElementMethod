#include "graphic_point.h"

GraphicPoint::GraphicPoint(double x, double y) : QGraphicsEllipseItem(x, y, CIRCLE_RADIUS, CIRCLE_RADIUS)
{
    this->x = x;
    this->y = y;
    this->setPen(*new QPen(*new QColor("red")));
}

double GraphicPoint::getX() { return this->x; }

double GraphicPoint::getY() { return this->y; }

bool GraphicPoint::isMovable() { return this->movable; }

double GraphicPoint::getValue() { return this->value; }
