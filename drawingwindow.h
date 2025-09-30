#ifndef DRAWINGWINDOW_H
#define DRAWINGWINDOW_H

#include <QMainWindow>
#include "drawingcanvas.h"

class DrawingWindow : public QMainWindow
{
    Q_OBJECT

public:
    DrawingWindow(QWidget *parent = nullptr);

private slots:
    void onRunClicked();
    void onClearClicked();

private:
    DrawingCanvas *canvas;
};

#endif // DRAWINGWINDOW_H
