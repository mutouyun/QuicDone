#include "HKFunctions.h"

#include <QApplication>
#include <QVector>
#include <QTimer>

#include <Windows.h>
#include <stdlib.h>

HKFunctions::HKFunctions(QObject* parent)
    : QObject(parent)
{
}

QString HKFunctions::appPath(void) const
{
    return qApp->applicationDirPath();
}

QString HKFunctions::appName(void) const
{
    return qApp->applicationName();
}

QString HKFunctions::appFull(void) const
{
    return qApp->applicationFilePath();
}

template <typename F>
void postCall(F call, int delay = 100)
{
    QTimer* timer = new QTimer;
    timer->setSingleShot(true);
    QObject::connect(timer, &QTimer::timeout, [timer, call]
    {
        call();
        delete timer;
    });
    timer->start(delay);
}

void HKFunctions::message(QString text) const
{
    postCall([text]
    {
        ::MessageBox(Q_NULLPTR,
#   ifdef UNICODE
            text.toStdWString().c_str(), L"QuicDone",
#   else
            text.toStdString().c_str(), "QuicDone",
#   endif
            MB_ICONINFORMATION | MB_OK);
    });
}

void HKFunctions::closeMonitor(void) const
{
    postCall([]{ ::PostMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, 2); });
}

void HKFunctions::shell(QString cmd) const
{
    system(cmd.toUtf8().data());
}

void HKFunctions::exec(QString cmd, QString param) const
{
    postCall([cmd, param]
    {
        ::ShellExecute(Q_NULLPTR,
#   ifdef UNICODE
            L"open", cmd.toStdWString().c_str(), param.toStdWString().c_str(),
#   else
            "open", cmd.toStdString().c_str(), param.toStdString().c_str(),
#   endif
            Q_NULLPTR, SW_SHOW);
    });
}

void HKFunctions::quit(void) const
{
    qApp->quit();
}

void HKFunctions::version(void) const
{
    message("QuicDone!\nv 1.0 (build 0010)");
}
