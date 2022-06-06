/*
 * Network Calculator
 *
 * Get mask, network, first host, last host and broadcast from a given IP with mask.
 * You may input a file too.
 *
 * IP/mask Ex: 10.3.56.100/8
 * File must contain one IP/mask (like the example avobe) per line.
 *
 * 
 * Made by Daniel @ Github :)
 * https://github.com/Chon33/IP-calculator
*/

#include <iostream>
#include <string>
#include <bitset>
#include <vector>
#include <fstream>

typedef unsigned long u32;
typedef unsigned char u8;

#include "Format.hpp"

using namespace std;

vector<u8> input_ip(string in = "") {
	string input;

	if (in == "") {
		cout << "IP/mask (no spaces): ";
		change_output_color(Colors::Yellow);
		cin >> input;
		change_output_color(Colors::White);

		clear();
	}
	else
		input = in;

	/* bytes and mask from IP address */
	u8 byte1, byte2, byte3, byte4, i_mask;

	size_t found1 = input.find(".");
	byte1 = stoi(input.substr(0, found1));

	size_t found2 = input.find(".", found1 + 1);
	byte2 = stoi(input.substr(found1 + 1, found2 - found1 - 1));

	size_t found3 = input.find(".", found2 + 1);
	byte3 = stoi(input.substr(found2 + 1, found3 - found2 - 1));

	size_t found5 = input.find("/");
	i_mask = stoi(input.substr(found5 + 1, input.size() - found5));

	byte4 = stoi(input.substr(found3 + 1, found5 - found3));

	cout << "IP: ";
	change_output_color(Colors::Cyan);
	cout << +byte1 << "." << +byte2 << "." << +byte3 << "." << +byte4;
	change_output_color(Colors::Yellow);
	cout << " /" << +i_mask << endl;
	change_output_color(Colors::White);

	return vector<u8>{byte1, byte2, byte3, byte4, i_mask};
}

vector<u8> calculate_mask(u8 i_mask) {
	u32 mask{ 0 };

	for (int i = 0; i < i_mask; i++)
		mask += (0b1 << i);
	mask <<= 32 - i_mask;

	/* mask bytes */
	u8 mask_byte1, mask_byte2, mask_byte3, mask_byte4;

	mask_byte1 = (mask >> 8 * 3) & 0xff;
	mask_byte2 = (mask >> 8 * 2) & 0xff;
	mask_byte3 = (mask >> 8 * 1) & 0xff;
	mask_byte4 = (mask >> 8 * 0) & 0xff;

	int space = 0;
	cout << "Mask: ";
	change_output_color(Colors::Yellow);
	for (int i = 0; i < i_mask; i++) {
		cout << "1";
		space++;
		if (space == 8) {
			cout << " ";
			space = 0;
		}
	}

	change_output_color(Colors::Cyan);
	for (int i = 0; i < 32 - i_mask; i++) {
		cout << "0";
		space++;
		if (space == 8) {
			cout << " ";
			space = 0;
		}
	}
	cout << endl;

	change_output_color(Colors::White);

	return vector<u8>{mask_byte1, mask_byte2, mask_byte3, mask_byte4};
}

vector<u8> calculate_network(vector<u8> ip, vector<u8> mask) {
	cout << "Network: ";

	u8 net_byte1, net_byte2, net_byte3, net_byte4;

	net_byte1 = (int)ip[0] & (int)mask[0];
	net_byte2 = (int)ip[1] & (int)mask[1];
	net_byte3 = (int)ip[2] & (int)mask[2];
	net_byte4 = (int)ip[3] & (int)mask[3];

	change_output_color(Colors::Cyan);
	cout << +net_byte1 << "." << +net_byte2 << "." << +net_byte3 << "." << +net_byte4 << endl;
	change_output_color(Colors::White);

	return vector<u8>{net_byte1, net_byte2, net_byte3, net_byte4 };
}

void calculate_first_host(vector<u8> network) {
	cout << "First Host: ";
	change_output_color(Colors::Cyan);
	cout << +network[0] << "." << +network[1] << "." << +network[2] << "." << +(network[3] + 0b1) << endl;
	change_output_color(Colors::White);
}

vector<u8> calculate_broadcast(vector<u8> network, vector<u8> mask) {
	cout << "Broadcast: ";
	change_output_color(Colors::Cyan);

	vector<u8> bc;

	u8 buff{ 0 };
	for (int i = 0; i < 4; i++) {
		buff = 0;

		for (int j = 7; j >= 0; j--) {
			if (((mask[i] >> j) & 0b1) == 1)
				buff += ((network[i] >> j) & 0b1) << j;
			else
				buff += 0b1 << j;
		}

		bc.push_back(buff);
	}

	cout << +bc[0] << "." << +bc[1] << "." << +bc[2] << "." << +bc[3] << endl;
	change_output_color(Colors::White);

	return bc;
}

void calculate_last_host(vector<u8> bc) {
	cout << "Last Host: ";

	change_output_color(Colors::Cyan);
	cout << +bc[0] << "." << +bc[1] << "." << +bc[2] << "." << +(bc[3] - 0b1) << endl;
	change_output_color(Colors::White);
}

void run_everything(string str = "") {
	vector<u8> ip{ input_ip(str) };

	if (ip[4] == 32) {
		change_output_color(Colors::Red);
		cout << "Cannot use /32" << endl;
		change_output_color(Colors::White);
		return;
	}

	vector<u8> mask{ calculate_mask(ip[4]) };
	vector<u8> network{ calculate_network(ip, mask) };
	calculate_first_host(network);
	vector<u8> broadcast{ calculate_broadcast(network, mask) };
	calculate_last_host(broadcast);
}

void ask_and_run() {
	string response = "";

	cout << "IP or file [i/f]?" << endl;
	change_output_color(Colors::Red);
	cout << "-( Q to exit )-" << endl;
	change_output_color(Colors::White);
	cout << ">> ";
	change_output_color(Colors::Yellow);
	
	cin >> response;
	change_output_color(Colors::White);
	clear();

	if (response == "I" || response == "i" || response == "") {
		run_everything();
		cout << endl;
		ask_and_run();
	}
	else if (response == "F" || response == "f") {
		string path;		
		cout << "File path: ";
		change_output_color(Colors::Yellow);

		cin >> path;
		cout << endl;
		change_output_color(Colors::White);

		ifstream file(path);
		string str;
		while (getline(file, str)) {
			run_everything(str);
			cout << endl;
		}
		ask_and_run();
	}
	else if (response == "Q" || response == "q") {
		return;
	}
	else { ask_and_run(); }
}

int main() {
	change_output_color(Colors::White);
	SetConsoleTitleA("IP Calculator");

	ask_and_run();

	return 0;
}