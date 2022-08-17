#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCompleter>
#include <QSettings>
#include <QDebug>
#include <QTextCodec>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString exePath=QCoreApplication::applicationDirPath();
    //配置文件为可执行程序所在的目录下的local.ini
    QString iniFile=exePath+"/local.ini";

    //m_IniFile为全局变量QSettings *m_IniFile;
    m_IniFile = new QSettings(iniFile, QSettings::IniFormat,this);
    //文件中的编码要设置和这里对应，比如我都设置成UTF-8
    m_IniFile->setIniCodec(QTextCodec::codecForName("UTF-8"));

    //通过Value函数将节下相对应的键值读取出来
    QString username =m_IniFile->value("client/username").toString();

    m_usernameList=username.split("|");
    ui->comboBox->setEditable(true);
    ui->comboBox->setCurrentText(m_usernameList.at(0));
    ui->comboBox->addItems(m_usernameList);

//    QCompleter *completer = new QCompleter(m_usernameList);
//    ui->comboBox->setCompleter(completer);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    //我希望的是每进行一次触发事件后，这次文本框中的内容会设置成在下次打开程序时的默认值
    //只有触发事件后才进行这样的操作
    QString currentContent=ui->comboBox->currentText();
    if(m_usernameList.contains(currentContent)){
        m_usernameList.removeAt(ui->comboBox->currentIndex());
    }
    m_usernameList.push_front(currentContent);
    m_usernameList.removeAll("");
    QString username;
    for (int i=0;i<m_usernameList.size();i++ ) {
        if(i==m_usernameList.size()-1){
            username+=m_usernameList.at(i);
        }else{
            username+=m_usernameList.at(i)+"|";
        }
    }
    m_IniFile->setValue("client/username",username);
    qDebug()<<ui->comboBox->currentText();
}

