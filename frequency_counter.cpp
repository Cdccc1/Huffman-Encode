#include "frequency_counter.h"


FrequencyCounter::FrequencyCounter() {}


FrequencyCounter::FrequencyCounter(const std::wstring& filename) {
    // �ڹ��캯���м����ַ�Ƶ��
    this->frequencyTable = countFrequency(filename);
}


FrequencyCounter::~FrequencyCounter() {}


// �����ַ�Ƶ��
std::map<std::wstring, int> FrequencyCounter::countFrequency(const std::wstring& filename) {
    std::wifstream file(filename);
    
    // ���õ�ǰ�ļ���ΪUTF-8
    file.imbue(std::locale(file.getloc(), new std::codecvt_utf8<wchar_t>));

    if (!file.is_open()) {
        throw std::runtime_error("FrequencyCounter�޷����ļ�");
    }

    std::map<std::wstring, int> frequencyTable;
    std::wstring line;
    while (std::getline(file, line)) {
        for (wchar_t ch : line) {
            frequencyTable[std::wstring(1, ch)]++;
        }
    }
    file.close();
    return frequencyTable;
}


void FrequencyCounter::writeFrequency(const std::wstring& outputFilename) {
    std::wofstream outFile(outputFilename);
    outFile.imbue(std::locale(outFile.getloc(), new std::codecvt_utf8<wchar_t>));

    if (!outFile.is_open()) {
        throw std::runtime_error("FrequencyCounter�޷������ļ�: ");
    }

    for (auto& pair : frequencyTable) {
        outFile << pair.first << L": " << pair.second << L"\n";
    }
    outFile.close();
}


