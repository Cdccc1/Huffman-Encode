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

	// 计算所给文件的字符频率
	std::map<std::string, int> countFrequency(const std::string& filename);
	
	// 将统计结果写入新文件
	void writeFrequency(const std::string& outputFilename);

private:
	// 存储所读取文档中的字符频率
	std::map<std::string, int> frequencyTable;
};