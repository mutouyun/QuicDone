#include <QVector>
#include <QSet>

#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>

QVector<HKHook*> __hooks;

template <size_t N>
constexpr static bool __testBit(const quint8 (&mask)[N], int bit)
{
    return ( mask[bit >> 3] & (1 << (bit & ~(((uint)~0) << 3))) );
}

static bool __install(void)
{
    if (!__hooks.isEmpty()) return false;

    QSet<int> ids;
    quint8 mask[(EV_MAX >> 3) + 1];
    for (int i = 0; i < 32; ++i)
    {
        QString name = QString("/dev/input/event%1").arg(i);
        int fd = open(name.toUtf8().data(), O_RDONLY);
        if (fd >= 0)
        {
            ioctl(fd, EVIOCGBIT(0, sizeof(mask)), mask);
            for (int j = 0; j < EV_MAX; ++j)
            {
                if (__testBit(mask, j))
                {
                    const char *type = "unknown";
                    switch (j)
                    {
                    case EV_KEY: { type = "keys/buttons"; ids << j; } break;
                    case EV_REL: { type = "relative"    ;           } break;
                    case EV_ABS: { type = "absolute"    ;           } break;
                    case EV_MSC: { type = "reserved"    ;           } break;
                    case EV_LED: { type = "leds"        ;           } break;
                    case EV_SND: { type = "sound"       ;           } break;
                    case EV_REP: { type = "repeat"      ;           } break;
                    case EV_FF : { type = "feedback"    ;           } break;
                    }
                    qDebug(" %s", type);
                }
            }
            qDebug("\n");
            close(fd);
        }
    }

    foreach (int id, ids)
    {
        auto hook = new HKHook;
        if (hook->install(id))
        {
            QObject::connect(hook, SIGNAL(keyEvent(int, int)), qApp, SIGNAL(keyEvent(int, int)));
            __hooks << hook;
        }
        else delete hook;
    }
    return !__hooks.isEmpty();
}

static void __uninstall(void)
{
    foreach (auto hook, __hooks)
    {
        hook->uninstall();
        delete hook;
    }
}
