#include "HKStore.h"

#include <QApplication>
#include <QFile>
#include <QJsonDocument>
#include <QJSEngine>
#include <QDebug>

static QString __cdatPath;

HKStore::HKStore(QObject *parent)
    : QObject(parent)
{
    __cdatPath = qApp->applicationDirPath() + "/" + qApp->applicationName() + ".dat";
    connect(this, &HKStore::datasChanged, [this]
    {
        QFile cdat(__cdatPath);
        if (cdat.open(QIODevice::WriteOnly))
        {
            QJsonDocument doc(m_datas);
            cdat.write(doc.toBinaryData());
        }
    });
}

void HKStore::init(QJSEngine* engine)
{
    if (engine == Q_NULLPTR) return;
    loadDatas();
    setConfigs(engine->newObject());
}

const QJsonObject& HKStore::getDatas(void) const
{
    return m_datas;
}

void HKStore::setDatas(const QJsonObject& var)
{
    if (m_datas == var) return;
    m_datas = var;
    emit datasChanged();
}

void HKStore::loadDatas(void)
{
    QFile cdat(__cdatPath);
    if (cdat.open(QIODevice::ReadOnly))
    {
        QByteArray data = cdat.readAll();
        m_datas = QJsonDocument::fromBinaryData(data).object();
    }
}

void HKStore::setData(QString key, QJsonValue val)
{
    m_datas.insert(key, val);
    emit datasChanged();
}

const QJSValue& HKStore::getConfigs(void) const
{
    return m_settingsVar;
}

void HKStore::setConfigs(const QJSValue& var)
{
    m_settingsVar = var;
    emit configsChanged();
}

void HKStore::setConfig(QString key, QJSValue val)
{
    m_settingsVar.setProperty(key, val);
    emit configsChanged();
}
