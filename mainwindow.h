#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>

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
    void on_action_Quit_triggered();

private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H
