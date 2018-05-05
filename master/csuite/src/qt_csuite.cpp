#include "qt_csuite.hpp"

#include <iostream>
#include <thread>

#include <QCloseEvent>

QT_CSuite::QT_CSuite() {
    bar.setRange(0, 100);
    bar.setValue(25);
    bar.setOrientation(Qt::Vertical);

    layout.addRow("Progress", &bar);
    layout.addRow("Label", &label);
    layout.addRow("Button", &button);

    central.setLayout(&layout);

    setCentralWidget(&central);

    std::thread t([&]() {
        while (!button.isDown()) {
        }
        std::cout << "button pushed" << std::endl;
    });
    t.detach();
}

QT_CSuite::~QT_CSuite() {}

void QT_CSuite::closeEvent(QCloseEvent* event) {
    std::cout << "close" << std::endl;
}
