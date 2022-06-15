#include <iostream>

struct node {
    char *data;
    int elements;
    node* next = NULL;
};

class LinkedList {
    private: 
        node* head = NULL;
        int size = 0;

    public:
        bool addData(char *data, int elements) {  
            if (head == NULL) {
                head = new node;
                head->data = new char[elements];
                for (int i = 0; i < elements; i++) {
                    head->data[i] = data[i];
                }
                head->elements = elements;
            } else if (head->next == NULL) {
                head->next = new node;
                head->next->data = new char[elements];
                for (int i = 0; i < elements; i++) {
                    head->next->data[i] = data[i];
                }
                head->next->elements = elements;
            } else {
                node *tmp = head;
                while (tmp->next != NULL) {
                    tmp = tmp->next;
                };
                tmp->next = new node;
                tmp->next->data = new char[elements];
                for (int i = 0; i < elements; i++) {
                    tmp->next->data[i] = data[i];
                }

                tmp->next->elements = elements;
            }
            this->size++;

            return 1;
        }

       char *getData(int index) {
            if (index < size) {
                node *tmp = head;
                for (int i = 0; i < index; i++) {
                    tmp = tmp->next;
                }
                //std::cout << " " << tmp->data[0] << std::endl;
                return tmp->data;
            } else {
                return 0;
            }
        }

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
    
        int getSize() {
            return size;
        }
};

/*
int main(void) {
    LinkedList lista;
    char *jmm = new  char[3];
    jmm[0] = 0x11;
    jmm[1] = 0x12;
    jmm[2] = 0x13;
    
    char *jmm2 = new  char[2];
    jmm2[0] = 0x01;
    jmm2[1] = 0xff;

    lista.addData(jmm, 3);
    lista.addData(jmm2, 2);
    lista.addData(jmm2, 2);

    printf("%x\n", lista.getData(0)[2]);
    printf("%x\n", lista.getData(1)[0]);
    printf("%x\n", lista.getData(2)[0]);
}
*/