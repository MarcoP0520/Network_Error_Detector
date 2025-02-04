//
// Created by marco on 2/4/2025.
//

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>


bool Pingip(const std::string& ipAddress) {
    std::string command_prompt = "ping -n 1 " + ipAddress + " > nul";
    int ping = system(command_prompt.c_str());
    return ping == 0;
}

int main() {
   std::vector<std::string> ipAddress_list{
       "10.0.0.1",
       "192.168.0.1",
   };
    std::vector<std::string> devices{
        "Router 1",
        "Test Device",
    };
    if(ipAddress_list.size() != devices.size()) {
        std::cout << "Error: Number of IP addresses and Device mismatch!" << std::endl;
    }
    else {

        for(int pos = 0; pos < ipAddress_list.size(); pos++) {
            std::string ip = ipAddress_list[pos];
            std::string device = devices[pos];

            bool status =  Pingip(ip);

            if(status == false) {
                std::cout <<"ALERT: " + device + " " + ip + " is currently down." << std::endl;
            }
            else {
                std::cout <<device + " " + ip + " Connected" << std::endl;
            }
        }
    }


};