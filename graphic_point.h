#ifndef GRAPHIC_POINT_H
#define GRAPHIC_POINT_H

#include <QGraphicsEllipseItem>
#include <QPen>
#include <QColor>

#define CIRCLE_RADIUS 6
/**
 * @brief Класс для создания точки на графике
 * Объект хранит координаты на сцене x и y
 * TODO сделать возможность настроки цвета объекта
 */
class GraphicPoint : public QGraphicsEllipseItem {
    private:
        double x;
        double y;
        bool movable;
        double value;
    public:
        /**
         * @brief Конструктор
         * @param X координата точки
         * @param Y координата точки
         *
         * @pre Оба параметра должны быть ицинициализированы и находится в границах
         * координат сцены (пока дефайнами задано от 0 до 1920 в ширину и от 0 до 1080 в высоту)
         */
        GraphicPoint(double x, double y);

        /**
         * @brief Метод для получения x координаты
         * @return Double значение координаты x
         */
        double getX();

        /**
         * @brief Метод для получение y координаты
         * @return Double значение координаты y
         */
        double getY();

        /**
         * @brief Геттер movable
         * @return Булево значение переменной movable
         */
        bool isMovable();

        /**
         * @brief Геттер для краевого условия первого рода
         * @return Double значение краевого условия
         */
        double getValue();
};

#endif // GRAPHIC_POINT_H
