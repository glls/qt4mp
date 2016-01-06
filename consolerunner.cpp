#include "consolerunner.h"

ConsoleRunner::ConsoleRunner(QObject *parent) : QObject(parent)
{
}

void ConsoleRunner::readyReadStandardOutput()
{
    QProcess *p = (QProcess *)sender();
    QByteArray buf = p->readAllStandardOutput();
    qDebug() << buf;
}

void ConsoleRunner::readyReadStandardError()
{
    QProcess *p = (QProcess *)sender();
    QByteArray buf = p->readAllStandardError();
    qDebug() << buf;
}

void ConsoleRunner::error(QProcess::ProcessError error)
{
    qDebug() << "Error: " << error;
}

void ConsoleRunner::finished(int exitCode, QProcess::ExitStatus exitStatus)
{
    qDebug() << "Finished with exit code: " << exitCode;
}

void ConsoleRunner::started()
{
    qDebug() << "ConsoleRunner Started";
}
