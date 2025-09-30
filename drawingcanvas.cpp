#include "drawingcanvas.h"
#include <QPainter>
#include <QMouseEvent>
#include <algorithm>
#include <QPainterPath>

DrawingCanvas::DrawingCanvas(QWidget *parent)
    : QWidget(parent), iterationsSlow(0), iterationsFast(0), totalDots(0) {
    setStyleSheet("background-color: white;");
}

void DrawingCanvas::clearCanvas() {
    points.clear();
    hull.clear();
    iterationsSlow = iterationsFast = 0;
    totalDots = 0;
    update();
}

void DrawingCanvas::mousePressEvent(QMouseEvent *event) {
    points.push_back(event->pos());
    totalDots = points.size();
    update();
}

void DrawingCanvas::runConvexHull() {
    hull.clear();
    iterationsSlow = iterationsFast = 0;
    if (points.size() < 3) return;

    QVector<QPointF> hullSlow = slowConvexHull(points, iterationsSlow);
    QVector<QPointF> hullFast = fastConvexHull(points, iterationsFast);

    // Gunakan hasil hull cepat untuk ditampilkan
    hull = hullFast;
    update();
}

// -------- Slow Convex Hull O(n^3) --------
QVector<QPointF> DrawingCanvas::slowConvexHull(const QVector<QPointF> &pts, int &iterationCount) {
    QVector<QPointF> hullEdges;
    iterationCount = 0;
    int n = pts.size();

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) continue;
            bool valid = true;
            for (int k = 0; k < n; k++) {
                if (k == i || k == j) continue;
                iterationCount++;
                if (orientation(pts[i], pts[j], pts[k]) == 2) { // left turn
                    valid = false;
                    break;
                }
            }
            if (valid) {
                hullEdges.push_back(pts[i]);
                hullEdges.push_back(pts[j]);
            }
        }
    }

    // Urutkan hasil edge jadi poligon
    std::sort(hullEdges.begin(), hullEdges.end(),
              [](const QPointF &a, const QPointF &b) {
                  return (a.x() < b.x()) || (a.x() == b.x() && a.y() < b.y());
              });
    return hullEdges;
}

// -------- Fast Convex Hull (Monotone Chain O(n log n)) --------
QVector<QPointF> DrawingCanvas::fastConvexHull(const QVector<QPointF> &pts, int &iterationCount) {
    QVector<QPointF> p = pts;
    iterationCount = 0;

    std::sort(p.begin(), p.end(), [](const QPointF &a, const QPointF &b) {
        return (a.x() < b.x()) || (a.x() == b.x() && a.y() < b.y());
    });

    QVector<QPointF> lower, upper;
    for (const QPointF &pt : p) {
        while (lower.size() >= 2 && orientation(lower[lower.size()-2], lower.last(), pt) != 1) {
            lower.pop_back();
            iterationCount++;
        }
        lower.push_back(pt);
    }
    for (int i = p.size() - 1; i >= 0; i--) {
        while (upper.size() >= 2 && orientation(upper[upper.size()-2], upper.last(), p[i]) != 1) {
            upper.pop_back();
            iterationCount++;
        }
        upper.push_back(p[i]);
    }
    lower.pop_back();
    upper.pop_back();
    lower += upper;
    return lower;
}

int DrawingCanvas::orientation(const QPointF &p, const QPointF &q, const QPointF &r) {
    double val = (q.y() - p.y()) * (r.x() - q.x()) -
                 (q.x() - p.x()) * (r.y() - q.y());
    if (val == 0) return 0; // collinear
    return (val > 0) ? 1 : 2; // 1 = clockwise, 2 = counterclockwise
}

// -------- Paint Event --------
void DrawingCanvas::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Gambar titik
    painter.setBrush(Qt::blue);
    for (const QPointF &p : points) {
        painter.drawEllipse(p, 3, 3);
    }

    // Gambar hull
    if (!hull.isEmpty()) {
        QPainterPath path;
        path.moveTo(hull[0]);
        for (int i = 1; i < hull.size(); i++) {
            path.lineTo(hull[i]);
        }
        path.closeSubpath();

        // Fill transparan
        QColor fillColor(0, 255, 0, 20); // hijau, alpha 80 (0-255)
        painter.fillPath(path, QBrush(fillColor));

        // Gambar garis tepi hull
        painter.setPen(QPen(Qt::green, 2));
        for (int i = 0; i < hull.size(); i++) {
            painter.drawLine(hull[i], hull[(i+1) % hull.size()]);
        }
    }

    // Gambar info iterasi
    painter.setPen(Qt::white);
    painter.drawText(10, 20, QString("Total dots: %1").arg(totalDots));
    painter.drawText(10, 40, QString("Slow Convex Hull iterations: %1").arg(iterationsSlow));
    painter.drawText(10, 60, QString("Fast Convex Hull iterations: %1").arg(iterationsFast));
}
