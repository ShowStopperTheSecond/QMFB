#ifndef TWOCHANNELFILTERBANK_H
#define TWOCHANNELFILTERBANK_H

#endif // TWOCHANNELFILTERBANK_H
#include <QVector>
#include <QMessageBox>

class TwoChannelFilterBank{

public:
    TwoChannelFilterBank();
    ~TwoChannelFilterBank();
    void setH0(QVector<double> data);
    void setInput(QVector<double> data);
    QVector<double> getH0();
    QVector<double> getH1();
    QVector<double> getG0();
    QVector<double> getG1();
    QVector<double> getA0();
    QVector<double> getA1();
    QVector<double> getB0();
    QVector<double> getB1();
    QVector<double> getC0();
    QVector<double> getC1();
    QVector<double> getD0();
    QVector<double> getD1();
    QVector<double> getH0Correlation();
    QVector<double> getOutput();
    QVector<double> getInput();
private:
    QVector<double> H0;
    QVector<double> H1;
    QVector<double> G0;
    QVector<double> G1;
    QVector<double> A0;
    QVector<double> A1;
    QVector<double> B0;
    QVector<double> B1;
    QVector<double> C0;
    QVector<double> C1;
    QVector<double> D0;
    QVector<double> D1;

    QVector<double> Input;
    QVector<double> Output;
    void refreshOutput();
    void createFilters();
    QVector<double> reverseVector(QVector<double> vec);
    QVector<double> zeroPadding(QVector<double> vec,int n_zeros);
    QVector<double> upSample(QVector<double> vec,int m=2);
    QVector<double> downSample(QVector<double> vec,int m=2);
    QVector<double> convolution(QVector<double> vec,QVector<double> kernel);
    QVector<double> Add(QVector<double> vec1,QVector<double> vec2);




};
