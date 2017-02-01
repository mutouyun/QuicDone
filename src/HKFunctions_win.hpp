#include <Windows.h>
#include <stdlib.h>

void HKFunctions::message(QString text) const
{
    postCall([text]
    {
        ::MessageBox(Q_NULLPTR,
#   ifdef UNICODE
            text.toStdWString().c_str(), L"QuicDone",
#   else
            text.toStdString().c_str(), "QuicDone",
#   endif
            MB_ICONINFORMATION | MB_OK);
    });
}

void HKFunctions::closeMonitor(void) const
{
    postCall([]{ ::PostMessage(HWND_BROADCAST, WM_SYSCOMMAND, SC_MONITORPOWER, 2); });
}

void HKFunctions::exec(QString cmd, QString param) const
{
    postCall([cmd, param]
    {
        ::ShellExecute(Q_NULLPTR,
#   ifdef UNICODE
            L"open", cmd.toStdWString().c_str(), param.toStdWString().c_str(),
#   else
            "open", cmd.toStdString().c_str(), param.toStdString().c_str(),
#   endif
            Q_NULLPTR, SW_SHOW);
    });
}
