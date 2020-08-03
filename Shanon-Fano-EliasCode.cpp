#include<iostream>
#include<vector>
#include<string>
#include<cmath>
#include<algorithm>

class ShanonFanoElias{
private:
    int n;
    std::vector<double> prob, Fhat;
    std::vector<int> length;
    std::vector<std::string> codeWord;
    const double eps = 1e-10;
public:
    ShanonFanoElias();
    ShanonFanoElias(int N, double p[]);
    std::string getCodeWord(int i);
};


ShanonFanoElias::ShanonFanoElias(){};

ShanonFanoElias::ShanonFanoElias(int N, double p[]){
    n = N;
    Fhat.resize(n);
    prob.resize(n);
    length.resize(n);
    codeWord.resize(n);
    for(int i = 0; i < n; i++){
        prob[i] = p[i];
    }

    Fhat[0] = prob[0] * 0.5;
    length[0] = std::ceil(std::log2(1.0 / prob[0])) + 1;
    for(int i = 1; i < n; i++){
        Fhat[i] = Fhat[i - 1] + (prob[i] + prob[i - 1]) * 0.5;
        length[i] = std::ceil(std::log2(1.0 / prob[i])) + 1;
    }

    for(int i = 0; i < n; i++){
        // get binary representation
        double transformedFhat = Fhat[i];
        for(int j = 0; j < length[i]; j++){
            transformedFhat *= 2.0;
        }
        int intFhat = transformedFhat + eps;
        for(int j = 0; j < length[i]; j++){
            codeWord[i] += (char)('0' + intFhat % 2);
            intFhat /= 2;
        }
        std::reverse(codeWord[i].begin(), codeWord[i].end());
    }
};

std::string ShanonFanoElias::getCodeWord(int i){
    return codeWord[i];
};

int main(){
    const int N = 5;
    double prob[] = {0.25, 0.25, 0.2, 0.15, 0.15};
    ShanonFanoElias code = ShanonFanoElias(N, prob);
    for(int i = 0; i < N; i++){
        std::cout << code.getCodeWord(i) << std::endl;
    }
    return 0;
}

