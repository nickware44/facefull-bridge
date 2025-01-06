#ifndef MAIN_H
#define MAIN_H

#include <wx/wx.h>
#include "frame.h"


class App : public wxApp {
private:
    Frame *frame;
public:
    bool OnInit() override;
};

#endif //MAIN_H
