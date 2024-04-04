#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <random>

void shakerSort(std::vector<int>& arr) {
    bool swapped = true;
    int start = 0;
    int end = arr.size() - 1;
    

    //until algortmus alg 1
    while (swapped) {
        swapped = false;

        //prechod na pravo alg 2
        for (int i = start; i < end; ++i) {
            if (arr[i] > arr[i + 1]) {
                std::swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }

        if (!swapped) break;

      ///prechod na lavo alg 3
        swapped = false;
        --end;
        for (int i = end - 1; i >= start; --i) {
            if (arr[i] > arr[i + 1]) {
                std::swap(arr[i], arr[i + 1]);
                swapped = true;
            }
        }
        ++start;
    }
}
 //radnom gen :)
std::vector<int> generateRandomVector(int length, int minVal, int maxVal) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(minVal, maxVal);
   
    std::vector<int> result;
    result.reserve(length);

    for (int i = 0; i < length; ++i) {
        result.push_back(dis(gen));
    }

    return result;
}

int main() {
    std::vector<int> randomVector = generateRandomVector(10000, 0, 1000); 
    //merannie casu pomocou shaker short
    auto start = std::chrono::high_resolution_clock::now();
    shakerSort(randomVector);
    auto end = std::chrono::high_resolution_clock::now();
    ///vypocet pre rozdiel medzi vystupom a vstupom
    std::chrono::duration<double> duration = end - start;
    std::cout << " cas vectoru je  " << duration.count() << " sekund" << std::endl;

    return 0;
}
