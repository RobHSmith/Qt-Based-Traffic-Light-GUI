#include <QApplication>
#include "mainwindow.h"

//! Creates a MainWindow and shows it
int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    MainWindow w;
    w.show();

    return a.exec();
    return 0; //success
}
//!
