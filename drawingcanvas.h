#ifndef DRAWINGCANVAS_H
#define DRAWINGCANVAS_H

#include <QWidget>
#include <QVector>
#include <QPointF>

class DrawingCanvas : public QWidget
{
    Q_OBJECT

public:
    explicit DrawingCanvas(QWidget *parent = nullptr);
    int getTotalDots() const { return totalDots; }

    void clearCanvas();
    void runConvexHull();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    QVector<QPointF> points;
    QVector<QPointF> hull;
    int iterationsSlow;
    int iterationsFast;
    int totalDots;

    QVector<QPointF> slowConvexHull(const QVector<QPointF> &pts, int &iterationCount);
    QVector<QPointF> fastConvexHull(const QVector<QPointF> &pts, int &iterationCount);
    int orientation(const QPointF &p, const QPointF &q, const QPointF &r);
};

#endif // DRAWINGCANVAS_H
