#include "mainwindow.h"

#include <QtWidgets>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

MainWindow::MainWindow():QMainWindow()
{

    this -> resize(800, 500);
    attachWidgets();

    setCentralWidget(this->textField);
    textField -> setMaximumSize(800, 340);
    textField -> setGeometry(400, 400, 100, 100);


    radioDock ->resize(800, 100);
}

void MainWindow::attachWidgets() {


    QMenuBar *menuBar = new QMenuBar;
    QMenu *file = new QMenu;
    QMenu *help = new QMenu;
    QAction *open = new QAction("Open...");
    QAction *end = new QAction("Close Window");
    QAction *save = new QAction("Save");
    open -> setShortcut(QKeySequence::Open);
    save -> setShortcut(QKeySequence::Save);
    end -> setShortcut(QKeySequence::Close);


    QLCDNumber *amChannelDisplay = new QLCDNumber();
    QLCDNumber *fmChannelDisplay = new QLCDNumber();
    QLCDNumber *bassSliderDisplay = new QLCDNumber();
    QLCDNumber *trebleSliderDisplay = new QLCDNumber();
    QRadioButton *amButton = new QRadioButton("AM");
    QRadioButton *fmButton = new QRadioButton("FM");
    QSlider *bassSlider = new QSlider();
    QSlider *trebleSlider = new QSlider();
    QDial *fmRadioDial = new QDial();
    QDial *amRadioDial = new QDial();
    QLabel *trebleLabel = new QLabel("Treble:");
    QLabel *bassLabel = new QLabel("Bass:");
    QLabel *volumeLabel = new QLabel("Volume:");
    QSpinBox *volumeAdjuster = new QSpinBox();
    QPushButton *quit = new QPushButton("Quit");

    file -> addAction(open);
    file -> addAction(save);
    file -> addAction(end);
    help -> addAction("Help...");

    menuBar -> addMenu(file);
    file -> setTitle("File");
    menuBar ->addMenu(help);
    help -> setTitle("Help");

    //  Connect widgets to and displays
    QObject::connect(fmRadioDial, SIGNAL(valueChanged(int)), fmChannelDisplay, SLOT(display(int)));
    QObject::connect(amRadioDial, SIGNAL(valueChanged(int)), amChannelDisplay, SLOT(display(int)));
    QObject::connect(bassSlider, SIGNAL(valueChanged(int)), bassSliderDisplay, SLOT(display(int)));
    QObject::connect(trebleSlider, SIGNAL(valueChanged(int)), trebleSliderDisplay, SLOT(display(int)));

    //  Connect quit button to close action
    QObject::connect(quit, SIGNAL(clicked()), this, SLOT(close()));

    //  Connect menu items to their actions
    QObject::connect(end, SIGNAL(triggered()), this, SLOT(close()));
    QObject::connect(open, SIGNAL(triggered()), this, SLOT(open()));
    QObject::connect(save, SIGNAL(triggered()), this, SLOT(save()));

    //  If amButton is clicked, hide FM options and show AM options
    QObject::connect(amButton, SIGNAL(clicked()), amRadioDial, SLOT(show()));
    QObject::connect(amButton, SIGNAL(clicked()), fmRadioDial, SLOT(hide()));
    QObject::connect(amButton, SIGNAL(clicked()), amChannelDisplay, SLOT(show()));
    QObject::connect(amButton, SIGNAL(clicked()), fmChannelDisplay, SLOT(hide()));

    //  If fmButton is clicked, hide AM options and show FM options
    QObject::connect(fmButton, SIGNAL(clicked()), fmRadioDial, SLOT(show()));
    QObject::connect(fmButton, SIGNAL(clicked()), amRadioDial, SLOT(hide()));
    QObject::connect(fmButton, SIGNAL(clicked()), fmChannelDisplay, SLOT(show()));
    QObject::connect(fmButton, SIGNAL(clicked()), amChannelDisplay, SLOT(hide()));


    //  Set widget options and names
    this -> setWindowTitle("Radio Controls");
    volumeAdjuster -> setRange(0,100);
    volumeAdjuster -> setValue(30);

    fmRadioDial -> setRange(880, 1080);
    fmRadioDial -> setValue(881);
    fmRadioDial -> setNotchTarget(0.1);
    fmRadioDial -> setNotchesVisible(true);

    amRadioDial -> setRange(540, 1600);
    amRadioDial -> setValue(540);
    amRadioDial -> setNotchTarget(10.0);
    amRadioDial -> setNotchesVisible(true);

    fmChannelDisplay -> setSegmentStyle(QLCDNumber::Flat);
    amChannelDisplay -> setSegmentStyle(QLCDNumber::Flat);
    trebleSliderDisplay -> setSegmentStyle(QLCDNumber::Flat);
    bassSliderDisplay -> setSegmentStyle(QLCDNumber::Flat);

    trebleSlider -> setRange(0,10);
    bassSlider -> setRange(0,10);

    bassSlider -> setValue(5);
    trebleSlider ->setValue(5);

    bassSlider -> setTickInterval(1);
    trebleSlider -> setTickInterval(1);


    //  Manually set widget positions
    fmButton -> setParent(this->radioDock);
    fmButton -> setGeometry(20,20, 40, 50);
    fmChannelDisplay -> setParent(this->radioDock);
    fmChannelDisplay -> setGeometry(115, 25, 72, 20);
    fmRadioDial -> setParent(this->radioDock);
    fmRadioDial -> setGeometry(100, 50, 100, 100);

    amButton -> setParent(this->radioDock);
    amButton -> setGeometry(20,60, 40, 50);
    amChannelDisplay -> setParent(this->radioDock);
    amChannelDisplay -> setGeometry(115, 25, 72, 20);
    amRadioDial -> setParent(this->radioDock);
    amRadioDial -> setGeometry(100, 50, 100, 100);

    volumeAdjuster -> setParent(this->radioDock);
    volumeAdjuster -> setGeometry(280, 52, 45, 22);
    volumeLabel -> setParent(this->radioDock);
    volumeLabel -> setGeometry(225, 45, 50, 35);

    bassLabel -> setParent(this->radioDock);
    bassLabel -> setGeometry(365, 45, 50, 35);
    bassSlider -> setParent(this->radioDock);
    bassSlider -> setGeometry (400, 27, 50, 75);
    bassSliderDisplay -> setParent(this->radioDock);
    bassSliderDisplay -> setGeometry(445, 54, 50, 20);

    trebleLabel -> setParent(this->radioDock);
    trebleLabel -> setGeometry(535, 45, 50, 35);
    trebleSlider -> setParent(this->radioDock);
    trebleSlider -> setGeometry (570, 27, 50, 75);
    trebleSliderDisplay -> setParent(this->radioDock);
    trebleSliderDisplay -> setGeometry(620, 54, 50, 20);

    quit -> setParent(this->radioDock);
    quit -> setGeometry(700, 50, 60, 40);

    this -> radioDock -> show();

    fmButton -> click();

    radioDock -> setAllowedAreas(Qt::BottomDockWidgetArea | Qt::RightDockWidgetArea);
    addDockWidget(Qt::BottomDockWidgetArea, radioDock);

}

void MainWindow::open() {
    QString *container = new QString;

    ifstream inFile;
    string fuckThis;
    inFile.open("/Users/Marc/AnotherTest/text.txt");

    while(!inFile.eof()) {

        getline(inFile, fuckThis);
        QString qstr = QString::fromStdString(fuckThis);
        container -> append(qstr + "\n");
        this -> textField->setPlainText(*container);

    }
    inFile.close();
}

void MainWindow::save() {

    QFile outfile;
    outfile.setFileName("/Users/Marc/AnotherTest/text.txt");
    outfile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&outfile);

    out << textField->toPlainText() << endl;

}


