#include "view.h"
#include <QDebug>

View::View(QWidget *parent): QGraphicsView(parent)
{
    this->figureIsDrawing = false;
    this->pointConfigCreated = false;
}

void View::leftMouseButtonPressed(QMouseEvent *event)
{
    // Если мы только начинаем рисовать новую фигуру, то создаём для
    // свой список и запихиваем точку туда, рисуем точку на сцене
    if (!this->isFigureDrawing() && !this->isPointConfigCreated()) {
        Scene *scene = (Scene *)this->scene();

        QPointF coord = this->mapToScene( event->x(), event->y() );

        GraphicPoint *point = new GraphicPoint(coord.x(), coord.y() );
        scene->addFigure();
        scene->addPoint(point);
        this->figureIsDrawing = true;
    }

    // Если мы уже в процессе рисования фигуры, то следим, чтобы пользователь
    // "почти попал" в начальную точку и тогда завершаем фигуру
    else if (!this->isPointConfigCreated()) {
        Scene *scene = (Scene *)this->scene();

        QPointF coord = this->mapToScene( event->x(), event->y() );

        GraphicPoint *point = new GraphicPoint( coord.x(), coord.y() );
        QList<GraphicPoint *> lastFigure = scene->getPoints().last();

        if ( this->approximateHit(lastFigure.first(), point) ) {
            this->figureIsDrawing = false;

            for (int i = 0; i < lastFigure.size() - 1; i++) {
                int x1 = lastFigure[i]->getX();
                int y1 = lastFigure[i]->getY();

                int x2 = lastFigure[i + 1]->getX();
                int y2 = lastFigure[i + 1]->getY();

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
    QPointF coord = this->mapToScene( event->x(), event->y() );
    QList<QGraphicsItem *> clickedItems = this->items(coord.x(),
                                                      coord.y(),
                                                      CIRCLE_RADIUS * 2,
                                                      CIRCLE_RADIUS * 2);
    if (!clickedItems.isEmpty()) {

        Scene *scene = static_cast<Scene *>(this->scene());

        for (int i = 0; i < clickedItems.size(); i++) {

            GraphicPoint *point = static_cast<GraphicPoint *>(clickedItems[i]);

            if (point != nullptr) {

                this->pointConfigCreated = true;
                PointConfig *pointConfig = new PointConfig(point);
                connect(pointConfig, &PointConfig::closed,
                        this, &View::pointConfigWasClosed);


                QGraphicsProxyWidget *pointEditWidget = scene->addWidget(pointConfig);
                pointEditWidget->setPos(coord);
                pointEditWidget->setZValue(1);

                this->denormalizeCoordinate(coord);
            }
        }
    }
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


QPointF View::denormalizeCoordinate(QPointF point)
{
    QPointF new_point = this->mapFromScene(point);
    qDebug() << new_point;
}

void View::pointConfigWasClosed()
{
    this->pointConfigCreated = false;
}
