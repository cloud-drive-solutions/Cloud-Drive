#include <iostream>
#include <string>
#include <cstring>

using namespace std;

struct node
{
    string data;
    node *next = NULL;
    int index = -1;
    //tuplas
    int x;
    string y;
};

class LinkedList
{
private:
    node *head = NULL;
    int size = 0;

public:
    void addData(string data,int index)
    {
        if (head == NULL)
        {
            head = new node;
            head->data = data;
            head->index = index;
       
        }
        else if (head->next == NULL)
        {
            head->next = new node;
            head->next->data = data;
            head->next->index = index;
          
        }
        else
        {
            node *tmp = head;
            while (tmp->next != NULL)
            {
                tmp = tmp->next;
            };
            tmp->next = new node;
            tmp->next->data = data;
            tmp->next->index = index;
        }
        this->size++;
    }

    string getData(int index)
    {
        if (index < size)
        {
            node *tmp = head;
            for (int i = 0; i < index; i++)
            {
                tmp = tmp->next;
            }
            return tmp->data;
        }
        else
        {
            return "erorr del index";
        }
    }

    int contains(string data){
        node *tmp = head;
        int i = 0;
            while (tmp != NULL)
            {
                if(tmp->data == data){
                    return tmp->index;
                }
                tmp = tmp->next;
                i++;
            }
            return -1;
    }

    int getIndex(int index){
        if (index < size)
        {
            node *tmp = head;
            for (int i = 0; i < index; i++)
            {
                tmp = tmp->next;
            }
            return tmp->index;
        }
        else
        {
            return -1;
        }
    }

    /*
            int getElements(int index) {
                if (index < size) {
                    node *tmp = head;
                    for (int i = 0; i < index; i++) {
                        tmp = tmp->next;
                    }
                    return tmp->elements;
                } else {
                    return 0;
                }
            }


            bool deleteData(int index) {
                node *tmp = head;
                if (index == 0) {
                    head = head->next;
                    delete tmp;
                    size--;
                    return 1;
                } else if (index < size) {
                    for (int i = 0; i < index -1; i++) {
                        tmp = tmp->next;
                    }
                    node *tmp2 = tmp->next;
                    tmp->next = tmp->next->next;
                    delete tmp2;
                    size--;
                    return 1;
                } else {
                    return 0;
                }
            }
         */
    int getSize()
    {
        return size;
    }
};
