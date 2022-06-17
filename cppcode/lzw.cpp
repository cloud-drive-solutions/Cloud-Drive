#include <string>
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <fstream>

#include "linkedList.cpp"

using namespace std;

class lzwCompressor {
private:
    string *dictionary;
    int dici = 0;
    int *code;
    int codei = 0;
    char *data;
    size_t size;

public:
    bool searchInDictionary(string search, int chars) {
        bool ret = false;
        for (int i = 0; i < size && !ret; i++) {
            if (dictionary[i].length() == chars) {
                if (dictionary[i] == search) {
                    ret = true;
                    break;
                } else if (dictionary[i] == "") {
                    break;
                } 
            } 
        }
        return ret;
    }

    int indexInDictionary(string search, int chars) {
        int ret = -1;
        for (int i = 0; i < size && ret == -1; i++) {
            if (dictionary[i].length() == chars) {
                if (dictionary[i] == search) {
                    ret = i;
                    break;
                } else if (dictionary[i] == "") {
                    break;
                } 
            } 
        }
        return ret;
    }

    void compress(string filename) {
        readFile(filename);
        initCharacters();
        
        string p;
        string c;
        string pc;

        p = data[0];      

        for (int i = 1; i < size; i++) {
            cout << dici << " " << i << " ";
            c = data[i];
            
            pc = p;
            pc += c;
            
            if (searchInDictionary(pc, pc.length())) {
                p = "";
                p += pc;

            } else {
                int codeDic = indexInDictionary(p, p.length());
                code[codei] = codeDic;
                codei++;

                dictionary[dici] = pc;
                dici++;

                p = "";
                p += c;

            }
            c = "";    
            pc = "";        
        }

        cout << endl;
        cout << endl;

        for (int i = 0; i < dici; i++) {
            string tmp = dictionary[i];
            printf("%d: ", i);
            for (int j = 0; j < tmp.length(); j++) {
                printf("%X", (unsigned char )tmp.c_str()[j]);
            }   
            printf("%s", ", ");   
        }

        cout << endl;
        cout << endl;

        for (int i = 0; i < dici; i++) {
            printf("%d, ", code[i]);      
        }
        
    }

    void initCharacters() {
        bool put = true;
        bool end = false;
        string character;
        for (int i = 0; i < size && !end; i++) {
            character += data[i];

            for (int j = 0; j < dici + 1 && put; j++) {
                if (dictionary[j] == character) {
                    put = false;  
                }
            }

            if (put) {
                dictionary[dici] = character;
                dici++;
            }
            put = true;
            character = "";
        }

        for (int i = 0; i < size; i++) {
            if (dictionary[i] != "") {
                printf("%X ", (unsigned char )dictionary[i].c_str()[0]);
            } else {
                break;
            }
        }
    }

    void readFile(string filename) {
        std::ifstream file;
        
        file.open(filename.c_str(), std::ios::binary | std::ios::in | std::ios::ate);

        file.seekg(0, std::ios::end);
        size = file.tellg();
        file.seekg(0, std::ios::beg);

        data = new char[size];
        file.read(data, size);

        code = new int[size];

        dictionary = new string[size];
        
        file.close();
    }

};


int main() {
    lzwCompressor lzw;

    lzw.compress("doc.pdf");

    return 0;
}
