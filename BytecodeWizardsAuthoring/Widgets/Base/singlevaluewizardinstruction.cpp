#include "singlevaluewizardinstruction.h"

#include <QIntValidator>

SingleValueWizardInstruction::SingleValueWizardInstruction(const QPoint& startPosition, const QString& instructionTitle, QWidget* const parent) : WizardInstruction(startPosition, instructionTitle, parent)
{
    //create a line field with int validator
    lineEdit.setParent(parent);

    lineEdit.setMinimumWidth(LINE_EDIT_WIDTH);
    lineEdit.setMaximumWidth(LINE_EDIT_WIDTH);

    QValidator *validator = new QIntValidator(0, 255, parent);
    lineEdit.setValidator(validator);

    lineEdit.show();

    //extra line edit make widget bigger
    HEIGHT = 80;
    MARGIN_TOP = 0;
}

void SingleValueWizardInstruction::Draw(QPainter& painter)
{
    WizardInstruction::Draw(painter);

    QPoint widgetCenter = QPoint(position.x(), position.y() + HEIGHT * 0.5f + MARGIN_TOP_TEXT);

    //write amount label
    QFont sizedFont = painter.font();
    sizedFont.setPointSize(FONT_SIZE);
    sizedFont.setBold(false);

    painter.setFont(sizedFont);

    QFontMetrics fontMetrics(sizedFont);

    QPoint textPosition(widgetCenter.x(), widgetCenter.y());
    float textHeight = fontMetrics.size(Qt::TextSingleLine, AMOUNT_TEXT).height();

    textPosition += QPoint(MARGIN_LEFT_TEXT, textHeight * 0.5f);
    painter.drawText(textPosition, AMOUNT_TEXT);

    widgetCenter += QPoint(MARGIN_LEFT_LINE_EDIT, -lineEdit.height() * 0.5f + MARGIN_TOP_LINE_EDIT);
    lineEdit.move(widgetCenter);
}
