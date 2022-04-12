#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QDebug>
#include <qcustomplot.h>
#include <string>
#include <twochannelfilterbank.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    QVector<QString> parse_text(QString str,QChar delimator);
    QVector<double> preprocess(QVector<QString> data);
    bool is_number(const QString &str);
    QVector<double> arrange(double min,double max,double step=1);
    double find_min(QVector<double> data);
    double find_max(QVector<double> data);
    void refreshGraphics();

    ~MainWindow();


private slots:
    void on_textEdit_2_textChanged();

    void on_textEdit_textChanged();

    void on_showinputsignal_toggled(bool checked);

    void on_showoutputsignal_toggled(bool checked);

    void on_showh0_toggled(bool checked);

    void on_showh1_toggled(bool checked);

    void on_showg0_toggled(bool checked);

    void on_showg1_toggled(bool checked);

    void on_showa0_toggled(bool checked);

    void on_showa1_toggled(bool checked);

    void on_showb0_toggled(bool checked);

    void on_showb1_toggled(bool checked);

    void on_showc0_toggled(bool checked);

    void on_showc1_toggled(bool checked);

    void on_showd0_toggled(bool checked);

    void on_showd1_toggled(bool checked);

    void on_showCorrelation_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    QGraphicsScene graphScnece ;
    TwoChannelFilterBank QFB ;
    QCustomPlot * plt=new QCustomPlot();
    void read_data();


};
#endif // MAINWINDOW_H
