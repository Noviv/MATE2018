#ifndef QT_CSUITE_HPP
#define QT_CSUITE_HPP

#include <QFormLayout>
#include <QLabel>
#include <QMainWindow>
#include <QProgressBar>
#include <QPushButton>
#include <QWidget>
#include <QX11Info>

class QT_CSuite : public QMainWindow {
private:
    Q_OBJECT

    QWidget central;
    QFormLayout layout;

    QProgressBar bar;
    QLabel label;
    QPushButton button;

public:
    QT_CSuite();
    virtual ~QT_CSuite();

    bool eventFilter(QObject*, QEvent*);
};

#endif
