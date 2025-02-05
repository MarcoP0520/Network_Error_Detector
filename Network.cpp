//
// Created by marco on 2/4/2025.
//

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <algorithm>

bool Pingip(const std::string& ipAddress) {
    std::string command_prompt = "ping -n 1 " + ipAddress + " > nul";
    int ping = system(command_prompt.c_str());
    return ping == 0;
}

int main() {
    std::vector<std::string> disconnected_ip;
    std::vector<std::string> connected_ip;

    std::vector<std::string> ipAddress_list{
        "10.0.0.1",
        "10.0.0.163",
    };
    std::vector<std::string> devices{
        "Router_1",
        "Switch_1",

    };

    while (true) {
        std::ofstream log("status.log", std::ios::app);

        if (ipAddress_list.size() != devices.size()) {
            std::cout << "Error: Number of IP addresses and Device mismatch!" << std::endl;
        }

        for (int pos = 0; pos < ipAddress_list.size(); pos++) {
            std::string ip = ipAddress_list[pos];
            std::string device = devices[pos];

            bool status = Pingip(ip);

            if (status == false) { // Device is Disconnected
                // Check if already logged in `disconnected_ip`
                if (std::find(disconnected_ip.begin(), disconnected_ip.end(), ip) == disconnected_ip.end()) {
                    disconnected_ip.push_back(ip);
                    connected_ip.erase(std::remove(connected_ip.begin(), connected_ip.end(), ip), connected_ip.end());

                    std::cout << device + " " + ip + " Disconnected " << std::endl;
                    log << device << " " << ip << " Disconnected " << std::endl;
                }
            } else { // Device is Connected
                // Check if already logged in `connected_ip`
                if (std::find(connected_ip.begin(), connected_ip.end(), ip) == connected_ip.end()) {
                    connected_ip.push_back(ip);
                    disconnected_ip.erase(std::remove(disconnected_ip.begin(), disconnected_ip.end(), ip), disconnected_ip.end());

                    std::cout << device + " " + ip + " Connected" << std::endl;
                    log << device << " " << ip << " Connected" << std::endl;
                }
            }
        }
        log.close();
    }
}
