/**
 * @file    2.cpp
 * @create  2020/03/17
 * @encoding GBK
 * @author  Holger
 * @description
 * 实验三 数据类型和数组
 *  从键盘输入一个不包括空格的仅由英文字母组成的字符串，长度不超过200
 *  个字符。统计26个英文字母的使用频率（出现的次数），不区分大小写。
 *  最后按使用频率从大到小的顺序输出字母（小写字母）及其使用频率，
 *  没有出现的字母不输出。
 * 备注：使用map也可统计出现频率
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool comp(const vector<int> &left, const vector<int> &right);

int main() {
    char str[201];    //英文字母组成的字符串
    cout << "请输入一个不包括空格的仅由英文字母组成的字符串，长度不超过200：" << endl;
    cin >> str;
    vector<vector<int>> alphabet;    //小写字母表
    //alphabet下标代表字母的顺序，元素为vector<int>
    //vector<int>的第一个元素为字母的ASCII值，第二个为出现频率
    for (char ch = 'a'; ch <= 'z'; ch++) {    //初始化字母表
        vector<int> alpha = {ch, 0};
        alphabet.push_back(alpha);
    }
    int i = 0;
    while (str[i]) {    //统计字母出现频率
        char lowerChar = (str[i] <= 'Z') ? str[i] + 32 : str[i];
        alphabet[lowerChar - 'a'][1]++;
        i++;
    }
    //按字母使用频率从大到小排序
    sort(alphabet.begin(), alphabet.end(), comp);
    //输出结果
    for (int j = 0; j < 26; j++) {
        if (alphabet[j][1] == 0) {    //没有出现的字母不输出
            break;
        }
        cout << "字母" << (char) alphabet[j][0]
             << "出现了" << alphabet[j][1] << "次" << endl;
    }
    return 0;
}

/*==============================================
比较两个字母出现频率大小(>)，供sort函数调用
参数说明：
	参数均为vector<int>的常引用，1号元素为出现频率
返回值说明：
	true——left代表字母出现频率大于right代表字母
	false——left代表字母出现频率不大于right代表字母
==============================================*/
bool comp(const vector<int> &left, const vector<int> &right) {
    return (left[1] > right[1]);
}
