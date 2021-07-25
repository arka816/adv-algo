#include <bits/stdc++.h>
#include <map>

using namespace std;

struct Node{
    char c;
    float prob;
    Node *left = NULL;
    Node *right = NULL;
    Node(char c, float prob) : c(c), prob(prob)
    {
    }
};

struct compareNodes {
    bool operator()(Node *n1, Node *n2)
    {
        return n1->prob > n2->prob;
    }
};

class Huffman{
    private:
    map<char, int> freqmap;
    map<char, int>::iterator freqitr;
    map<char, string> codeMap;
    map<char, string>::iterator codeitr;
    priority_queue<Node *, vector<Node *>, compareNodes> q;
    set<char> charset;
    Node *root;

    public:
    Huffman(map<char, int> freqmap){
        Node *n1, *n2, *merged;

        for (freqitr = freqmap.begin(); freqitr != freqmap.end(); ++freqitr){
            q.push(new Node(freqitr->first, freqitr->second));
            charset.insert(freqitr->first);
        }
    
        while(q.size() > 1){
            n1 = q.top(); q.pop();
            n2 = q.top(); q.pop();
            merged = new Node('$', n1->prob + n2->prob);
            merged->left = n2;
            merged->right = n1;
            q.push(merged); 
        }

        string s = "";
        root = q.top();
        q.pop();
        assignCode(s, root, codeMap);
        for (codeitr = codeMap.begin(); codeitr != codeMap.end(); ++codeitr) {
            //cout<< codeitr->first<<": "<< codeitr->second<<endl;
        }
    }

    private:
    void assignCode(string s, Node *curr, map<char, string> &codeMap){
        if(curr->c != '$'){
            codeMap.insert({curr->c, s});
            return;
        }
        assignCode(s + "0", curr->left, codeMap);
        assignCode(s + "1", curr->right, codeMap);
        return;
    }

    public:
    string encode(string s){
        string encodedString = "";
        for(char c : s){
            if(charset.find(c) != charset.end()){
                encodedString += codeMap[c];
            }
            else{
                throw "character set exception";
            }
        }
        return encodedString;
    }

    

    public:
    string decode(string s){
        string decodedString = "";
        Node *curr = root;
        int i = 0;
        while(i < s.size()){
            if(s[i] == '0'){
                curr = curr->left;
            }
            else if(s[i] == '1'){
                curr = curr->right;
            }
            if(curr->c != '$'){
                decodedString += curr->c;
                curr = root;
            }
            i++;
        }
        return decodedString;
    }
};

int main(){
    int n;
    float f;
    char c;
    map<char, int> freqmap;

    //cin>>n;

    /*for(int i = 0; i < n; i++){
        cin>>c>>f;
        freqmap.insert({c, f});
    }*/
    freqmap.insert({'a', 5});
    freqmap.insert({'b', 9});
    freqmap.insert({'c', 12});
    freqmap.insert({'d', 13});
    freqmap.insert({'e', 16});
    freqmap.insert({'f', 45});

    Huffman codec(freqmap);
    string code = codec.encode("abcdef");
    cout<<code<<endl;
    cout<<codec.decode(code);
}