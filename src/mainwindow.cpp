#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    edittor = new Edittor();
    connect(edittor, &Edittor::firstWindow, this, &MainWindow::show);
    searcher = NULL;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    edittor->show();
    this->close();
}

void MainWindow::on_pushButton_2_clicked()
{
    if(searcher != NULL)
        delete searcher;
    searcher = new Searcher();
    connect(searcher, &Searcher::firstWindow, this, &MainWindow::show);
    searcher->show();
    this->close();
}
