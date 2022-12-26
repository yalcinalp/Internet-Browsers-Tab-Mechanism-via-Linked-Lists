#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

#include "Node.h"

template <class T>
class LinkedList
{
public: 
    LinkedList();
    LinkedList(const LinkedList<T> &obj);
    ~LinkedList();

    LinkedList<T> &operator=(const LinkedList<T> &rhs);

    int getSize() const;
    bool isEmpty() const;
    bool containsNode(Node<T> *node) const;
    int getIndex(Node<T> *node) const;

    Node<T> *getFirstNode() const;
    Node<T> *getLastNode() const;
    Node<T> *getNode(const T &data) const;
    Node<T> *getNodeAtIndex(int index) const;

    void append(const T &data);
    void prepend(const T &data);
    void insertAfterNode(const T &data, Node<T> *node);
    void insertAtIndex(const T &data, int index);
    void moveToIndex(int currentIndex, int newIndex);

    void removeNode(Node<T> *node);
    void removeNode(const T &data);
    void removeNodeAtIndex(int index);
    void removeAllNodes();

    void print() const;

private: // WE MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.

private:
    Node<T> *head;
    int size;
};

template<class T>
LinkedList<T>::LinkedList()
{
    head = NULL;
    size = 0;   
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &obj)
{   
    head = NULL;
    size = 0;
    
    *this = obj; // use of assignment operator =
}


template<class T>
LinkedList<T>::~LinkedList()
{
    removeAllNodes();
    size = 0;
}

template<class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs)
{
    if(this == &rhs){ 
        return *this;
    }   
    
    else{
        
        if(head != NULL){
        
            Node<T> *current = head;
            Node<T> *next = NULL;
        
            do{
            
                next = current->next;
                delete current; 
                current = next;
            }
            
            while(current != head);
            
            size = 0;
            head = NULL;
        }
        
        Node<T> *tmp;
        Node<T> *current;
        Node<T> *follower;
        
        current = head;
        tmp = rhs.head;
        
        int flag = 0;
        
        if(rhs.head != NULL){
            
            if(tmp->next != rhs.head){
            
                while(tmp->next != rhs.head){
                    
                    if (flag == 1){
                        
                        follower = current;
                        current = new Node<T>(tmp->data);
                        current->prev = follower;
                        follower->next = current;
                        tmp = tmp->next;
                    }
                    
                    else{

                        head = new Node<T>(rhs.head->data);
                        current = head;
                        
                        flag = 1;
                        tmp = tmp->next;
                    }
                }
                
                follower = current;
                current = new Node<T>(tmp->data);
                current->prev = follower;
                follower->next = current;
                
                current->next = head;
                head->prev = current;
            }
            
            else{
                
                head = new Node<T>(rhs.head->data);
                head->next = head;
                head->prev = head;
                
            }
            
        }
        
        else{
            head = NULL;
        }
        
        this->size = rhs.size;
        return *this;
    }
}

template<class T>
int LinkedList<T>::getSize() const
{
    return size;
}

template<class T>
bool LinkedList<T>::isEmpty() const
{
    if(size == 0){
        return true;
    }

    else{
        return false;
    }
}

template<class T>
bool LinkedList<T>::containsNode(Node<T> *node) const
{
    if(head != NULL){
        
        Node<T> *current;
        current = head;
        int flag = 0;
        
        while(current->next != head){
            
            if(current == node){
                flag = 1;
                break;
            }

            current = current->next;
        }
        
        //AFTER THE LOOP WE ARE ON THE LAST NODE
        
        if(current == node){
            flag = 1;
        }
        
        if (flag == 1){
            return true;
        }
        
        else{
            return false;
        }
    }
    
    else{
        return false;
    }
        
}

template<class T>
Node<T> *LinkedList<T>::getFirstNode() const
{
    if(head != NULL){
        return head;   
    }

    else{
        return NULL;
    }
}

template<class T>
Node<T> *LinkedList<T>::getLastNode() const
{
    if(head != NULL){
        return (head->prev);    
    }
    
    else{
        return NULL;
    }
    
}

template<class T>
Node<T> *LinkedList<T>::getNode(const T &data) const
{
    if(head != NULL){
        
        if(head->data == data){
            
            return head;
        }
        
        else{
            
            Node<T> *current;
            current = head->next;
            
            while(current != head){
                
                if(current->data == data){
                    return current;
                    
                }
                
                current = current->next;
            }
            
            return NULL;
        }
    }
    
    else{
        return NULL;
    }
    
}

template<class T>
Node<T> *LinkedList<T>::getNodeAtIndex(int index) const
{
    int idx = 1;
    
    if(size-1 < index){
        return NULL;
    }
    
    else if(index < 0){
        return NULL;
    }
    
    else{
        
        if(head != NULL){
        
            if(index == 0){
                return head;
            }
            
            else{
            
                Node<T> *current;
                current = head->next;
                
                while(current != head){
                    
                    if(idx == index){
                        return current;
                    }
                    
                    idx++;
                    current = current->next;
                }
            
                return NULL;
            }
        }

        else{
            return NULL;
        }
    }
}

template<class T>
void LinkedList<T>::append(const T &data)
{
    if(head == NULL){
        
        head = new Node<T>(data);
        head->prev = head;
        head->next = head;
        
        size = 1;
    }
    
    else{
        
        Node<T> *current;
        Node<T> *fresh_made;
        
        fresh_made = new Node<T>(data);
        
        fresh_made->next = head;
        fresh_made->prev = head->prev;
        
        head->prev->next = fresh_made;
        head->prev = fresh_made;
        
        size++;
    }
    
}

template<class T>
void LinkedList<T>::prepend(const T &data)
{
    //dont forget that head will always change in this case
    
    if(head == NULL){
        
        head = new Node<T>(data);
        head->prev = head;
        head->next = head;
        
        size = 1;
    }
    
    else{
        
        Node<T> *current;
        Node<T> *fresh_made;
        
        current = head->prev;
        fresh_made = new Node<T>(data);
        
        fresh_made->next = head;
        fresh_made->prev = current;
        
        head->prev = fresh_made;
        current->next = fresh_made;
        
        head = fresh_made;
        size++;
        
    }
}

template<class T>
void LinkedList<T>::insertAfterNode(const T &data, Node<T> *node)
{
    Node<T> *current;
    
    if(head != NULL){
        
        if(head == node){
                
            Node<T> *fresh_made = new Node<T>(data);
            
            fresh_made->next = head->next;
            fresh_made->prev = head;
            
            head->next->prev = fresh_made;
            head->next = fresh_made;
            
            size++;
        }
        
        else{
            
            current = head->next;
            
            while(current != head){
             
                if(current == node){

                    Node<T> *fresh_made= new Node<T>(data);
                    
                    fresh_made->next = current->next;
                    fresh_made->prev = current;
                    
                    current->next->prev =fresh_made;
                    current->next = fresh_made;
                    break;

                }
            
                current = current->next;
            }
            
            size++;
        }
    }
}

template<class T>
void LinkedList<T>::insertAtIndex(const T &data, int index)
{
    if(index < 0){
        
    }
    
    if(size-1 < index){
        
    }
    
    if(size = 0 && index == 0){
        
        head = new Node<T>(data);
        size = 1;
    }
    
    else{
        
        if(index == 0){
            
            Node<T> *fresh_made = new Node<T>(data);
            
            fresh_made->next = head;
            fresh_made->prev = head->prev;
            
            head->prev->next = fresh_made;
            head->prev = fresh_made;
            
            head = fresh_made;
            size++;
            
        }
        
        else{
            
            Node<T> *fresh_made = new Node<T>(data);
            int idx = 1;
            
            Node<T> *current;
            current = head->next;
            
            while(current != head){
             
                 if(idx == index){
                     
                    fresh_made->prev = current->prev;
                    fresh_made->next = current;
                     
                    current->prev->next = fresh_made;
                    current->prev = fresh_made;
                     
                    size++;
                    break;
                }
                 
                idx++;
                current = current->next;
            }
        }
    }
}

template<class T>
int LinkedList<T>::getIndex(Node<T> *node) const
{   
    if(head != NULL){
        
        int index = 1;
        Node<T> *current;
        
        current = head->next;
        
        if(head == node){
            return 0;
        }
        
        else{
            
            while(current != head){
                
                if(current == node){  
                 return index;
                }
                
                index++;
                current = current->next;
            }
        }

        return -1;
    }
    
    else{
        return -1;
    }
}

template<class T>
void LinkedList<T>::moveToIndex(int currentIndex, int newIndex)
{

    if(currentIndex > size-1){

    }

    if(head == NULL && size == 0){
    //there is nothing to move, do nothing
    }

    else{

        if(size == 1){

        }

        else{

            Node<T> *current_idx;
            Node<T> *new_idx;

            if(currentIndex == newIndex){
            }

            else{

                current_idx = getNodeAtIndex(currentIndex);

                if(newIndex > size-1){

                    //in this case, it should be the last node

                    current_idx->prev->next = current_idx->next;
                    current_idx->next->prev = current_idx->prev;

                    head->prev->next = current_idx;
                    head->prev = current_idx;

                }

                else if(newIndex == 0){

                    //we need to change the head as well...

                    new_idx = getNodeAtIndex(newIndex);

                    current_idx->prev->next = current_idx->next;
                    current_idx->next->prev = current_idx->prev;

                    current_idx->next = new_idx;
                    current_idx->prev = new_idx->prev;

                    head->prev->next = current_idx;
                    head->prev = current_idx;
                    head = current_idx;

                }

                else{

                        //smth between...
                        if(currentIndex == 0 && newIndex == size-1){

                            head = head->next;

                        }

                        else if(currentIndex == 0 && newIndex != 0){

                            new_idx = getNodeAtIndex(newIndex);
                            Node<T> *temp_node;
                            
                            temp_node = head->next;

                            head->prev->next = head->next;
                            head->next->prev = head->prev;

                            new_idx->next->prev = head;

                            current_idx->next = new_idx->next;
                            new_idx->next = head;

                            head = temp_node;

                            // current_idx->next = new_idx->next;
                            
                            current_idx->prev = new_idx;

                        }


                        else{

                            new_idx = getNodeAtIndex(newIndex);

                            current_idx->prev->next = current_idx->next;
                            current_idx->next->prev = current_idx->prev; 

                            if(newIndex > currentIndex){

                                current_idx->next = new_idx->next;
                                current_idx->prev = new_idx;

                                new_idx->next->prev = current_idx;
                                new_idx->next = current_idx;

                            } 

                            else if(newIndex < currentIndex){

                                current_idx->next = new_idx;
                                current_idx->prev = new_idx->prev;

                                new_idx->prev->next = current_idx;
                                new_idx->prev = current_idx;

                            }
                        }
                }
            }
        }
    }
}

template<class T>
void LinkedList<T>::removeNode(Node<T> *node)
{

    if (head != NULL) {

        if (head->next != head) {
    
            if (head == node) {
                
                // special case
                // need to change the head
                
                Node<T> *current;
                Node<T> *to_delete;
                
                current = head->prev;
                to_delete = head; 
                
                current->next = head->next;
                head->next->prev = current;
                
                head = head->next;
                delete to_delete;
                size--;
                
            }
            
            else {
                
                if(containsNode(node)){
                
                    node->next->prev = node->prev;
                    node->prev->next = node->next;
                    
                    delete node;
                    size--;
                }
            }
        }

        else {

            if (head == node) {
                delete head;
                
                size = 0;
                
                head = NULL;
            }
        }    
    }
}

template<class T>
void LinkedList<T>::removeNode(const T &data)
{
    
    if (head != NULL) {
    
        if(size == 1 && head->data == data){
            
            delete head;
            head = NULL;
            size = 0;
        }
        
        else{
            
            if(head->data == data){
                
                // we need to move head to head->next
                
                Node<T> *current;           
                current = head;
                
                head->prev->next = head->next;
                head->next->prev = head->prev;
                
                head = head->next;
                
                delete current;
                size--;
                
            }
            
            else{
                
                Node<T> *current;
                current = head->next;
                
                while(current != head){
                    
                    if(current->data == data){
                        
                        Node<T> *temp;
                        
                        current->next->prev = current->prev;
                        current->prev->next = current->next;
                        
                        temp = current;
                        current = current->next;
                        
                        delete temp;
                        size--;
                        
                    }
                    
                    current = current->next;
                }
            
            }
         
            if(size == 0){
                
                head = NULL;
            }         
            
        }
        
    }
    
}

template<class T>
void LinkedList<T>::removeNodeAtIndex(int index)
{
    /* TODO */
    
    if(size == 0){
        
    }
    
    if(size-1 < index){
        
        
    }
    
    else{
        
        if(index == 0 && size == 1){
            
            delete head;
            head = NULL;
            size = 0;
        }
        
        else{
            
            Node<T> *current;
            int idx = 1; 
            
            if(index == 0){
            
                head->prev->next = head->next;
                head->next->prev = head->prev;
                
                current = head;
                
                head = head->next;
                
                delete current;
                
                size--;
            
            }
            
            else{
                
                current = head->next;
                
                while(current != head){
                    
                    if(idx == index){
                    
                        current->prev->next = current->next;
                        current->next->prev = current->prev;
                        size--;
                        
                        delete current;
                        break;
                    }
                    
                    idx++;
                    current = current->next;
                }
            }
        }
    }
}
template<class T>
void LinkedList<T>::removeAllNodes()
{

    if(head != NULL){
        
        Node<T> *temp;
        Node<T> *current;
        
        current = head->next;
        
        while(current != head) {
            temp = current->next;
            delete current;
            current = temp;
        }
        
        delete head;
        head = NULL;
        size = 0;
        
    }
}

template<class T>
void LinkedList<T>::print() const
{
    if (this->isEmpty()) {
        std::cout << "The list is empty." << std::endl;
        return;
    }

    Node<T> *node = this->getFirstNode();

    do {
        std::cout << *node << std::endl;
        node = node->next;
    }
    while (node != this->getFirstNode());
}

#endif //LINKEDLIST_H
