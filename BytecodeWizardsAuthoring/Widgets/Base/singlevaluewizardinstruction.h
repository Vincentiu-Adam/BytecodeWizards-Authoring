#ifndef SINGLEVALUEWIZARDINSTRUCTION_H
#define SINGLEVALUEWIZARDINSTRUCTION_H

#include "wizardinstruction.h"

#include <QLineEdit>

class SingleValueWizardInstruction : public WizardInstruction
{
public:
    SingleValueWizardInstruction(const QPoint& startPosition, const QString& instructionTitle, QWidget* const parent);

    void Draw(QPainter& painter) override;

protected:
    QString AMOUNT_TEXT = "Amount :";

    inline int GetAmountValue() { return lineEdit.text().toInt(); }

private:
    const int       LINE_EDIT_WIDTH         = 32;
    const int       MARGIN_LEFT_TEXT        = 15;
    const int       MARGIN_LEFT_LINE_EDIT   = 70;
    const int       MARGIN_TOP_TEXT         = 24;
    const int       MARGIN_TOP_LINE_EDIT    = 2;

    QLineEdit lineEdit;
};

#endif // SINGLEVALUEWIZARDINSTRUCTION_H
