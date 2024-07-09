#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // 这是构造函数,初始化窗口.
    ui->setupUi(this);
    setWindowTitle("聊天室");

    sender = new QUdpSocket(this);
    receiver = new QUdpSocket(this);
    receiver->bind(5555, QUdpSocket::ShareAddress);
    // 槽机制, 如果receiver监听的端口里面有readyRead()这个信号过来,就调用this里面的槽函数,槽函数ReadMessage要定义在private slots中.
    connect(receiver, SIGNAL(readyRead()), this, SLOT(ReadMessage()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::ReadMessage()
{
    while (receiver->hasPendingDatagrams()) // 等待数据
    {
        QByteArray datagram;
        datagram.resize(receiver->pendingDatagramSize()); // 指定接收大小
        receiver->readDatagram(datagram.data(), datagram.size());
        text2.clear();
        text2.prepend(datagram);
        ui->label->setText(text2);
    }
}

void MainWindow::SendMessage()
{
    text1 = ui->textEdit->toPlainText();
    QByteArray datagram = text1.toUtf8();
    sender->writeDatagram(datagram.data(), datagram.size(), QHostAddress("127.0.0.1"), 6666);

}


void MainWindow::on_pushButton_clicked()
{
    SendMessage();
}
