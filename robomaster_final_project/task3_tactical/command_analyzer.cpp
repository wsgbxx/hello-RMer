#include <iostream>
#include <fstream>//文件流对象
#include <string>
#include <map>
using namespace std

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <log_file_path>" <<endl;
        return 1;//程序异常终止
    }// 检查命令行参数

    string filename = argv[1];//将日志文件路径转换为字符串
    ifstream file(filename);// 创建一个输入文件流对象并 尝试 打开指定的文件
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return 1;
    }// 检查文件是否成功打开

    map<string, int> commandCount;
    string line;

    while (getline(file, line)) {//循环读取文件的每一行，直到文件结束。
        if (!line.empty()) {
            commandCount[line]++;
        }
    }

    file.close();//显式关闭文件

    cout << "Command execution statistics:" << endl;
    for (const auto& pair : commandCount) {
        cout << pair.first << ": " << pair.second << " times" << std::endl;
    }
    //遍历map中的所有键值对, 
    //auto关键字自动推导变量类型（这里是pair<const string, int>）。

    //const表示不会修改元素。

    //&表示通过引用访问，避免不必要的拷贝。

    return 0;
}
//is_open()是文件流对象的成员函数，如果文件成功打开返回true，否则返回false。
//string line: 用于存储从文件中读取的每一行文本。
//getline()函数从输入流中读取一行文本（直到换行符）并存储到line变量中。
