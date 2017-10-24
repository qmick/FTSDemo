#include "resultitemdelegate.h"
#include <QTextEdit>
#include <QApplication>
#include <QLabel>
#include <QPainter>
#include <QAbstractTextDocumentLayout>
#include <QDebug>

ResultItemDelegate::ResultItemDelegate()
{

}


void ResultItemDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(option.state & QStyle::State_Selected)
        painter->fillRect(option.rect, option.palette.highlight());

    painter->save();
    QTextDocument document;
    document.setTextWidth(option.rect.width());
    QVariant value = index.data(Qt::DisplayRole);
    if (value.isValid() && !value.isNull())
    {
                document.setHtml(value.toString());
                painter->translate(option.rect.topLeft());
                document.drawContents(painter);
    }

    painter->restore();
}


//QWidget *ResultItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
//{
//    if (index.column() == 2)
//    {
//        auto textedit = new QTextEdit(parent);
//        textedit->setReadOnly(true);
//        return textedit;
//    }
//    else
//        return NULL;
//}

//void ResultItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
//{
//    QString value = index.model()->data(index, Qt::EditRole).toString();
//    auto textedit = static_cast<QTextEdit *>(editor);
////    if (index.column() == 2)
//        textedit->setHtml(value);
////    else
////        textedit->setPlainText(value);
//}


//QSize ResultItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
//{
//    QStyleOptionViewItemV4 options = option;
//    initStyleOption(&options, index);

//    QTextDocument doc;
//    doc.setHtml(options.text);
//    doc.setTextWidth(options.rect.width());
//    return QSize(doc.idealWidth(), doc.size().height());
//}


//void ResultItemDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
//{
//    editor->setGeometry(option.rect.x(),option.rect.y(),editor->sizeHint().width(),editor->sizeHint().height());
//}
