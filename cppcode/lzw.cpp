#include <string>
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <fstream>

#include "linkedList.cpp"

using namespace std;

class lzwCompressor {
private:
    LinkedList *dictionary;
    int *code = new int[10000];
    char *data;
    size_t size;

public:
    bool searchInDictionary(char* search, int chars) {
        bool ret = false;
        for (int i = 0; i < dictionary->getSize(); i++) {
            if (dictionary->getElements(i) == chars) {
                dictionary->getData(i);
                for (int j = 0; j < chars; j++) {

                }
            }
            ret = true;
            break;
        }
        return ret;
    }

    void compress(string filename) {
        readFile(filename);
        initCharacters();

        string p = "";
        p += data[0];
        char c;
        string pc = "";

        for (int i = 1; i < 300; i++) {
            c = data[i];

            pc = p;
            p += c;

            char pcChar[pc.length() + 1];
            strcpy(pcChar, pc.c_str());

            cout << pc << endl;

            if (searchInDictionary(pcChar, pc.length())) {

            }
        }
        
       

        char charr = 0x25;
        p += charr;
        p += 0x50;

        char strinng[p.length() + 1];
        strcpy(strinng, p.c_str());
        cout << "P: " << p << " : " << strinng << " : " << endl;

        

        


        /*
        char *toPrint = new char[3];
        for (int i = 0; i < 9; i++) {
            printf("%d ", strlen(toPrint));
            toPrint[0] = data[i];
            toPrint[1] = data[i + 1];
            toPrint[2] = '\0';

            printf("%x ", toPrint[0]);
            printf("%x ", toPrint[1]);
            printf("%x\n", toPrint[2]);
            
            //printf("%x ", toPrint[1]);
            //printf("%d ", toPrint);
        }

        char *compare = new char[3];
        compare[0] = 0x25;
        compare[1] = 0x50;
        compare[2] = '\0';

        toPrint[0] = data[0];
        toPrint[1] = data[1];
        toPrint[2] = '\0';

        if (strcmp(compare, toPrint) == 0) {
            printf("%s ", "nao");
        }
        */


    }

    void initCharacters() {
        char *character = new char;
        bool put = true;

        for (int i = 0; i < 300; i++) {
            character = new char;
            *character = this->data[i];
            for (int j = 0; j < dictionary->getSize() && put; j++) {
                if (dictionary->getData(j)[0] == *character) {
                    put = false;  
                }
            }

            if (put) {
                dictionary->addData(character, 1);
            }
            put = true;
        }

        for (int i = 0; i < dictionary->getSize(); i++) {
            printf("%X ", (unsigned char)dictionary->getData(i)[0]);
        }
    }

    void readFile(string filename) {
        dictionary = new LinkedList();
        std::ifstream file;
        
        file.open(filename.c_str(), std::ios::binary | std::ios::in | std::ios::ate);

        file.seekg(0, std::ios::end);
        size = file.tellg();
        file.seekg(0, std::ios::beg);

        data = new char[300];
        file.read(data, 300);

        //for (int i = 0; i < size; i++) {
        //    printf("%x ", (unsigned char)data[i]);
        //}
        
        file.close();
    }

};

/*
int main() {
    lzwCompressor lzw;

    lzw.compress("pddf.pdf");

    return 0;
}
 */