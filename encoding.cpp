/*
        @uthor: Kashish Gilhotra
        user: CodeChef, CodeForces, HackerEarth, HackerRank, SPOJ: kashish001
*/

#include <bits/stdc++.h>
using namespace std;

#define int long long int
typedef vector<int> vi;
typedef vector<pair<char, int>> vpi;
typedef vector<pair<char, string>> vsi;
typedef vector<vi> vvi;
const int mod = 1e9 + 7; 

#define FAST ios_base::sync_with_stdio(false); cin.tie(NULL) 
#define debug(...) cerr << "[" << #__VA_ARGS__ ": " << (__VA_ARGS__) << "] " 
#define EB emplace_back
#define ALL(v) v.begin(), v.end() 
#define size(v) (int)v.size() 
#define endl '\n'
#define UMO unordered_map
#define USO unordered_set
#define TC int t; cin >> t; while (t--) 

int freqOfChars[256];

class HuffTree {
    public : 

    int frequency;
    char data;
    HuffTree *left;
    HuffTree *right;
    HuffTree(char data, int frequency) {
        this -> frequency = frequency;
        this -> data = data;
        this -> left = this -> right = NULL;
    }
};

class Compare {
    public : 
    bool operator() (HuffTree * first, HuffTree * second) {
        return first -> frequency > second -> frequency;
    }
};

//Calculating Frequencies of All Chracters
void calculate_frequency(ifstream &inpf, string &finalDataString) {
    char data;
    while(inpf.get(data)) freqOfChars[data]++, finalDataString += data;
    inpf.clear();
    inpf.seekg(0);
    inpf.close();
    return ;
}

HuffTree * buildTree() {
    priority_queue<HuffTree*, vector<HuffTree*>, Compare> q;
    for(int i = 0; i < 256; i++) if(freqOfChars[i]) q.push(new HuffTree((char)(i), freqOfChars[i]));
    while(size(q) > 1) {
        HuffTree * left = q.top(); q.pop();
        HuffTree * right = q.top(); q.pop();
        HuffTree * CombinedNode = new HuffTree('`', left -> frequency + right -> frequency);
        CombinedNode -> left = left, CombinedNode -> right = right;
        q.push(CombinedNode);
    }
    return q.top();
}

void makecodeForchars(HuffTree * root, string code, UMO<char, string> &codeForChars) {
    if(!root) return;
    if(root -> data != '`') {
        codeForChars[root -> data] = code;
        return ;
    }
    makecodeForchars(root -> left, code + "0", codeForChars), makecodeForchars(root -> right, code + "1", codeForChars);
}

string encode(string finalDataString, UMO<char, string> codeForChars) {
    string encodedText;
    for(auto i : finalDataString) encodedText += codeForChars[i];
    return encodedText;
}

void padEncodedstring(string &encodedText) {
    int padInfo = 8 - size(encodedText) % 8;
    for(int i = 0; i < padInfo; i++) encodedText += "0";
    encodedText = bitset<8>(padInfo).to_string() + encodedText;
}

void writeTreeinFile(ofstream &outf, HuffTree* root)                                                          //Write tree to file
{
    if(!root) return ;
    if(root -> data != '`') {
        outf << '1';
        outf << root -> data;
    } else {
        outf << '0';
        writeTreeinFile(outf, root -> left);
        writeTreeinFile(outf, root -> right);
    }
}

void makeCompressedFile(ofstream &outf, string encodedText) {
    int i = 0, j = 0;
    for (i = 0; i < encodedText.length(); i += 8)
    {
        bitset<8> data(bitset<8>(encodedText.substr(i, 8)));
        unsigned char byte = (data.to_ulong() & 0xFF);
        outf.put(byte);
    }
    return ;
}

void Panda() {
    string fileName;
    cout << "Enter FileName : ";
    cin >> fileName;
    ifstream input_file(fileName, ios::binary);
    ofstream output_file((fileName + ".huf"), ios::binary);
    //Finding Frequencies of All chracters 
    string finalDataString;
    clock_t start_time=clock(); 
    calculate_frequency(input_file, finalDataString);

    HuffTree * tree = buildTree();

    UMO<char, string> codeForChars;
    makecodeForchars(tree, "", codeForChars);

    string encodedText = encode(finalDataString, codeForChars);

    padEncodedstring(encodedText);

    writeTreeinFile(output_file, tree);
    output_file << ' ';
    makeCompressedFile(output_file, encodedText);
    output_file.close();
    input_file.close();
    clock_t stop_time=clock();

    if(remove(fileName.c_str()) != 0) perror("Error Occured");
    cout << "**************************************Compressing***************************************" << endl << endl;
    cout << "File Succesfully Compressed :-)" << endl << endl;
    cout<<"Time taken to Compress:\t"<<double(stop_time-start_time)/CLOCKS_PER_SEC<<" seconds" << endl << endl;
    // return encodedText;
}
  
int32_t main() {

    // freopen("input.txt", "r", stdin); 
    // freopen("output.txt", "w", stdout);

    Panda();

    return 0; 
} 
