#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>


struct record {
    std::string row;
    std::vector<int> groups;
};


std::vector<std::string> split(std::string s, std::string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

bool isRowValid(std::string& row, std::vector<int>& com){
    auto iter = std::find(row.begin(), row.end(), '1');
    int help = 0, iterC = 0, passC = 0;

    while(iter != row.end() || passC != com.size()){

            while (*iter == '1'){
                help++;
                iter++;
                if (iter == row.end())
                    break;
            }
            if (help == com[iterC]){
                passC++;
                iterC++;
                help = 0;
            }else{
                return false;
            }
            if (iter == row.end()){
                if (passC == com.size()){
                    return true;
                }else{
                    return false;
                }

            }

            iter = std::find(iter, row.end(), '1');
    }

    return true;
}


void  calculatePossibleRows(std::string s, int pr, int& result, std::vector<int> groups){

    std::string line;
    std::vector<int> idxs;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '.') {
            line.push_back('0');
        } else if (s[i] == '?') {
            line.push_back('2');
            idxs.push_back(i);
        } else if (s[i] == '#') {
            line.push_back('1');
        }
    }

    for (int mask = 0; mask < (1 << idxs.size()); ++mask) {
        std::string line_copy = line;
        for (int i = 0; i < idxs.size(); ++i) {
            if (mask & (1 << i)) {
                line_copy[idxs[i]] = '0';
            } else {
                line_copy[idxs[i]] = '1';
            }
        }

        if (isRowValid(line_copy, groups)) {
            result++;
        }
    }



}



void func(std::ifstream& file){
    std::vector<std::string> data, convData, groups;
    int result = 0;


    for (std::string line; std::getline(file, line);)
        data.push_back(line);

    for (int i = 0; i < data.size(); ++i) {
        convData = split(data.at(i), " ");

        record R;
        R.row = convData.at(0);
        groups = split(convData.at(1), ",");
        for (const auto & group : groups) {
            R.groups.push_back(stoi(group));
        }
        //number of ? in string
        int qms = std::count(R.row.begin(), R.row.end(), '?');

        //possible rows by number of ?
        int posibleRows = pow(qms,2);
        //calculate and valid rows
        calculatePossibleRows(R.row, posibleRows, result, R.groups);


    }

    std::cout << result << std::endl;

}

int main(){
    std::ifstream myfile;
    myfile.open ("input_day12.txt");

    if (myfile.is_open())
    {
        func(myfile);
    }

    myfile.close();
    return 0;
}
