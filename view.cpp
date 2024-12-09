#include "view.h"
#include <QDebug>

View::View(QWidget *parent): QGraphicsView(parent)
{
    this->figureIsDrawing = false;
}

void View::leftMouseButtonPressed(QMouseEvent *event)
{
    // Если мы только начинаем рисовать новую фигуру, то создаём для
    // свой список и запихиваем точку туда, рисуем точку на сцене
    if (!this->isFigureDrawing()) {
        Scene *scene = (Scene *)this->scene();

        QPointF coord = this->mapToScene( event->x(), event->y() );

        GraphicPoint *point = new GraphicPoint( (int)coord.x(), (int)coord.y() );
        scene->addFigure();
        scene->addPoint(point);
        this->figureIsDrawing = true;
    }

    // Если мы уже в процессе рисования фигуры, то следим, чтобы пользователь
    // "почти попал" в начальную точку и тогда завершаем фигуру
    else {
        Scene *scene = (Scene *)this->scene();

        QPointF coord = this->mapToScene( event->x(), event->y() );

        GraphicPoint *point = new GraphicPoint( (int)coord.x(), (int)coord.y() );
        QList<GraphicPoint *> lastFigure = scene->getPoints().last();

        if ( this->approximateHit(lastFigure.first(), point) ) {
            this->figureIsDrawing = false;

            for (int i = 0; i < lastFigure.size() - 1; i++) {
                int x1 = lastFigure[i]->getX();
                int y1 = lastFigure[i]->getY();

                int x2 = lastFigure[i+1]->getX();
                int y2 = lastFigure[i+1]->getY();

                QGraphicsLineItem *line = new QGraphicsLineItem(x1 + CIRCLE_RADIUS / 2,
                                                                y1 + CIRCLE_RADIUS / 2,
                                                                x2 + CIRCLE_RADIUS / 2,
                                                                y2 + CIRCLE_RADIUS / 2);
                line->setPen(* new QPen(* new QColor("white")));

                scene->addItem(line);
            }
            // Завершить фигуру после "тыка" в первую точку
            scene->finishFigure();
        }
        else {
            scene->addPoint(point);
        }
    }
}

void View::rightMouseButtonPressed(QMouseEvent *event)
{

}

void View::mousePressEvent(QMouseEvent *event)
{
    try {
        if (event->button() == Qt::LeftButton ) {
            this->leftMouseButtonPressed(event);
        }
        else if (event->button() == Qt::RightButton) {
            this->rightMouseButtonPressed(event);
        }
    } catch (const std::exception err) {
        qDebug() << err.what();
    }
}

bool View::approximateHit(GraphicPoint *start, GraphicPoint *end)
{
    if ( end->getX() > start->getX() - HIT_RADIUS / 2 &&
         end->getX() < start->getX() + HIT_RADIUS / 2 &&
         end->getY() > start->getY() - HIT_RADIUS / 2 &&
         end->getY() < start->getY() + HIT_RADIUS / 2)
        return true;
    return false;
}

bool View::isFigureDrawing()
{
    return this->figureIsDrawing;
}
