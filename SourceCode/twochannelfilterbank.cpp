#include <twochannelfilterbank.h>

TwoChannelFilterBank::TwoChannelFilterBank(){}
TwoChannelFilterBank::~TwoChannelFilterBank(){}

void TwoChannelFilterBank::setH0(QVector<double> data){
    H0=data;
    createFilters();

}

void TwoChannelFilterBank::setInput(QVector<double> data){
    Input=data;
}

QVector<double> TwoChannelFilterBank::getOutput(){
    if (H0.isEmpty() || Input.isEmpty()){
        QMessageBox::critical(nullptr,"Wning","Either H0 or Input are not set.\n Check out the Input Signal or the H0 filter and then try again.");
        return QVector<double> ();
    }
    refreshOutput();
    return Output;
}

QVector<double> TwoChannelFilterBank::getB0(){
    if (H0.isEmpty() || Input.isEmpty()){
        QMessageBox::critical(nullptr,"Wning","Either H0 or Input are not set.\n Check out the Input Signal or the H0 filter and then try again.");
        return QVector<double> ();
    }
    refreshOutput();
    return B0;
}

QVector<double> TwoChannelFilterBank::getB1(){
    if (H0.isEmpty() || Input.isEmpty()){
        QMessageBox::critical(nullptr,"Wning","Either H0 or Input are not set.\n Check out the Input Signal or the H0 filter and then try again.");
        return QVector<double> ();
    }
    refreshOutput();
    return B1;
}
QVector<double> TwoChannelFilterBank::getC0(){
    if (H0.isEmpty() || Input.isEmpty()){
        QMessageBox::critical(nullptr,"Wning","Either H0 or Input are not set.\n Check out the Input Signal or the H0 filter and then try again.");
        return QVector<double> ();
    }
    refreshOutput();
    return C0;
}
QVector<double> TwoChannelFilterBank::getC1(){
    if (H0.isEmpty() || Input.isEmpty()){
        QMessageBox::critical(nullptr,"Wning","Either H0 or Input are not set.\n Check out the Input Signal or the H0 filter and then try again.");
        return QVector<double> ();
    }
    refreshOutput();
    return C1;
}
QVector<double> TwoChannelFilterBank::getD0(){
    if (H0.isEmpty() || Input.isEmpty()){
        QMessageBox::critical(nullptr,"Wning","Either H0 or Input are not set.\n Check out the Input Signal or the H0 filter and then try again.");
        return QVector<double> ();
    }
    refreshOutput();
    return D0;
}
QVector<double> TwoChannelFilterBank::getD1(){
    if (H0.isEmpty() || Input.isEmpty()){
        QMessageBox::critical(nullptr,"Wning","Either H0 or Input are not set.\n Check out the Input Signal or the H0 filter and then try again.");
        return QVector<double> ();
    }
    refreshOutput();
    return D1;
}
void TwoChannelFilterBank::refreshOutput(){
    A0=convolution(Input,H0);
    A1=convolution(Input,H1);
    B0=downSample(A0,2);
    B1=downSample(A1,2);
    C0=upSample(B0,2);
    C1=upSample(B1,2);
    D0=convolution(C0,G0);
    D1=convolution(C1,G1);
    Output=Add(D0,D1);
}

QVector<double> TwoChannelFilterBank::getA0(){
    if (H0.isEmpty() || Input.isEmpty()){
        QMessageBox::critical(nullptr,"Warning","Either H0 or Input are not set.\n Check out the Input Signal or the H0 filter and then try again.");
        return QVector<double> ();
    }
    refreshOutput();
    return A0;

}



QVector<double> TwoChannelFilterBank::getA1(){
    if (H0.isEmpty() || Input.isEmpty()){
        QMessageBox::critical(nullptr,"Warning","Either H0 or Input are not set.\n Check out the Input Signal or the H0 filter and then try again.");
        return QVector<double> ();
    }
    refreshOutput();
    return A1;

}


QVector<double> TwoChannelFilterBank::getH0(){
    if (H0.isEmpty() ){
        QMessageBox::critical(nullptr,"Warning","H0 filter is not set up correctly. Check out the H0 filter and then try again  ");
        return QVector<double> ();
    }
    return H0;
}



QVector<double> TwoChannelFilterBank::getG0(){
    if (H0.isEmpty() ){
        QMessageBox::critical(nullptr,"Warning","H0 filter is not set up correctly. Check out the H0 filter and then try again  ");
        return QVector<double> ();
    }
    return G0;
}


QVector<double> TwoChannelFilterBank::getG1(){
    if (H0.length()==0 ){
        QMessageBox::critical(nullptr,"Warning","H0 filter is not set up correctly. Check out the H0 filter and then try again  ");
        return QVector<double>();
    }
    return G1;
}



QVector<double> TwoChannelFilterBank::getH1(){
    if (H0.length()==0 ){
        QMessageBox::critical(nullptr,"Warning","H0 filter is not set up correctly. Check out the H0 filter and then try again  ");
        return QVector<double> ();
    }
    return H1;
}

QVector<double> TwoChannelFilterBank::getInput(){
    if (Input.isEmpty()){
        QMessageBox::critical(nullptr,"Warning","No Input signal is set. Check out the input signal.");
        return QVector<double> ();
    }
    return Input;
}


void TwoChannelFilterBank::createFilters(){
    QVector<double> tmp;
    //Creating H1
    tmp=H0;
    int sgn=-1;
    for (int i=0 ; i<tmp.length();i++){
        tmp[i]=sgn*tmp[i];
        sgn=-1*sgn;
    }
    H1=reverseVector(tmp);
    //creating G0
    G0=reverseVector(H0);
    //creating G1
    G1=reverseVector(H1);
}
QVector<double> TwoChannelFilterBank::reverseVector(QVector<double> vec){
    QVector<double> tmp;
    for (int i=vec.length()-1;i>=0;i--){
        tmp.append(vec.at(i));
    }
    return tmp;
}


QVector<double> TwoChannelFilterBank::zeroPadding(QVector<double> vec,int n_zeros){
    QVector<double> tmp;

    for (int i=0 ;i<n_zeros;i++){
        tmp.append(0);
    }
    for (int i=0 ;i<vec.length();i++){
        tmp.append(vec.at(i));
    }
    for (int i=0 ;i<n_zeros;i++){
        tmp.append(0);
    }
    return tmp;
}

QVector<double> TwoChannelFilterBank::upSample(QVector<double> vec,int m){
    QVector<double> tmp;
    for (int i=0;i<vec.length();i++){
        tmp.append(vec.at(i));
        for (int j=0;j<m-1;j++){
        tmp.append(0);
        }
    }
    return tmp;
}
QVector<double> TwoChannelFilterBank::downSample(QVector<double> vec,int m){
    QVector<double> tmp;
    for(int i=0;i<vec.length();i+=m){
        tmp.append(vec.at(i));
    }
    return tmp;
}
QVector<double> TwoChannelFilterBank::convolution(QVector<double> vec, QVector<double> kernel){
    QVector<double> zero_padded_vec;
    QVector<double> tmpKernel;
    QVector<double> tmp;
    int is_symmetric=kernel.length()%2;
    double sum_of_multiplications;
    int radius_kernel=int(kernel.length()/2);
    zero_padded_vec=zeroPadding(vec,2*radius_kernel);
    tmpKernel=reverseVector(kernel);

    for (int i=radius_kernel;i<zero_padded_vec.length()-radius_kernel;i++){
        sum_of_multiplications=0;
        for(int j=-radius_kernel;j<radius_kernel+is_symmetric;j++){
            sum_of_multiplications+=tmpKernel.at(j+radius_kernel)*zero_padded_vec.at(i+j);
        }
        tmp.append(sum_of_multiplications);
    }
    return tmp;
}


QVector<double> TwoChannelFilterBank::getH0Correlation(){
    if (H0.isEmpty() ){
        QMessageBox::critical(nullptr,"Warning","H0 filter is not set up correctly. Check out the H0 filter and then try again  ");
        return QVector<double> ();
    }
    return convolution(H0,reverseVector(H0));
}
QVector<double> TwoChannelFilterBank::Add(QVector<double> vec1,QVector<double> vec2){
    QVector<double> tmp ;
    for(int i =0 ;i<vec1.length();i++){
        tmp.append(vec1.at(i)+vec2.at(i));
    }
    return tmp;
}


