#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

struct Node{
    double prob;
    std::string codeword;
    bool isMerged; // created by Huffman Reduction?
};

class Huffman{
private:
    int N;
    int D;
    int initN;
    int depth;
    std::vector<std::vector<Node>> nodeVec;

    void forward(int d){
        if(d == depth) return;

        int num = N - d * (D - 1); // 今の要素数
        double meargedProb = 0.0;
        for(int i = 0; i < D; i++){
            meargedProb += nodeVec[num - 1 - i][d].prob;
        }

        int offset = 0;
        for(int i = 0; i < num - (D - 1); i++){
            if(offset == 0 && (nodeVec[i][d].prob <= meargedProb || i == num - (D - 1))){
                offset = 1;
                nodeVec[i][d + 1].prob = meargedProb;
                nodeVec[i][d + 1].isMerged = true;
            }else{
                nodeVec[i][d + 1].prob = nodeVec[i - offset][d].prob;
                nodeVec[i][d + 1].isMerged = false;
            }
        }

        forward(d + 1);
    }

    void backward(int d){
        if(d != 0){
            int num = N - d * (D - 1); // 今の要素数
            int nextNum = num + (D - 1); // 次の層の要素数
            int offset = 0;
            for(int i = 0; i < num; i++){
                if(nodeVec[i][d].isMerged){
                    offset = 1;
                    for(int j = 0; j < D; j++){
                        nodeVec[nextNum - 1 - j][d - 1].codeword = nodeVec[i][d].codeword + (char)('0' + (D - 1 - j));
                    }
                }else{
                    nodeVec[i - offset][d - 1].codeword = nodeVec[i][d].codeword;
                }
            }

            backward(d - 1);
        }
    }
public:
    Huffman(){}
    Huffman(int n, int d, double prob[]){
        N = n;
        D = d;
        initN = n;
        depth = (N - 1 + D - 1) / (D - 1);

        // add dummy symbols
        if((N - 1) % (D - 1) != 0){
            N = depth * (D - 1) + 1;
        }

        nodeVec.resize(N);
        nodeVec[0].resize(depth + 1);
        for(int i = 1; i < N; i++){
            nodeVec[i].resize(depth - i / D);
        }

        std::sort(prob, prob + initN, std::greater<double>());
        for(int i = 0; i < initN; i++){
            nodeVec[i][0].prob = prob[i];
            nodeVec[i][0].isMerged = false;
        }
        for(int i = initN; i < N; i++){
            nodeVec[i][0].prob = 0.0;
            nodeVec[i][0].isMerged = false;
        }
    }

    void createHuffmanCode(){
        forward(0);
        backward(depth);
    }

    void DispCodewords(){
        for(int i = 0; i < N; i++){
            std::cout << nodeVec[i][0].codeword << "\n";
        }
    }
};

int main(){
    const int n = 5;
    const int d = 2;
    double prob[] = {0.25, 0.25, 0.2, 0.15, 0.15}; 
    Huffman huffman = Huffman(n, d, prob);
    huffman.createHuffmanCode();
    huffman.DispCodewords();
    return 0;
}
