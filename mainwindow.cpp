
#include "mainwindow.h"

#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    regExp.setPattern("(https?|ftp|file)://[-A-Za-z0-9+&@#/%?=~_|!:,.;]+[-A-Za-z0-9+&@#/%=~_|]");
    v.setPage(&p);
    QObject::connect(ui->lineEdit_inputurl, &QLineEdit::textChanged, this, [&](const QString &text) {
        url = text;
    });
    QObject::connect(ui->pushButton_save, &QPushButton::clicked, this,
                     [&]() {
                         QUrl qurl = QUrl::fromUserInput(url);
                         qDebug() << "url: " << url << " qurl: " << qurl << " isValid: " << regExp.match(url).hasMatch();

                         if (url.isEmpty() || !regExp.match(url).hasMatch()) {
                             QMessageBox::warning(this,
                                                  "错误",
                                                  "网址无效，请检查输入: " + url,
                                                  QMessageBox::Close,
                                                  QMessageBox::Close);
                             return;
                         }
                         QString filePath = QFileDialog::getSaveFileName(this, "选择保存路径", "/", "文本文件(*.txt);; All(*.*);; ");
                         if (filePath.isEmpty()) {
                             QMessageBox::warning(this,
                                                  "错误",
                                                  "未选择正确的保存路径",
                                                  QMessageBox::Close,
                                                  QMessageBox::Close);
                             return;
                         }
                         QFileInfo fileInfo(filePath);
                         filePath = fileInfo.absoluteFilePath();
                         if (fileInfo.isDir()) {
                             filePath += "/urls.txt";
                         } else if (fileInfo.suffix() != "txt") {
                             filePath += ".txt";
                         }
                         qDebug() << "filePath: " << filePath;
                         p.profile()->setUrlRequestInterceptor(new WebEngineUrlRequestInterceptor(filePath));
                         v.setUrl(qurl);
                         v.show();
                     });

    QObject::connect(&p, &QWebEnginePage::newWindowRequested, this, [&](QWebEngineNewWindowRequest &request) {
        v.setUrl(request.requestedUrl());
    });
    /*QObject::connect(&p, &QWebEnginePage::windowCloseRequested,this, [&]() {
        qDebug() << "got close signal";
    });*/
}

MainWindow::~MainWindow() {
    delete ui;
}
