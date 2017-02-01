#include "HKDefs.h"

#include <QGuiApplication>
#include <QByteArray>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QString>
#include <QDateTime>
#include <QHash>

#include <iostream>

#if defined(Q_OS_WIN32)
#include "HKDefs_win.hpp"
#elif defined(Q_OS_LINUX)
#include "HKDefs_linux.hpp"
#endif

namespace HK {

EN_KeyEvent vkEventTrans(int evt)
{
    auto it = __evtTable.find(evt);
    if (it == __evtTable.end())
    {
        return HK::KeyNone;
    }
    return it.value();
}

const char* vkCodeTrans(int code)
{
    auto it = __codeTable.find(code);
    if (it == __codeTable.end())
    {
        return Q_NULLPTR;
    }
    return it.value();
}

void output(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
    QString msgType;
    switch (type)
    {
    case QtDebugMsg:
        msgType = "DEBUG";
        break;
    case QtInfoMsg:
        msgType = "INFO";
        break;
    case QtWarningMsg:
        msgType = "WARNING";
        break;
    case QtCriticalMsg:
        msgType = "CRITICAL";
        break;
    case QtFatalMsg:
        msgType = "FATAL";
    }
    QString timestamp = QDateTime::currentDateTime().toString("hh:mm:ss.zzz");
    QString output = QString("%1 [%2] - [%3:%4] %5")
                             .arg(timestamp)
                             .arg(msgType)
                             .arg(QFileInfo(context.file).fileName())
                             .arg(context.line)
                             .arg(msg);
    std::cerr << output.toLatin1().constData() << std::endl;

    static struct Log
    {
        QString path;
        QFile file;
        int index;

        Log(void)
            : path(qApp->applicationDirPath() + "/" + qApp->applicationName() + "_%1%2")
            , index(0)
        {
            openNewFile();
        }

        void openNewFile(void)
        {
            if (file.isOpen()) file.close();

            ++index;
            QString rem = path.arg(index - 10).arg(".log");
            if (QFileInfo::exists(rem))
            {
                QFile::remove(rem);
            }

            file.setFileName(path.arg(index).arg(".log"));
            file.open(QIODevice::WriteOnly);
            file.close();
        }

        Log& operator+= (const QString& log)
        {
            file.open(QIODevice::ReadWrite | QIODevice::Append);
            QTextStream stream(&file);
            stream << log << "\r\n";
            file.flush();

            QFileInfo fi(file);
            if (fi.size() > 1024 * 1024)
            {
                openNewFile();
            }
            else file.close();
            return (*this);
        }
    } log;
    log += output;
}

} // namespace HK
