#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <algorithm>
using namespace std;

//======================================CPU=====================================
/// @brief 表示CPU的类
//================================================================================
class CPU {
private:
    double m_MainFreq; //主频，单位GHz
    int m_CoreNum; //核心数
    double m_Power; //功率，单位：W

public:
    CPU(double MainFreq, int CoreNum, double Power);
    double GetMainFreq(void) const; //获取主频
    CPU& operator++(); //前自增，主频加0.1，核心数加2，功率加1.0
    CPU operator++(int); //后自增，规则同上
    friend ostream& operator<<(ostream& Out, const CPU& Obj); //输出CPU的参数，
                                                              //主频占6列，小数部分保留2位，左对齐
                                                              //核心数占3列，左对齐
                                                              //功率占6列，小数部分保留1位，左对齐
};

//===================================CPU::CPU()===================================
/// @brief 构造函数
///
/// @param MainFreq 主频
/// @param CoreNum 核心数
/// @param Power 功率
//================================================================================
CPU::CPU(double MainFreq, int CoreNum, double Power)
    : m_MainFreq(MainFreq), m_CoreNum(CoreNum), m_Power(Power) { }

//===============================CPU::GetMainFreq()===============================
/// @brief 获取主频
///
/// @return 主频
//================================================================================
double CPU::GetMainFreq() const {
    return m_MainFreq;
}

//===============================CPU::operator++()==============================
/// @brief 前自增
/// 主频加0.1，核心数加2，功率加1.0
///
/// @return 本对象引用
//================================================================================
CPU& CPU::operator++() {
    m_MainFreq += 0.1;
    m_CoreNum += 2;
    m_Power += 1.0;
    return *this;
}

//===============================CPU::operator++()==============================
/// @brief 前自增
/// 主频加0.1，核心数加2，功率加1.0
///
/// @return 本对象的临时拷贝
//================================================================================
CPU CPU::operator++(int) {
    CPU backup(*this);
    ++(*this);
    return backup;
}

//==================================operator<<()==================================
/// @brief 输出CPU的参数
/// 主频占6列，小数部分保留2位，左对齐
/// 核心数占3列，左对齐
/// 功率占6列，小数部分保留1位，左对齐
///
/// @param Out ostream类对象
/// @param Obj 要输出的CPU对象
/// @return 输出后的ostream类对象
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
/// @brief 计算机（Computer）基类
//================================================================================
class Computer {
private:
    CPU m_CPU;
    int m_Memory; //内存容量，单位：G
    int m_HD; //硬盘容量，单位：G

public:
    Computer(double CPU_MainFreq, int CPU_CoreNum, double CPU_Power, int Memory, int HD);
    CPU GetCPU(void) const; //获取CPU数据
    double GetMemory(void) const; //获取内存容量
    Computer& operator++(); //前自增，CPU部分自增规则同CPU类，内存扩大4G，硬盘扩大128G
    Computer operator++(int); //后自增，规则同上
    friend ostream& operator<<(ostream& Out, const Computer& Obj);
                                                                    //CPU部分数据的输出规则与CPU类中定义相同
                                                                    //内存容量占6列，左对齐
                                                                    //硬盘容量占8列，左对齐
};

//==============================Computer::Computer()==============================
/// @brief 构造函数
///
/// @param CPU_MainFreq CPU主频
/// @param CPU_CoreNum CPU核心数
/// @param CPU_Power CPU功率
/// @param Memory 内存容量
/// @param HD 硬盘容量
//================================================================================
Computer::Computer(double CPU_MainFreq, int CPU_CoreNum, double CPU_Power, int Memory, int HD)
    : m_CPU(CPU_MainFreq, CPU_CoreNum, CPU_Power), m_Memory(Memory), m_HD(HD) { }

//===============================Computer::GetCPU()===============================
/// @brief 获取CPU数据
///
/// @return CPU数据
//================================================================================
CPU Computer::GetCPU() const {
    return m_CPU;
}

//=============================Computer::GetMemory()============================
/// @brief 获取内存容量
///
/// @return 内存容量
//================================================================================
double Computer::GetMemory() const {
    return m_Memory;
}

//=============================Computer::operator++()=============================
/// @brief 前自增
/// CPU部分自增规则同CPU类，内存扩大4G，硬盘扩大128G
///
/// @return 本对象引用
//================================================================================
Computer& Computer::operator++() {
    ++m_CPU;
    m_Memory += 4;
    m_HD += 128;
    return *this;
}

//=============================Computer::operator++()=============================
/// @brief 后自增
/// CPU部分自增规则同CPU类，内存扩大4G，硬盘扩大128G
///
/// @return 本对象的临时拷贝
//================================================================================
Computer Computer::operator++(int) {
    Computer backup(*this);
    ++(*this);
    return backup;
}

//==================================operator<<()==================================
/// @brief 输出Computer对象
/// CPU部分数据的输出规则与CPU类中定义相同，内存容量占6列，左对齐，硬盘容量占8列，左对齐
///
/// @param Out ostream类对象
/// @param Obj 要输出的Computer对象
/// @return 输出后的ostream类对象
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
/// @brief 表示工控机的IPC类
/// 父类: Computer
//================================================================================
class IPC : public Computer {
private:
    int m_ProtectGrade; //防护等级
    static int m_Counts; //工控机数量

public:
    IPC(double CPU_MainFreq = 3.7, int CPU_CoreNum = 6, double CPU_Power = 95.0, int Memory = 16, int HD = 512,
        int ProtectGrade = 65);
    IPC(const IPC& Obj);
    double GetProtectGrade(void) const; //获取防护等级
    static int GetCounts(void); //获取当前工控机数量
    IPC& operator++(); //前自增，Computer数据自增规则同上，防护等级加1
    IPC operator++(int); //后自增，规则同上
    friend ostream& operator<<(ostream& Out, const IPC& Obj);
                                                             //Computer部分数据的输出规则与Computer类中定义相同
                                                             //防护等级占5列，左对齐
    ~IPC();
};

int IPC::m_Counts = 0;  /// 工控机数量

//===================================IPC::IPC()===================================
/// @brief 构造函数
/// 工控机数量加一
///
/// @param CPU_MainFreq CPU主频
/// @param CPU_CoreNum CPU核心数
/// @param CPU_Power CPU功率
/// @param Memory 内存容量
/// @param HD 硬盘容量
/// @param ProtectGrade 防护等级
//================================================================================
IPC::IPC(double CPU_MainFreq, int CPU_CoreNum, double CPU_Power, int Memory, int HD, int ProtectGrade)
    :Computer(CPU_MainFreq, CPU_CoreNum, CPU_Power, Memory, HD), m_ProtectGrade(ProtectGrade) {
    m_Counts++;
}

//===================================IPC::IPC()===================================
/// @brief 复制构造函数
/// 工控机数量加一
///
/// @param Obj 另一个IPC对象
//================================================================================
IPC::IPC(const IPC& Obj): Computer(Obj), m_ProtectGrade(Obj.m_ProtectGrade) {
    m_Counts++;
}

//=============================IPC::GetProtectGrade()=============================
/// @brief 获取防护等级
///
/// @return 防护等级
//================================================================================
double IPC::GetProtectGrade() const {
    return m_ProtectGrade;
}

//================================IPC::GetCounts()================================
/// @brief 获取当前工控机数量
///
/// @return 当前工控机数量
//================================================================================
int IPC::GetCounts() {
    return m_Counts;
}

//===============================IPC::operator++()==============================
/// @brief 前自增
/// Computer数据自增规则同上，防护等级加1
///
/// @return 本对象引用
//================================================================================
IPC& IPC::operator++() {
    Computer::operator++();
    m_ProtectGrade++;
    return *this;
}

//===============================IPC::operator++()==============================
/// @brief 后自增
/// Computer数据自增规则同上，防护等级加1
///
/// @return 本对象的临时拷贝
//================================================================================
IPC IPC::operator++(int) {
    IPC backup(*this);
    ++(*this);
    return backup;
}

//==================================IPC::~IPC()=================================
/// @brief 析构函数
/// 工控机数量减一
//================================================================================
IPC::~IPC() {
    m_Counts--;
}

//==================================operator<<()==================================
/// @brief 输出IPC对象 
/// Computer部分数据的输出规则与Computer类中定义相同，防护等级占5列，左对齐
///
/// @param Out ostream类对象
/// @param Obj 要输出的IPC对象
/// @return 输出后的ostream类对象
//================================================================================
ostream& operator<<(ostream& Out, const IPC& Obj) {
    Out << static_cast<Computer>(Obj);
    Out << setiosflags(ios::left);
    Out << setw(5) << Obj.m_ProtectGrade;
    Out << resetiosflags(ios::left);
    return Out;
}


//=================================ReadIPCFile()================================
/// @brief 读取数量未知个工控机数据，构成一个IPC类型的向量。
/// 文本文件中每条工控机信息中顺序包含了CPU主频、CPU核心数、CPU功率、内存容量、硬盘容量、防护等级，占1行。
///
/// @param [in] path 文本文件路径
/// @param [out] vec_ipc IPC类型的向量
/// @return 0 - 正常读取; 1 - 文件无法打开
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
/// @brief 重载<运算符，比较IPC对象
/// 先比较CPU主频, 一致比较防护等级 
///
/// @param left IPC对象
/// @param right IPC对象
/// @return true - left < right成立; false - left < right不成立
//================================================================================
bool operator<(const IPC& left, const IPC& right) {
    if (left.GetCPU().GetMainFreq() == right.GetCPU().GetMainFreq()) {
        return (left.GetProtectGrade() < right.GetProtectGrade());
    }
    return (left.GetCPU().GetMainFreq() < right.GetCPU().GetMainFreq());
}

//===================================SortIPC()==================================
/// @brief 对IPC向量进行增序排序
/// 排序条件： a) CPU主频, b) 防护等级 
/// 注意：上述排序条件是有顺序的，必须按照“a条件 - b条件”的顺序来进行处理 
///
/// @param vec_ipc IPC类型的向量
/// @return 无返回值
//================================================================================
void SortIPC(vector<IPC>& vec_ipc){
    sort(vec_ipc.begin(), vec_ipc.end());
}

//=================================IncreaseIPC()================================
/// @brief 对向量中内存容量小于等于4G的工控机数据进行前自增处理
/// 自增处理后的工控机数据必须要仍然保存在A向量中原数据位置处。
///
/// @param vec_ipc IPC类型的向量
/// @return 无返回值
//================================================================================
void IncreaseIPC(vector<IPC>& vec_ipc) {
    for (auto& ipc : vec_ipc) {
        if (ipc.GetMemory() <= 4) {
            ++ipc;
        }
    }
}

//================================OutputIPCFile()===============================
/// @brief 将向量中所有工控机数据保存在文本文件
/// 文件保存格式与IPC类中operator<<的定义规则相同
///
/// @param vec_ipc IPC类型的向量
/// @param path 文本文件路径
/// @return 0 - 正常写入; 1 - 文件无法写入
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

/// @brief 主函数
void main() {
    vector<IPC> A;
    
    ReadIPCFile("d:\\source.txt", A);
    cout << "当前工控机台数: " << IPC::GetCounts() << endl;
    SortIPC(A);
    IncreaseIPC(A);
    cout << "当前工控机台数: " << IPC::GetCounts() << endl;
    OutputIPCFile(A, "d:\\res.txt");
    
    IPC t1;
    
    cout << t1 << endl;
    cout << t1++ << endl;
    cout << t1 << endl;
    cout << "当前工控机台数" << IPC::GetCounts() << endl;
    
    IPC t2(t1);
    
    cout << t2 << endl;
    cout << "当前工控机台数" << IPC::GetCounts() << endl;
}
