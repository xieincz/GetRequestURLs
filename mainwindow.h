
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QMainWindow>
#include <QMessageBox>
#include <QRegularExpression>
#include <QTextStream>
#include <QWebEngineNewWindowRequest>
#include <QWebEnginePage>
#include <QWebEngineProfile>
#include <QWebEngineSettings>
#include <QWebEngineUrlRequestInterceptor>
#include <QWebEngineView>

class WebEngineUrlRequestInterceptor : public QWebEngineUrlRequestInterceptor {
    Q_OBJECT
public:
    explicit WebEngineUrlRequestInterceptor(QString outputPath = "") {
        if (!outputPath.isEmpty()) {
            file = new QFile(outputPath);
            if (!file->open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
                QMessageBox::warning(nullptr,
                                     "错误",
                                     "无法打开文件：" + outputPath,
                                     QMessageBox::Close,
                                     QMessageBox::Close);
            } else {
                out = new QTextStream(file);
            }
        }
    }
    virtual void interceptRequest(QWebEngineUrlRequestInfo &info) override {
        if (out != nullptr) {
            (*out) << info.requestUrl().toString() << '\n';
            out->flush();
        }
    }
    ~WebEngineUrlRequestInterceptor() {
        if (file != nullptr) {
            file->close();
            if (out != nullptr)
                delete out;
            file->deleteLater();
        }
    }

private:
    QFile *file = nullptr;
    QTextStream *out = nullptr;
};

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString url;
    QRegularExpression regExp;
    QWebEnginePage p;
    QWebEngineView v;
};

#endif  // MAINWINDOW_H
