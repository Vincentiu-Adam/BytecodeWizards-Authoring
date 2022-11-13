#ifndef SINGLEVALUEINSTRUCTION_H
#define SINGLEVALUEINSTRUCTION_H

#include "baseinstructionwidget.h"

#include <QLineEdit>

class SingleValueInstruction : public QObject, public BaseInstructionWidget
{
    Q_OBJECT

public:
    SingleValueInstruction(const QPoint& startPosition, const QString& instructionTitle, QWidget* const parent);

    void Draw(QPainter& painter) override;

protected:
    inline int GetValue() { return lineEdit.text().toInt(); }
    inline bool IsEmpty() { return lineEdit.text().isEmpty(); }

private:
    const int       FONT_SIZE               = 8;
    const int       LINE_EDIT_WIDTH         = 32;
    const int       MARGIN_LEFT_TEXT        = 15;
    const int       MARGIN_LEFT_LINE_EDIT   = 70;
    const int       MARGIN_TOP              = 5;
    const int       MARGIN_TOP_LINE_EDIT    = 2;
    const QString   AMOUNT_TEXT             = "Amount :";

    QLineEdit lineEdit;

private slots:
    void Validate(const QString &text);
};

#endif // SINGLEVALUEINSTRUCTION_H
