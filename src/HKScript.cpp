#include "HKDefs.h"
#include "HKScript.h"
#include "HKFunctions.h"
#include "HKStore.h"

#include <QFileInfo>
#include <QFile>
#include <QTextStream>

HKScript::HKScript(void)
{
    HK::instance<HKStore>().init(&m_engine);

    m_engine.globalObject().setProperty("HK"     , m_engine.newQObject(&HK::instance<HKFunctions>()));
    m_engine.globalObject().setProperty("HKStore", m_engine.newQObject(&HK::instance<HKStore>()));
}

void HKScript::evaluate(const QString& value)
{
    if (value.isEmpty()) return;
    QString program;
    QFileInfo info(value);
    if (info.isFile())
    {
        qDebug("[HKScript] value is file: %s", info.fileName().toUtf8().data());
        QFile script(value);
        if (script.open(QIODevice::ReadOnly))
        {
            QTextStream stream(&script);
            program = stream.readAll();
            script.close();
        }
    }
    else
    {
        program = value;
    }
    m_engine.evaluate(program);
}
