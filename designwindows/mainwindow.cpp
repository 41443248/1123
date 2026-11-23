#include "mainwindow.h"
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QStatusBar>
#include <QStyle>
#include <QKeySequence>
#include <QFileDialog>
#include <QPixmap>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Image Studio");
    resize(800, 600);

    actOpen = new QAction(style()->standardIcon(QStyle::SP_DialogOpenButton), "Open Image", this);
    actOpen->setShortcut(QKeySequence::Open);

    actSave = new QAction(style()->standardIcon(QStyle::SP_DialogSaveButton), "Save", this);
    actSave->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_S));

    actExit = new QAction(style()->standardIcon(QStyle::SP_DialogCloseButton), "Exit", this);
    actExit->setShortcut(QKeySequence::Quit);

    actUndo = new QAction(style()->standardIcon(QStyle::SP_ArrowBack), "Undo", this);
    actUndo->setShortcut(QKeySequence::Undo);

    QMenu *fileMenu = menuBar()->addMenu("File");
    fileMenu->addAction(actOpen);
    fileMenu->addAction(actSave);
    fileMenu->addSeparator();
    fileMenu->addAction(actExit);

    QMenu *editMenu = menuBar()->addMenu("Edit");
    editMenu->addAction(actUndo);

    QMenu *imageMenu = menuBar()->addMenu("Image");

    QToolBar *toolBar = addToolBar("Main Toolbar");
    toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    toolBar->addAction(actOpen);
    toolBar->addAction(actSave);
    toolBar->addAction(actUndo);

    workspace = new QLabel("IMAGE WORKSPACE", this);
    workspace->setAlignment(Qt::AlignCenter);
    workspace->setStyleSheet("background-color: #1e1e1e; color: #7f8c8d; font-size: 24px; font-weight: bold;");
    setCentralWidget(workspace);

    statusInfo = new QLabel("Ready | 0 x 0 px", this);
    statusBar()->addWidget(statusInfo);

    connect(actOpen, &QAction::triggered, this, &MainWindow::onOpen);
    connect(actSave, &QAction::triggered, this, &MainWindow::onSave);
    connect(actExit, &QAction::triggered, this, &QWidget::close);
    connect(actUndo, &QAction::triggered, this, &MainWindow::onUndo);
}

MainWindow::~MainWindow()
{
}

void MainWindow::onOpen()
{
    QString path = QFileDialog::getOpenFileName(this, "Open Image", "", "Images (*.png *.jpg *.bmp)");
    if (!path.isEmpty()) {
        QPixmap img(path);
        if (!img.isNull()) {
            workspace->setPixmap(img.scaled(workspace->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
            statusInfo->setText(QString("Ready | %1 x %2 px").arg(img.width()).arg(img.height()));
        }
    }
}

void MainWindow::onSave()
{
    statusBar()->showMessage("Save triggered (Ctrl+S)", 2000);
}

void MainWindow::onUndo()
{
    statusBar()->showMessage("Undo triggered", 2000);
}