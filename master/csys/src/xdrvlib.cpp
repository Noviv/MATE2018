#include <math.h>
#include <stdio.h>
#include <string.h>

#include <X11/X.h>
#include <X11/Xatom.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>

#include "xdrvlib.h"

Atom MagellanMotionEvent;
Atom MagellanButtonPressEvent;
Atom MagellanButtonReleaseEvent;
Atom MagellanCommandEvent;

Window MagellanWindow = InputFocus;
bool MagellanExist = false;

bool MagellanInit(Display* display, Window window) {
    /* Define the Magellan Event types */
    MagellanMotionEvent = XInternAtom(display, "MotionEvent", true);
    MagellanButtonPressEvent = XInternAtom(display, "ButtonPressEvent", true);
    MagellanButtonReleaseEvent =
        XInternAtom(display, "ButtonReleaseEvent", true);
    MagellanCommandEvent = XInternAtom(display, "CommandEvent", true);

    /* TRUE if Driver exist */
    MagellanExist =
        (MagellanMotionEvent != 0) && (MagellanButtonPressEvent != 0) &&
        (MagellanButtonReleaseEvent != 0) && (MagellanCommandEvent != 0);
    if (!MagellanExist) {
        return false;
    }

    MagellanExist = MagellanSetWindow(display, window);
    if (!MagellanExist) {
        return true;
    }

    return MagellanExist;
}

int MagellanErrorHandler(Display* display, XErrorEvent* Error) {
    char Buffer[128];
    switch (Error->error_code) {
        case BadWindow:
            break;
        default:
            XGetErrorText(display, Error->error_code, Buffer, sizeof(Buffer));
            fprintf(stderr, "Magellan: Error = %s. Exit ... \n", Buffer);
            break;
    }

    return 0;
}

bool MagellanApplicationSensitivity(Display* display, double Sensitivity) {
    XTextProperty MagellanWindowName;
    XEvent CommandMessage;
    Atom ActualType;
    int ActualFormat;
    unsigned long NItems, BytesReturn;
    unsigned char* PropReturn;
    Window root;
    int (*ApplicationErrorHandler)(Display*, XErrorEvent*);
    MagellanTypeConversion MagellanType;
    bool result = false;

    ApplicationErrorHandler = XSetErrorHandler(MagellanErrorHandler);

    /* Read the window of the Magellan Driver */
    root = RootWindow(display, DefaultScreen(display));

    PropReturn = NULL;
    XGetWindowProperty(display, root, MagellanCommandEvent, 0, 1, false,
                       AnyPropertyType, &ActualType, &ActualFormat, &NItems,
                       &BytesReturn, &PropReturn);

    MagellanWindow = InputFocus;
    if (PropReturn != NULL) {
        MagellanWindow = *(Window*)PropReturn;
        XFree(PropReturn);

        if (XGetWMName(display, MagellanWindow, &MagellanWindowName) != 0) {
            if (strcmp((char*)"Magellan "
                              "Window",
                       (char*)MagellanWindowName.value) == 0) {
                /* Send the
                 * application
                 * window to the
                 * Magellan X
                 * Window Driver
                 */
                CommandMessage.type = ClientMessage;
                CommandMessage.xclient.format = 16;
                CommandMessage.xclient.send_event = false;
                CommandMessage.xclient.display = display;
                CommandMessage.xclient.window = MagellanWindow;
                CommandMessage.xclient.message_type = MagellanCommandEvent;

                MagellanType.Float = (float)Sensitivity;
                CommandMessage.xclient.data.s[0] = (short)MagellanType.Short[0];
                CommandMessage.xclient.data.s[1] = (short)MagellanType.Short[1];
                CommandMessage.xclient.data.s[2] =
                    CommandMessageApplicationSensitivity;

                result = XSendEvent(display, MagellanWindow, false, 0x0000,
                                    &CommandMessage) != 0;

                XFlush(display);
            }
        }
    }

    XSetErrorHandler(ApplicationErrorHandler);
    return result;
}

bool MagellanSetWindow(Display* display, Window window) {
    XTextProperty MagellanWindowName;
    XEvent CommandMessage;
    Atom ActualType;
    int ActualFormat;
    unsigned long NItems, BytesReturn;
    unsigned char* PropReturn;
    Window root;
    int (*ApplicationErrorHandler)(Display*, XErrorEvent*);
    bool result = false;

    ApplicationErrorHandler = XSetErrorHandler(MagellanErrorHandler);

    /* Read the window of the Magellan Driver */
    root = RootWindow(display, DefaultScreen(display));

    PropReturn = NULL;
    XGetWindowProperty(display, root, MagellanCommandEvent, 0, 1, false,
                       AnyPropertyType, &ActualType, &ActualFormat, &NItems,
                       &BytesReturn, &PropReturn);

    MagellanWindow = InputFocus;
    if (PropReturn != NULL) {
        MagellanWindow = *(Window*)PropReturn;
        XFree(PropReturn);

        if (XGetWMName(display, MagellanWindow, &MagellanWindowName)) {
            if (strcmp((char*)"Magellan "
                              "Window",
                       (char*)MagellanWindowName.value) == 0) {
                /* Send the
                 * application
                 * window to the
                 * Magellan X
                 * Window Driver
                 */
                CommandMessage.type = ClientMessage;
                CommandMessage.xclient.format = 16;
                CommandMessage.xclient.send_event = false;
                CommandMessage.xclient.display = display;
                CommandMessage.xclient.window = MagellanWindow;
                CommandMessage.xclient.message_type = MagellanCommandEvent;

                CommandMessage.xclient.data.s[0] = (short)XHigh32(window);
                CommandMessage.xclient.data.s[1] = (short)XLow32(window);
                CommandMessage.xclient.data.s[2] =
                    CommandMessageApplicationWindow;

                result = XSendEvent(display, MagellanWindow, false, 0x0000,
                                    &CommandMessage) != 0;

                XFlush(display);
            }
        }
    }

    XSetErrorHandler(ApplicationErrorHandler);
    return result;
}

void MagellanClose(Display* display) {
    MagellanInit(display, InputFocus);
    MagellanExist = false;
}

bool MagellanInputEvent(Display* display,
                        XEvent* Event,
                        MagellanIntEvent* MagellanEvent) {
    if (!MagellanExist) {
        return false;
    }

    if (Event->type == ClientMessage) {
        if (Event->xclient.message_type == MagellanMotionEvent) {
            MagellanEvent->type = MagellanInputMotionEvent;
            MagellanEvent->u.data[0] = Event->xclient.data.s[2];
            MagellanEvent->u.data[1] = Event->xclient.data.s[3];
            MagellanEvent->u.data[2] = Event->xclient.data.s[4];
            MagellanEvent->u.data[3] = Event->xclient.data.s[5];
            MagellanEvent->u.data[4] = Event->xclient.data.s[6];
            MagellanEvent->u.data[5] = Event->xclient.data.s[7];
            MagellanEvent->u.data[6] = Event->xclient.data.s[8] * 1000 / 60;
            return MagellanInputMotionEvent;
        } else if (Event->xclient.message_type == MagellanButtonPressEvent) {
            MagellanEvent->type = MagellanInputButtonPressEvent;
            MagellanEvent->u.button = Event->xclient.data.s[2];
            return MagellanInputButtonPressEvent;
        } else if (Event->xclient.message_type == MagellanButtonReleaseEvent) {
            MagellanEvent->type = MagellanInputButtonReleaseEvent;
            MagellanEvent->u.button = Event->xclient.data.s[2];
            return MagellanInputButtonReleaseEvent;
        }
    }

    return display == NULL;
}

int MagellanTranslateEvent(Display* display,
                           XEvent* Event,
                           MagellanFloatEvent* MagellanEvent,
                           double MagellanTranslationScale,
                           double MagellanRotationScale) {
    if (!MagellanExist) {
        return 0;
    }

    if (Event->type == ClientMessage) {
        if (Event->xclient.message_type == MagellanMotionEvent) {
            MagellanEvent->MagellanType = MagellanInputMotionEvent;
            MagellanEvent->MagellanData[MagellanX] =
                Event->xclient.data.s[2] * MagellanTranslationScale;
            MagellanEvent->MagellanData[MagellanY] =
                Event->xclient.data.s[3] * MagellanTranslationScale;
            MagellanEvent->MagellanData[MagellanZ] =
                Event->xclient.data.s[4] * MagellanTranslationScale;
            MagellanEvent->MagellanData[MagellanA] =
                Event->xclient.data.s[5] * MagellanRotationScale;
            MagellanEvent->MagellanData[MagellanB] =
                Event->xclient.data.s[6] * MagellanRotationScale;
            MagellanEvent->MagellanData[MagellanC] =
                Event->xclient.data.s[7] * MagellanRotationScale;
            MagellanEvent->MagellanPeriod = Event->xclient.data.s[8];
            return MagellanInputMotionEvent;
        } else if (Event->xclient.message_type == MagellanButtonPressEvent) {
            MagellanEvent->MagellanType = MagellanInputButtonPressEvent;
            MagellanEvent->MagellanButton = Event->xclient.data.s[2];
            return MagellanInputButtonPressEvent;
        } else if (Event->xclient.message_type == MagellanButtonReleaseEvent) {
            MagellanEvent->MagellanType = MagellanInputButtonReleaseEvent;
            MagellanEvent->MagellanButton = Event->xclient.data.s[2];
            return MagellanInputButtonReleaseEvent;
        }
    }

    return display == NULL;
}

Bool MagellanCheckMotionEvent(Display*, XEvent* event, char*) {
    if (event->type == ClientMessage)
        if (event->xclient.message_type == MagellanMotionEvent)
            return True;
    return False;
}

void MagellanRemoveMotionEvents(Display* display) {
    XEvent event;

    while (XCheckIfEvent(display, &event, MagellanCheckMotionEvent, NULL))
        ;
}
