#pragma once

#include <QApplication>

#include "HKAssembly.h"

class HKApplication : public QApplication
{
    Q_OBJECT

public:
    HKApplication(int &argc, char **argv);
    ~HKApplication(void);

signals:
    void keyEvent(int evt, int code);

private slots:
    void onKeyAssembled(HKKey key);
};
