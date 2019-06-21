#include "mainwindow.h"

#include <QtWidgets>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

MainWindow::MainWindow():QMainWindow() {

    this -> setWindowTitle("Radio Controls");
    this -> resize(800, 500);

    setCentralWidget(this -> textField);
    attachWidgets();

    textField -> setMaximumSize(800, 340);
    textField -> setGeometry(400, 400, 100, 100);

    radioDock -> resize(800, 100);
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

    QLCDNumber *amChannelDisplay = new QLCDNumber(this -> radioDock);
    QLCDNumber *fmChannelDisplay = new QLCDNumber(this -> radioDock);
    QLCDNumber *bassSliderDisplay = new QLCDNumber(this -> radioDock);
    QLCDNumber *trebleSliderDisplay = new QLCDNumber(this -> radioDock);
    QRadioButton *amButton = new QRadioButton("AM", this -> radioDock);
    QRadioButton *fmButton = new QRadioButton("FM", this -> radioDock);
    QSlider *bassSlider = new QSlider(this -> radioDock);
    QSlider *trebleSlider = new QSlider(this -> radioDock);
    QDial *fmRadioDial = new QDial(this -> radioDock);
    QDial *amRadioDial = new QDial(this -> radioDock);
    QLabel *trebleLabel = new QLabel("Treble:", this -> radioDock);
    QLabel *bassLabel = new QLabel("Bass:", this -> radioDock);
    QLabel *volumeLabel = new QLabel("Volume:", this -> radioDock);
    QSpinBox *volumeAdjuster = new QSpinBox(this -> radioDock);
    QPushButton *quit = new QPushButton("Quit", this -> radioDock);

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
    fmButton -> setGeometry(20, 20, 40, 50);
    fmChannelDisplay -> setGeometry(115, 25, 72, 20);
    fmRadioDial -> setGeometry(100, 50, 100, 100);

    amButton -> setGeometry(20,60, 40, 50);
    amChannelDisplay -> setGeometry(115, 25, 72, 20);
    amRadioDial -> setGeometry(100, 50, 100, 100);

    volumeAdjuster -> setGeometry(280, 52, 45, 22);
    volumeLabel -> setGeometry(225, 45, 50, 35);

    bassLabel -> setGeometry(365, 45, 50, 35);
    bassSlider -> setGeometry (400, 27, 50, 75);
    bassSliderDisplay -> setGeometry(445, 54, 50, 20);

    trebleLabel -> setGeometry(535, 45, 50, 35);
    trebleSlider -> setGeometry (570, 27, 50, 75);
    trebleSliderDisplay -> setGeometry(620, 54, 50, 20);

    quit -> setGeometry(700, 50, 60, 40);

    this -> radioDock -> show();

    fmButton -> click();

    radioDock -> setAllowedAreas(Qt::BottomDockWidgetArea | Qt::RightDockWidgetArea);
    addDockWidget(Qt::BottomDockWidgetArea, radioDock);

}

void MainWindow::open() {

    QString *container = new QString;
    ifstream inFile;
    string killme;
    inFile.open("/Users/Marc/Radio/text.txt");

    while(!inFile.eof()) {

        getline(inFile, killme);
        QString qstr = QString::fromStdString(killme);
        container -> append(qstr + "\n");
        this -> textField -> setPlainText(*container);
    }

    inFile.close();
}

void MainWindow::save() {

    QFile outfile;
    outfile.setFileName("/Users/Marc/Radio/text.txt");
    outfile.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream out(&outfile);

    out << textField->toPlainText() << endl;

}
