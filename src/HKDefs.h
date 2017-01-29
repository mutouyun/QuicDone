#pragma once

#include <QString>
#include <utility>

namespace HK {

template <typename T, typename... A>
T& instance(A&&... args)
{
    static T i(std::forward<A>(args)...);
    return i;
}

const char* vkCodeTrans(int code);
void output(QtMsgType type, const QMessageLogContext& context, const QString& msg);

} // namespace HK
