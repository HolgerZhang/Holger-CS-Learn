#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <vector>

using namespace std;


// deposit������
class deposit {
private:
    string name; // �˻�����
    double balance, loan, charge; // �˻�������, �˻��������, ÿ�λ������
public:
    // ���캯����nameĬ��ֵΪ��NoName�����������Ĭ��ֵΪ0.0
    deposit(const string& name = "NoName", double balance = 0.0, double loan = 0.0, double charge = 0.0)
        : name(name), balance(balance), loan(loan), charge(charge) { }

    // �����˻�����
    void setName(const string& name);

    // ִ�л�������
    bool pay();

    // ����ǰ�����ÿ�λ������charge����100
    deposit operator++(int);

    // ��ʾһ���������Ϣ
    friend ostream& operator<<(ostream& out, const deposit& self);

};


// ȫ�ֺ�������

int inputData(const string& filePath, vector<deposit>& accounts); // ��ȡ�ļ�����
void incData(vector<deposit>& accounts); // �����˻��Ļ����������100
int decData(vector<deposit>& accounts); // �����˻�ִ��һ�λ��������������޷���ɻ������˻���
void outPut(const vector<deposit>& accounts); // ���ڰ������е�������ʾ���


// ���������
int main() {
    vector<deposit> v_acc;
    string path = "d:\\account.txt";
    inputData(path, v_acc);
    outPut(v_acc);
    cout << "-------------------------------" << endl;
    incData(v_acc);
    outPut(v_acc);
    cout << "-------------------------------" << endl;
    cout << "can not pay = " << decData(v_acc) << endl;
    outPut(v_acc);
    return 0;
}


// ���Ա����ʵ��

// �����˻�����
void deposit::setName(const string& name) {
    this->name = name;
}

// ִ�л�������
bool deposit::pay() {
    // ���balance�����ڻ������charge���򲻻�����ԭ���ƺ���ӡ�(*)��
    if (!(balance > charge)) {
        name += "(*)";
        return false;
    }
    // ����
    // ���loan����charge���򻹴����Ϊcharge�����򻹴����Ϊloan
    double this_charge = (loan > charge) ? charge : loan;
    balance -= this_charge;
    loan -= this_charge;
    return true;
}

// ����ǰ�����ÿ�λ������charge����100
deposit deposit::operator++(int) {
    deposit backup(*this); // ����++����һ������
    charge += 100;
    return backup;
}

// ��ʾһ���������Ϣ

ostream& operator<<(ostream& out, const deposit& self) {
    // nameռ10�в�����룬balance��loan��charge��ռ15�в���ȷ��С�����2λ
    out << setiosflags(ios::left);
    out << setw(10) << self.name;
    out << setiosflags(ios::right | ios::fixed) << setprecision(2);
    out << setw(15) << self.balance;
    out << setw(15) << self.loan;
    out << setw(15) << self.charge;
    out << resetiosflags(ios::left | ios::right | ios::fixed);
    return out;
}


// ȫ�ֺ���ʵ��

// ��ȡ�ļ�������������������accounts��
int inputData(const string& filePath, vector<deposit>& accounts) {
    ifstream inFile(filePath); // ���ļ�
    // ����ļ��Ƿ�򿪳ɹ�
    if (!inFile.is_open()) {
        return -1;
    }

    while (!inFile.eof()) {
        // ��ȡ����
        string line; // �ļ��е�һ��
        string name; // �˻�����
        double balance, loan, charge; // �˻�������, �˻��������, ÿ�λ������
        getline(inFile, line);
        if (line.empty()) { // ��ֹ�������
            continue;
        }
        istringstream is(line);
        is >> name >> balance >> loan >> charge;
        // ��������
        accounts.push_back(deposit(name, balance, loan, charge));
    }

    inFile.close(); // �ر��ļ�
    return 0;
}

// �����˻��Ļ����������100
void incData(vector<deposit>& accounts) {
    for (deposit& account : accounts) {
        account++;
    }
}

// �����˻�ִ��һ�λ��������������޷���ɻ������˻���
int decData(vector<deposit>& accounts) {
    int number = 0;
    for (deposit& account : accounts) {
        if (!account.pay()) { // �޷���ɻ�����ͳ����+1
            number++;
        }
    }
    return number;
}

// ���ڰ������е�������ʾ���
void outPut(const vector<deposit>& accounts){
    for (const deposit& account : accounts) {
        cout << account << endl;
    }
}
