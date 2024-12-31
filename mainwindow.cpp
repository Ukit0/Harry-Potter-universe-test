#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setWindowTitle("Тест какая палочка из Гарри Потера тебе подходит");

    QPixmap* piXxmap = new QPixmap(":/information/pipa.jpg");

    ui->label->setPixmap(piXxmap->scaled(size(),Qt::KeepAspectRatio));

    radioButtons = {ui->radioButton_1, ui->radioButton_2, ui->radioButton_3, ui->radioButton_4};
    readFile();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete Question_iter;
    for (auto rB : radioButtons){
        delete rB;
    }
}


void MainWindow::on_ButtonNext_clicked()
{
    // При нажатие далее добавляем баллы к палочки выбранного ответа
    for (int r = 0; r<radioButtons.length(); r++){
        if (radioButtons[r]->isChecked()){
            wands[answers[r]] += 1;
        }
    }

    setNextQuestion(); //Переключаем вопрос
}


void MainWindow::on_ButtonToFinish_clicked()
{
    endOfTest();//Запускаем завершение теста
}


void MainWindow::endOfTest()
{
    QFont fontt = ui->label_answer->font();//Получаем текущий параметры лейбла с результатами

    //Убираем вопрос, все кнопки и радиоБатоны
    for (auto rB : radioButtons){
        rB->hide();
    }
    ui->label_question->hide();
    ui->label->hide();
    ui->ButtonToFinish->hide();
    ui->ButtonNext->hide();

    ui->label_answer->setStyleSheet("color: rgb(148, 0, 211)");//Меняем цвет лейбла на фиолетовый
    fontt.setPixelSize(28);// Ставим размер шрифта лейбла 28
    ui->label_answer->setFont(fontt);//устанавливаем изменённый шрифт

    //Выбираем волшебную палочку с наибольшим баллом
    QString str = wands.key(0);
    for (QString key : wands.keys()){
        if (wands[str] < wands[key]){ str = key; }
    }

    ui->label_answer->setText(QString("Вам подходит палочка из %1").arg(str));
}


void MainWindow::setNextQuestion()
{
    if(!Question_iter->hasNext()){ return endOfTest(); } //Проверяем на существование строчек с вопросами, если нет то завершаем
    ui->label_question->setText(Question_iter->next()); //Устанавлеваем вопрос

    int i = 0;
    for(auto rB : radioButtons){
        if(!Question_iter->hasNext()){ return endOfTest(); } //Проверяем на существование строчек с ответами, если нет то завершаем
        rB->setText(Question_iter->next()); //Устанавлеваем ваши ответы
        answers[i++] = Question_iter->next(); //Записываем в список для каждого ответа палочку
    }
}


void MainWindow::readFile()
{
    QFile file(":/information/texttt.txt");
    //Проверяем правильно ли указан файл
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this,"Ошибка","Файл не найден");
        delete this;
        return;
    }
    QByteArray data = file.readAll(); //Записываем данные из файла в битный массив
    file.close(); //Закрываем файл из-за дальнейшей ненадобности

    QStringList text = QString(data).split("||"); //отделяем волшебные палочки от теста добавив в лист(массив) при помощи ||

    QStringList magic_wands = text[0].split(","); //Создаем лист из первых строчек в котором записаны палочки

    //Создаем спиок из палочек
    for(auto elem : magic_wands){ wands[elem] = 0; }

    Question_iter = new QListIterator<QString>(text[1].split("\r\n")); //Для удобства записываем в листитератор строчки теста

    setNextQuestion();
}
