#include <string>
#include <iostream>
#include <stdio.h>
#include <fstream>
#include "linkedlist.cpp"

using namespace std;

class lz78Compressor
{
private:
    LinkedList *dictionary = new LinkedList;
    LinkedList *tuplas = new LinkedList;
    char *data;
    size_t size;
    int current_index = 0;

public:
    void compress()
    {
        dictionary->addData("", 0);
        current_index++;
        string tmp;
        string toTupla;
        int next= 0;
        int x = 0;
        tmp = (unsigned char)this->data[0];
        int length = this->size+1;
        int contain = dictionary->contains(tmp);
        while (x < length)
        {
            contain = dictionary->contains(tmp);
            toTupla = (unsigned char)this->data[x];

            if (contain == -1)
            {
                dictionary->addData(tmp, current_index);
                tuplas->addData(toTupla, next);

                current_index++;
                x++;

                tmp = (unsigned char)this->data[x];
                next = 0;
            }
            else if (contain != -1)
            {
                next = contain;
                tmp += (unsigned char)this->data[x + 1];
                toTupla = (unsigned char)this->data[x + 1];
                x++;
            }
        }

    }

    void tuplastxt(string filename){
        fstream file;
        file.open(filename,std::ios_base::out);
        for (int i = 0; i <tuplas->getSize(); i++){
            file<<"(";
            file<<tuplas->getIndex(i);
            file<<",";
            file<<tuplas->getData(i);
            file<<")\n";
        }
        file.close();
    }

    void dictionarytxt(string filename){
        fstream file;
        file.open(filename,std::ios_base::out);
        for (int i = 0; i <dictionary->getSize(); i++){
            file<<dictionary->getIndex(i);
            file<<"-";
            file<<dictionary->getData(i);
            file<<"\n";
        }
        file.close();
    }

    void decompress(){
        string decompressed;
        for (int i = 0; i < tuplas->getSize(); i++)
        {
            decompressed+= dictionary->getData(tuplas->getIndex(i)) + tuplas->getData(i) ;
        }
        cout <<endl<<endl<<"EL ARCHIVO DESCOMPRIMIDO ES: "<< decompressed <<endl;
    }

  void createGIF(){
        fstream gif;
        gif.open("testgif.gif",std::ios_base::out);
        string giff;
          for (int i = 0; i < tuplas->getSize(); i++)
        {
            gif<< dictionary->getData(tuplas->getIndex(i)) + tuplas->getData(i) ;
            //giff+= lista->getData(tuplas->getIndex(i)) +tuplas->getData(i) ;
        }
        //gif<<giff;
        gif.close();
    }

    void readFile(string filename)
    {
        std::ifstream file;

        file.open(filename.c_str(), std::ios::binary | std::ios::in | std::ios::ate);

        file.seekg(0, std::ios::end);
        this->size = file.tellg();
        file.seekg(0, std::ios::beg);

        data = new char[this->size +1];
        file.read(data, this->size +1); 

        file.close();
        //this->printdata(this->size +1); 
    }

    void printdata(int size)
    {
        for (int i = 0; i < size; i++)
        {
            //printf("%X ", (unsigned char)this->data[i]);
            cout<<this->data[i];
        }
        cout<<endl;
    }

  
};

int main()
{
    lz78Compressor lz78;
    lz78.readFile("stickman.gif");
    lz78.compress();
    lz78.decompress();
    lz78.tuplastxt("tuplas.txt"); 
    lz78.dictionarytxt("dictionary.txt");
    //lz78.createGIF(); //No está sirviendo
    return 0;
}