#ifndef VIEW_H
#define VIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <graphic_point.h>
#include <scene.h>
#include <QGraphicsProxyWidget>
#include "pointconfig.h"

#define HIT_RADIUS 50
/**
 * @brief Класс отображения
 * Отображает всё, что добавлено в выбранную активную сцены
 */
class View : public QGraphicsView {
    private:
        /**
         * @brief Флажок того, что идёт заполнение незакрытой фигуры
         */
        bool figureIsDrawing;

        /**
         * @brief Флаг того, что сейчас создан point config
         */
        bool pointConfigCreated;

        /**
         * @brief Функция для определения примерного попадания пользователя по радиусу HIT_RADIUS
         *
         * @param Первая точка фигуры, в которую нужно попасть
         *
         * @param Предположительно последняя точка фигуры, должна почти совпадать с начальной, чтобы
         * получить замкнутый контур
         *
         * @return True, если пользователь почти попал в точку, false - если он был совсем далёк
         */
        bool approximateHit(GraphicPoint *start, GraphicPoint *end);
        bool isPointConfigCreated();

        void leftMouseButtonPressed(QMouseEvent *event);
        void rightMouseButtonPressed(QMouseEvent *event);

    public slots:
        void pointConfigWasClosed();

    public:
        /**
         * @brief Конструктор
         *
         * @param Родительский виджет на отображении
         */
        View(QWidget *parent = nullptr);

        /**
         * @brief Переопределённый метод нажатия на View.
         * Нужен для обработки щелчков мышью.
         *
         * @param Событие мыши
         */
        void mousePressEvent(QMouseEvent *event) override;

        /**
         * @brief Метод для доступа к флагу figureIsDrawing
         *
         * @return True, если сейчас идёт заполнение фигуры, false - иначе
         */
        bool isFigureDrawing();

        /**
         * @brief Координаты сцены в Qt нормализованные, поэтому мы будет пользоваться
         * кастомной денормализацией
         * @param Точка, координаты которой мы хотим нормализовать
         * @pre Точка должна находиться в границах сцены
         * @return Нормализованная точка
         */
        QPointF denormalizeCoordinate(QPointF point);
};

#endif // VIEW_H
