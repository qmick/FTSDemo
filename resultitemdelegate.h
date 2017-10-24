#ifndef RESULTITEMDELEGATE_H
#define RESULTITEMDELEGATE_H

#include <QStyledItemDelegate>

class ResultItemDelegate : public QStyledItemDelegate
{
public:
    ResultItemDelegate();

    // QAbstractItemDelegate interface
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

//public:
//    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
//    void setEditorData(QWidget *editor, const QModelIndex &index) const override;

//public:
//    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

//    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // RESULTITEMDELEGATE_H
