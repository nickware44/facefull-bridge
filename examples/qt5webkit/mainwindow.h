#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <facefull/bridge/qt5webkit.hpp>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    QVBoxLayout *MainLayout;
    QWidget *MainWidget;
    QWebView *WebView;
    FacefullBridgeQt5WebKit *Bridge;
protected:
    bool eventFilter(QObject* object, QEvent* event) override;

public slots:
    void doBridgeEventReceive(const QString&) const;
signals:
    void BridgeEventHandler(QString, QString);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
};

#endif //MAINWINDOW_H
