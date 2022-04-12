#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(& this->graphScnece);
    ui->showinputsignal->setChecked(true);
    plt->addGraph();
    plt->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    plt->graph(0)->setLineStyle(QCPGraph::lsImpulse);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refreshGraphics(){
//    read_data();
    this->graphScnece.clear();
    QVector<double> y;
    if (ui->showg0->isChecked()){
        y=QFB.getG0();
    }
    if (ui->showg1->isChecked()){
        y=QFB.getG1();
    }
    if (ui->showh0->isChecked()){
        y=QFB.getH0();
    }
    if (ui->showh1->isChecked()){
        y=QFB.getH1();
    }
    if (ui->showinputsignal->isChecked()){
        y=QFB.getInput();
    }
    if (ui->showoutputsignal->isChecked()){
        y=QFB.getOutput();
    }
    if (ui->showa0->isChecked()){
        y=QFB.getA0();
    }
    if (ui->showa1->isChecked()){
        y=QFB.getA1();
    }
    if (ui->showb0->isChecked()){
        y=QFB.getB0();
    }
    if (ui->showb1->isChecked()){
        y=QFB.getB1();
    }
    if (ui->showc0->isChecked()){
        y=QFB.getC0();
    }
    if (ui->showc1->isChecked()){
        y=QFB.getC1();
    }
    if (ui->showd0->isChecked()){
        y=QFB.getD0();
    }
    if (ui->showd1->isChecked()){
        y=QFB.getD1();
    }
    if (ui->showCorrelation->isChecked()){
        y=QFB.getH0Correlation();
    }

    if (y.isEmpty()){
        throw ("No data available");
    }

    QVector<double> x=arrange(0,y.length());

    plt->graph(0)->setData(x,y);
    plt->xAxis->setRange(-5,x.length()+5);
    double y_min=find_min(y);
    double y_max=find_max(y);
    plt->yAxis->setRange(y_min-.3*abs(y_min),y_max+.3*abs(y_max));
    plt->replot();
    plt->update();

    QPixmap current_graph=plt->toPixmap();
    graphScnece.addPixmap(current_graph);
    ui->graphicsView->update();




}

////    ui->graphicsView->show();

QVector<double> MainWindow::arrange(double min,double max,double step){
    QVector<double> vec;
    for (double i = min; i < max; i+=step) {
        vec.append(i);
    }
    return vec;
}
QVector<QString> MainWindow::parse_text(QString str, QChar delimator){
    int beginning=0,end=0;
    QVector<QString> sparsed_text;

    for (int i = 0; i < str.length(); ++i) {
        if (str[i]==delimator){
            end=i;
            sparsed_text.append(str.mid(beginning+(int)(beginning!=0),end-beginning-(int)(beginning!=0)));
            beginning=end;
        }
    }
    if (str.endsWith(delimator)==false){
        sparsed_text.append(str.mid(beginning+1));
    }
    return sparsed_text;
}

double MainWindow::find_min(QVector<double> data){
    double min=data.at(0);
    for (int i = 0; i < data.length(); ++i) {
        if (data.at(i)<min){
            min=data.at(i);
        }
    }
    return min;
}

double MainWindow::find_max(QVector<double> data){
    double max=data.at(0);
    for (int i = 0; i < data.length(); ++i) {
        if (data.at(i)>max){
            max=data.at(i);
        }
    }
    return max;
}

QVector<double> MainWindow::preprocess(QVector<QString> data){
    QVector<double> processed_data;
    QString text;
    for (int i = 0; i < data.length(); ++i) {
        text=data.at(i);
        if (is_number(text)==false){
            continue;
            processed_data.append(0);
        }

        processed_data.append(text.toDouble());
    }
    return processed_data;
}

bool MainWindow::is_number(const QString &str) {

    if (str.isEmpty()){return false;}
    for (int i = 0; i < str.length(); ++i) {
        if (str[i].isDigit() == false && str[i] !='-'&& str[i] !='.'){

            return false;
        }
    }
    return true;
}



void MainWindow::read_data(){
    QString strh0;
    strh0=ui->textEdit_2->toPlainText();
    auto parsed_text=parse_text(strh0,',');
    QVector<double> h0filter=preprocess( parsed_text);
    if  (h0filter.isEmpty()){
        return;
    }
    QFB.setH0(h0filter);
    QString input;
    input=ui->textEdit->toPlainText();
    QVector<double> input_signal=preprocess( parse_text(input,','));
    if  (input_signal.isEmpty()){
        return;
    }
    QFB.setInput(input_signal);
}


void MainWindow::on_textEdit_2_textChanged()
{
        read_data();
        try{
            refreshGraphics();
        }catch(...){
        }
}

void MainWindow::on_textEdit_textChanged()
{
    read_data();
    try{
        refreshGraphics();
    }catch(...){

    }
}

void MainWindow::on_showinputsignal_toggled(bool checked)
{
    try{
        refreshGraphics();
    }catch(...){

    }
}

void MainWindow::on_showoutputsignal_toggled(bool checked)
{
    try{
        refreshGraphics();
    }catch(...){

    }
}

void MainWindow::on_showh0_toggled(bool checked)
{
    try{
        refreshGraphics();
    }catch(...){

    }
}

void MainWindow::on_showh1_toggled(bool checked)
{
    try{
        refreshGraphics();
    }catch(...){

    }
}

void MainWindow::on_showg0_toggled(bool checked)
{
    try{
        refreshGraphics();
    }catch(...){

    }
}

void MainWindow::on_showg1_toggled(bool checked)
{
    try{
        refreshGraphics();
    }catch(...){

    }
}

void MainWindow::on_showa0_toggled(bool checked)
{
    try{
        refreshGraphics();
    }catch(...){

    }
}

void MainWindow::on_showa1_toggled(bool checked)
{
    try{
        refreshGraphics();
    }catch(...){

    }
}

void MainWindow::on_showb0_toggled(bool checked)
{
    try{
        refreshGraphics();
    }catch(...){

    }
}

void MainWindow::on_showb1_toggled(bool checked)
{
    try{
        refreshGraphics();
    }catch(...){

    }
}

void MainWindow::on_showc0_toggled(bool checked)
{
    try{
        refreshGraphics();
    }catch(...){

    }
}

void MainWindow::on_showc1_toggled(bool checked)
{
    try{
        refreshGraphics();
    }catch(...){

    }
}

void MainWindow::on_showd0_toggled(bool checked)
{
    try{
        refreshGraphics();
    }catch(...){

    }
}

void MainWindow::on_showd1_toggled(bool checked)
{
    try{
        refreshGraphics();
    }catch(...){

    }
}

void MainWindow::on_showCorrelation_toggled(bool checked)
{
    try{
        refreshGraphics();
    }catch(...){

    }
}
