#include <iostream>

#include <QApplication>
#include <QStyle>
#include <QDesktopWidget>

#include "qt_csuite.hpp"

int main(int argc, char** argv) {
	QApplication a(argc, argv);

	QT_CSuite w;
	w.setGeometry(
		QStyle::alignedRect(
			Qt::LeftToRight,
			Qt::AlignCenter,
			w.size(),
			a.desktop()->availableGeometry()
		)
	);
	w.show();

	return a.exec();
}
