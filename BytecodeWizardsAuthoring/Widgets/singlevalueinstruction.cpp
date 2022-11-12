#include "singlevalueinstruction.h"

#include <QIntValidator>

SingleValueInstruction::SingleValueInstruction(const QPoint& startPosition, const QString& instructionTitle, QWidget* const parent) : BaseInstructionWidget(startPosition, instructionTitle)
{
    //create a line field with int validator
    lineEdit.setParent(parent);

    lineEdit.setMinimumWidth(LINE_EDIT_WIDTH);
    lineEdit.setMaximumWidth(LINE_EDIT_WIDTH);

    QValidator *validator = new QIntValidator(100, 999, parent);
    lineEdit.setValidator(validator);

    lineEdit.show();
}

void SingleValueInstruction::Generate(QByteArray& bytecode)
{

}

void SingleValueInstruction::Draw(QPainter& painter)
{
    BaseInstructionWidget::Draw(painter);

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