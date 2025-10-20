#include "drawingcanvas.h"
#include <filesystem>

DrawingCanvas::DrawingCanvas(QWidget *parent)  {
    // Set a minimum size for the canvas
    setMinimumSize(this->WINDOW_WIDTH, this->WINDOW_HEIGHT);
    // Set a solid background color
    setStyleSheet("background-color: white; border: 1px solid gray;");
}

void DrawingCanvas::clearPoints(){
    m_points.clear();
    // Trigger a repaint to clear the canvas
    update();
}

void DrawingCanvas::paintLines(){
    /* Todo
     * Implement lines drawing per even pair
    */

    isPaintLinesClicked = true;
    update();
}

void DrawingCanvas::segmentDetection(){
    QPixmap pixmap = this->grab(); //
    QImage image = pixmap.toImage();

    cout << "image width " << image.width() << endl;
    cout << "image height " << image.height() << endl;

    const int windowSize = 10;
    const int maxX = image.width() - windowSize;
    const int maxY = image.height() - windowSize;

    for (int i = 0; i <= maxX; i++)
    {
        for (int j = 0; j <= maxY; j++)
        {
            QVector<QVector<bool>> local_window(windowSize, QVector<bool>(windowSize, false));
            bool isEmpty = true;
            for (int m = 0; m < windowSize; m++)
            {
                for (int n = 0; n < windowSize; n++)
                {
                    QRgb rgbValue = image.pixel(i + m, j + n);
                    bool pixelOn = (rgbValue != 0xffffffff);
                    local_window[m][n] = pixelOn;
                    if (pixelOn)
                    {
                        isEmpty = false;
                    }
                }
            }

            if (!isEmpty)
            {
                cout << "Window at position (" << i << ", " << j << "):" << endl;
                for (int m = 0; m < windowSize; m++)
                {
                    for (int n = 0; n < windowSize; n++)
                    {
                        cout << (local_window[m][n] ? "1" : "0") << " ";
                    }
                    cout << endl;
                }
                cout << endl;
            }
        }
    }

    return;
}

// Implementasi kode dari Gemini
// void DrawingCanvas::segmentDetection(){
//     QPixmap pixmap = this->grab();
//     QImage image = pixmap.toImage();

//     const QList<QPair<int, int>> windowSizes = {{3, 3}, {5, 5}, {7, 7}, {10, 10}, {20, 20}, {50, 50}, {100, 100}};

//     for (const auto &size : windowSizes) {
//         const int windowWidth = size.first;
//         const int windowHeight = size.second;

//         QString dirName = QString("output_w%1_h%2").arg(windowWidth).arg(windowHeight);
//         const std::filesystem::path dirPath = dirName.toStdString();
//         if (!std::filesystem::exists(dirPath)) {
//             std::filesystem::create_directories(dirPath);
//         }

//         const int maxX = image.width() - windowWidth;
//         const int maxY = image.height() - windowHeight;
//         if (maxX < 0 || maxY < 0) {
//             continue;
//         }

//         int strideX = windowWidth / 2;
//         int strideY = windowHeight / 2;
//         if (strideX < 1) {
//             strideX = 1;
//         }
//         if (strideY < 1) {
//             strideY = 1;
//         }

//         int windowCount = 0;
//         for (int j = 0; j <= maxY; j += strideY) {
//             for (int i = 0; i <= maxX; i += strideX) {
//                 bool isEmpty = true;
//                 for (int y = j; y < j + windowHeight && isEmpty; ++y) {
//                     for (int x = i; x < i + windowWidth; ++x) {
//                         if (image.pixel(x, y) != 0xffffffff) {
//                             isEmpty = false;
//                             break;
//                         }
//                     }
//                 }

//                 if (!isEmpty) {
//                     QRect windowRect(i, j, windowWidth, windowHeight);
//                     QImage windowImage = image.copy(windowRect);
//                     QString fileName = QString("%1/window_%2.png").arg(dirName).arg(windowCount++);
//                     windowImage.save(fileName);
//                 }
//             }
//         }

//         Q_UNUSED(windowCount);
//     }
// }

void DrawingCanvas::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Set up the pen and brush for drawing the points
    QPen pen(Qt::blue, 5);
    painter.setPen(pen);
    painter.setBrush(QBrush(Qt::blue));

    // Draw a small circle at each stored point
    for (const QPoint& point : std::as_const(m_points)) {
        painter.drawEllipse(point, 3, 3);
    }

    if(isPaintLinesClicked){
        cout << "paint lines block is called" << endl;
        pen.setColor(Qt::red);
        pen.setWidth(4); // 4-pixel wide line
        pen.setStyle(Qt::SolidLine);
        painter.setPen(pen);

        // Set the painter's pen to our custom pen.
        painter.setPen(pen);

        for(int i=0;i<m_points.size()-1;i+=2){
            //cout << m_points[i].x() << endl;
            painter.drawLine(m_points[i], m_points[i+1]);
        }
        isPaintLinesClicked = false;

        //return painter pen to blue
        pen.setColor(Qt::blue);
        painter.setPen(pen);
    }
}

void DrawingCanvas::mousePressEvent(QMouseEvent *event) {
    // Add the mouse click position to our vector of points
    m_points.append(event->pos());
    // Trigger a repaint
    update();
}


