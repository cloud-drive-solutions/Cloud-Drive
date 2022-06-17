#include <vector>
#include <iostream>
#include <map>
#include <queue>
#include <fstream>
#include <iterator>
#include <algorithm>

using namespace std;

/**
 * Class that creates a heap node for the Huffman tree
 */
class MinHeapNode
{
public:
    char value;	// Value of the node
    int freq;	// Frequency of the character
    MinHeapNode *left{}, *right{}; // Left and right branches

    /**
     *
     * Constructor function that establishes value and frequency for the node
     *
     * @param value
     * @param freq
     */
    MinHeapNode(char value, int freq)
    {
        this->value = value;
        this->freq = freq;
    }
};

/**
 * Class used for the priority queue, return bool of left > right
 */
class compare
{
public:
    bool operator()(MinHeapNode* l, MinHeapNode* r) // Creates two heap nodes for left and right branches
    {
        return (l->freq > r->freq); // Compares if left is larger than right
    }
};

/**
 * Class that includes different functions for the compression of a string via the Huffman algorithm
 */
class HuffmanTree
{
public:
    priority_queue<MinHeapNode*, vector<MinHeapNode*>, compare> minHeap; // Creates tree queue
    map<char, int> freq; // frequency has a char and number associated
    map<char, string> codes; // Codes have a char and string associated

    /**
     *
     * Measures the frequency of each character in the input string
     *
     * @param str
     * @param n
     */
    void FreqMeasure(const string& str, int n)
    {
        for (char i : str) { // For character in string increase frequency int
            freq[i]++;
        }
    }

    /**
     *
     * Stores the given codes on the tree heap nodes
     *
     * @param root
     * @param str
     */
    void storeCodes(MinHeapNode* root, const string& str)
    {
        if (root == nullptr)   // if the root is null stop
        {return;}
        if (root->value != '\0') // if the value of root isnt null
        {codes[root->value] = str;} // the value of root is now in codes

        storeCodes(root->left, str + "0");  // assign 0 to left branch
        storeCodes(root->right, str + "1"); // assign 1 to right branch
    }

    /**
     * Generates a tree using heap nodes, the priority queue and storing its codes on the codes map
     */
    void generateTree()
    {
        MinHeapNode *left, *right, *top;  // Creates node and its branches
        for (auto &v: freq) {   // For values in freq, add a node with its value and frequency
            minHeap.push(new MinHeapNode(v.first, v.second));
        }
        while (minHeap.size() != 1)
        {
            left = minHeap.top(); // Left is the largest element
            minHeap.pop(); // Remove it from queue
            right = minHeap.top(); // Right is the second largest element
            minHeap.pop(); // Remove it from queue
            top = new MinHeapNode('\0', left->freq + right->freq); // top value null, frequency is left+right
            top->left = left; // left branch of top node is left
            top->right = right; // right branch of top node is right
            minHeap.push(top); // push top to the queue
        }
        storeCodes(minHeap.top(), ""); // Stores the root of the queue with value ""
    }

    /**
     * Helpful function to print out the dictionary
     */
    void printCodes()
    {
        for (auto &code : codes) { // For code pair in codes, print first value and second value
            cout << code.first << ": " << code.second << endl;
        }
    }

    /**
     *
     * Decodes a compressed string using the heap node as a dictionary, returning the original string
     *
     * @param root
     * @param encodedString
     * @return
     */
    static string decode_file(MinHeapNode* root, const string& encodedString)
    {
        string decodedString;
        MinHeapNode* curr = root;
        
        for (char i : encodedString)
        {
            if (i == '0') { // If code is 0, traverse left branch
                curr = curr->left;
            }
            else if (i == '1') {  // If code is 1, traverse right branch
                    curr = curr->right;
            }

            if (curr->left == nullptr and curr->right == nullptr) // If next branches are null, add the value of the
                                                                 // node to output, return to root
            {
                decodedString += curr->value;
                curr = root;
            }
        }
        return decodedString; // Return decoded string
    }
};

int main() {
    string line;
    ifstream fileToCompress("example_text.txt");
    ofstream compressedFile("example_text.huffman");
    string stringToCompress;

    if (fileToCompress.is_open()) { // if
        while (getline(fileToCompress, line)) {
            stringToCompress += line + "\n";
        }
        fileToCompress.close();
    }

    else {
        cout << "Unable to open file";
    }

    //string str = "begin";
    string encodedString, decodedString;

    HuffmanTree h1;

    h1.FreqMeasure(stringToCompress, stringToCompress.length()); // Measures frequency for library
    h1.generateTree();  // Creates a Huffman tree

    cout << "Library is: " << endl;
    h1.printCodes();

    for (auto i: stringToCompress) {
        encodedString += h1.codes[i]; // Adds the Huffman compressed codes to the string
    }

    /*
    cout << endl;
    cout << "Compressed code is: " << endl;
    cout << encodedString << endl;

    cout << endl;
    cout << "Decompressed code is: " << endl;

    decodedString = h1.decode_file(h1.minHeap.top(), encodedString);

    cout << decodedString << endl;
    */

    if (compressedFile.is_open()) {
        compressedFile << encodedString;
        compressedFile.close();
    }

    else {
        cout << "Unable to open file" << endl;
    }
    return 0;
}