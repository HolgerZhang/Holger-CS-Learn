"""
71. 使用 random 模块生成一个整数类型的随机数集合：生成 100 个[0,1000]范
    围内的随机数。这些数字组成集合 A。同理，按此方法生成集合 B。在此基
    础上实现以下功能：
    a)  显示 A 和 B 的结果。要求每行最多显示 10 个数，每个数占 5 列，右对齐；
    b)  要求用户输入 A | B 和 A & B 的结果，并告诉用户他(或她)的答案是
        否正确。如果用户回答错误，允许他(或她)修改解决方案，然后重新验证
        用户输入的答案。如果用户三次提交的答案均不正确，程序将显示正确结果。
"""
import random


def Display(s):
    j = 0
    for i in s:
        print("%5d" % i, end='')
        j += 1
        if j % 10 == 0:
            print()
    print()


def InputAnswer():
    print('NOTICE: Numbers are separated by whitespace.')
    answer1 = set(map(int, input('Input set A|B:').split()))
    answer2 = set(map(int, input('Input set A&B:').split()))
    return answer1, answer2


def judgement(getAnswer, realAnswer, cnt):
    if cnt <= 0:
        return False
    answer = getAnswer()
    if all(map(lambda x: x[0] == x[1], zip(answer, realAnswer))):
        return True
    else:
        cnt -= 1
        print('Wrong! You can input it again. %d chance(s) left.\n' % cnt)
        judgement(InputAnswer, realAnswer, cnt)


if __name__ == "__main__":
    setA = {random.randint(0, 1000) for i in range(100)}
    setB = {random.randint(0, 1000) for j in range(100)}
    print('set A:')
    Display(setA)
    print('set B:')
    Display(setB)
    real = (setA | setB, setA & setB)
    print('Now, you should input your answers...\n'
          'You have 3 chances.')
    if judgement(InputAnswer, real, 3):
        print('Your answer is right!')
    else:
        print('Wrong! Right answer is: ')
        print('A|B:')
        Display(real[0])
        print('A&B:')
        Display(real[1])