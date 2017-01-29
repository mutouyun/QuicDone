#include "HKDefs.h"
#include "HKScript.h"
#include "HKFunctions.h"

#include <QFileInfo>
#include <QFile>
#include <QTextStream>

HKScript::HKScript(void)
{
    m_engine.globalObject().setProperty("HK", m_engine.newQObject(&HK::instance<HKFunctions>()));
}

void HKScript::evaluate(const QString& value)
{
    if (value.isEmpty()) return;
    QScriptProgram program;
    QFileInfo info(value);
    if (info.isFile())
    {
        qDebug("[HKScript] value is file: %s", info.fileName().toUtf8().data());
        QFile script(value);
        if (script.open(QIODevice::ReadOnly))
        {
            QTextStream stream(&script);
            program = QScriptProgram(stream.readAll(), value);
            script.close();
        }
    }
    else
    {
        program = QScriptProgram(value);
    }
    m_engine.evaluate(program);
}
