#include <bits/stdc++.h>
using namespace std;

// A Huffman tree node
class MinHeapNode
{
public:
    char data;			 // One of the input characters
    int freq;			 // Frequency of the character
    MinHeapNode *left{}, *right{}; // Left and right child

    MinHeapNode(char data, int freq)
    {
        //left = right = nullptr;
        this->data = data;
        this->freq = freq;
    }
};

// utility function for the priority queue
class compare
{
public:
    bool operator()(MinHeapNode* l, MinHeapNode* r)
    {
        return (l->freq > r->freq);
    }
};

// STL priority queue to store heap tree, according to their heap root node value
priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap;

// to store the frequency of character of the input data
map<char, int> freq;

// utility function to store map each character with its frequency in input string
void FreqMeasure(const string& str)
{
    for (char i : str) {
        freq[i]++;
    }
}

// to map each character its huffman value
map<char, string> codes;

// utility function to store characters along with there huffman value in a hash table, here we have C++ STL map
void storeCodes(struct MinHeapNode* root, const string& str)
{
    if (root == nullptr)
        return;
    if (root->data != '$')
        codes[root->data]=str;
    storeCodes(root->left, str + "0");
    storeCodes(root->right, str + "1");
}

// function to build the Huffman tree and store it
// in minHeap
void HuffmanCodes()
{
    struct MinHeapNode *left, *right, *top;
    for (auto & v : freq)
        minHeap.push(new MinHeapNode(v.first, v.second));
    while (minHeap.size() != 1)
    {
        left = minHeap.top();
        minHeap.pop();
        right = minHeap.top();
        minHeap.pop();
        top = new MinHeapNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        minHeap.push(top);
    }
    storeCodes(minHeap.top(), "");
}

// utility function to print characters along with
// there huffman value
void printCodes(struct MinHeapNode* root, const string& str)
{
    if (!root)
        return;
    if (root->data != '$')
        cout << root->data << ": " << str << "\n";
    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}

// function iterates through the encoded string s
// if s[i]=='1' then move to node->right
// if s[i]=='0' then move to node->left
// if leaf node append the node->data to our output string
string decode_file(struct MinHeapNode* root, const string& s)
{
    string ans;
    struct MinHeapNode* curr = root;
    for (char i : s)
    {
        if (i == '0')
            curr = curr->left;
        else
            curr = curr->right;

        // reached leaf node
        if (curr->left==nullptr and curr->right==nullptr)
        {
            ans += curr->data;
            curr = root;
        }
    }
    return ans;
}

/*
int main() {
    string str = "TEC";

    FreqMeasure(str);
    HuffmanCodes();

    string encodedString, decodedString;

    for (auto i: str)
        encodedString += codes[i];

    cout << "Compressed Huffman code: " << encodedString << endl;

    decodedString = decode_file(minHeap.top(), encodedString);

    cout << "Uncompressed Huffman code: " << decodedString << endl;
}
*/