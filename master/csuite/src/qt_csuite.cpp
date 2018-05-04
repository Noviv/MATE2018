#include "qt_csuite.hpp"

QT_CSuite::QT_CSuite() {
    bar.setRange(0, 100);
    bar.setValue(25);
    bar.setOrientation(Qt::Vertical);

    layout.addRow("Progress", &bar);

    central.setLayout(&layout);

    setCentralWidget(&central);
}

QT_CSuite::~QT_CSuite() {}
