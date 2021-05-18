//
// Created by danie on 20.04.2021.
//

#ifndef PROIECT_FIGURE_H
#define PROIECT_FIGURE_H

#include <QPixmap>
#include <QWidget>
#include <QPaintEvent>
#include <Square.h>
#include <SquareTexture.h>
#include <Util.h>
//#include <Board.h>
#include <Figure.h>
#include <string>

class Figure : public QWidget {
    Q_OBJECT
public:
    constexpr static int SQUARE_COUNT = 4;
//    explicit Figure (QWidget * parent) noexcept : QWidget(parent) { }

    virtual void drawFigure (int x, int y, Square ** & boardMatrix) noexcept (false);
    virtual QPixmap * getSquareTexture () const noexcept = 0;
    virtual const char * toString () noexcept = 0;
    virtual int rotationCount () const noexcept = 0;
    virtual int const * xOffsetsForRotation (int) const noexcept = 0;
    virtual int const * yOffsetsForRotation (int) const noexcept = 0;

    ~Figure () noexcept override = default;
};

#endif //PROIECT_FIGURE_H
