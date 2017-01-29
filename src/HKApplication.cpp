#include "HKDefs.h"
#include "HKApplication.h"
#include "HKConfig.h"
#include "HKScript.h"

#include <QKeyEvent>
#include <QDebug>

#include <Windows.h>

HHOOK __keyboardHook = Q_NULLPTR;

struct ST_HandleInfo
{
    bool  hasHandled = false;
    DWORD vkCode     = 0;
} __info = {};

static LRESULT CALLBACK __winKeyProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode >= HC_ACTION)
    {
        KBDLLHOOKSTRUCT* ks = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);
        if (wParam == WM_SYSKEYDOWN || wParam == WM_KEYDOWN || __info.vkCode != ks->vkCode)
        {
            __info.hasHandled = false; // Reset the flag.
        }
        emit qobject_cast<HKApplication*>(qApp)->keyEvent(wParam, ks->vkCode);
        __info.vkCode = ks->vkCode;
    }
    LRESULT ret = ::CallNextHookEx(0, nCode, wParam, lParam);
    return __info.hasHandled ? 1 : ret;
}

HKApplication::HKApplication(int &argc, char **argv)
    : QApplication(argc, argv)
{
    __keyboardHook = ::SetWindowsHookEx(WH_KEYBOARD_LL, __winKeyProc, ::GetModuleHandle(Q_NULLPTR), 0);
    if (__keyboardHook == Q_NULLPTR) quit();

    connect(&HK::instance<HKAssembly>(), SIGNAL(keyEvent(HKKey)), this, SLOT(onKeyAssembled(HKKey)));
    connect(this, SIGNAL(keyEvent(int, int)), &HK::instance<HKAssembly>(), SLOT(onKeyEvent(int, int)));
}

HKApplication::~HKApplication(void)
{
    ::UnhookWindowsHookEx(__keyboardHook);
    __keyboardHook = Q_NULLPTR;
}

void HKApplication::onKeyAssembled(HKKey key)
{
    if (key.isEmpty()) return;
    qDebug() << "[HKApplication] onKeyAssembled:" << key.toString();
    auto it = HK::instance<HKConfig>().find(key);
    if (it == HK::instance<HKConfig>().end()) return;
    qDebug("Matched!!");
    __info.hasHandled = true;
    HK::instance<HKScript>().evaluate(it.value());
}
