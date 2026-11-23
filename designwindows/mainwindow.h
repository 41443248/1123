#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onOpen();
    void onSave();
    void onUndo();

private:
    QAction *actOpen;
    QAction *actSave;
    QAction *actExit;
    QAction *actUndo;
    QLabel *workspace;
    QLabel *statusInfo;
};

#endif