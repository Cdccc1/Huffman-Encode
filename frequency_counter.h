#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <codecvt>
#include <locale>


// 读取文件，统计字符频率，存储为map<std::string, int>
// 根据存储的字符频率表，将统计结果写入新文件
class FrequencyCounter {


public:
	FrequencyCounter();
	FrequencyCounter(const std::string& filename);
	~FrequencyCounter();

    //char utf8char[10]{ 0 };
    

    // 辅助函数，从字节流中读取下一个UTF-8编码的字符
	std::string& readUTF8Char(std::ifstream& stream);

	// 计算所给文件的字符频率
	std::map<std::string, int> countFrequency(const std::string& filename);
	
	// 将统计结果写入新文件
	void writeFrequency(const std::string& outputFilename);

private:
	// 存储所读取文档中的字符频率
	std::map<std::string, int> frequencyTable;

	// utf-8编码字符
    std::string utf8char;
};