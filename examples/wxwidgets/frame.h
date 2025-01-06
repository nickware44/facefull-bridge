#ifndef FRAME_H
#define FRAME_H

#include <wx/wx.h>
#include <wx/webview.h>
#include <facefull/bridge/wx.hpp>

class Frame : public wxFrame {
private:
    wxWebView *WebView;
    FacefullBridgeWx *Bridge;
public:
    Frame(wxApp *app, const wxString& title);
};

#endif //FRAME_H
