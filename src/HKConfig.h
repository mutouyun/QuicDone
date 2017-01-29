#pragma once

#include <QString>
#include <QHash>

#include "HKAssembly.h"

class HKConfig : public QHash<HKKey, QString>
{
public:
    HKConfig(void);

    bool isLogOutput(void) const;

private:
    bool m_isLogOutput;
};
