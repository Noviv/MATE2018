#include "qt_csuite.hpp"

#include <iostream>

#include <QEvent>

#include <X11/Xlib.h>

Atom motion_evt;

QT_CSuite::QT_CSuite() {
    motion_evt = XInternAtom(QX11Info::display(), "MotionEvent", true);

    bar.setRange(0, 100);
    bar.setValue(25);
    bar.setOrientation(Qt::Vertical);

    layout.addRow("Progress", &bar);
    layout.addRow("Label", &label);
    layout.addRow("Button", &button);

    central.setLayout(&layout);

    setCentralWidget(&central);
}

QT_CSuite::~QT_CSuite() {}

bool QT_CSuite::eventFilter(QObject* o, QEvent* e) {
    std::cout << e->type() << " vs. " << motion_evt << std::endl;
    if (e->type() == motion_evt) {
        std::cout << "FUCK YA" << std::endl;
    }
    return false;  // keep handling
}
