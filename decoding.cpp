/*
        @uthor: Kashish Gilhotra
        user: CodeChef, CodeForces, HackerEarth, HackerRank, SPOJ: kashish001
*/

#include <bits/stdc++.h>
using namespace std;
  
#define int long long int 
typedef vector<int> vi;
typedef vector<pair<int, int>> vpi;
typedef vector<vi> vvi;
const int mod = 1e9 + 7; 

#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL) 
#define debug(...) cerr << "[" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] " 
#define EB emplace_back
#define ALL(v) v.begin(), v.end() 
#define size(v) (int)(v.size()) 
#define endl '\n'
#define UMO unordered_map
#define USO unordered_set
#define TC int t; cin >> t; while (t--) 

class HuffTree {
    public :  
    char data;
    HuffTree *left;
    HuffTree *right;
    HuffTree(char data) {
        this -> data = data;
        this -> left = this -> right = NULL;
    }
    HuffTree(char data, HuffTree * left, HuffTree * right) {
        this -> data = data;
        this -> left = left;
        this -> right = right;
    }
};

HuffTree * reverseEngineerTree(ifstream &inpf) {
    char data;
    inpf.get(data);
    if(data == '1') {
        inpf.get(data);
        return new HuffTree(data);
    } else {
        HuffTree * left = reverseEngineerTree(inpf);
        HuffTree * right = reverseEngineerTree(inpf);
        return new HuffTree('`', left, right);
    }
}

void removePadding(string &encodedText) {
    int paddedInfo = bitset<8>(encodedText.substr(0, 8)).to_ullong();
    encodedText = encodedText.substr(8, size(encodedText) - paddedInfo - 8);
    return ;
}

void decode(HuffTree * Root, string encodedText, ofstream &outpf) {
    int index = 0;
    HuffTree * root = Root;
    while(index <= size(encodedText)) {
        if(root -> data != '`') {
            outpf << root -> data;
            root = Root;
        } else if(encodedText[index] == '0') {
            if(!root -> left) root = Root ;
            else root = root -> left, index++;
        } else {
            if(!root -> right) root = Root;
            else root = root -> right, index++;
        }
    }
    return ;
}

void decodeThefile(string &encodedText, string filename, HuffTree * Root) {
    ofstream outpf((filename.erase(size(filename) - 4)).c_str(),ios::binary);
    if(!outpf.good()) {
        perror("Error:\t");
        exit(-1);
    }
    decode(Root, encodedText, outpf);
    outpf.close();
}

void Panda() {
    string filename;
    cout << "Enter file Name : ";
    cin >> filename;
    ifstream input_file(filename, ios::binary);
    if(!input_file.good()) {
        perror("Error:\t");
        exit(-1);
    }
    if(filename.find(".huf")==string::npos) {
        cout << "Error: File is already decompressed" << endl << endl;
        exit(-1);
    }
    cout << endl;
    clock_t start_time=clock();
    HuffTree* tree = reverseEngineerTree(input_file);
    char data;
    input_file.get(data);
    string encodedText;
    while(input_file.get(data)) encodedText += bitset<8>(data).to_string();

    removePadding(encodedText);

    decodeThefile(encodedText, filename, tree);
    input_file.close();
    clock_t stop_time=clock();
    if(remove(filename.c_str())!=0) perror("Error deleting the compressed file:\t");
    cout << endl;
    cout << "****************************Decompressing*******************************" << endl << endl;
    cout << "File Decompressed Successfully! :-)" << endl;
    cout<<"Time taken to Compress:\t"<<double(stop_time-start_time)/CLOCKS_PER_SEC<<" seconds" << endl << endl;
}
int32_t main() {
 

    //freopen("input.txt", "r", stdin); 
    //freopen("output.txt", "w", stdout); 
    
    Panda();

    return 0; 
} 