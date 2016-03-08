#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "listdialog.h"

MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent)
    ,ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionRestart_game, SIGNAL(triggered()), this, SLOT(restartGame()));
    connect(ui->actionShow_tip, SIGNAL(triggered()), this, SLOT(showTip()));
    connect(ui->actionStart_new_game, SIGNAL(triggered()), this, SLOT(startNewGame()));
    connect(ui->openGLWidget, SIGNAL(resizeParent(QSize)), this, SLOT(customResize(QSize)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::restartGame()
{
    ui->openGLWidget->restart();
}

void MainWindow::showTip()
{

    ui->openGLWidget->showTip();
}

void MainWindow::startNewGame()
{
    ListDialog *list = new ListDialog(this);
    if(list->exec() == QDialog::Accepted) {
        ui->openGLWidget->startNewGame(list->getFileName().toUtf8().constData());
    }
}

void MainWindow::customResize(QSize size)
{
    this->setMaximumSize(size);
    this->setMinimumSize(size);
    resize(size);
}

