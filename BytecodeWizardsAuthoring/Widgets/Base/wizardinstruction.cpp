#include "wizardinstruction.h"

WizardInstruction::WizardInstruction(const QPoint& startPosition, const QString& instructionTitle, QWidget* const parent) : BaseInstructionWidget(startPosition, instructionTitle)
{
    //create a combo box and set it to 0 and 1
    comboBox.setParent(parent);

    comboBox.addItem("0");
    comboBox.addItem("1");

    comboBox.show();
}

void WizardInstruction::Generate(QByteArray& bytecode)
{
    bytecode.append(0x0B);
}

void WizardInstruction::Draw(QPainter& painter, int drawOrder)
{
    BaseInstructionWidget::Draw(painter, drawOrder);

    QPoint widgetCenter = QPoint(position.x(), position.y() + HEIGHT * 0.5f + MARGIN_TOP);

    //write text label
    QFont sizedFont = painter.font();
    sizedFont.setPointSize(FONT_SIZE);
    sizedFont.setBold(false);

    painter.setFont(sizedFont);

    QFontMetrics fontMetrics(sizedFont);

    QPoint textPosition(widgetCenter.x(), widgetCenter.y());
    float textHeight = fontMetrics.size(Qt::TextSingleLine, WIZARD_ID_TEXT).height();

    textPosition += QPoint(MARGIN_LEFT_TEXT, textHeight * 0.5f);
    painter.drawText(textPosition, WIZARD_ID_TEXT);

    widgetCenter += QPoint(MARGIN_LEFT_COMBO, -comboBox.height() * 0.5f + MARGIN_TOP_COMBO);
    comboBox.move(widgetCenter);
}
