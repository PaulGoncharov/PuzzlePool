#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <memory>

#include <QMainWindow>

//Forward declaration
class Game;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void restartGame();
    void showTip();
    void startNewGame();
    void customResize(QSize size);
};

#endif // MAINWINDOW_H
