#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "config.h"

#include <QDesktopWidget>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // add some default actions dynamicaly
    QAction *tba = ui->mainToolBar->toggleViewAction();
    ui->menuBar->insertAction(ui->actionViewStatusbar, tba);
    readSettings();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::closeEvent
 * @param event
 */
void MainWindow::closeEvent(QCloseEvent *event)
{
    writeSettings();
    QMainWindow::closeEvent(event);
}

/**
 * @brief MainWindow::writeSettings
 */
void MainWindow::writeSettings()
{
    QSettings settings(qApp->applicationName()+".ini", QSettings::IniFormat);
    // if running on debug mode display where .ini is stored
#ifdef QT_DEBUG
    qDebug(settings.fileName().toStdString().c_str());
#endif
    settings.beginGroup("mainwindow");
    settings.setValue("size", this->size());
    settings.endGroup();
}

/**
 * @brief MainWindow::readSettings
 */
void MainWindow::readSettings()
{
    QSettings settings(qApp->applicationName()+".ini", QSettings::IniFormat);
    this->resize(settings.value("mainwindow/size", QSize(320,200)).toSize());
}

void MainWindow::on_actionAbout_triggered()
{
    QString text = QString("<h2>%3</h2>Version %1<br>"
                           "<b><i>%3</i></b> is a cross-platform application<br><br>"
                           "Website: <a href=https://github.com/glls/qt4mp>%3</a>.<br>"
                           "Contact: <a href=mailto:GeorgeLitos%2gmail.com>GeorgeLitos%2gmail.com</a>.<br><br>"
                           "The program is provided AS IS with NO WARRANTY OF ANY KIND.<br>")
            .arg(VERSION).arg("@").arg(qApp->applicationName());

    QMessageBox::about(this, "About "+(qApp->applicationName()),
                       text);
}

void MainWindow::on_actionExit_triggered()
{
    close();
}
