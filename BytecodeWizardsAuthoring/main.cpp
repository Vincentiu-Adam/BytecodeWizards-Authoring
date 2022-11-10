#include "authoringwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    AuthoringWindow w;
    w.show();

    return a.exec();
}
