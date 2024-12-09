#ifndef GRAPHIC_POINT_H
#define GRAPHIC_POINT_H

#include <QGraphicsEllipseItem>
#include <QPen>
#include <QColor>

#define CIRCLE_RADIUS 5
/**
 * @brief Класс для создания точки на графике
 * Объект хранит координаты на сцене x и y
 * TODO сделать возможность настроки цвета объекта
 */
class GraphicPoint : public QGraphicsEllipseItem {
    private:
        int x;
        int y;
    public:
        /**
         * @brief Конструктор
         * @param X координата точки
         * @param Y координата точки
         *
         * @pre Оба параметра должны быть ицинициализированы и находится в границах
         * координат сцены (пока дефайнами задано от 0 до 1920 в ширину и от 0 до 1080 в высоту)
         */
        GraphicPoint(int x, int y);

        /**
         * @brief Метод для получения x координаты
         * @return Целое значение координаты x
         */
        int getX();

        /**
         * @brief Метод для получение y координаты
         * @return Целое значение координаты y
         */
        int getY();
};

#endif // GRAPHIC_POINT_H
