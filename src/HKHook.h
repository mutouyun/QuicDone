#pragma once

#include <QObject>

class HKHookLocker
{
public:
    HKHookLocker(void);
    ~HKHookLocker(void);
};

class HKHook_;
class HKHook : public QObject
{
    Q_OBJECT

public:
    static void setHandled(void);

    explicit HKHook(QObject* parent = Q_NULLPTR);
    ~HKHook(void);

    bool install(int id);
    void uninstall(void);

signals:
    void readyToWork(void);
    void keyEvent(int evt, int code);

private slots:
    void doWork(void);

private:
    friend class HKHook_;
    HKHook_* p_;
};
