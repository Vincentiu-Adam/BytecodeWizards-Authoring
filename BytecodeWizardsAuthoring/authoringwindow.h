#ifndef AUTHORINGWINDOW_H
#define AUTHORINGWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class AuthoringWindow; }
QT_END_NAMESPACE

class AuthoringWindow : public QMainWindow
{
    Q_OBJECT

public:
    AuthoringWindow(QWidget *parent = nullptr);
    ~AuthoringWindow();

private:
    Ui::AuthoringWindow *ui;
};
#endif // AUTHORINGWINDOW_H
