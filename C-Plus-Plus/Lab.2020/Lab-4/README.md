# C++ʵ�鱨��

### ʵ���� ����

�����ļ����룺GBK (source code encoding)

��˵���ĵ����룺GBK (this file encoding)

### һ.   ʵ��Ŀ��

ͨ������ʵ��Ҫ�ﵽ����Ŀ�ģ�

1.	���⺯���Ļ�������

2.	���պ����Ķ��塢���ú�������������

3.	���������ں������ù����е���Ҫ���ã����������ʹ�÷���

4.	���Ⲣ���պ�������Ĭ��ֵ�ͺ������صľ���ʹ�÷���

### ��.	ʵ������

1.	дһ���ж�һ�������Ƿ��������ĺ���IsPrime��������������1000���ڵ�����������ÿ�� 8���������Ļ�ϡ�����ԭ��Ҫ��Ϊ��

~~~c++
int IsPrime(int Num);
~~~

2.	��дһ������InverseBits����һ�������ĸ�λ���ֶԵ������������б�д���Դ��룬��������������µ����������磺���� 123�����øú���֮�󣬵õ����Ϊ  321������ԭ��Ҫ��Ϊ��

~~~c++
int InverseBits(int Num);
~~~

3.	���һ������Calc��������¹��ܡ�

-	��������������Ϊ������
-	��������Լ������С������������Ҫ��Calc������ʹ�������������
-	�����ں���������ʹ�����á�
-	��д�����������Ժ������ܡ�
-	����ԭ��Ҫ��Ϊ��

~~~c++
void Calc(int Num1, int Num2, int &GCD, int &LCM);
~~~

4.	��д�������غ���printOut�ֱ�ʵ�����������������������string�ַ��������Ҫ�����£�

-	��������ռ10�У��Ҷ���
-	�����ͣ���4λС��
-	�ַ�����ռ10�У��Ҷ���
-	��д���Գ��򣬲��Գ����е����������������ַ������û����롣