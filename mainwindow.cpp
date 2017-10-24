#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <resultitemdelegate.h>
#include <resulttablemodel.h>
#include <SQLiteCPP/DB.h>
//#include <SQLiteCPP/sample/MyTokenizer.h>
#include <SQLiteCPP/sample/rankfunc.h>
#include <SQLiteCPP/sqlite3.h>
#include <memory>
#include <string>
#include <QDebug>
#include <QMessageBox>
#include <QTime>
#include <cassert>
#include <QFile>
#include <QFileInfoList>
#include <QDir>

using std::make_shared;
using std::string;
using std::get;
using std::to_string;

static string sql1 = "CREATE VIRTUAL TABLE IF NOT EXISTS file_index USING fts4(name, path, content, tokenize=porter)";
static string sql3 = "INSERT INTO file_index VALUES(?,?,?)";
static string sql6 = "SELECT name,rank,snippet(file_index, \"<font color=red>\", \"</font>\", \"...\", -1, 11) AS snippet,path,content FROM file_index JOIN (SELECT docid, rank(matchinfo(file_index,'pcxnl'),1,1,1) AS rank FROM file_index WHERE file_index MATCH ? ORDER BY rank DESC ) AS ranktable USING(docid) WHERE file_index MATCH ? ORDER BY ranktable.rank DESC";


QFileInfoList getFileList(QString path)
{
    QDir dir(path);
    QFileInfoList file_list = dir.entryInfoList(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    QFileInfoList folder_list = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot);

    for(int i = 0; i != folder_list.size(); i++)
    {
         QString name = folder_list.at(i).absoluteFilePath();
         QFileInfoList child_file_list = getFileList(name);
         file_list.append(child_file_list);
    }

    return file_list;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _db("../msg.db")
{
    ui->setupUi(this);
    ui->tableView->setItemDelegate(&_delegate);
    ui->tableView->setModel(&_model);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->statusBar->addWidget(&_count_label);
    ui->statusBar->addWidget(&_time_label);
    connect(ui->lineEdit, SIGNAL(textChanged(const QString &)),
            this, SLOT(search(const QString &)));
    connect(ui->tableView, SIGNAL(doubleClicked(QModelIndex)),
            this, SLOT(pop_content(QModelIndex)));
    try {
        initDB();
    } catch (std::exception &e) {
        QMessageBox::warning(this, "Error", e.what(), QMessageBox::Ok);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initDB()
{
//    auto tknz = make_shared<MyTokenizer>("../FTSDemo/dict/");
//    _db.add_tokenizer("jieba", tknz);
    _db.create_function("rank", -1, rankfunc);
    _db.update("DROP TABLE IF EXISTS file_index");
    _db.update(sql1);

    QFileInfoList files = getFileList("./");
    auto stmt = _db.prepare(sql3);
    for (auto &i : files)
    {
        stmt.bind_all(i.baseName().toLocal8Bit().data(),
                      i.absoluteFilePath().toLocal8Bit().data(), "");
        stmt.step();
        stmt.reset();
    }
}

void MainWindow::search(const QString &keyword)
{
    _model.mData.clear();

//    if (keyword.size() == 0) return;

    string local_keyword = (keyword + '*').toUtf8().data();

    int count = 0;

    QTime myTimer;
    myTimer.start();

    try {
        auto rs = _db.query(sql6, local_keyword, local_keyword);
        while (rs.next())
        {
            count++;
            auto r = rs.get<string, double, string, string>();
            QStringList row;
            row.append(QString::fromUtf8(get<0>(r).c_str()));
            row.append(QString::number(get<1>(r)));
            row.append(QString::fromUtf8(get<2>(r).c_str()));
            row.append(QString::fromUtf8(get<3>(r).c_str()));
            _model.mData.append(row);
        }
    }
    catch (std::exception &e)
    {
        QMessageBox::warning(this, "Error", e.what(), QMessageBox::Ok);
    }

    _time_label.setText(QString::number(myTimer.elapsed()) + "ms");
    _count_label.setText(QString::number(count));

    emit _model.layoutChanged();
}

void MainWindow::pop_content(QModelIndex index)
{
    auto data = _model.mData[index.row()].last();
    QMessageBox::information(this, "Msg", data, QMessageBox::Ok);
}
