#include "qt_csuite.hpp"

#include <QWidget>
#include <QLineEdit>
#include <QFormLayout>

QT_CSuite::QT_CSuite() {
	QWidget* central = new QWidget;

	QLineEdit* firstNm = new QLineEdit;
	QLineEdit* lastNm = new QLineEdit;
	QLineEdit* age = new QLineEdit;

	QFormLayout* layout = new QFormLayout;
	layout->addRow("FirstName", firstNm);
	layout->addRow("LastName", lastNm);
	layout->addRow("Age", age);

	central->setLayout(layout);

	setCentralWidget(central);
}

QT_CSuite::~QT_CSuite() {

}
