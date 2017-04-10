#ifndef DEBUG_H
#define DEBUG_H
#include "global.h"
#include <iostream>
#include <QtCore>
#include <QApplication>
#include <QMutex>

void debugMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
    static QMutex mutex;
    mutex.lock();
    QString text;
    switch (type) {
    case QtDebugMsg:
        text = QString("Debug:");
        break;
    case QtInfoMsg:
        text = QString("Info:");
        break;
    case QtWarningMsg:
        text = QString("Warning:");
        break;
    case QtFatalMsg:
        text = QString("Fatal:");
        break;
    case QtCriticalMsg:
        text = QString("Critical:");
    default:
        break;
    }

    QString contextInfo = QString("  Message:{ %1 }\n  File:{ %2 }\n  Line:{ %3 }\n  Func:{ %4 }\n  Time:{ %5 }\n")
            .arg(msg).arg(QString(context.file)).arg(QString::number(context.line))
            .arg(QString(context.function)).arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd"));
    qout << text << "\n" << contextInfo << endl;
    mutex.unlock();
}

#endif // DEBUG_H
