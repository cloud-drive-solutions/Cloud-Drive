#include <string>
#include <iostream>
#include <cstring>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <iterator>
#include <charconv>

#include "linkedlist.cpp"

using namespace std;

class lz78Compressor
{
private:
    LinkedList *lista = new LinkedList; // The dictionary
    LinkedList *tuplas = new LinkedList;
    char *data;
    size_t size;
    int current_index = 0;

public:
    void compress()
    {
        lista->addData("", 0);
        current_index++;
        string tmp;
        string toTupla;
        int next= 0;
        int x = 0;
        tmp = (unsigned char)this->data[0];
        int length = this->size+1;//this->size;
        int contain = lista->contains(tmp);
        while (x < length)
        {
            contain = lista->contains(tmp);
            toTupla = (unsigned char)this->data[x];
            if (contain == -1)
            {
                lista->addData(tmp, current_index);
                tuplas->addData(toTupla, next);
                current_index++;
                x++;
                tmp = (unsigned char)this->data[x];
                next = 0;
            }
            else if (contain != -1)
            {
               
                next = contain;
                //cout<<next<<" ESTE ES EL next CUANDO LO CONTIENE"<<endl;
                tmp += (unsigned char)this->data[x + 1];
                //cout<<tmp << "OMG PRAY PARA QUR SIRVAAAA"<<endl;
                toTupla = (unsigned char)this->data[x + 1];
                x++;
            }
        }
    


//tuplas
/*
        for (int i = 0; i < tuplas->getSize(); i++)
        {
            cout << "( ";
            cout<<tuplas->getIndex(i);
            cout << " - ";
            printf("%X ", (unsigned char)tuplas->getData(i)[0]);
            cout << " )" << endl;
           
        }
        */


        //cout << "\n"<< "\nRESULTADO DESCOMPRIMIDO LOL: ";
        int for_decompress;
        
        for (int i = 0; i <tuplas->getSize(); i++)
        {
            for_decompress = tuplas->getIndex(i);
            if (lista->getData(for_decompress)[0] == *""){
                //printf("%X ", (unsigned char)tuplas->getData(i)[0]);
                
            }else{  
                //printf("%X ", (unsigned char)lista->getData(for_decompress)[0]);
                //printf("%X ", (unsigned char)tuplas->getData(i)[0]);
            }
        }

        //decompress

        string lolo;
        for (int i = 0; i < tuplas->getSize(); i++)
        {
            //cout<<"/"<<lista->getData(i);
            //cout <<"( " <<tuplas->getIndex(i)<<" / " << tuplas->getData(i)<<" )\n";
            lolo+= lista->getData(tuplas->getIndex(i)) +tuplas->getData(i) ;
            //cout << result<<" PROGRESOOOO"<<endl;
        }
        cout <<endl<<endl<<"DESCOMPRIMIDO: "<< lolo<<endl;


        // dictionary
        
        /*
        cout <<endl<< "diccionario: "<<endl;
        for (int i = 0; i < lista->getSize(); i++)
        {
            cout << lista->getIndex(i);
            cout<<"- ";
            //printf("%X ", (unsigned char)lista->getData(i)[0]);
            cout << lista->getData(i);
            cout<<endl;
        }
        */


        fstream file;
        file.open("txtrandom.txt",std::ios_base::out);
        for (int i = 0; i <tuplas->getSize(); i++){
            file<<"(";
            file<<tuplas->getIndex(i);
            file<<",";
            file<<tuplas->getData(i);
            file<<")\n";
        }
        file<< "tamaño del diccionario: ";
        file<<lista->getSize();
        file<<endl;
        file<<"Cantidad de tuplas: ";
        file<<tuplas->getSize();
        file<<endl;
        
        
        

        /*
        cout <<endl<<endl<< "elements in the dictionary:"<<endl;
        for (int i = 0; i < lista->getSize(); i++)
        {
            printf("%X ", (unsigned char)lista->getData(i)[0]);
        }
        */
        

    }

    void readFile(string filename)
    {
        std::ifstream file;

        file.open(filename.c_str(), std::ios::binary | std::ios::in | std::ios::ate);

        file.seekg(0, std::ios::end);
        this->size = file.tellg();
        file.seekg(0, std::ios::beg);

        data = new char[this->size+1];
        file.read(data, this->size+1);

        file.close();
        this->printdata(this->size +1);
        cout << "\n";
    }

    void printdata(int size)
    {
        for (int i = 0; i < size; i++)
        {
            //printf("%X ", (unsigned char)this->data[i]);
            cout<<this->data[i];
        }
    }
};

int main()
{
    lz78Compressor lz78;
    lz78.readFile("stickman.gif");
    // lz78.printdata();
    lz78.compress();
    return 0;
}