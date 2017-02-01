#include "HKDefs.h"

#include <Windows.h>

static WPARAM __wParam = 0;
static DWORD  __vkCode = 0;

LRESULT CALLBACK __winKeyProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode >= HC_ACTION)
    {
        KBDLLHOOKSTRUCT* ks = reinterpret_cast<KBDLLHOOKSTRUCT*>(lParam);
        if (HK::vkEventTrans(wParam) == HK::KeyPress || __vkCode != ks->vkCode)
        {
            __hasHandled = false; // Reset the flag.
        }
        __wParam = wParam;
        __vkCode = ks->vkCode;
        emit HK::instance<HKHook>().readyToWork();
    }
    LRESULT ret = ::CallNextHookEx(0, nCode, wParam, lParam);
    return __hasHandled ? 1 : ret;
}

class HKHook_
{
    friend class HKHook;

    HKHook* t_;
    HHOOK  keyboardHook;

    HKHook_(HKHook* t)
        : t_(t), keyboardHook(Q_NULLPTR)
    {
    }

    bool install(int /*id*/)
    {
        if (keyboardHook == Q_NULLPTR)
        {
            keyboardHook = ::SetWindowsHookEx(WH_KEYBOARD_LL, __winKeyProc, ::GetModuleHandle(Q_NULLPTR), 0);
            return keyboardHook != Q_NULLPTR;
        }
        else return false;
    }

    void uninstall(void)
    {
        if (keyboardHook != Q_NULLPTR)
        {
            ::UnhookWindowsHookEx(keyboardHook);
            keyboardHook = Q_NULLPTR;
        }
    }
};

HKHookLocker:: HKHookLocker(void) {}
HKHookLocker::~HKHookLocker(void) {}

void HKHook::doWork(void)
{
    emit this->keyEvent(__wParam, __vkCode);
}
