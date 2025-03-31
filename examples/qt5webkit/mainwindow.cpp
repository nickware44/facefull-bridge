#include <iostream>
#include <QDir>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow) {
    ui -> setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);

    std::cout << "WebKit version: " << qWebKitVersion().toStdString() << std::endl;

    MainLayout = new QVBoxLayout();
    MainLayout -> addSpacing(0);
    MainLayout -> setContentsMargins(0, 0, 0, 0);
    WebView = new QWebView(this);
    MainLayout -> addWidget(WebView);
    MainWidget = new QWidget();
    MainWidget -> setLayout(MainLayout);
    setCentralWidget(MainWidget);

    auto respath = "qrc:/ui/index.html";
    Bridge = new FacefullBridgeQt5WebKit(this, WebView, QUrl(QString::fromStdString(respath)));

    std::cout << "Window loaded" << std::endl;

    Bridge -> doEventAttach("onTestMessage", [this](const std::string& data) {
        std::cout << data << std::endl;
    });

    Bridge -> doEventAttach("doWindowReady", [this](const std::string& data) {
        Bridge -> doEventSend("doTestMessage", "Bridge event system test message");
    });
}

void MainWindow::doBridgeEventReceive(const QString &data) const {
    Bridge -> doEventCatch(data.toStdString());
}

bool MainWindow::eventFilter(QObject* object, QEvent* event) {
    Bridge -> doMoveWindow((QMouseEvent*)event);
    return false;
}

MainWindow::~MainWindow() {
    delete ui;
}
