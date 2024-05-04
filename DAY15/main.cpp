#include <iostream>
#include <fstream>
#include <string>

int decode(std::string data){
    int result = 0;

    for (int i = 0; i < data.length(); ++i) {
        result += data[i];
        result = ((result * 17) % 256);
    }

    return result;
}

void func(std::ifstream& file){
    long result = 0;

    for (std::string step; std::getline(file, step, ','); ) {
        //remove \n char if necessary
        if (step.back() == '\n') { step.pop_back(); }

        result += decode(step);



    }

    std::cout << result;

}

int main(){
    std::ifstream myfile;
    myfile.open ("input_day15.txt");

    if (myfile.is_open())
    {
        func(myfile);
    }

    myfile.close();
}
