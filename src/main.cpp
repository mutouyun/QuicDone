#include "HKApplication.h"
#include "HKConfig.h"
#include "HKDefs.h"

int main(int argc, char *argv[])
{
    HKApplication a(argc, argv);
    HK::instance<HKConfig>();
    qInstallMessageHandler([](QtMsgType type, const QMessageLogContext& context, const QString& msg)
    {
        if (HK::instance<HKConfig>().isLogOutput())
            HK::output(type, context, msg);
    });
    return a.exec();
}
