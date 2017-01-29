#include "HKDefs.h"

#include <QGuiApplication>
#include <QByteArray>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>
#include <QString>
#include <QDateTime>
#include <QHash>

#include <Windows.h>
#include <iostream>

namespace HK {

const char* vkCodeTrans(int code)
{
    static const QHash<int, const char*> __table =
    {
        { VK_SPACE   , "SPACE" },
        { VK_ESCAPE  , "ESC"   },
        { VK_RETURN  , "ENTER" },
        { VK_LSHIFT  , "SHIFT" },
        { VK_RSHIFT  , "SHIFT" },
        { VK_LCONTROL, "CTRL"  },
        { VK_RCONTROL, "CTRL"  },
        { VK_LMENU   , "ALT"   },
        { VK_RMENU   , "ALT"   },
        { VK_LWIN    , "WIN"   },
        { VK_RWIN    , "WIN"   }
    };
    auto it = __table.find(code);
    if (it == __table.end())
    {
        if ((code >= 'A' && code <= 'Z') ||
            (code >= '0' && code <= '9'))
        {
            static char alphabet[2] = {};
            alphabet[0] = code;
            return alphabet;
        }
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
