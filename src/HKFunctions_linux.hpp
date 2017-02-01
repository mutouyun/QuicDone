#include <QMessageBox>

#include <unistd.h>

void HKFunctions::message(QString text) const
{
    postCall([text]{ QMessageBox::information(Q_NULLPTR, "QuicDone", text); });
}

void HKFunctions::closeMonitor(void) const
{
    postCall([this]{ shell("xset dpms force off"); });
}

void HKFunctions::exec(QString cmd, QString param) const
{
    if (!param.isEmpty()) cmd += " " + param;
    postCall([cmd, this]{ shell(cmd.toUtf8().data()); });
}
