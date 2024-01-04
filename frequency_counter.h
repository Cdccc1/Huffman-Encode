#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <codecvt>
#include <locale>


// ��ȡ�ļ���ͳ���ַ�Ƶ�ʣ��洢Ϊmap<std::string, int>
// ���ݴ洢���ַ�Ƶ�ʱ���ͳ�ƽ��д�����ļ�
class FrequencyCounter {


public:
	FrequencyCounter();
	FrequencyCounter(const std::string& filename);
	~FrequencyCounter();

    //char utf8char[10]{ 0 };
    

    // �������������ֽ����ж�ȡ��һ��UTF-8������ַ�
	std::string& readUTF8Char(std::ifstream& stream);

	// ���������ļ����ַ�Ƶ��
	std::map<std::string, int> countFrequency(const std::string& filename);
	
	// ��ͳ�ƽ��д�����ļ�
	void writeFrequency(const std::string& outputFilename);

private:
	// �洢����ȡ�ĵ��е��ַ�Ƶ��
	std::map<std::string, int> frequencyTable;

	// utf-8�����ַ�
    std::string utf8char;
};