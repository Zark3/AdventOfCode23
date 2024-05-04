#include <iostream>
#include <fstream>
#include <vector>
#include <string>




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

std::vector<int> processROW(const std::vector<int>& row){
    std::vector<int> result;
    result.reserve(row.size() - 1);

        for (auto i = 0; i < row.size() - 1; ++i) {

            result.push_back(row[i+1] - row[i]);
            //std::cout << row[i] << " ";

        }

    return result;
}

bool isRowZero(std::vector<int>& vect) {

    for (int i : vect) {

        if(i > 0 || i < 0){
            return false;
        }

    }

    return true;
}

void clearVector(std::vector<std::vector<int>>& vectors){
    for (auto & vector : vectors) {
        vector.clear();
        vector.shrink_to_fit();
    }
}

void func(std::ifstream& file){
    long rowSum = 0, result = 0;


    //data load
    std::vector<std::string> data, convData;
    std::vector<int> numbers, newRow;
    std::vector<std::vector<int>> mainVect;

    for (std::string line; std::getline(file, line);)
        data.push_back(line);

    //for every line
    for (int i = 0; i < data.size(); ++i) {

        //parse line to numbers
            convData = split(data.at(i), " ");
        //convert every number
        for (int j = 0; j < convData.size(); ++j) {
            numbers.push_back(stoi(convData.at(j)));
            //std::cout << stoi(convData[j]) << " ";
        }

        mainVect.clear();

        mainVect.push_back(numbers);
        numbers.clear();
        convData.clear();
        //process row of converted numbers
        while(!isRowZero(mainVect.back())){
            //calculate step between numbers
            newRow = processROW(mainVect.back());

            mainVect.push_back(newRow);
        }

        //go through vect in reverse to get needed numbers
        rowSum = 0;
        for (int k = mainVect.size() - 1; k >= 0; --k) {
            //first should be zero
            rowSum  += mainVect.at(k).back();
        }

        clearVector(mainVect);

        result += rowSum;

        //std::cout << std::endl;

    }

    std::cout << result;

}


int main(){
    std::ifstream myfile;
    myfile.open ("input_day09.txt");

    if (myfile.is_open())
    {
        func(myfile);
    }

    myfile.close();
}
