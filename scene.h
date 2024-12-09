#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QList>
#include <QGraphicsLineItem>
#include <graphic_point.h>
#include <QPen>
#include <QColor>
#include <QObject>


#define WIDTH 1920
#define HEIGHT 1080
#define GRID_STEP 25

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
        QList<QList<GraphicPoint *>> points;

        /**
         * @brief Создаёт сетку на сцене в конструкторе
         */
        void createGrid();
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
        QList<QList<GraphicPoint *>> getPoints();

        /**
         * @brief Добавить точку на сцену
         * @param Точка, которую нужно добавить
         * @pre Координаты точки должны быть в допустимом для сцены диапазоне
         */
        void addPoint(GraphicPoint *point);

        /**
         * @brief Создаёт список QList<Point *> внутри внешнего списка points.
         * Что в смысловой нагрузке и означает "Добавить фигуру"
         */
        void addFigure();

        /**
         * @brief Действия для завершения фигуры при "тыке" пользователя в начальную точку
         * Красит первую точку в дефолтный цвет (сейчас фиксировано красный)
         * Соединяет первую и последние точки, образуя замкнутую фигуру
         */
        void finishFigure();

};

#endif // SCENE_H
