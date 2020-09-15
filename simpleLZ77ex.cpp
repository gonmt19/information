#include<iostream>
#include<vector>
#include<string>
#include<tuple>

class lz77{
    const bool existPhrase = true;
    const int w; // window size: w < 256
    const std::string s;
    std::vector<std::tuple<bool, char, int>> compressed_str;
    std::string decoded_s;
    void encoder();
    void decoder();
public:
    lz77(): w(0), s(""){};
    lz77(int windowSize, std::string inputStr): w(windowSize), s(inputStr){};
    void run();
    std::string get_decodedstr();
};

void lz77::encoder(){
    for(int i = 0; i < s.size();){
        int start = std::max(i - w, 0);
        int maxlen = 0;
        int pos = 0;
        for(int j = start; j < i; j++){
            int len = 0;
            for(int k = 0; i + k < s.size(); k++){
                if(s[j + k] != s[i + k]) break;
                len++;
            }
            
            if(maxlen < len){
                maxlen = len;
                pos = i - j;
            }
        }

        if(maxlen == 0){
            compressed_str.emplace_back(!existPhrase, s[i], !existPhrase);
            i++;
        }else{
            compressed_str.emplace_back(existPhrase, pos, maxlen);
            i += maxlen;
        }
    }
}

void lz77::decoder(){
    for(int i = 0; i < compressed_str.size(); i++){
        int flag = std::get<0>(compressed_str[i]);
        if(flag != existPhrase){
            decoded_s += std::get<1>(compressed_str[i]);
        }else{
            int pos = std::get<1>(compressed_str[i]);
            int len = std::get<2>(compressed_str[i]);
            int now = decoded_s.size();
            for(int j = now - pos; j < now - pos + len; j++){
                decoded_s.push_back(s[j]);
            }
        }
    }
}

void lz77::run(){
    encoder();
    decoder();
}

std::string lz77::get_decodedstr(){
    return decoded_s;
}

int main(){
    std::string input = "ABBABBABBBAABABA";
    int window_size = 5;
    lz77 compressor(window_size, input);
    compressor.run();
    std::string decoded_s = compressor.get_decodedstr();
    if(input == decoded_s){
        std::cout << "correctly decoded" << std::endl;
    }else{
        std::cout << "fail to decode" << std::endl;
    }
    return 0;
}
