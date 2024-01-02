#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include <codecvt>
#include <locale>


// ��ȡ�ļ���ͳ���ַ�Ƶ�ʣ��洢Ϊmap<std::wstring, int>
// ���ݴ洢���ַ�Ƶ�ʱ���ͳ�ƽ��д�����ļ�
class FrequencyCounter {


public:
	FrequencyCounter();
	FrequencyCounter(const std::wstring& filename);
	~FrequencyCounter();

	// ���������ļ����ַ�Ƶ��
	std::map<std::wstring, int> countFrequency(const std::wstring& filename);
	
	// ��ͳ�ƽ��д�����ļ�
	void writeFrequency(const std::wstring& outputFilename);

private:
	// �洢����ȡ�ĵ��е��ַ�Ƶ��
	std::map<std::wstring, int> frequencyTable;
};