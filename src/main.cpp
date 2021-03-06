// Copyright (C) 2014 - 2015 Leslie Zhai <xiang.zhai@i-soft.com.cn>

#include <QtQml>
#include <QtQuick/QQuickView>

#include "globaldeclarations.h"
#include "qtsingleapplication/QtSingleApplication"
#include "qwxuuid.h"
#include "scan.h"
#include "cookie.h"
#include "statreport.h"
#include "init.h"
#include "sync.h"
#include "contact.h"
#include "headimg.h"
#include "statusnotify.h"
#include "sendmsg.h"
#include "monitor.h"
#include "getmsg.h"
#include "circleimage.h"
#include "process.h"
#include "xiaodoubi.h"
#include "chatlog.h"
#include "emotion.h"
#include "logout.h"
#include "ipcity.h"
#include "weather.h"
#include "i18n.h"
#include "clipboard.h"

int main(int argc, char* argv[]) 
{                                                                        
    QtSingleApplication app(argc, argv);

    if (app.isRunning())
        return 0;

    app.setApplicationName(CODE_NAME);
    app.setApplicationVersion(APPLICATION_VERSION);
    // TODO: session management testcase
    // http://marc.info/?l=kde-core-devel&m=144832700109449
    // KDEBUG-341930
    // perhaps we need to wait Qt5.9.x to fix it ;-)
    //app.setQuitOnLastWindowClosed(false);

    I18N i18n(TRANSLATIONS_PATH, APPLICATION_ENCODING);
    i18n.translate();

    qmlRegisterType<QwxUUID>("cn.com.isoft.qwx", 1, 0, "QwxUUID");
    qmlRegisterType<Scan>("cn.com.isoft.qwx", 1, 0, "Scan");
    qmlRegisterType<Cookie>("cn.com.isoft.qwx", 1, 0, "Cookie");
    qmlRegisterType<StatReport>("cn.com.isoft.qwx", 1, 0, "StatReport");
    qmlRegisterType<Init>("cn.com.isoft.qwx", 1, 0, "Init");
    qmlRegisterType<Sync>("cn.com.isoft.qwx", 1, 0, "Sync");
    qmlRegisterType<Contact>("cn.com.isoft.qwx", 1, 0, "Contact");
    qmlRegisterType<HeadImg>("cn.com.isoft.qwx", 1, 0, "HeadImg");
    qmlRegisterType<StatusNotify>("cn.com.isoft.qwx", 1, 0, "StatusNotify");
    qmlRegisterType<SendMsg>("cn.com.isoft.qwx", 1, 0, "SendMsg");
    qmlRegisterType<Monitor>("cn.com.isoft.qwx", 1, 0, "Monitor");
    qmlRegisterType<GetMsg>("cn.com.isoft.qwx", 1, 0, "GetMsg");
    qmlRegisterType<CircleImage>("cn.com.isoft.qwx", 1, 0, "CircleImage");
    qmlRegisterType<Process>("cn.com.isoft.qwx", 1, 0, "Process");
    qmlRegisterType<XiaoDouBi>("cn.com.isoft.qwx", 1, 0, "XiaoDouBi");
    qmlRegisterType<ChatLog>("cn.com.isoft.qwx", 1, 0, "ChatLog");
    qmlRegisterType<Emotion>("cn.com.isoft.qwx", 1, 0, "Emotion");
    qmlRegisterType<LogOut>("cn.com.isoft.qwx", 1, 0, "LogOut");
    qmlRegisterType<IpCity>("cn.com.isoft.qwx", 1, 0, "IpCity");
    qmlRegisterType<Weather>("cn.com.isoft.qwx", 1, 0, "Weather");
    qmlRegisterType<Clipboard>("cn.com.isoft.qwx", 1, 0, "Clipboard");

    QQmlApplicationEngine engine(QUrl("qrc:/qml/main.qml")); 
    QObject* topLevel = engine.rootObjects().value(0);
    QQuickWindow* window = qobject_cast<QQuickWindow*>(topLevel); 
    if (!window) {
        qWarning("Error: Your root item has to be a Window.");
        return -1;
    }
    // FIXME: it does not work for KWin 5.7.x
    // https://blog.martin-graesslin.com/blog/2016/07/multi-screen-woes-in-plasma-5-7/
    // Newly opened windows not placed on the primary screen
    window->setScreen(app.primaryScreen());
    window->show();

    return app.exec();
}
