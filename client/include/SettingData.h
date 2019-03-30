
#ifndef SETTINGDATA_H
#define SETTINGDATA_H

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

using namespace std;


class SettingData {
private:
    char* IP;
    int port;

public:
    SettingData();
    char* getIP();
    int getPort();
};
#endif /* SETTINGDATA_H */
