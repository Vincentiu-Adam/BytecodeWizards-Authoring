#ifndef VALUEINSTRUCTION_H
#define VALUEINSTRUCTION_H

#include "baseinstructionwidget.h"

#include <QComboBox>

class ValueInstruction : public BaseInstructionWidget
{
public:
    ValueInstruction(const QPoint& startPosition, const QString& instructionTitle, QWidget* const parent);

    void Draw(QPainter& painter) override;

    void Generate(QByteArray& bytecode) override;

protected:
    const int FONT_SIZE = 8;

    int MARGIN_TOP = 5;

private:
    const int       MARGIN_LEFT_TEXT    = 15;
    const int       MARGIN_LEFT_COMBO   = 70;
    const int       MARGIN_TOP_COMBO    = 2;
    const QString   WIZARD_ID_TEXT      = "Wizard ID :";

    QComboBox comboBox;
};

#endif // VALUEINSTRUCTION_H
