#pragma once

#include <QJSEngine>

class HKScript
{
public:
    HKScript(void);

    void evaluate(const QString& value);

private:
    QJSEngine m_engine;
};
