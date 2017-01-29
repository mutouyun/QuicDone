#pragma once

#include <QScriptEngine>

class HKScript
{
public:
    HKScript(void);

    void evaluate(const QString& value);

private:
    QScriptEngine m_engine;
};
