# C++实验报告

### 实验八 继承

代码文件编码：UTF-8 (source code encoding)

本说明文档编码：UTF-8 (this file encoding)

### 一.   实验目的

通过本次实验要达到如下目的：

(1)	掌握C++语言的基础知识

(2)	熟悉C++语言的开发环境visual studio 2010

(3)	熟悉并掌握类的继承与组合。

(4)	掌握程序调试的基本技巧。

### 二.	实验内容

编写程序解决以下问题：

E01. 有1个person类定义如下：

~~~c++
class CPerson
{
private:
    string  m_name;       // 姓名
    int   m_age;		      // 年龄
    char  m_sex;		     // 性别
public:
    CPerson(const string &name, int age, char sex)
    {
        m_name = name;
        m_age = age;
        m_sex = sex;
    }
    CPerson()
    {
        m_name = "无名";
        m_age = 18;
        m_sex = 'M';
    }
    void  print()
    {
        cout<<"\n姓名："<<m_name<<"\n年龄："<<m_age<<"\n";
        if (m_sex == 'M')
            cout<<"性别： 男"<<endl;
        else 
            cout<<"性别： 女"<<endl;
    } 
};
~~~

请以CPerson类为基类定义一个派生类CStudent,要求该类具有以下属性成员和成员函数：

-	学生所属大学名称，string类型表示
-	学生所在年级，int类型表示
-	`CStudent();`    // 以 `{"无名"、18岁、男性、"苏州大学"、1年级}` 为默认值的无参构造函数；
-	`CStudent(const string &name, int age, char sex, const string &collageName, int grade);`  // 带参数的构造函数
-	`void print();`    // 显示学生类对象的所有信息

编写对CStudent类的测试程序，要求如下：

(1)	定义一个学生类student1，属性值为默认属性值，并输出其信息

(2)	定义一个学生类student2，其属性为：

-	姓名："Liming"
-	年龄：21
-	性别：男
-	大学：苏州大学
-	年级：1

(3)	提供CStudent类的完整测试程序，要求界面友好，输出结果应该有相应的提示信息。
