#include "HKFunctions.h"
#include "HKApplication.h"

#include <QTimer>

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

void HKFunctions::quit(void) const
{
    qobject_cast<HKApplication*>(qApp)->quit();
}

void HKFunctions::version(void) const
{
    message("QuicDone!\nv 1.0 (build 0014)");
}

void HKFunctions::shell(QString cmd) const
{
    system(cmd.toUtf8().data());
}

template <typename F>
static inline void postCall(F call, int delay = 500)
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

#if defined(Q_OS_WIN32)
#include "HKFunctions_win.hpp"
#elif defined(Q_OS_LINUX)
#include "HKFunctions_linux.hpp"
#endif
