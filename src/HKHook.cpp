#include "HKHook.h"

static bool __hasHandled = false;

#if defined(Q_OS_WIN32)
#include "HKHook_win.hpp"
#elif defined(Q_OS_LINUX)
#include "HKHook_linux.hpp"
#endif

void HKHook::setHandled(void)
{
    __hasHandled = true;
}

HKHook::HKHook(QObject* parent)
    : QObject(parent)
    , p_(new HKHook_(this))
{
}

HKHook::~HKHook(void)
{
    delete p_;
}

bool HKHook::install(int id)
{
    return p_->install(id);
}

void HKHook::uninstall(void)
{
    p_->uninstall();
}
