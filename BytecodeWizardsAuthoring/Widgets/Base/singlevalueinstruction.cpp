#include "singlevalueinstruction.h"

#include <QIntValidator>

SingleValueInstruction::SingleValueInstruction(const QPoint& startPosition, const QString& instructionTitle, QWidget* const parent) : BaseInstructionWidget(startPosition, instructionTitle)
{
    //create a line field with int validator
    lineEdit.setParent(parent);

    lineEdit.setMinimumWidth(LINE_EDIT_WIDTH);
    lineEdit.setMaximumWidth(LINE_EDIT_WIDTH);

    QValidator *validator = new QIntValidator(0, 255, parent);
    lineEdit.setValidator(validator);

    lineEdit.show();

    QObject::connect(&lineEdit, &QLineEdit::textChanged, this, &SingleValueInstruction::Validate);
}

void SingleValueInstruction::Draw(QPainter& painter, int drawOrder)
{
    BaseInstructionWidget::Draw(painter, drawOrder);

    //draw this only on top of lines
    if (drawOrder == 0)
    {
        return;
    }

    QPoint widgetCenter = QPoint(position.x(), position.y() + HEIGHT * 0.5f + MARGIN_TOP);

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

void SingleValueInstruction::Validate(const QString &text)
{
    if (text.isEmpty())
    {
        return;
    }

    int value = text.toInt();

    //clamp and set back to line edit
    value = qBound(0, value, 255);
    lineEdit.setText(QString::number(value));
}
