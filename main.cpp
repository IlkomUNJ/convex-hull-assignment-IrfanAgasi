#include "drawingwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    DrawingWindow window;
    window.setWindowTitle("Convex Hull Visualization");
    window.show();
    return app.exec();
}
