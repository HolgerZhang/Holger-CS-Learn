//main.cpp
#include "account.h"
#include "controller.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

/* 运行说明：
 * 程序可以以无参数方式运行, 默认打开/新建名为"command_this_runtime.account"的文本文件在当前运行目录下
 *      并[读取文件中的命令且]保存本次正确运行的命令；
 * 程序也可以接受一个参数, 表示打开并读取该文本文件的记录并保存本次正确运行的命令到这个文件。
 */

int main(int argc, char* argv[]) {
    //起始日期的创建
    Date date(2019, 11, 1); cout << "Default date: 2019-11-01." << endl;
    Controller controller(date);                 //控制台程序
    string cmdLine;                              //命令行
    //文件位置 读取后缀为account的文件
    char* FILE_NAME = const_cast<char *>(argv[1] ? argv[1] : "command_this_runtime.account");

    ifstream FileIn(FILE_NAME);     //读取历史记录
    if (FileIn) {
        cout << "History:" << endl;
        while(getline(FileIn, cmdLine)) {
            try {
                controller.run(cmdLine, false);
            } catch (exception &e){     //文件错误信息捕获
                cout << "Bad line in " << FILE_NAME << ": " << cmdLine << endl;
                cout << "Error: " << e.what() << endl;
                FileIn.close();
                return 1;
            }
        }
        FileIn.close();
    }

    controller.help();      //显示帮助文档

    ofstream FileOut(FILE_NAME, ios_base::app); //执行并追加写入命令行
    cout << "Commands:" << endl;
    while (!controller.isEnd()) {
        cout << controller.getDate() << "\tTotal: " << Account::getTotal()
             << "\t>>> ";
        getline(cin, cmdLine);
        try {
            if(controller.run(cmdLine))
                FileOut << cmdLine << endl; //写入命令行
        } catch (AccountException &ae) {    //捕获账户错误信息
            cout << "Bad line in " << "<stdin> " << cmdLine << endl;
            cout << "Error(#" << ae.getAccount()->getId() << "): "
                 << ae.what() << endl;
        } catch (exception &e){             //捕获其他错误信息
            cout << "Bad line in " << "<stdin> " << cmdLine << endl;
            cout << "Error: " << e.what() << endl;
        }
    }
    FileOut.close();
    return 0;
}
