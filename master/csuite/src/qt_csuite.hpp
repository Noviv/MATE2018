#ifndef QT_CSUITE_HPP
#define QT_CSUITE_HPP

#include <QMainWindow>
#include <QProgressBar>
#include <QFormLayout>
#include <QWidget>

class QT_CSuite : public QMainWindow {
private:
    Q_OBJECT

	QWidget central;
	QProgressBar bar;
	QFormLayout layout;

public:
    QT_CSuite();
    virtual ~QT_CSuite();
};

#endif
