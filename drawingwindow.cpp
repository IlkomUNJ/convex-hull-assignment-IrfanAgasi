#include "drawingwindow.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QWidget>

DrawingWindow::DrawingWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    QVBoxLayout *layout = new QVBoxLayout(central);

    canvas = new DrawingCanvas(this);
    canvas->setMinimumSize(600, 400);

    QPushButton *btnRun = new QPushButton("Run Convex Hull", this);
    QPushButton *btnClear = new QPushButton("Clear", this);

    layout->addWidget(canvas);
    layout->addWidget(btnRun);
    layout->addWidget(btnClear);

    connect(btnRun, &QPushButton::clicked, this, &DrawingWindow::onRunClicked);
    connect(btnClear, &QPushButton::clicked, this, &DrawingWindow::onClearClicked);
}

void DrawingWindow::onRunClicked() {
    canvas->runConvexHull();
}

void DrawingWindow::onClearClicked() {
    canvas->clearCanvas();
}
