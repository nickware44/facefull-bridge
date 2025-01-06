#include "main.h"

IMPLEMENT_APP(App)

App *Main;

bool App::OnInit() {
    Main = this;
    if (!wxApp::OnInit()) return false;
    frame = new Frame(this, wxT("Facefull native desktop app example"));
    return true;
}
