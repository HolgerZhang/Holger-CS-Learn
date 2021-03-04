#include <iostream>
#include "LinkedList.h"
using namespace std;

int main() {
    char cmd = 0;
    cout << "Do you want to test class LinkedList?(Y/n)";
    cin >> cmd;
    switch (cmd){
        case 'n': return 0;
        case 'Y': goto TEST;
        case 'y': goto TEST;
        default: cerr << "Invalid character." << endl; exit(1);
    }

    TEST:
    //排序方法测试 PASSED
    LinkedList<int> lst1;
    cout << "Input 8 int numbers:";
    lst1.input(8);
    cout << lst1 << ',' << lst1.length() << endl;
    lst1.sort();
    cout << lst1 << ',' << lst1.length() << endl;
    lst1.sort(true);
    cout << lst1 << ',' << lst1.length() << endl;
    //翻转方法测试 PASSED
    LinkedList<int> lst2;
    cout << "Input 5 int numbers:";
    lst2.input(5);
    cout << lst2 << endl;
    lst2.reverse();
    cout << lst2 << endl;


    //运算符方法测试PASSED
    LinkedList<int> lst3;
    cout << "lst1 " << lst1 << endl;
    cout << "lst2 " << lst2 << endl;
    cout << "lst3 " << lst3 << endl;
    //PASSED
    lst3 = lst1+lst2;
    cout << "lst3 = lst1+lst2: " << lst3 << endl;
    lst2 *= 3;
    cout << "lst2 *= 3: " << lst2 << endl;
    lst2 = lst1;
    cout << "lst2 = lst1: " << lst2 << endl;
    //PASSED
    cout << "lst1: " << lst1 << endl;
    cout << "lst1[2]: " << lst1[2] << endl;
    cout << "lst1[3]: " << lst1[3] << endl;
    cout << "lst1[7]: " << lst1[7] << endl;
    lst1[4] = 1000;
    lst1[6] = 2000;
    cout << "lst1[4] = 1000;\nlst1[6] = 2000;: "
         << endl << lst1 << endl;

    //下标测试PASSED
    LinkedList<int> lst4;
    lst4 = lst1.copy();
    cout << "lst4 = lst1.copy(): " << lst4 << endl;
    lst4.reset(1);
    cout << "lst4.reset(1): " << lst4.data() << endl;
    lst4.next();
    cout << "lst4.next(): " << lst4.data() << endl;
    cout << lst4.index() << endl;


    //数据的插入与删除 1_ERROR
    LinkedList<char> lst5;
    cout << "Input 10 characters:";
    lst5.input(10);
    lst5.show();
    lst5.rmf();
    cout << "lst5.rmf(): ";
    cout << lst5 << ',' << lst5.length() << endl;
    lst5.rml(); //ERROR
    cout << "lst5.rml(): ";
    cout << lst5 << ',' << lst5.length() << endl;
    lst5.reset(5); lst5.remove();
    cout << "lst5.reset(5); lst5.remove(): ";
    cout << lst5 << ',' << lst5.length() << endl;
    lst5.headin('p');
    cout << "lst5.headin('p'): ";
    cout << lst5 << ',' << lst5.length() << endl;
    lst5.append('q');
    cout << "lst5.append('q'): ";
    cout << lst5 << ',' << lst5.length() << endl;
    lst5.reset(6);
    cout << "lst5.reset(6)" << endl;
    lst5.insert('z');
    cout << "lst5.insert('z'): ";
    cout << lst5 << ',' << lst5.length() << endl;
    lst5.insertf('y');
    cout << "lst5.insertf('y'): ";
    cout << lst5 << ',' << lst5.length() << endl;
    lst5.clear();
    cout << "lst5.clear(): ";
    cout << lst5 << ',' << lst5.length() << endl;
    LinkedList<char> lst6;
    lst6.append('1');  lst6.show();
    char i = lst6.rmf(); lst6.show();
    cout << i << endl;
    lst6.append('2');  lst6.show();
    i = lst6.rml(); lst6.show();
    cout << i << endl;
    lst6.append('3');  lst6.show();
    i = lst6.remove(); lst6.show();
    cout << i << endl;

    return 0;
}
