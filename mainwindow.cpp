#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "config.h"
#include "consolerunner.h"

#include <QDesktopWidget>
#include <QMessageBox>
#include <QProcess>
#include <QRegExp>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setCentralWidget(ui->plainTextEdit);

    ui->actionViewStatusbar->setCheckable(true);
    ui->actionViewStatusbar->setChecked(true);
    // add toggleViewAction to menu
    ui->menuWindow->insertAction(ui->actionViewStatusbar, ui->mainToolBar->toggleViewAction());

    //connect
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->actionViewStatusbar, SIGNAL(triggered()), this, SLOT(toggleStatusbar()));

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

void MainWindow::toggleStatusbar()
{
    if (ui->actionViewStatusbar->isChecked()) {
        ui->statusBar->show();
    } else {
        ui->statusBar->hide();
    }
}

void MainWindow::on_actionRun_triggered()
{
    QProcess p;
    QString program;
    QStringList arguments;
#ifdef Q_OS_WIN
    program = "cmd";
    arguments << "/c dir /s C:\\qt\\";
#elif defined Q_OS_MAC
    program = "open";
    arguments << "/";
#endif
    ConsoleRunner cr;

    ui->plainTextEdit->appendPlainText("running  console app "+program);
    QObject::connect(&p, SIGNAL(finished(int,QProcess::ExitStatus)), &cr, SLOT(finished(int, QProcess::ExitStatus)));
    //QObject::connect(&p, SIGNAL(readyReadStandardOutput()), &cr, SLOT(readyReadStandardOutput()));
    QObject::connect(&p, SIGNAL(readyReadStandardOutput()), this, SLOT(readyReadStandardOutput()));
    QObject::connect(&p, SIGNAL(started()), &cr, SLOT(started()));

    p.start(program, arguments);
    p.waitForFinished();
}

void MainWindow::readyReadStandardOutput()
{
    QProcess *p = (QProcess *)sender();
    QByteArray buf = p->readAllStandardOutput();
    ui->plainTextEdit->appendPlainText(buf);
}
