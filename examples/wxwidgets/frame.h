#ifndef FRAME_H
#define FRAME_H

#include <wx/wx.h>
#include <wx/webview.h>
#include <facefull/bridge/wx.hpp>

class Frame : public wxFrame {
private:
    wxWebView *WebView;
    FacefullBridgeWx *Bridge;
#ifdef __WIN32__
    WXLRESULT MSWWindowProc(WXUINT nMsg, WXWPARAM wParam, WXLPARAM lParam) wxOVERRIDE;
#endif
public:
    Frame(wxApp *app, const wxString& title);
};

#endif //FRAME_H
