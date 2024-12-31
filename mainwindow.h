#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QString>
#include <QRadioButton>
#include <QPixmap>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void readFile();
    void setNextQuestion();
    void endOfTest();

private slots:
    void on_ButtonNext_clicked();

    void on_ButtonToFinish_clicked();

private:
    Ui::MainWindow *ui;
    QHash<QString, int> wands;// Почему здесь хеш, а не мап? Блин это самая невероятная проблема которая со мной происходила
    // Когда обьявлялась фунция endOfTest, то начинался перибор палочек на самое большое значение балла. И вроде всё должно работать,
    // но по какой-то причине из двух равных по баллам палочек он выберал ту что позже шла в массиве
    // Оказалась что изначально он отсортировывал по первым буквам и когда начислялись баллы и начиналась выборка палочки
    // Он выберал ту что по алфовиту выше, а не ту что стояла в текстовом файле "texttt.txt" первее
    QMap<int, QString> answers;
    QList<QRadioButton*> radioButtons;
    QListIterator<QString> *Question_iter;
};
#endif // MAINWINDOW_H
