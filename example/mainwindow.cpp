#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("db.sqlite");
    if(!db.open()) {
        qDebug()<<db.lastError().text();
        return;
    }

    updateObjects();
    connect(ui->btnSave, SIGNAL(released()), this, SLOT(createObject()));
    connect(ui->btnDelete, SIGNAL(released()), this, SLOT(deleteObject()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createObject()
{
    try {
        QVariant code(ui->edCode->value());
        QVariant name(ui->edName->text());
        QVariant description(ui->edDescription->toPlainText());
        Test *newObj = new Test();
        newObj->setProperty("code", code);
        newObj->setProperty("name", name);
        newObj->setProperty("description", description);
        if (newObj->save()) {
            _resetCreateObjFields();
            delete newObj;
        } else {
            QMessageBox::warning(0,"Warning", "Object not saved!");
        }
    } catch (EOrmException *e) {
        QMessageBox::critical(0, "Critical", e->message());
    }
}

void MainWindow::updateObjects()
{
    try {
        ui->tableView->reset();
        QList<Test*> list = EOrmFind::find()->all<Test>();
        EOrmModel *model = new EOrmModel();
        model->setData(list);
        ui->tableView->setModel(model);
    } catch (EOrmException *e) {
        QMessageBox::critical(0, "Critical", e->message());
    }
}

void MainWindow::deleteObject()
{
    try {
        if (ui->tableView->selectionModel()->
                selection().indexes().count() > 0) {
                int row = ui->tableView->selectionModel()->currentIndex().row();
                Test *delObj = new Test(ui->tableView->model()->
                                        data(ui->tableView->model()->
                                             index(row, 0)));
                delObj->remove();
                delete delObj;
                updateObjects();

        } else {
            QMessageBox::warning(0,"Warning", "Select object for delete!");
        }
    } catch (EOrmException *e) {
        QMessageBox::warning(0,"Critical", e->message());
    }
}

void MainWindow::_resetCreateObjFields()
{
    ui->edCode->clear();
    ui->edName->clear();
    ui->edDescription->clear();
}
