#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <resultitemdelegate.h>
#include <resulttablemodel.h>
#include <QMainWindow>
#include <SQLiteCPP/DB.h>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class ResultItemDelegate;
class ResultTableModel;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    ResultItemDelegate _delegate;
    ResultTableModel _model;
    sqlite::DB _db;
    QLabel _count_label;
    QLabel _time_label;

    void initDB();

public slots:
    void search(const QString &keyword);
    void pop_content(QModelIndex index);
};

#endif // MAINWINDOW_H
