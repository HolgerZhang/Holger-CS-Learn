#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H


#include <iostream>
#include "Node.h"
#include <cassert>
using namespace std;

template <class T>          //链表类模板
class LinkedList{
private:
    //私有数据成员
    Node<T> *head, *rear;           //表头和表尾指针
    Node<T> *prev, *curr;           //记录表当前遍历位置的指针, 由insert和del操作更新
    int size;                       //表中元素的个数
    int position;                   //当前元素在表中的位置序号, 由reset调用

    //结点操作方法
    //生成新结点, item为数据域, nextP为指针域
    Node<T> *newNode(const T &item, Node<T> *nextP=NULL);
    void free(Node<T> *P);          //释放结点

    //私有数据处理方法
    //复制链表L到当前链表(假设为空), 由复制构造函数和operator=调用
    void copy(const LinkedList<T> &L);
    void swap(int pos);             //交换两个结点, 当前位置到pos
    void swap(int pos1, int pos2);  //交换两个结点的数据, pos1到pos2

public:
    LinkedList();                           //构造函数
    LinkedList(const LinkedList<T> &L);     //复制构造函数
    ~LinkedList();                          //析构函数

    //常用运算符= [] + += * *=的重载函数
    //重载赋值运算符
    LinkedList<T> &operator=(const LinkedList<T> &L);
    //重载下标运算符
    T &operator[](int pos);
    //重载+运算符, 返回拼接的两个链表
    LinkedList<T> &operator+(LinkedList<T> &L);
    //重载+=运算符
    LinkedList<T> &operator+=(LinkedList<T> &L);
    //重载*运算符
    LinkedList<T> &operator*(int n);
    //重载*=运算符
    LinkedList<T> &operator*=(int n);

    //基础数据接口
    int length() const { return size; }                    //获取元素个数
    bool isEmpty() const { return (size == 0); }           //判断是否为空链表
    T &data();                          //返回当前结点成员数据的引用
    const T &data() const ;             //返回当前结点成员数据的常引用
    T &find(int pos);                   //返回指定位置结点成员数据的引用
    LinkedList<T> &copy();              //获得链表的深复制对象

    //索引方法
    void reset(int pos=0);              //初始化索引位置
    void next();                        //索引指向下一个结点
    bool isEnd()const { return (curr == NULL); }           //判断索引是否到达表的末尾
    int index() const { return position; }                 //返回索引位置

    //结点(数据)操作方法
    //插入
    void headin(const T &item);         //在表头插入结点
    void append(const T &item);         //在表尾插入结点
    void insertf(const T &item);        //在当前节点之前插入结点
    void insert(const T &item);         //在当前节点之后插入结点

    //扩展
    void extend(LinkedList<T> &L);      //用一个同类型的链表对象扩展本对象
    //删除
    T rmf();                            //删除头结点
    T rml();                            //删除尾结点
    T remove();                         //删除当前结点

    //数据处理方法
    //清空链表并释放所有结点的内存空间, 但保留链表对象. 也被析构函数和operator=调用
    void clear();
    void input(int number);             //支持cin的数据批量输入
    //链表对象输出show()方法依赖全局函数: ostream &operator<<(ostream &out, LinkedList<T> lst)
    void show(){ cout << *this << endl; }
    void sort(bool reverse=false);      //原地排序(冒泡排序法)
    void reverse();                     //原地翻转

};


//类实现部分
//private方法实现

//结点操作方法
//生成新结点, item为数据域, nextP为指针域
template<class T>
Node<T> *LinkedList<T>::newNode(const T &item, Node<T> *nextP) {
    Node<T> *newNodePtr;
    newNodePtr = new Node<T>(item, nextP);
    if (NULL == newNodePtr){
        cerr << "Memory allocation failure!";
        exit(1);
    }
    return newNodePtr;
}
template<class T>               //释放结点
void LinkedList<T>::free(Node<T> *P) {
    delete P;
}

//私有数据处理方法
//复制链表L到当前链表(假设为空), 由复制构造函数和operator=调用
template<class T>
void LinkedList<T>::copy(const LinkedList<T> &L) {
    if(L.size == 0) {
        this->clear();
        return;
    }
    this->head = this->rear = newNode(L.head->data);
    for (Node<T> *srcNode = L.head->next();
         srcNode != NULL;
         srcNode = srcNode->next())  {
        Node<T> *newNodePtr = newNode(srcNode->data);
        this->rear->insert(newNodePtr);
        this->rear = newNodePtr;
    }
    this->size = L.size;
    reset(position = L.index());
}
template<class T>           //交换两个结点的数据, 当前位置到pos
void LinkedList<T>::swap(int pos) {
    assert(pos>=0 && pos<size);
    assert(position>=0 && position<size);
    T temp = curr->data;
    curr->data = find(pos);
    find(pos) = temp;
    reset();
}
template<class T>           //交换两个结点的数据, pos1到pos2
void LinkedList<T>::swap(int pos1, int pos2) {
    assert(pos1>=0 && pos1<size);
    reset(pos1);
    swap(pos2);
}

//public方法实现
//构造函数
template<class T>
LinkedList<T>::LinkedList()
    :head(NULL), rear(NULL), prev(NULL), curr(NULL), size(0), position(0) { }
template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &L)
    :head(NULL), rear(NULL), prev(NULL), curr(NULL), size(0), position(0) {
    this->copy(L);
}
//析构函数
template<class T>
LinkedList<T>::~LinkedList() {
    this->clear();
}

//运算符重载函数 (常用运算符= [] + += * *=)
//重载赋值运算符
template<class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &L) {
    this->clear();
    this->copy(L);
    return *this;
}
//重载下标运算符
template<class T>
T &LinkedList<T>::operator[](int pos) {
    assert(pos>=0 && pos<size);
    reset(pos);
    return data();
}
template<class T>           //重载+运算符, 返回拼接的两个链表
LinkedList<T> &LinkedList<T>::operator+(LinkedList<T> &L){
    static LinkedList<T> result = *this;
    result.extend(L);
    return result;
}
template<class T>           //重载+=运算符
LinkedList<T> &LinkedList<T>::operator+=(LinkedList<T> &L) {
    this->extend(L);
    return *this;
}

template<class T>           //重载*运算符
LinkedList<T> &LinkedList<T>::operator*(int n) {
    assert(n>0);
    if(n==1)
        return *this;
    static LinkedList<T> result;
    for(int i=0; i<n; ++i)
        result.extend(*this);
    return result;
}
template<class T>           //重载*=运算符
LinkedList<T> &LinkedList<T>::operator*=(int n) {
    assert(n>0);
    if(n==1)
        return *this;
    LinkedList<T> temp = *this;
    for(int i=0; i<n-1; ++i)
        this->extend(temp);
    return *this;
}

//基础数据接口
//返回对当前结点成员数据的引用
template<class T>
const T& LinkedList<T>::data() const{
    if (curr == NULL) {
        cerr << "Current node is invalid." << endl;
        exit(1);
    }
    return curr->data;
}
template<class T>
T &LinkedList<T>::data() {
    if (curr == NULL) {
        cerr << "Current node is invalid." << endl;
        exit(1);
    }
    return curr->data;
}
//返回指定位置结点成员数据的引用
template<class T>
T &LinkedList<T>::find(int pos) {
    assert(pos>=0 && pos<size);
    reset(pos);
    return curr->data;
}
//获得链表的深复制对象
template<class T>
LinkedList<T> &LinkedList<T>::copy() {
    static LinkedList<T> temp;
    temp.copy(*this);
    return temp;
}

//索引方法
/* 初始化索引位置
 * pos无限制
 * 当 pos 在 0 和 size 之间时 prev 和 curr 正常指示;
 * 当 pos 为 0 时            prev = NULL, curr = head;
 * 当 pos 为 size 时         prev = rear, curr = NULL;
 * 当 pos 取其他值时          prev = curr = NULL
*/
template<class T>
void LinkedList<T>::reset(int pos) {
    if(pos>=0 && pos<=size){
        position = 0;
        prev = NULL;
        curr = head;
        while(pos--) next();
    } else{
        position = pos;
        prev = NULL;
        curr = NULL;
    }
}
//索引指向下一个结点
template<class T>
void LinkedList<T>::next() {
    position++;
    prev = curr;
    if (curr != NULL)
        curr = curr->next();
}

//结点(数据)操作方法
//插入结点
template<class T>       //在表头插入结点
void LinkedList<T>::headin(const T &item) {
    head = newNode(item, head);
    if(isEmpty()) rear = head;
    ++size;
    reset(++position);
}
template<class T>       //在表尾插入结点
void LinkedList<T>::append(const T &item) {
    Node<T> *newNodePtr = newNode(item);
    if(isEmpty())
        rear = head = newNodePtr;
    else{
        rear->insert(newNodePtr);
        rear = newNodePtr;
    }
    ++size;
    reset(position);
}
template<class T>       //在当前节点之前插入结点
void LinkedList<T>::insertf(const T &item) {
    assert(curr != NULL);
    Node<T> *newNodePtr = newNode(item, curr);
    if(prev != NULL)
        prev->insert(newNodePtr);
    else
        head = prev = newNodePtr;
    ++size;
    reset(++position);
}
template<class T>       //在当前节点之后插入结点
void LinkedList<T>::insert(const T &item) {
    assert(curr != NULL);
    Node<T> *newNodePtr = newNode(item, curr->next());
    curr->insert(newNodePtr);
    if(rear == curr) rear = newNodePtr;
    ++size;
    reset(position);
}
//扩展链表
template<class T>           //用一个同类型的LinkedList对象扩展本对象
void LinkedList<T>::extend(LinkedList<T> &L) {
    for(int i=0; i<L.size; ++i)
        append(L.find(i));
    L.reset();
}
//删除结点
template<class T>       //删除头结点
T LinkedList<T>::rmf() {
    if(isEmpty()){
        cerr << "RemoveError: List is empty." << endl;
        exit(1);
    }
    Node<T> *removeNode = head;
    head = head->next();
    if(--size == 0)
        rear = NULL;
    reset((--position>=0)?position:0);
    T item = removeNode->data;
    free(removeNode);
    return item;
}
template<class T>       //删除尾结点
T LinkedList<T>::rml() {
    if(isEmpty()){
        cerr << "RemoveError: List is empty." << endl;
        exit(1);
    }
    int pos = position;
    T item = rear->data;
    reset(size-1);
    this->remove();
    if(isEmpty())
        reset((pos>=0 && pos<size)?pos:0);
    return item;
}
template<class T>       //删除当前结点
T LinkedList<T>::remove() {
    assert(curr != NULL);
    T item;
    item = rear->data;
    if(curr == head)
        head = curr->next();
    if(curr == rear)
        rear = prev;
    if(prev != NULL)
        prev->del();
    free(curr);
    --size;
    reset(position);
    return item;
}

//数据处理方法
template<class T>       //清空链表并释放所有结点的内存空间, 但保留链表对象. 也被析构函数和operator=调用
void LinkedList<T>::clear(){
    while (!isEmpty())
        rmf();
}
template<class T>       //支持cin的数据批量输入
void LinkedList<T>::input(int number) {
    for (int i=0; i<number; ++i) {
        T x;
        cin >> x;
        this->append(x);
    }
}
template<class T>       //原地排序(冒泡排序法)
void LinkedList<T>::sort(bool reverse) {
    for(int i=0; i<size-1; ++i) {
        int t = i;
        while (i >= 0){
        if (!reverse) {
            if (find(i) > find(i + 1))
                swap(i, i+1);
        } else {
            if (find(i) < find(i + 1))
                swap(i, i+1);
        }
        i -= 1;
        }
        i = t;
    }
}
template<class T>       //原地翻转
void LinkedList<T>::reverse() {
    reset(0);
    for(int i=0; i<size/2; reset(++i))
        swap(size - 1 - i);
}


//全局函数
template<class T>       //重载<<运算符以显示链表
ostream &operator<<(ostream &out, LinkedList<T> lst) {
    out << '[';
    lst.reset(0);
    for (int i = 0; i < lst.length(); ++i) {
        out << lst[i];
        if (i != lst.length() - 1)
            out << ", ";
    }
    out << ']';
    return out;
}


#endif //_LINKEDLIST_H
