#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QProcess>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void writeSettings();
    void readSettings();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void toggleStatusbar();
    void readyReadStandardOutput();
    void on_actionAbout_triggered();    
    void on_actionRun_triggered();    

    void on_plainTextEdit_textChanged();

private:
    Ui::MainWindow *ui;
    QProcess m_process;
};

#endif // MAINWINDOW_H
