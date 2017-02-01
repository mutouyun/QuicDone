#pragma once

#include <QObject>

class HKFunctions : public QObject
{
    Q_OBJECT

public:
    explicit HKFunctions(QObject* parent = Q_NULLPTR);

    Q_INVOKABLE QString appPath(void) const;
    Q_INVOKABLE QString appName(void) const;
    Q_INVOKABLE QString appFull(void) const;
    Q_INVOKABLE void quit(void) const;
    Q_INVOKABLE void version(void) const;
    Q_INVOKABLE void message(QString text) const;
    Q_INVOKABLE void closeMonitor(void) const;
    Q_INVOKABLE void shell(QString cmd) const;
    Q_INVOKABLE void exec(QString cmd, QString param = "") const;
};
