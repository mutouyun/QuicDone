
static bool __install(void)
{
    if (HK::instance<HKHook>().install(0))
    {
        QObject::connect(&HK::instance<HKHook>(), SIGNAL(keyEvent(int, int)), qApp, SIGNAL(keyEvent(int, int)));
        return true;
    }
    return false;
}

static void __uninstall(void)
{
    HK::instance<HKHook>().uninstall();
}
