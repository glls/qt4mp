#ifndef CONSOLERUNNER_H
#define CONSOLERUNNER_H

#include <QObject>
#include <QStringList>
#include <QProcess>
#include <QDebug>

class ConsoleRunner : public QObject
{
    Q_OBJECT
public:
    explicit ConsoleRunner(QObject *parent = 0);

signals:

public slots:
    void readyReadStandardError();
    void readyReadStandardOutput();
    void error(QProcess::ProcessError error);
    void finished(int exitCode, QProcess::ExitStatus exitStatus);
    void started();
private:
    QProcess m_process;
    bool m_stopped;
};

#endif // CONSOLERUNNER_H
