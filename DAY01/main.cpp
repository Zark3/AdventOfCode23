#include <iostream>
#include "string.h"


size_t func(FILE* file){
    char line[75];
    int len = 75;
    char first;
    char second;
    size_t result = 0;
    int iter;

    while (fgets(line, len, file)){
        for (int i = 0; i < strlen(line); ++i) {
            if((line[i]-48) > 0 && (line[i]-48) <= 9){
                first = line[i];
                second = line[i];
                iter = i;
                break;
            }
        }
        for (int i = iter; i < strlen(line); ++i) {
            if((line[i]-48) > 0 && (line[i]-48) <= 9){
                second = line[i];
            }
        }
        result += ((first-'0')*10) + (second-'0');
    }

    return result;

}


int main() {



    FILE* fptr = fopen("input_day01.txt","r");
    if (!fptr) {
        printf("The file is not opened. The program will "
               "now exit.");
        exit(0);
    }


    printf("Result: %zu", func(fptr));

    fclose(fptr);
    return 0;
}
