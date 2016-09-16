#include <iostream>
#include <string>
#include <cmath>
#include <vector>
using namespace std;
#include "sutils.h"

int index_of(vector<string> arr, string el){
	int i = 0;
	for(auto &s: arr){
		int a = s.compare(el);
		if(!a) return i;
		i++;
	}
	return -1;
}

string trim(string& str){
    size_t first = str.find_first_not_of(' ');
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last-first+1));
}

double parse_double(string str_to_parse){
	const char* str = str_to_parse.c_str();
	int i = 0;
	double number = 0;
	double mantisse = 0;
	int sm = 0;
	while(str[i] != '\0'){
		if(str[i] >= '0' && str[i] <= '9'){
			if(sm) mantisse = mantisse + (str[i] - '0')/pow(10, sm);
			else number = number*10 + (str[i] - '0');
		}
		if(str[i] == '.' || sm) sm++;
		if(!(str[i] >= '0' && str[i] <= '9') && str[i] != '.')
			throw "Not a valid double.";
		i++;
	}
	
	return number+mantisse;
}
