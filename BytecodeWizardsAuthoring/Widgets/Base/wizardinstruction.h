#ifndef WIZARDINSTRUCTION_H
#define WIZARDINSTRUCTION_H

#include "baseinstructionwidget.h"

#include <QComboBox>

class WizardInstruction : public BaseInstructionWidget
{
public:
    WizardInstruction(const QPoint& startPosition, const QString& instructionTitle, QWidget* const parent);

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

#endif // WIZARDINSTRUCTION_H
