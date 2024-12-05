#include "scene.h"

Scene::Scene(QObject *parent) : QGraphicsScene{parent}
{
    QRectF *sceneRect = new QRectF(0, 0, WIDTH, HEIGHT);
    this->setSceneRect(*sceneRect);
}

QList<QList<Point *>> Scene::getPoints()
{
    return this->points;
}

void Scene::addPoint(Point *point)
{
    this->points.last().append(point);
}

void Scene::addFigure()
{
    QList<Point *> new_figure;
    this->points.append(new_figure);
}
