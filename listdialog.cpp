#include "listdialog.h"
#include "ui_listdialog.h"
#include <QDir>
#include <QStringList>

ListDialog::ListDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ListDialog),
    fileName("")
{
    ui->setupUi(this);
    connect(ui->listWidget, SIGNAL(currentTextChanged(QString)),
            this, SLOT(onItemChanged(QString)));
    QDir dir(":/images/images/");
    QStringList exts, files;
    exts << "*.jpg" << "*.png";
    files = dir.entryList(exts);

    if(files.size() > 0) {
        foreach (QString file, files) {
            ui->listWidget->addItem(file);
        }
        ui->listWidget->item(0)->setSelected(true);
    }
}

ListDialog::~ListDialog()
{
    delete ui;
}

void ListDialog::onItemChanged(QString fileName_)
{
   fileName = fileName_;
}
