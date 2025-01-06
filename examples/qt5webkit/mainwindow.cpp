#include <iostream>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::MainWindow) {
    ui -> setupUi(this);

    std::cout << "WebKit version: " << qWebKitVersion().toStdString() << std::endl;

    MainLayout = new QVBoxLayout();
    MainLayout -> addSpacing(0);
    MainLayout -> setContentsMargins(0, 0, 0, 0);
    WebView = new QWebView(this);
    MainLayout -> addWidget(webview);
    MainWidget = new QWidget();
    MainWidget -> setLayout(MainLayout);
    setCentralWidget(MainWidget);

    Bridge = new FacefullBridgeQt5WebKit(this, WebView, "../ui/window.html");

    std::cout << "Window loaded" << std::endl;

    Bridge -> doEventAttach("doWindowReady", [this](const std::string& data) {
        show();
    });
}

MainWindow::~MainWindow() {
    delete ui;
}
