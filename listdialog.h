#ifndef LISTDIALOG_H
#define LISTDIALOG_H

#include <QDialog>

namespace Ui {
class ListDialog;
}

class ListDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ListDialog(QWidget *parent = 0);
    ~ListDialog();
    QString getFileName() {return fileName;}

private:
    Ui::ListDialog *ui;
    QString fileName;

private slots:
    void onItemChanged(QString fileName_);
};

#endif // LISTDIALOG_H
