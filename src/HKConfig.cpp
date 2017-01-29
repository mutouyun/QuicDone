#include "HKConfig.h"

#include <QApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QDebug>

HKConfig::HKConfig(void)
    : m_isLogOutput(false)
{
    QFile cfg(qApp->applicationDirPath() + "/" + qApp->applicationName() + ".config");
    if (cfg.open(QIODevice::ReadOnly))
    {
        QJsonObject datas = QJsonDocument::fromJson(cfg.readAll()).object();
        for (auto it = datas.begin(); it != datas.end(); ++it)
        {
            if (!isLogOutput() && it.key().toLower() == "log")
            {
                m_isLogOutput = it.value().toBool();
            }
            else this->insert(HKKey(it.key()), it.value().toString());
        }
    }
}

bool HKConfig::isLogOutput(void) const
{
    return m_isLogOutput;
}
