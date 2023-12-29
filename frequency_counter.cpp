#include "frequency_counter.h"


FrequencyCounter::FrequencyCounter() {}


FrequencyCounter::FrequencyCounter(const std::wstring& filename) {
    // �ڹ��캯���м����ַ�Ƶ��
    this->frequency_table = countFrequency(filename);
}


FrequencyCounter::~FrequencyCounter() {}


std::map<std::wstring, int> FrequencyCounter::countFrequency(const std::wstring& filename) {
    std::wifstream file(filename);
    
    // ���õ�ǰ�ļ���ΪUTF-8
    file.imbue(std::locale(file.getloc(), new std::codecvt_utf8<wchar_t>));

    if (!file.is_open()) {
        throw std::runtime_error("FrequencyCounter�޷����ļ�");
    }

    std::map<std::wstring, int> frequency_table;
    std::wstring line;
    while (std::getline(file, line)) {
        for (wchar_t ch : line) {
            frequency_table[std::wstring(1, ch)]++;
        }
    }
    file.close();
    return frequency_table;
}


void FrequencyCounter::writeFrequency(const std::wstring& outputFilename) {
    std::wofstream outFile(outputFilename);
    outFile.imbue(std::locale(outFile.getloc(), new std::codecvt_utf8<wchar_t>));

    if (!outFile.is_open()) {
        throw std::runtime_error("FrequencyCounter�޷������ļ�: ");
    }

    for (auto& pair : frequency_table) {
        outFile << pair.first << L": " << pair.second << L"\n";
    }
    outFile.close();
}


