#include "imagerender.h"

#include <QImage>
#include <QByteArray>

#include <iostream>

void ImageRenderer::render(
    const std::string& ImageData,
    int MaxColumns,
    int MaxRows
    )
{
    (void)MaxRows;

    QImage Image;

    if (!Image.loadFromData(
            reinterpret_cast<const uchar*>(ImageData.data()),
            static_cast<int>(ImageData.size())
            ))
    {
        std::cerr << "Failed to decode image.\n";
        return;
    }

    int TargetWidth = MaxColumns;

    int TargetHeight =
        static_cast<int>(
            (static_cast<double>(Image.height()) / Image.width()) * TargetWidth
            );

    QImage Scaled =
        Image.scaled(
                 TargetWidth,
                 TargetHeight,
                 Qt::IgnoreAspectRatio,
                 Qt::SmoothTransformation
                 ).convertToFormat(QImage::Format_RGB32);

    for (int Y = 0; Y < Scaled.height() - 1; Y += 2)
    {
        for (int X = 0; X < Scaled.width(); ++X)
        {
            QRgb TopPixel = Scaled.pixel(X, Y);
            QRgb BottomPixel = Scaled.pixel(X, Y + 1);

            std::cout
                << "\x1b[38;2;"
                << qRed(TopPixel) << ";"
                << qGreen(TopPixel) << ";"
                << qBlue(TopPixel) << "m"
                << "\x1b[48;2;"
                << qRed(BottomPixel) << ";"
                << qGreen(BottomPixel) << ";"
                << qBlue(BottomPixel) << "m"
                << "\u2580";
        }

            std::cout << "\x1b[H";
    }
}