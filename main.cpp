#include <iostream>

#include "widget.h"

#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>

int main(int argc, char *argv[]) {
    QApplication application(argc, argv);

    QTranslator qtTranslator;
    qtTranslator.load("qt_" + QLocale::system().name(),
            QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    application.installTranslator(&qtTranslator);

    QTranslator myappTranslator;
    myappTranslator.load("myapp_" + QLocale::system().name());
    application.installTranslator(&myappTranslator);

    Widget widget;
    widget.show();

    return application.exec();
}
