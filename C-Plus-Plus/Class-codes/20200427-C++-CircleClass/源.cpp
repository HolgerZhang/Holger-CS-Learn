#include <iostream>
using namespace std;

const float PI = 3.14159f;
const float FencePrice = 35;
const float ConcretePrice = 20;
//声明类Circle 及其数据和方法
class Circle
{
private:
	float radius;
public:
	Circle(float radius); //构造函数
	float Circumference() const; //圆周长
	float Area() const; //圆面积
};

// 类的实现
// 构造函数初始化数据成员radius
Circle::Circle(float radius)
{
	this->radius = radius;
}
// 计算圆的周长
float Circle::Circumference() const
{
	return 2 * PI * radius;
}
// 计算圆的面积
float Circle::Area() const
{
	return PI * radius * radius;
}

int main()
{
	float radius;
	float FenceCost, ConcreteCost;
	// 提示用户输入半径
	cout << "Enter the radius of the pool: ";
	cin >> radius;
	// 声明Circle 对象
	Circle* p1 = new Circle(radius);
	Circle* p2 = new Circle(radius + 3);
	// 计算栅栏造价并输出
	FenceCost = p2->Circumference() * FencePrice;
	cout << "Fencing Cost is ￥" << FenceCost << endl;
	// 计算过道造价并输出
	ConcreteCost = (p2->Area() - p1->Area()) * ConcretePrice;
	cout << "Concrete Cost is ￥" << ConcreteCost << endl;
	delete p1;
	delete p2;
	return 0;
}