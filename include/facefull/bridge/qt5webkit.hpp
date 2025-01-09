/////////////////////////////////////////////////////////////////////////////
// Name:
// Purpose:
// Author:      Nickolay Babbysh
// Created:     03.01.2025
// Copyright:   (c) NickWare Group
// Licence:     MIT licence
/////////////////////////////////////////////////////////////////////////////

#ifndef FACEFULL_BRIDGE_QT5WEBKIT_HPP
#define FACEFULL_BRIDGE_QT5WEBKIT_HPP

#ifndef __WIN32__
#include <facefull/bridge/interface.h>
#include <iostream>
#include <QMainWindow>
#include <QtWebKitWidgets/QWebView>
#include <QtWebKitWidgets/QWebPage>
#include <QtWebKitWidgets/QWebFrame>

class FacefullBridgeQt5WebKit : public FacefullBridgeInterface {
private:
    QMainWindow *Frame;
    QWebView *WebView;
    bool CaptureFlag;

    void WebViewCommandExecutor(const std::string &data) override {
        auto frame = WebView->page()->mainFrame();
        frame -> evaluateJavaScript(QString::fromStdString(data));
    }

    void onWindowMaximize() override {
        if (isMaximized()) Frame -> setWindowState(Qt::WindowNoState);
        else Frame -> setWindowState(Qt::WindowMaximized);
    }

    void onWindowMinimize() override {
        Frame -> setWindowState(Frame->windowState() | Qt::WindowMinimized);
    }

    void onWindowMove() override {

    }

    void doEventSend(const std::string& comm, const std::string &data) override {
        QMetaObject::invokeMethod((QMainWindow*)Frame
                , "BridgeEventHandler"
                , Qt::AutoConnection
                , Q_ARG(QString, QString::fromStdString(comm)), Q_ARG(QString, QString::fromStdString(data)));
    }

    void onWindowReady() override {
//        Frame -> show();
    }

    void onWindowClose() override {
        Frame -> hide();
        exit(0);
    }

public:
    FacefullBridgeQt5WebKit(QMainWindow *frame, QWebView *webview, const QUrl& window) {
        Frame = frame;
        WebView = webview;

        QObject::connect(WebView, SIGNAL(titleChanged(const QString&)), Frame, SLOT(doBridgeEventReceive(const QString&)));

        webview -> setUrl(window);
        webview -> page() -> mainFrame() -> addToJavaScriptWindowObject("bridge", (QMainWindow*)Frame);
    }

    void setWebView(QWebView *webview) {
        WebView = webview;
    }

    bool isMaximized() {
        return Frame -> windowState() == Qt::WindowMaximized;
    }
};
#endif

#endif //FACEFULL_BRIDGE_QT5WEBKIT_HPP
