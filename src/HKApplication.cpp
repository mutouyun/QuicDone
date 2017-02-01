#include "HKDefs.h"
#include "HKApplication.h"
#include "HKConfig.h"
#include "HKScript.h"
#include "HKHook.h"

#include <QKeyEvent>
#include <QDebug>

static bool __shouldQuit = false;

static bool __install(void);
static void __uninstall(void);

#if defined(Q_OS_WIN32)
#include "HKApplication_win.hpp"
#elif defined(Q_OS_LINUX)
#include "HKApplication_linux.hpp"
#endif

HKApplication::HKApplication(int &argc, char **argv)
    : QApplication(argc, argv)
{
    if (!__install())
    {
        qFatal("[HKApplication] Key hooks failed!!");
        quit();
    }

    connect(&HK::instance<HKAssembly>(), SIGNAL(keyEvent(HKKey)), this, SLOT(onKeyAssembled(HKKey)));
    connect(this, SIGNAL(keyEvent(int, int)), &HK::instance<HKAssembly>(), SLOT(onKeyEvent(int, int)));
}

HKApplication::~HKApplication(void)
{
    __uninstall();
}

void HKApplication::quit(void)
{
    __shouldQuit = true;
    QApplication::quit();
}

bool HKApplication::event(QEvent* evt)
{
    if ((evt->type() == QEvent::Quit) && !__shouldQuit)
    {
        return true;
    }
    return QApplication::event(evt);
}

void HKApplication::onKeyAssembled(HKKey key)
{
    if (key.isEmpty()) return;
    qDebug() << "[HKApplication] onKeyAssembled:" << key.toString();
    auto it = HK::instance<HKConfig>().find(key);
    if (it == HK::instance<HKConfig>().end()) return;
    qDebug("Matched!!");
    HKHook::setHandled();
    HK::instance<HKScript>().evaluate(it.value());
}
