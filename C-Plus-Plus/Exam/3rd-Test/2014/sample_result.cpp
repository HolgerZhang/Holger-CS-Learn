// ��ϰ2
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// ��ʾ�̳���Ʒ��Ϣ��CGoods�ඨ��
class CGoods {
private:
    int m_num; //��Ʒ���
    string m_name; //��Ʒ����
    float m_price; //��Ʒ�۸�

public:
    CGoods(int, const string&, float);
    friend ostream& operator<<(ostream&, const CGoods&);
    //��Ʒ���ơ���Ʒ��ź���Ʒ�۸����ʾ��ʽ��Ҫ��Ϊռ10�С��Ҷ���
};


// ��ʾ�̳������۵�·������Ʒ��CRouter�ඨ��
class CRouter : public CGoods {
private:
    float m_frequency; // ·�����ź�Ƶ��
    int m_channels; // ·�����˿�����

public:
    CRouter(int = 1, const string& = "M8", float = 100.0f, float = 2.4f, int = 8);
    int GetChannels() const; // ��ȡ·�����˿�����
    float GetFrequency() const; // ��ȡ·�����ź�Ƶ��
    CRouter& operator++(); // �˿�������1
    CRouter operator++(int);
    bool operator<(const CRouter&); // �Ƚ���·������Ʒ
    friend ostream& operator<<(ostream&, const CRouter&); // ��·������Ʒȫ����Ϣ����ʾ
};


// ȫ�ֺ�����ǰ������

int ReadData(vector<CRouter>&, const string&); // ���ı��ļ��ж�ȡ����δ֪��·������Ʒ���ݣ�����һ������
void DisplayData(const vector<CRouter>&); // ��ʾ����������·������Ʒ����
CRouter FindMax(vector<CRouter>&); // ���ҵ������С��˿��������ź�Ƶ�ʵĳ˻��������Ǹ�Ԫ��


// ������
void main() {
    vector<CRouter> s;

    ReadData(s, "D:\\Data.txt");
    cout << "��ȡ��ɺ������Ϊ" << endl;
    DisplayData(s);

    CRouter t;
    cout << endl << "·��������ĳ�ʼֵΪ" << endl << t << endl;

    t = FindMax(s);
    cout << endl << "�˻���������Ԫ��Ϊ" << endl << t << endl;

    cout << endl << "�˻���������Ԫ�ؽ��������������ֱ�����:" << endl;
    cout << t++ << endl;
    cout << t << endl;

    cout << ++t << endl;
    cout << t << endl;
}


// CGoods���Ա����ʵ��

/**
 * \brief CGoods�๹�캯��
 * \param num ��Ʒ���
 * \param name ��Ʒ����
 * \param price ��Ʒ�۸�
 */
CGoods::CGoods(int num, const string& name, float price)
    : m_num(num), m_name(name), m_price(price) { }

/**
 * \brief �����ʾCGoods������Ʒ���ơ���Ʒ��ź���Ʒ�۸����ʾ��ʽ��Ҫ��Ϊռ10�С��Ҷ���
 * \param out ostream�������
 * \param self Ҫ�����CGoods����
 * \return ������ostream�������
 */
ostream& operator<<(ostream& out, const CGoods& self) {
    out << setw(10) << self.m_num;
    out << setw(10) << self.m_name;
    out << setw(10) << self.m_price;
    return out;
}


// CRouter���Ա����ʵ��

/**
 * \brief CRouter�๹�캯��
 * \param num ��Ʒ���
 * \param name ��Ʒ����
 * \param price ��Ʒ�۸�
 * \param frequency ·�����ź�Ƶ��
 * \param channels ·�����˿�����
 */
CRouter::CRouter(int num, const string& name, float price, float frequency, int channels)
    : CGoods(num, name, price), m_frequency(frequency), m_channels(channels) { }

/**
 * \brief ��ȡ·�����˿�����
 * \return ·�����˿�����
 */
inline int CRouter::GetChannels() const { return m_channels; }

/**
 * \brief ��ȡ·�����ź�Ƶ��
 * \return ·�����ź�Ƶ��
 */
inline float CRouter::GetFrequency() const { return m_frequency; }

/**
 * \brief ǰ������������غ�����ʵ�ֶ˿�������1�Ĳ���
 * \return ������Ķ���
 */
CRouter& CRouter::operator++() {
    ++m_channels;
    return *this;
}

/**
 * \brief ��������������غ�����ʵ�ֶ˿�������1�Ĳ���
 * \return ����ǰ���󸱱�
 */
CRouter CRouter::operator++(int) {
    CRouter backup(*this);
    ++(*this);
    return backup;
}

/**
 * \brief ����"�˿��������ź�Ƶ�ʵĳ˻�"�Ƚ���CRouter����
 * \param other ��һ��CRouter����
 * \return true - (*this<other); false - !(*this<other)
 */
bool CRouter::operator<(const CRouter& other) {
    return (this->m_frequency * this->m_channels) < (other.m_frequency * other.m_channels);
}

/**
 * \brief �����ʾCRouter����
 *  ���ಿ�ֳ�Ա����ʾ��ʽҪ����CGoods�ಿ����ͬ���ź�Ƶ�ʺͶ˿���������ʾ��ʽ��Ҫ��Ϊռ10�С��Ҷ���
 * \param out ostream�������
 * \param self Ҫ�����CRouter����
 * \return ������ostream�������
 */
ostream& operator<<(ostream& out, const CRouter& self) {
    out << static_cast<CGoods>(self);
    out << setw(10) << self.m_frequency;
    out << setw(10) << self.m_channels;
    return out;
}


// ȫ�ֺ���ʵ��

/**
 * \brief ���ı��ļ��ж�ȡ����δ֪��·������Ʒ���ݣ�����һ������
 * \param routers ·������������
 * \param path �ı��ļ�·��������˳���������Ʒ��š���Ʒ���ơ���Ʒ�۸��ź�Ƶ�ʡ��˿�������ÿ������ռ1��
 * \return 0 - �ɹ���ȡ; 1 - ��ȡʧ��
 */
int ReadData(vector<CRouter>& routers, const string& path) {
    ifstream inFile(path);
    if (!inFile.is_open()) {
        // �ļ��Ƿ�򿪳ɹ�
        return 1;
    }

    int num, channels;
    string name;
    float price, frequency;
    while (inFile >> num>>name>>price>>frequency>>channels) {
        routers.push_back(CRouter(num, name, price, frequency, channels));
    }

    inFile.close();
    return 0;
}

/**
 * \brief ��ʾ����������·������Ʒ����
 * \param routers Ҫ�����·������������
 */
void DisplayData(const vector<CRouter>& routers) {
    for (const auto& router : routers) {
        cout << router << endl;
    }
}

/**
 * \brief ���ҵ������С��˿��������ź�Ƶ�ʵĳ˻��������Ǹ�Ԫ��
 * \param routers Ŀ��·������������
 * \return �˿��������ź�Ƶ�ʵĳ˻�����Ԫ��
 */
CRouter FindMax(vector<CRouter>& routers) {
    return *max_element(routers.begin(), routers.end());
}