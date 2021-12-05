struct Lnode{
    int val;
    Lnode* prev;
    Lnode* next;
    Lnode():val(0),prev(nullptr),next(nullptr){};
    Lnode(int _val):val(_val),prev(nullptr),next(nullptr){};
};
class MyLinkedList {
private:
    int size;
    Lnode* head;
    Lnode* tail;
public:
    MyLinkedList() {
        size=0;
        head=new Lnode();
        tail=new Lnode();
        head->next=tail;
        tail->prev=head;
    }
    
    int get(int index) {
        if(index<0||index>=size){
            return -1;
        }
        Lnode* node=head;
        for(int i=0;i<=index;i++){
            node=node->next;
        }
        return node->val;
    }
    
    void addAtHead(int val) {
        Lnode* node=new Lnode(val);
        node->prev=head;
        node->next=head->next;
        head->next->prev=node;
        head->next=node;
        size++;
        return ;
    }
    
    void addAtTail(int val) {
        Lnode* node=new Lnode(val);
        node->next=tail;
        node->prev=tail->prev;
        tail->prev->next=node;
        tail->prev=node;
        size++;
        return ;
    }
    
    void addAtIndex(int index, int val) {
        if(index>size){
            return ;
        }
        if(index<0){
            addAtHead(val);
            return ;
        }
        if(index==size){
            addAtTail(val);
            return ;
        }
        Lnode* node=head;
        for(int i=0;i<=index;i++){
            node=node->next;
        }
        Lnode* node1=new Lnode(val);
        node1->next=node;
        node1->prev=node->prev;
        node->prev->next=node1;
        node->prev=node1;
        size++;
        return ;
    }
    
    void deleteAtIndex(int index) {
        if(index<0||index>=size){
            return ;
        }
        Lnode* node=head;
        for(int i=0;i<=index;i++){
            node=node->next;
        }
        node->next->prev=node->prev;
        node->prev->next=node->next;
        size--;
        delete node;
        return ;
    }
};
