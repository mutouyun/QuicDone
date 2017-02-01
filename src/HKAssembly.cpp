#include "HKAssembly.h"
#include "HKHook.h"
#include "HKDefs.h"

#include <QDebug>

HKKey::HKKey(void)
{

}

HKKey::HKKey(const QString& key)
{
    this->fromString(key);
}

HKKey& HKKey::fromString(QString key)
{
    this->clear();
    auto list = key.remove(' ').split('+', QString::SkipEmptyParts);
    foreach(const QString& k, list) (*this) << k.toUpper();
    return (*this);
}

QString HKKey::toString(void) const
{
    QString ret;
    foreach (const QString& k, *this) (ret += k) += " + ";
    return ret.mid(0, ret.length() - 3);
}

HKAssembly::HKAssembly(QObject* parent)
    : QObject(parent)
{

}

void HKAssembly::onKeyEvent(int evt, int code)
{
    HKHookLocker locker;
    Q_UNUSED(locker)

    auto keyEvt = HK::vkEventTrans(evt);
    if (keyEvt == HK::KeyNone) return;
    auto keyStr = HK::vkCodeTrans(code);
    if (keyStr == Q_NULLPTR) return;
    switch (keyEvt)
    {
    case HK::KeyPress:
        {
            HKKey key = m_key;
            key << keyStr;
            if (key != m_key) emit keyEvent(m_key = key);
        }
        break;
    case HK::KeyRelease:
        {
            m_key.remove(keyStr);
            HKKey key = m_key;
            key << (QString(keyStr) + "[RELEASE]");
            emit keyEvent(key);
        }
        break;
    default: break;
    }
}
