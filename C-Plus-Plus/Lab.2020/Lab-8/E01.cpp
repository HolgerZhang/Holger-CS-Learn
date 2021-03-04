/**
 * @file E01.cpp
 * @create 2020-06-29 12:13
 * @encoding UTF-8
 * @author Holger
 * @description
 * 请以CPerson类为基类定义一个派生类CStudent,要求该类具有以下属性成员和成员函数：
 * - 学生所属大学名称，string类型表示
 * - 学生所在年级，int类型表示
 * - CStudent();    // 以{"无名"、18岁、男性、"苏州大学"、1年级}为默认值的无参构造函数；
 * - CStudent(const string &name, int age, char sex, const string &collageName, int grade);  // 带参数的构造函数
 * - void print();    // 显示学生类对象的所有信息
 * 编写对CStudent类的测试程序，要求如下：
 * (1) 定义一个学生类student1，属性值为默认属性值，并输出其信息
 * (2) 定义一个学生类student2，其属性为：
 * - 姓名："Liming"
 * - 年龄：21
 * - 性别：男
 * - 大学：苏州大学
 * - 年级：1
 * (3) 提供CStudent类的完整测试程序，要求界面友好，输出结果应该有相应的提示信息。
 **/

#include <iostream>
#include <string>

using namespace std;

/**
 * CPerson 基类定义
 */
class CPerson {
private:
    string m_name;       // 姓名
    int m_age;           // 年龄
    char m_sex;          // 性别

public:
    CPerson(const string &name, int age, char sex) {
        m_name = name;
        m_age = age;
        m_sex = sex;
    }

    CPerson() {
        m_name = "无名";
        m_age = 18;
        m_sex = 'M';
    }

    void print() {
        cout << "\n姓名：" << m_name << "\n年龄：" << m_age << "\n";
        if (m_sex == 'M')
            cout << "性别： 男" << endl;
        else
            cout << "性别： 女" << endl;
    }
};

/**
 * 派生类 CStudent 定义
 */
class CStudent : public CPerson {
private:
    string m_collageName;    // 所属大学名称
    int m_grade;        // 所在年级

public:
    // 以{"无名"、18岁、男性、"苏州大学"、1年级}为默认值的无参构造函数；
    CStudent() : CPerson(), m_collageName("苏州大学"), m_grade(1) {}

    // 带参数的构造函数
    CStudent(const string &name, int age, char sex, const string &collageName, int grade)
            : CPerson(name, age, sex), m_collageName(collageName), m_grade(grade) {}

    // 显示学生类对象的所有信息
    void print() {
        CPerson::print();
        cout << "大学：" << m_collageName << "\n年级：" << m_grade << endl;
    }
};


int main() {
    cout << "=========================\n";
    // 定义一个学生类student1，属性值为默认属性值，并输出其信息
    CStudent student1;
    cout << "学生类对象student1的信息为：";
    student1.print();
    cout << "=========================\n";
    // 定义一个学生类student2
    CStudent student2("Liming", 21, 'M', "苏州大学", 1);
    cout << "学生类对象student2的信息为：";
    student2.print();
    cout << "=========================\n";
    return 0;
}
