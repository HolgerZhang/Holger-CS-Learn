#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

//======================================CPU=====================================
/// @brief ��ʾCPU����
//================================================================================
class CPU {
private:
    double m_MainFreq; //��Ƶ����λGHz
    int m_CoreNum; //������
    double m_Power; //���ʣ���λ��W

public:
    CPU(double MainFreq, int CoreNum, double Power);
    double GetMainFreq(void) const; //��ȡ��Ƶ
    CPU& operator++(); //ǰ��������Ƶ��0.1����������2�����ʼ�1.0
    CPU operator++(int); //������������ͬ��
    friend ostream& operator<<(ostream& Out, const CPU& Obj); //���CPU�Ĳ�����
                                                              //��Ƶռ6�У�С�����ֱ���2λ�������
                                                              //������ռ3�У������
                                                              //����ռ6�У�С�����ֱ���1λ�������
};

//===================================CPU::CPU()===================================
/// @brief ���캯��
///
/// @param MainFreq ��Ƶ
/// @param CoreNum ������
/// @param Power ����
//================================================================================
CPU::CPU(double MainFreq, int CoreNum, double Power)
    : m_MainFreq(MainFreq), m_CoreNum(CoreNum), m_Power(Power) { }

//===============================CPU::GetMainFreq()===============================
/// @brief ��ȡ��Ƶ
///
/// @return ��Ƶ
//================================================================================
double CPU::GetMainFreq() const {
    return m_MainFreq;
}

//===============================CPU::operator++()==============================
/// @brief ǰ����
/// ��Ƶ��0.1����������2�����ʼ�1.0
///
/// @return ����������
//================================================================================
CPU& CPU::operator++() {
    m_MainFreq += 0.1;
    m_CoreNum += 2;
    m_Power += 1.0;
    return *this;
}

//===============================CPU::operator++()==============================
/// @brief ǰ����
/// ��Ƶ��0.1����������2�����ʼ�1.0
///
/// @return ���������ʱ����
//================================================================================
CPU CPU::operator++(int) {
    CPU backup(*this);
    ++(*this);
    return backup;
}

//==================================operator<<()==================================
/// @brief ���CPU�Ĳ���
/// ��Ƶռ6�У�С�����ֱ���2λ�������
/// ������ռ3�У������
/// ����ռ6�У�С�����ֱ���1λ�������
///
/// @param Out ostream�����
/// @param Obj Ҫ�����CPU����
/// @return ������ostream�����
//================================================================================
ostream& operator<<(ostream& Out, const CPU& Obj) {
    Out << setiosflags(ios::left | ios::fixed);
    Out << setprecision(2) << setw(6) << Obj.m_MainFreq;
    Out << setw(3) << Obj.m_CoreNum;
    Out << setprecision(1) << setw(6) << Obj.m_Power;
    Out << resetiosflags(ios::left | ios::fixed);
    return Out;
}


//=====================================Computer===================================
/// @brief �������Computer������
//================================================================================
class Computer {
private:
    CPU m_CPU;
    int m_Memory; //�ڴ���������λ��G
    int m_HD; //Ӳ����������λ��G

public:
    Computer(double CPU_MainFreq, int CPU_CoreNum, double CPU_Power, int Memory, int HD);
    CPU GetCPU(void) const; //��ȡCPU����
    double GetMemory(void) const; //��ȡ�ڴ�����
    Computer& operator++(); //ǰ������CPU������������ͬCPU�࣬�ڴ�����4G��Ӳ������128G
    Computer operator++(int); //������������ͬ��
    friend ostream& operator<<(ostream& Out, const Computer& Obj);
                                                                    //CPU�������ݵ����������CPU���ж�����ͬ
                                                                    //�ڴ�����ռ6�У������
                                                                    //Ӳ������ռ8�У������
};

//==============================Computer::Computer()==============================
/// @brief ���캯��
///
/// @param CPU_MainFreq CPU��Ƶ
/// @param CPU_CoreNum CPU������
/// @param CPU_Power CPU����
/// @param Memory �ڴ�����
/// @param HD Ӳ������
//================================================================================
Computer::Computer(double CPU_MainFreq, int CPU_CoreNum, double CPU_Power, int Memory, int HD)
    : m_CPU(CPU_MainFreq, CPU_CoreNum, CPU_Power), m_Memory(Memory), m_HD(HD) { }

//===============================Computer::GetCPU()===============================
/// @brief ��ȡCPU����
///
/// @return CPU����
//================================================================================
CPU Computer::GetCPU() const {
    return m_CPU;
}

//=============================Computer::GetMemory()============================
/// @brief ��ȡ�ڴ�����
///
/// @return �ڴ�����
//================================================================================
double Computer::GetMemory() const {
    return m_Memory;
}

//=============================Computer::operator++()=============================
/// @brief ǰ����
/// CPU������������ͬCPU�࣬�ڴ�����4G��Ӳ������128G
///
/// @return ����������
//================================================================================
Computer& Computer::operator++() {
    ++m_CPU;
    m_Memory += 4;
    m_HD += 128;
    return *this;
}

//=============================Computer::operator++()=============================
/// @brief ������
/// CPU������������ͬCPU�࣬�ڴ�����4G��Ӳ������128G
///
/// @return ���������ʱ����
//================================================================================
Computer Computer::operator++(int) {
    Computer backup(*this);
    ++(*this);
    return backup;
}

//==================================operator<<()==================================
/// @brief ���Computer����
/// CPU�������ݵ����������CPU���ж�����ͬ���ڴ�����ռ6�У�����룬Ӳ������ռ8�У������
///
/// @param Out ostream�����
/// @param Obj Ҫ�����Computer����
/// @return ������ostream�����
//================================================================================
ostream& operator<<(ostream& Out, const Computer& Obj) {
    Out << Obj.m_CPU;
    Out << setiosflags(ios::left);
    Out << setw(6) << Obj.m_Memory;
    Out << setw(8) << Obj.m_HD;
    Out << resetiosflags(ios::left);
    return Out;
}

//======================================IPC=====================================
/// @brief ��ʾ���ػ���IPC��
/// ����: Computer
//================================================================================
class IPC : public Computer {
private:
    int m_ProtectGrade; //�����ȼ�
    static int m_Counts; //���ػ�����

public:
    IPC(double CPU_MainFreq = 3.7, int CPU_CoreNum = 6, double CPU_Power = 95.0, int Memory = 16, int HD = 512,
        int ProtectGrade = 65);
    IPC(const IPC& Obj);
    double GetProtectGrade(void) const; //��ȡ�����ȼ�
    static int GetCounts(void); //��ȡ��ǰ���ػ�����
    IPC& operator++(); //ǰ������Computer������������ͬ�ϣ������ȼ���1
    IPC operator++(int); //������������ͬ��
    friend ostream& operator<<(ostream& Out, const IPC& Obj);
                                                             //Computer�������ݵ����������Computer���ж�����ͬ
                                                             //�����ȼ�ռ5�У������
    ~IPC();
};

int IPC::m_Counts = 0;  /// ���ػ�����

//===================================IPC::IPC()===================================
/// @brief ���캯��
/// ���ػ�������һ
///
/// @param CPU_MainFreq CPU��Ƶ
/// @param CPU_CoreNum CPU������
/// @param CPU_Power CPU����
/// @param Memory �ڴ�����
/// @param HD Ӳ������
/// @param ProtectGrade �����ȼ�
//================================================================================
IPC::IPC(double CPU_MainFreq, int CPU_CoreNum, double CPU_Power, int Memory, int HD, int ProtectGrade)
    :Computer(CPU_MainFreq, CPU_CoreNum, CPU_Power, Memory, HD), m_ProtectGrade(ProtectGrade) {
    m_Counts++;
}

//===================================IPC::IPC()===================================
/// @brief ���ƹ��캯��
/// ���ػ�������һ
///
/// @param Obj ��һ��IPC����
//================================================================================
IPC::IPC(const IPC& Obj): Computer(Obj), m_ProtectGrade(Obj.m_ProtectGrade) {
    m_Counts++;
}

//=============================IPC::GetProtectGrade()=============================
/// @brief ��ȡ�����ȼ�
///
/// @return �����ȼ�
//================================================================================
double IPC::GetProtectGrade() const {
    return m_ProtectGrade;
}

//================================IPC::GetCounts()================================
/// @brief ��ȡ��ǰ���ػ�����
///
/// @return ��ǰ���ػ�����
//================================================================================
int IPC::GetCounts() {
    return m_Counts;
}

//===============================IPC::operator++()==============================
/// @brief ǰ����
/// Computer������������ͬ�ϣ������ȼ���1
///
/// @return ����������
//================================================================================
IPC& IPC::operator++() {
    Computer::operator++();
    m_ProtectGrade++;
    return *this;
}

//===============================IPC::operator++()==============================
/// @brief ������
/// Computer������������ͬ�ϣ������ȼ���1
///
/// @return ���������ʱ����
//================================================================================
IPC IPC::operator++(int) {
    IPC backup(*this);
    ++(*this);
    return backup;
}

//==================================IPC::~IPC()=================================
/// @brief ��������
/// ���ػ�������һ
//================================================================================
IPC::~IPC() {
    m_Counts--;
}

//==================================operator<<()==================================
/// @brief ���IPC���� 
/// Computer�������ݵ����������Computer���ж�����ͬ�������ȼ�ռ5�У������
///
/// @param Out ostream�����
/// @param Obj Ҫ�����IPC����
/// @return ������ostream�����
//================================================================================
ostream& operator<<(ostream& Out, const IPC& Obj) {
    Out << static_cast<Computer>(Obj);
    Out << setiosflags(ios::left);
    Out << setw(5) << Obj.m_ProtectGrade;
    Out << resetiosflags(ios::left);
    return Out;
}


//=================================ReadIPCFile()================================
/// @brief ��ȡ����δ֪�����ػ����ݣ�����һ��IPC���͵�������
/// �ı��ļ���ÿ�����ػ���Ϣ��˳�������CPU��Ƶ��CPU��������CPU���ʡ��ڴ�������Ӳ�������������ȼ���ռ1�С�
///
/// @param [in] path �ı��ļ�·��
/// @param [out] vec_ipc IPC���͵�����
/// @return 0 - ������ȡ; 1 - �ļ��޷���
//================================================================================
int ReadIPCFile(const char* path, vector<IPC>& vec_ipc) {
    ifstream inFile(path);
    if (!inFile.is_open()) {
        return 1;
    }
    double CPU_MainFreq;
    int CPU_CoreNum;
    double CPU_Power;
    int Memory;
    int HD;
    int ProtectGrade;
    while (inFile >> CPU_MainFreq >> CPU_CoreNum >> CPU_Power >> Memory >> HD >> ProtectGrade) {
        vec_ipc.push_back(IPC(CPU_MainFreq, CPU_CoreNum, CPU_Power, Memory, HD, ProtectGrade));
    }
    inFile.close();
    return 0;
}


//==================================operator<()=================================
/// @brief ����<��������Ƚ�IPC����
/// �ȱȽ�CPU��Ƶ, һ�±ȽϷ����ȼ� 
///
/// @param left IPC����
/// @param right IPC����
/// @return true - left < right����; false - left < right������
//================================================================================
bool operator<(const IPC& left, const IPC& right) {
    if (left.GetCPU().GetMainFreq() == right.GetCPU().GetMainFreq()) {
        return (left.GetProtectGrade() < right.GetProtectGrade());
    }
    return (left.GetCPU().GetMainFreq() < right.GetCPU().GetMainFreq());
}

//===================================SortIPC()==================================
/// @brief ��IPC����������������
/// ���������� a) CPU��Ƶ, b) �����ȼ� 
/// ע�⣺����������������˳��ģ����밴�ա�a���� - b��������˳�������д��� 
///
/// @param vec_ipc IPC���͵�����
/// @return �޷���ֵ
//================================================================================
void SortIPC(vector<IPC>& vec_ipc){
    sort(vec_ipc.begin(), vec_ipc.end());
}

//=================================IncreaseIPC()================================
/// @brief ���������ڴ�����С�ڵ���4G�Ĺ��ػ����ݽ���ǰ��������
/// ���������Ĺ��ػ����ݱ���Ҫ��Ȼ������A������ԭ����λ�ô���
///
/// @param vec_ipc IPC���͵�����
/// @return �޷���ֵ
//================================================================================
void IncreaseIPC(vector<IPC>& vec_ipc) {
    for (auto& ipc : vec_ipc) {
        if (ipc.GetMemory() <= 4) {
            ++ipc;
        }
    }
}

//================================OutputIPCFile()===============================
/// @brief �����������й��ػ����ݱ������ı��ļ�
/// �ļ������ʽ��IPC����operator<<�Ķ��������ͬ
///
/// @param vec_ipc IPC���͵�����
/// @param path �ı��ļ�·��
/// @return 0 - ����д��; 1 - �ļ��޷�д��
//================================================================================
int OutputIPCFile(const vector<IPC>& vec_ipc, const char* path) {
    ofstream outFile(path);
    if (!outFile.is_open()) {
        return 1;
    }
    for (const auto& ipc : vec_ipc) {
        outFile << ipc << endl;
    }
    outFile.close();
    return 0;
}

/// @brief ������
void main() {
    vector<IPC> A;
    
    ReadIPCFile("d:\\source.txt", A);
    cout << "��ǰ���ػ�̨��: " << IPC::GetCounts() << endl;
    SortIPC(A);
    IncreaseIPC(A);
    cout << "��ǰ���ػ�̨��: " << IPC::GetCounts() << endl;
    OutputIPCFile(A, "d:\\res.txt");
    
    IPC t1;
    
    cout << t1 << endl;
    cout << t1++ << endl;
    cout << t1 << endl;
    cout << "��ǰ���ػ�̨��" << IPC::GetCounts() << endl;
    
    IPC t2(t1);
    
    cout << t2 << endl;
    cout << "��ǰ���ػ�̨��" << IPC::GetCounts() << endl;
}
