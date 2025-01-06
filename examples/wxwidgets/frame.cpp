#include <iostream>
#include "frame.h"
#include <wx/filename.h>
#include <wx/stdpaths.h>
#include <string>

Frame::Frame(wxApp *app, const wxString& title) : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(1000, 700), wxNO_BORDER) {
    Centre();
    wxFileName f(wxStandardPaths::Get().GetExecutablePath());
    auto apath = f.GetPath().ToStdString();
    std::cout << apath << std::endl;

    if (wxWebView::IsBackendAvailable(wxWebViewBackendEdge)) {
        std::cout << "Using Edge backend on Windows" << std::endl;
        WebView = wxWebView::New(this, wxID_ANY, wxEmptyString, wxDefaultPosition, GetClientSize(), wxWebViewBackendEdge, wxNO_BORDER);
    } else {
        std::cout << "Using default backend" << std::endl;
        WebView = wxWebView::New(this, wxID_ANY, wxEmptyString, wxDefaultPosition, GetClientSize(), wxWebViewBackendDefault, wxNO_BORDER);
    }

    Bridge = new FacefullBridgeWx(app, this, WebView, apath+"/../ui/window.html");

    std::cout << "Window loaded" << std::endl;

    Bridge -> doEventAttach("doWindowReady", [this](const std::string& data) {
        Show();
    });
}
