#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    readSettings();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_action_Quit_triggered()
{
    qApp->aboutQt();
    qApp->exit();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    writeSettings();
    QMainWindow::closeEvent(event);
}

void MainWindow::writeSettings()
{
    QSettings settings(qApp->applicationName()+".ini", QSettings::IniFormat);
    qDebug(settings.fileName().toStdString().c_str());
    settings.beginGroup("mainwindow");
    settings.setValue("size", this->size());
    settings.endGroup();
}

void MainWindow::readSettings()
{
    QSettings settings(qApp->applicationName()+".ini", QSettings::IniFormat);
    this->resize(settings.value("mainwindow/size", QSize(320,200)).toSize());
}
