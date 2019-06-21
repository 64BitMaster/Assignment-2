#include "mainwindow.h"

#include <QtWidgets>

int main(int argc, char **argv)
{
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    QApplication app(argc, argv);

    MainWindow *mainWin = new MainWindow();

    mainWin->show();

    return app.exec();
}
