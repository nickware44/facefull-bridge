/////////////////////////////////////////////////////////////////////////////
// Name:
// Purpose:
// Author:      Nickolay Babbysh
// Created:     02.01.2025
// Copyright:   (c) NickWare Group
// Licence:     MIT licence
/////////////////////////////////////////////////////////////////////////////

#ifndef FACEFULL_BRIDGE_WX_HPP
#define FACEFULL_BRIDGE_WX_HPP

#include <facefull/bridge/interface.h>
#include <iostream>
#include <wx/wx.h>
#include <wx/webview.h>
#include <wx/display.h>

class FacefullBridgeWx : public FacefullBridgeInterface {
private:
    wxWebView *WebView;
    wxFrame *Frame;
    wxRect WindowSize;
    wxPoint WindowPosition;
    wxPoint PointerPosition;
    wxTimer *WindowTimer;
    bool CaptureFlag;

    void WebViewCommandExecutor(const std::string &str) override {
        wxCommandEvent event(wxEVT_COMMAND_ENTER);
        event.SetString(str);
        wxPostEvent(Frame, event);
    }

    void doUISync(wxCommandEvent &evt) {
        WebView -> RunScript(evt.GetString());
    }

    void doMoveWindow(wxMouseEvent &evt) {
        if (!evt.Dragging()) {
            WebView -> ReleaseMouse();
            CaptureFlag = false;
        } else {
            wxPoint p;
            p = wxGetMousePosition();
            if (!CaptureFlag) {
                PointerPosition.x = p.x - Frame->GetScreenPosition().x;
                PointerPosition.y = p.y - Frame->GetScreenPosition().y;
            }
            p.x -= PointerPosition.x;
            p.y -= PointerPosition.y;
            Frame -> SetPosition(p);
            CaptureFlag = true;
        }
    }

    void doWindowPosReset(wxTimerEvent&) {
        Frame -> SetPosition(WindowPosition);
        delete WindowTimer;
    }

    void onWindowMaximize() override {
        if (!isMaximized()) {
            wxDisplay display;
            WindowPosition = Frame -> GetScreenPosition();
            WindowSize = Frame -> GetClientRect();
#ifdef __WIN32__
            APPBARDATA abd;
            abd.cbSize = sizeof(APPBARDATA);
            SHAppBarMessage(ABM_GETTASKBARPOS, &abd);
            if (!abd.rc.top && abd.rc.bottom-abd.rc.top < 256) Frame -> SetPosition(wxPoint(0, abd.rc.bottom));
            else if (!abd.rc.left && abd.rc.bottom-abd.rc.top > 256) Frame -> SetPosition(wxPoint(abd.rc.right, 0));
            else
#endif
            Frame -> SetPosition(wxPoint(0, 0));
            Frame -> Maximize();
            Frame -> SetClientSize(display.GetClientArea());
        } else {
            Frame -> Maximize(false);
            WindowTimer = new wxTimer;
            WindowTimer -> Bind(wxEVT_TIMER, &FacefullBridgeWx::doWindowPosReset, this);
            WindowTimer -> StartOnce(1);
            Frame -> SetClientSize(WindowSize);
        }
    }

    void onEventReceive(wxCommandEvent &evt) {
        doEventCatch(evt.GetString().ToStdString());
    }

    void onWindowMinimize() override {
        Frame -> Iconize();
    }

    void onWindowMove() override {
        if (isMaximized()) return;
        WebView -> CaptureMouse();
    }

    void onWindowReady() override {
//        Frame -> Show();
    }

    void onWindowClose() override {
        Frame -> Hide();
        exit(0);
    }

public:
    FacefullBridgeWx(wxApp *app, wxFrame *frame, wxWebView *webview, const std::string& window) {
        WindowTimer = nullptr;
        CaptureFlag = false;

        Frame = frame;
        WebView = webview;
        app -> Bind(wxEVT_MOTION, &FacefullBridgeWx::doMoveWindow, this);
        Frame -> Bind(wxEVT_COMMAND_ENTER, &FacefullBridgeWx::doUISync, this);
        WebView -> Bind(wxEVT_WEBVIEW_TITLE_CHANGED, &FacefullBridgeWx::onEventReceive, this);
        WebView -> Bind(wxEVT_WEBVIEW_SCRIPT_MESSAGE_RECEIVED, &FacefullBridgeWx::onEventReceive, this);
        WebView -> AddScriptMessageHandler("facefullio");

        WebView -> LoadURL(window);
    }

    void setWebView(wxWebView *webview) {
        WebView = webview;
        WebView -> Bind(wxEVT_WEBVIEW_TITLE_CHANGED, &FacefullBridgeWx::onEventReceive, this);
        WebView -> Bind(wxEVT_WEBVIEW_SCRIPT_MESSAGE_RECEIVED, &FacefullBridgeWx::onEventReceive, this);
        WebView -> AddScriptMessageHandler("facefullio");
    }

    bool isMaximized() {
        return Frame->IsMaximized();
    }
};

#endif //FACEFULL_BRIDGE_WX_HPP
