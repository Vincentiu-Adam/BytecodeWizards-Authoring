#ifndef SINGLEVALUEINSTRUCTION_H
#define SINGLEVALUEINSTRUCTION_H

#include "baseinstructionwidget.h"

#include <QLineEdit>

class SingleValueInstruction : public BaseInstructionWidget
{
public:
    SingleValueInstruction(const QPoint& startPosition, const QString& instructionTitle, QWidget* const parent);

    void Draw(QPainter& painter) override;

    void Generate(QByteArray& bytecode) override;

private:
    const int       FONT_SIZE               = 8;
    const int       LINE_EDIT_WIDTH         = 32;
    const int       MARGIN_LEFT_TEXT        = 15;
    const int       MARGIN_LEFT_LINE_EDIT   = 70;
    const int       MARGIN_TOP              = 5;
    const int       MARGIN_TOP_LINE_EDIT    = 2;
    const QString   AMOUNT_TEXT             = "Amount :";

    QLineEdit lineEdit;
};

#endif // SINGLEVALUEINSTRUCTION_H
