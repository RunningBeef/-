#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>

bool readFile()
{
      std::ifstream inFile("C:\\Users\\86130\\Desktop\\sharedir\\test-problem\\snap.csv", std::ios::in);
      if (!inFile)
      {
            std::cout << "打开文件失败！" << std::endl;
            exit(1);
      }
      else
      {
            std::cout << "打开文件成功！" << std::endl;
      }
      int i = 0;
      std::string line;
      std::string field;
      while (getline(inFile, line)) // getline(inFile, line)表示按行读取CSV文件中的数据
      {
            std::cout << "line: " << line << std::endl;
            // string field;
            // istringstream sin(line); //将整行字符串line读入到字符串流sin中

            // getline(sin, field, ',');           //将字符串流sin中的字符读入到field字符串中，以逗号为分隔符
            // cout << atoi(field.c_str()) << " "; //将刚刚读取的字符串转换成int

            // getline(sin, field);           //将字符串流sin中的字符读入到field字符串中，以逗号为分隔符
            // cout << field.c_str() << endl; //将刚刚读取的字符串转换成int

            i++;
      }
      inFile.close();
      std::cout << "共读取了：" << i << "行" << std::endl;
      std::cout << "读取数据完成" << std::endl;
}

bool writeFile()
{
      std::ofstream outFile("snap.csv", std::ios::out);
      // ios::out：如果没有文件，那么生成空文件；如果有文件，清空文件
      if (!outFile)
      {
            std::cout << "打开文件失败！" << std::endl;
            exit(1);
      }
      //写入3行数据
      for (int i = 0; i < 3; i++)
      {
            outFile << 12 << ",";
            outFile << 13 << ",";
            outFile << 14 << ",";
            outFile << "NaN" << std::endl;
      }
      outFile.close();
      std::cout << "写入数据完成" << std::endl;
}

int main()
{
      // readFile();
      writeFile();
      return 0;
}