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

#ifdef __WIN32__
#include <facefull/bridge/interface.h>
#include <iostream>
#include <QMainWindow>
#include <QtWebKitWidgets/QWebView>
#include <QtWebKitWidgets/QWebPage>
#include <QtWebKitWidgets/QWebFrame>

class FacefullBridgeQt5WebKit : public FacefullBridgeInterface {
private:
    QMainWindow *Frame;
    QWebView *Window;
    bool CaptureFlag;

    void WebViewCommandExecutor(const std::string &data) override {
        auto frame = Window->page()->mainFrame();
        frame -> evaluateJavaScript(data);
    }

    void onEventReceive(const QString &event) {
//        if (!WebView) return;
        doEventCatch(event);
    }

    void onWindowMinimize() override {
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
        ExitProcess(0);
    }

public:
    FacefullBridgeQt5WebKit(QMainWindow *frame, QWebView *webview, const std::string& window) {
        Frame = frame;
        WebView = webview;

        connect(webview, SIGNAL(titleChanged(const QString&)), this, SLOT(onEventReceive(const QString&)));

        webview -> setUrl(QUrl(QString::fromStdString(window)));
        webview -> page() -> mainFrame() -> addToJavaScriptWindowObject("bridge", (QMainWindow*)frame);
    }

    void setWebView(QWebView *webview) {
        WebView = webview;
    }

    bool isMaximized() {
//        return WindowSize != Frame->GetClientRect();
    }
};
#endif

#endif //FACEFULL_BRIDGE_QT5WEBKIT_HPP
