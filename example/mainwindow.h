 #ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include "test.h"
#include "eormfind.h"
#include "eormmodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void createObject();
    void updateObjects();
    void deleteObject();
    
private:
    void _resetCreateObjFields();
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
