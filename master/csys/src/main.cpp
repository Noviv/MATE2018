#include <algorithm>
#include <iostream>

#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/Xos.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>

#include "calc.hpp"
#include "common/xnet.hpp"
#include "xdrvlib.h"

double MagellanSensitivity = 1;

Display* display;
Window window;

bool MagellanDemoEnd = false;
GC wingc;

XNet net("10.42.0.232", 512);
bool enabled = false;

template <unsigned N>
constexpr void clamp(R<N>& d, int sens = 450, double lo = -1, double hi = 1) {
    for (auto& v : d) {
        v = std::max(lo, std::min(v / sens, hi));
    }
}

void magellan() {
    XEvent report;
    KeySym keysym;
    XComposeStatus compose;
    char MagellanBuffer[256];

    MagellanFloatEvent event;

    R<3> pos, rot;
    R<8> thrusts;

    XNextEvent(display, &report);
    switch (report.type) {
        case KeyRelease:
            break;

        case KeyPress:
            XLookupString((XKeyEvent*)&report, MagellanBuffer,
                          sizeof(MagellanBuffer), &keysym, &compose);
            MagellanDemoEnd = keysym == XK_Escape;
            printf("keypress\n");
            break;

        case ClientMessage:
            switch (MagellanTranslateEvent(display, &report, &event, 1, 1)) {
                case MagellanInputMotionEvent:
                    pos = {-event.MagellanData[MagellanX],
                           event.MagellanData[MagellanY],
                           event.MagellanData[MagellanZ]};
                    clamp(pos);
                    rot = {-event.MagellanData[MagellanA],
                           event.MagellanData[MagellanB],
                           event.MagellanData[MagellanC]};
                    clamp(rot);
                    thrusts = calc(pos, rot);
                    clamp(thrusts, 1);
                    net.send("8[" + pos.to_string() + "," +
                             thrusts.to_string() + "]");

                    MagellanRemoveMotionEvents(display);
                    sprintf(MagellanBuffer,
                            "x=%+5.0f y=%+5.0f "
                            "z=%+5.0f a=%+5.0f "
                            "b=%+5.0f c=%+5.0f",
                            event.MagellanData[MagellanX],
                            event.MagellanData[MagellanY],
                            event.MagellanData[MagellanZ],
                            event.MagellanData[MagellanA],
                            event.MagellanData[MagellanB],
                            event.MagellanData[MagellanC]);

                    XClearWindow(display, window);
                    XDrawString(display, window, wingc, 10, 40, MagellanBuffer,
                                strlen(MagellanBuffer));
                    XFlush(display);
                    break;

                case MagellanInputButtonPressEvent:
                    printf("Button %d pressed\n", event.MagellanButton);

                    if (event.MagellanButton == 1) {
                        net.send(std::to_string((int)enabled));
                        std::cout << "sending"
                                     " enable"
                                     "d: "
                                  << enabled << std::endl;
                        enabled = !enabled;
                    }
                    break;

                case MagellanInputButtonReleaseEvent:
                    break;

                default:
                    printf("weird ass message\n");
                    break;
            }
    }
}

int main(int argc, char** argv) {
    Window root;

    int screennumber, width, height;
    XSizeHints* sizehints;
    XWMHints* wmhints;
    XClassHint* classhints;

    const char* WinName = "Magellan 3D Controller";
    XTextProperty WindowName;
    XGCValues xgcvalues;

    // ALLOCATE X11 WINDOW
    sizehints = XAllocSizeHints();
    wmhints = XAllocWMHints();
    classhints = XAllocClassHint();
    if (sizehints == NULL || wmhints == NULL || classhints == NULL) {
        fprintf(stderr, "Can't allocate memory! Exit ... \n");
        exit(-1);
    }

    display = XOpenDisplay(NULL);
    if (display == NULL) {
        fprintf(stderr, "Can't open display! Exit ... \n");
        exit(-1);
    }

    screennumber = DefaultScreen(display);
    width = DisplayWidth(display, screennumber);
    height = DisplayHeight(display, screennumber);
    root = DefaultRootWindow(display);
    window = XCreateSimpleWindow(display, root, 0, 0, width / 5, height / 8, 20,
                                 BlackPixel(display, screennumber),
                                 WhitePixel(display, screennumber));

    XStringListToTextProperty((char**)&WinName, 1, &WindowName);

    wmhints->initial_state = NormalState;
    wmhints->input = true;
    wmhints->flags = StateHint | InputHint;

    classhints->res_name = (char*)WinName;
    classhints->res_class = (char*)"BasicWindow";
    XSetWMProperties(display, window, &WindowName, NULL, argv, argc, sizehints,
                     wmhints, classhints);

    XMapWindow(display, window);
    xgcvalues.foreground = BlackPixel(display, 0);
    xgcvalues.background = WhitePixel(display, 0);
    wingc = XCreateGC(display, window, GCForeground | GCBackground, &xgcvalues);

    // INIT MAGELLAN & PASS X11
    if (!MagellanInit(display, window)) {
        fprintf(stderr, "No driver is running. Exit ... \n");
        exit(-1);
    }

    XSelectInput(display, window, KeyPressMask | KeyReleaseMask);

    while (!MagellanDemoEnd) {
        magellan();
    }

    MagellanClose(display);
    XFree(sizehints);
    XFree(wmhints);
    XFree(classhints);
    XFreeGC(display, wingc);
    XDestroyWindow(display, window);
    XCloseDisplay(display);
    return 0;
}
