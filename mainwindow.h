#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <scene.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

/**
 * @brief Класс главного окна приложения
 */
class MainWindow : public QMainWindow {
        Q_OBJECT

    public:
        /**
         * @brief Конструктор
         * @param Нагенерено по Qt'ом, поэтому оставил, можно никак не задавать
         */
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private:
        /**
         * @brief Статически созданная разметка приложения
         * внутри пока только View
         */
        Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
