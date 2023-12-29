#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <codecvt>
#include <locale>
class FrequencyCounter {
public:
	FrequencyCounter();
	FrequencyCounter(const std::wstring& filename);
	~FrequencyCounter();

	// 计算所给文件的字符频率
	std::map<std::wstring, int> countFrequency(const std::wstring& filename);
	
	// 将统计结果写入新文件
	void writeFrequency(const std::wstring& outputFilename);
private:
	// 存储所读取文档中的字符频率
	std::map<std::wstring, int> frequency_table;
};