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
            return "Index error";
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

    int getSize()
    {
        return size;
    }
};
