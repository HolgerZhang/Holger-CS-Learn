#include <iostream>
using namespace std;

const float PI = 3.14159f;
const float FencePrice = 35;
const float ConcretePrice = 20;
//������Circle �������ݺͷ���
class Circle
{
private:
	float radius;
public:
	Circle(float radius); //���캯��
	float Circumference() const; //Բ�ܳ�
	float Area() const; //Բ���
};

// ���ʵ��
// ���캯����ʼ�����ݳ�Աradius
Circle::Circle(float radius)
{
	this->radius = radius;
}
// ����Բ���ܳ�
float Circle::Circumference() const
{
	return 2 * PI * radius;
}
// ����Բ�����
float Circle::Area() const
{
	return PI * radius * radius;
}

int main()
{
	float radius;
	float FenceCost, ConcreteCost;
	// ��ʾ�û�����뾶
	cout << "Enter the radius of the pool: ";
	cin >> radius;
	// ����Circle ����
	Circle* p1 = new Circle(radius);
	Circle* p2 = new Circle(radius + 3);
	// ����դ����۲����
	FenceCost = p2->Circumference() * FencePrice;
	cout << "Fencing Cost is ��" << FenceCost << endl;
	// ���������۲����
	ConcreteCost = (p2->Area() - p1->Area()) * ConcretePrice;
	cout << "Concrete Cost is ��" << ConcreteCost << endl;
	delete p1;
	delete p2;
	return 0;
}