#include<iostream>
#include<fstream>
#include<string>
using namespace std;

int main(){
    fstream fin("iris.dat", ios::in);
    while (!fin.eof()) {
        string str;
        fin>>str;
        cout<<str<<endl;
    }
    fin.close();
    return 0;
}
