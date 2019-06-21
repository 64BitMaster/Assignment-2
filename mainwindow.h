#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>

class ToolBar;
QT_FORWARD_DECLARE_CLASS(QMenu)

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    typedef QMap<QString, QSize> CustomSizeHintMap;
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
