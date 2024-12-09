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
    if (this->points.last().size() == 1) {
        point->setPen(* new QPen(* new QColor("#ffff00")));
    }
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

void Scene::finishFigure()
{
    QList<GraphicPoint *> lastFigure = this->points.last();
    // Создать линию между первым и последним узлом и сделать фигуру закрытой
    int x1 = lastFigure.first()->getX();
    int y1 = lastFigure.first()->getY();

    lastFigure.first()->setPen(* new QPen(* new QColor("red")));

    int x2 = lastFigure.last()->getX();
    int y2 = lastFigure.last()->getY();
    QGraphicsLineItem *line = new QGraphicsLineItem(x1 + CIRCLE_RADIUS / 2,
                                                    y1 + CIRCLE_RADIUS / 2,
                                                    x2 + CIRCLE_RADIUS / 2,
                                                    y2 + CIRCLE_RADIUS / 2);
    line->setPen(* new QPen(* new QColor("white")));
    this->addItem(line);
}

