#include "scene.h"

Scene::Scene(QObject *parent) : QGraphicsScene{parent}
{
    QRectF *sceneRect = new QRectF(0, 0, WIDTH, HEIGHT);
    this->setSceneRect(*sceneRect);
    this->createGrid();
}

QList<QList<GraphicPoint *>> Scene::getPoints()
{
    return this->points;
}

void Scene::addPoint(GraphicPoint *point)
{
    this->points.last().append(point);
    this->addItem(point);
}

void Scene::addFigure()
{
    QList<GraphicPoint *> new_figure;
    this->points.append(new_figure);
}

void Scene::createGrid()
{
    for (int i = 0; i < WIDTH; i += GRID_STEP) {
        QGraphicsLineItem *line = new QGraphicsLineItem(i, 0, i, HEIGHT);
        line->setPen(* new QPen(* new QColor("#444444")));
        this->addItem(line);
    }

    for (int j = 0; j < HEIGHT; j += GRID_STEP) {
        QGraphicsLineItem *line = new QGraphicsLineItem(0, j, WIDTH, j);
        line->setPen(* new QPen(* new QColor("#444444")));
        this->addItem(line);
    }
}
