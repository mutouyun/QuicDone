#pragma once

#include <QString>
#include <utility>

namespace HK {

template <typename T>
T& instance(void)
{
    static T i;
    return i;
}

void output(QtMsgType type, const QMessageLogContext& context, const QString& msg);

enum EN_KeyEvent
{
    KeyNone,
    KeyPress,
    KeyRelease
};
EN_KeyEvent vkEventTrans(int evt);
const char* vkCodeTrans(int code);

} // namespace HK
