#ifndef POINTCONFIG_H
#define POINTCONFIG_H

#include <QWidget>
#include "graphic_point.h"

namespace Ui {
class PointConfig;
}

class PointConfig : public QWidget
{
    Q_OBJECT

public:
    explicit PointConfig(GraphicPoint* point, QWidget *parent = nullptr);
    ~PointConfig();

private:
    Ui::PointConfig *ui;
    GraphicPoint *point;
};

#endif // POINTCONFIG_H
