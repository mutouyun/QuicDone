#include "HKDefs.h"

#include <QThread>
//#include <QMutex>
//#include <QWaitCondition>

#include <stdio.h>
#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>

//static QMutex         __hookMutex;
//static QWaitCondition __hookCondition;

class HKHook_
{
    friend class HKHook;

    HKHook* t_;
    int fd;
    QThread thread;

    HKHook_(HKHook* t)
        : t_(t), fd(0)
    {
        QObject::connect(t_, &HKHook::readyToWork, &HKHook::doWork, Qt::QueuedConnection);
    }

    bool install(int id)
    {
        if (fd > 0) return false;
        QString name = QString("/dev/input/event%1").arg(id);
        fd = open(name.toUtf8().data(), O_RDONLY /*O_RDWR*/);
        if (fd <= 0)
        {
            qWarning("[HKHook] open %s, device error!", name.toUtf8().data());
            return false;
        }
        t_->moveToThread(&thread);
        QObject::connect(&thread, &QThread::started, t_, &HKHook::readyToWork, Qt::QueuedConnection);
        thread.start();
        return true;
    }

    void uninstall(void)
    {
        if (fd <= 0) return;
        thread.quit();
        thread.wait();
        close(fd);
    }
};

HKHookLocker:: HKHookLocker(void) { /*__hookMutex.lock();*/ }
HKHookLocker::~HKHookLocker(void) { /*__hookCondition.wakeAll(); __hookMutex.unlock();*/ }

//static __u16 __vkCode = 0;

void HKHook::doWork(void)
{
//    QMutexLocker locker(&__hookMutex);
//    Q_UNUSED(locker)

    input_event t;
    if (read(p_->fd, &t, sizeof(t)) == sizeof(t))
    {
        switch (t.type)
        {
        case EV_KEY:
            {
//                if (HK::vkEventTrans(t.value) == HK::KeyPress || __vkCode != t.code)
//                {
//                    __hasHandled = false; // Reset the flag.
//                }
//                __vkCode = t.code;
                emit this->keyEvent(t.value, t.code);
//                __hookCondition.wait(&__hookMutex);
            }
            break;
        }
    }
    emit this->readyToWork();
}
