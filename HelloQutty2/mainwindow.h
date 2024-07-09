#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void SendMessage();

private slots:
    void ReadMessage();
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QString text1;
    QString text2;
    QUdpSocket *sender;
    QUdpSocket *receiver;
};
#endif // MAINWINDOW_H
