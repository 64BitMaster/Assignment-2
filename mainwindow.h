#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>

class MainWindow:public QMainWindow {
    Q_OBJECT

public:
    QTextEdit *textField = new QTextEdit;
    QDockWidget *radioDock = new QDockWidget(this);

    explicit MainWindow();
    void attachWidgets();

public slots:
    void open();
    void save();

private:

};

#endif // MAINWINDOW_H
