#pragma once

#include <QObject>
#include <QSet>

class HKKey : public QSet<QString>
{
public:
    HKKey(void);
    explicit HKKey(const QString& key);
    HKKey& fromString(QString key);
    QString toString(void) const;
};

class HKAssembly : public QObject
{
    Q_OBJECT

public:
    explicit HKAssembly(QObject *parent = Q_NULLPTR);

signals:
    void keyEvent(HKKey key);

private slots:
    void onKeyEvent(int evt, int code);

private:
    HKKey m_key;
};
