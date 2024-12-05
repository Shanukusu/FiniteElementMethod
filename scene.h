#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QList>
#include <point.h>
#include <QObject>


#define WIDTH 1920
#define HEIGHT 1080

/**
 * @brief Класс сцены, которая хранит в себе объекты и рисует их
 *
 * Обычно необходима в тех случаях, когда у нас несколько несвязанных (или почти)
 * между собой сцен, которые нужно менять. Добавил, т.к. не знаю, какой может понадобиться
 * функционал, но она особо и не мешает
 */
class Scene : public QGraphicsScene {
    private:
        /**
         * @brief Список всех точек. Первый список хранит в себе "фигуры".
         * По-сути просто вложенная иерархия для удобной нафигации по точкам.
         */
        QList<QList<Point *>> points;

    public:
        /**
         * @brief Конструктор
         * @param Родительский элемент - передаётся конструктору QObject
         */
        explicit Scene(QObject *parent = nullptr);

        /**
         * @brief Геттер точек сцены
         * @return Собственно - список списков точек на сцене
         */
        QList<QList<Point *>> getPoints();

        /**
         * @brief Добавить точку на сцену
         * @param Точка, которую нужно добавить
         * @pre Координаты точки должны быть в допустимом для сцены диапазоне
         */
        void addPoint(Point *point);

        /**
         * @brief Создаёт список QList<Point *> внутри внешнего списка points.
         * Что в смысловой нагрузке и означает "Добавить фигуру"
         */
        void addFigure();
};

#endif // SCENE_H
