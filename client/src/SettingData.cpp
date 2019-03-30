#include "../include/SettingData.h"

/**
 * function name: SettingData
 * input: void
 * output: SettingData
 * operation: constructor
 */
SettingData::SettingData() {
    ifstream inFile;
    string s;
    inFile.open("../exe/server settings.txt");
    // assign the IP
    inFile >> s;
    char* ip = new char[s.size() + 1];
    copy(s.begin(), s.end(), ip);
    ip[s.size()] = '\0';
    strcpy(IP, ip);
    delete[] ip;
    // assign the port
    inFile >> s;
    int p = atoi(s.c_str());
    port = p;
    inFile.close();
}

/**
 * function name: getIP
 * input: void
 * output: char*
 * operation: returns the ip address
 */
char* SettingData::getIP() {
    return IP;
}

/**
 * function name: getPort
 * input: void
 * output: int
 * operation: returns the port address
 */
int SettingData::getPort() {
    return port;
}