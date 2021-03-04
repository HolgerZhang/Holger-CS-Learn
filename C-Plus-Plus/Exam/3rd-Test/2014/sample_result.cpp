// 练习2
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// 表示商场商品信息的CGoods类定义
class CGoods {
private:
    int m_num; //商品编号
    string m_name; //商品名称
    float m_price; //商品价格

public:
    CGoods(int, const string&, float);
    friend ostream& operator<<(ostream&, const CGoods&);
    //商品名称、商品编号和商品价格的显示格式都要求为占10列、右对齐
};


// 表示商场所销售的路由器商品的CRouter类定义
class CRouter : public CGoods {
private:
    float m_frequency; // 路由器信号频率
    int m_channels; // 路由器端口数量

public:
    CRouter(int = 1, const string& = "M8", float = 100.0f, float = 2.4f, int = 8);
    int GetChannels() const; // 获取路由器端口数量
    float GetFrequency() const; // 获取路由器信号频率
    CRouter& operator++(); // 端口数量加1
    CRouter operator++(int);
    bool operator<(const CRouter&); // 比较两路由器商品
    friend ostream& operator<<(ostream&, const CRouter&); // 对路由器商品全部信息的显示
};


// 全局函数的前引声明

int ReadData(vector<CRouter>&, const string&); // 从文本文件中读取数量未知个路由器商品数据，构成一个向量
void DisplayData(const vector<CRouter>&); // 显示向量中所有路由器商品数据
CRouter FindMax(vector<CRouter>&); // 查找到向量中“端口数量和信号频率的乘积”最大的那个元素


// 主函数
void main() {
    vector<CRouter> s;

    ReadData(s, "D:\\Data.txt");
    cout << "读取完成后的向量为" << endl;
    DisplayData(s);

    CRouter t;
    cout << endl << "路由器对象的初始值为" << endl << t << endl;

    t = FindMax(s);
    cout << endl << "乘积最大的向量元素为" << endl << t << endl;

    cout << endl << "乘积最大的向量元素进行自增运算结果分别如下:" << endl;
    cout << t++ << endl;
    cout << t << endl;

    cout << ++t << endl;
    cout << t << endl;
}


// CGoods类成员函数实现

/**
 * \brief CGoods类构造函数
 * \param num 商品编号
 * \param name 商品名称
 * \param price 商品价格
 */
CGoods::CGoods(int num, const string& name, float price)
    : m_num(num), m_name(name), m_price(price) { }

/**
 * \brief 输出显示CGoods对象，商品名称、商品编号和商品价格的显示格式都要求为占10列、右对齐
 * \param out ostream流类对象
 * \param self 要输出的CGoods对象
 * \return 输出后的ostream流类对象
 */
ostream& operator<<(ostream& out, const CGoods& self) {
    out << setw(10) << self.m_num;
    out << setw(10) << self.m_name;
    out << setw(10) << self.m_price;
    return out;
}


// CRouter类成员函数实现

/**
 * \brief CRouter类构造函数
 * \param num 商品编号
 * \param name 商品名称
 * \param price 商品价格
 * \param frequency 路由器信号频率
 * \param channels 路由器端口数量
 */
CRouter::CRouter(int num, const string& name, float price, float frequency, int channels)
    : CGoods(num, name, price), m_frequency(frequency), m_channels(channels) { }

/**
 * \brief 获取路由器端口数量
 * \return 路由器端口数量
 */
inline int CRouter::GetChannels() const { return m_channels; }

/**
 * \brief 获取路由器信号频率
 * \return 路由器信号频率
 */
inline float CRouter::GetFrequency() const { return m_frequency; }

/**
 * \brief 前自增运算符重载函数，实现端口数量加1的操作
 * \return 自增后的对象
 */
CRouter& CRouter::operator++() {
    ++m_channels;
    return *this;
}

/**
 * \brief 后自增运算符重载函数，实现端口数量加1的操作
 * \return 自增前对象副本
 */
CRouter CRouter::operator++(int) {
    CRouter backup(*this);
    ++(*this);
    return backup;
}

/**
 * \brief 按照"端口数量和信号频率的乘积"比较两CRouter对象
 * \param other 另一个CRouter对象
 * \return true - (*this<other); false - !(*this<other)
 */
bool CRouter::operator<(const CRouter& other) {
    return (this->m_frequency * this->m_channels) < (other.m_frequency * other.m_channels);
}

/**
 * \brief 输出显示CRouter对象
 *  基类部分成员的显示格式要求与CGoods类部分相同，信号频率和端口数量的显示格式都要求为占10列、右对齐
 * \param out ostream流类对象
 * \param self 要输出的CRouter对象
 * \return 输出后的ostream流类对象
 */
ostream& operator<<(ostream& out, const CRouter& self) {
    out << static_cast<CGoods>(self);
    out << setw(10) << self.m_frequency;
    out << setw(10) << self.m_channels;
    return out;
}


// 全局函数实现

/**
 * \brief 从文本文件中读取数量未知个路由器商品数据，构成一个向量
 * \param routers 路由器数据向量
 * \param path 文本文件路径，其中顺序包含了商品编号、商品名称、商品价格、信号频率、端口数量，每条数据占1行
 * \return 0 - 成功读取; 1 - 读取失败
 */
int ReadData(vector<CRouter>& routers, const string& path) {
    ifstream inFile(path);
    if (!inFile.is_open()) {
        // 文件是否打开成功
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
 * \brief 显示向量中所有路由器商品数据
 * \param routers 要输出的路由器数据向量
 */
void DisplayData(const vector<CRouter>& routers) {
    for (const auto& router : routers) {
        cout << router << endl;
    }
}

/**
 * \brief 查找到向量中“端口数量和信号频率的乘积”最大的那个元素
 * \param routers 目标路由器数据向量
 * \return 端口数量和信号频率的乘积最大的元素
 */
CRouter FindMax(vector<CRouter>& routers) {
    return *max_element(routers.begin(), routers.end());
}