#include <iostream>
using namespace std;

class CGateCount {
public:
    // ��1������count�Ĺ��캯��
    CGateCount(int count = 0): m_count(count) {
        m_gateNum = ++m_totalGate; // ������ŵ���բ��������1, բ��������1
        m_totalCount += count; // �ϼ�ͨ��������count
    }

    // �������캯��
    CGateCount(const CGateCount&): m_count(0) {
        m_gateNum = ++m_totalGate; // ������ŵ���բ��������1, բ��������1
    }

    // ��������
    ~CGateCount() {
        m_totalGate--;
    }

    // ���õ�����������
    static void set_maxCount(int count) {
        m_maxCount = count;
    }

    // ��������բ��ͨ������
    static int get_totalCount() {
        return m_totalCount;
    }

    // ʵ�ַ��ص�ǰբ��ͨ������
    int get_count() const {
        return m_count;
    }

    // ǰ���������++������ǰբ��ͨ������������բ��ͨ��������1
    CGateCount& operator++() {
        if (m_totalCount >= m_maxCount) {
            return *this;
        }
        m_totalCount++;
        m_count++;
        return *this;
    }

    // �����������++
    CGateCount operator++(int) {
        CGateCount backup(*this);
        ++(*this);
        return backup;
    }

    // ��������㣬��ʾһ��բ����ͨ����Ϣ
    friend ostream& operator<<(ostream& out, const CGateCount& self);

private:
    static int m_maxCount; // ������������
    static int m_totalGate; // բ������
    static int m_totalCount; // �ϼ�ͨ������
    int m_gateNum; // ��բ�����
    int m_count; // ��բ��ͨ������
};

// ��̬���ݳ�Ա�ĳ�ʼ��

int CGateCount::m_maxCount = 0;
int CGateCount::m_totalGate = 0;
int CGateCount::m_totalCount = 0;

// ��������㣬��ʾһ��բ����ͨ����Ϣ
ostream& operator<<(ostream& out, const CGateCount& self) {
    out << "==========" << endl;
    out << "բ����ţ�" << self.m_gateNum << endl;
    out << "ͨ��������" << self.m_count << endl;
    out << "�ϼ�������" << self.m_totalCount << endl;
    out << "����������" << self.m_maxCount << endl;
    out << "==========" << endl;
    return out;
}


void main() {
    CGateCount::set_maxCount(3000); //�������ͨ������
    CGateCount gate1; //����բ������
    gate1++;
    cout << gate1;
    CGateCount gate2(gate1); //����բ������2
    (++gate2)++;
    cout << "gate2ͨ������:" << gate2.get_count() << endl;
    cout << "�ϼ�ͨ������:" << gate2.get_totalCount() << endl;

    CGateCount pGate3(2997);
    cout << "gate3ͨ������:" << pGate3.get_count() << endl;
    cout << "�ϼ�ͨ������:" << pGate3.get_totalCount() << endl;

    cout << ++gate2;
}
