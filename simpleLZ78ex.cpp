#include<iostream>
#include<vector>
#include<string>
#include<map>

int main(){
    std::string input = "ABBABBABBBAABABAA";
    input += "\n";
    int index = 1;
    std::vector<std::pair<int, char>> compressed_str;
    std::map<std::string, int> dict;
    std::vector<std::string> rev_dict(1, "");
    for(int i = 0; i < input.size();){
        for(int len = 1; i + len < input.size(); len++){
            std::string phrase(input.substr(i, len));
            if(dict[phrase] == 0){
                dict[phrase] = index;
                rev_dict.push_back(phrase);
                if(len == 1){
                    compressed_str.emplace_back(0, phrase[0]);
                }else{
                    char c = phrase[len - 1];
                    phrase.pop_back();
                    if(i + len + 1 == input.size()){
                        len++;
                        phrase += c;
                        c = '\n';
                    }
                    compressed_str.emplace_back(dict[phrase], c);
                }
                i += len;
                index++;
                break;
            }
        }
    }

    // decode
    std::string decoded_s;
    for(int i = 0; i < compressed_str.size(); i++){
        decoded_s += rev_dict[compressed_str[i].first] + compressed_str[i].second;
    }

    if(input == decoded_s){
        std::cout << "correctly decoded" << std::endl;
    }else{
        std::cout << "fail to decode" << std::endl;
    }
    return 0;
}
