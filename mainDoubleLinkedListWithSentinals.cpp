#include<iostream>
#include <string>
#include <sstream>

using namespace std;


struct Element{
    int key;
    int value;
};

struct ElementLL{
    Element elem;
    ElementLL *next, *prev;
};

// Two-way ordered cycled list with sentinel
struct List2W{
    ElementLL *sentinel;
};

void init(List2W& l){
    l.sentinel=new ElementLL();
    l.sentinel->next=l.sentinel;
    l.sentinel->prev=l.sentinel;
}



void insertElem(List2W & l, Element elem){
    

    // when list is empty
    if(l.sentinel->next == l.sentinel && l.sentinel->prev == l.sentinel){
        ElementLL *p = new ElementLL();
        
        p->elem = elem;
        
        p->next = l.sentinel;
        p->prev = l.sentinel;
        l.sentinel ->next = p;
        l.sentinel->prev = p;
        
        return;
    }
    
    ElementLL *p = new ElementLL();
    p =l.sentinel;
    
    
    ///For set 1 and higher
    while(elem.key  >= p->next->elem.key){
       
        p = p->next;
        //add element at the end of list
        if(p->next == l.sentinel){
            ElementLL *newEl = new ElementLL();
            newEl->elem = elem;
            
            newEl->next = p->next;
            newEl->prev = p;
            
            p->next->prev = newEl;
            p->next = newEl;
            
            return;
            
        }
        
    }
    
    //add element in the middle or begining of list
    ElementLL *newEl = new ElementLL();
    newEl->elem = elem;
    
    newEl->next = p->next;
    newEl->prev = p;
    
    p->next->prev = newEl;
    p->next = newEl;
    
    
}

//first key
bool findKey(List2W & l,int key, Element &elem){
    
    ElementLL *p = new ElementLL();
    //empty list
    if(l.sentinel->next == l.sentinel && l.sentinel->prev == l.sentinel){
        return false;
    }
    
    
    p = l.sentinel->next;
    //1 or higher set
    do {
        p = p->next;
        if(p->prev->elem.key == key){
            elem.key = p->prev->elem.key;
            elem.value = p->prev->elem.value;
            return true;
        }
        
        
        
    } while (p != l.sentinel);
    
    
    
    return false;
}

void removeAllKeys(List2W& l, int key){
    
    ElementLL *p = new ElementLL();
    //empty set
    if(l.sentinel->next == l.sentinel && l.sentinel->prev == l.sentinel){
        return;
    }
    
    
    p = l.sentinel->next;
    //1 or higher set
    do {
        p = p->next;
        if(p->prev->elem.key == key){
            
            p->prev = p->prev->prev;
            delete p->prev->next;
        
            p->prev->next = p;
        
        }
        
        
        
    } while (p != l.sentinel);
    
    
    
}

void showListFromHead(List2W& l){
    
    ElementLL *p = new ElementLL();
    
    p = l.sentinel->next;;
    
   
    while(p != l.sentinel){
    
        std:: cout << p->elem.key << "(" << p->elem.value <<"),";
        
        p = p->next;
    }
    std:: cout << std::endl;
}

void showListFromTail(List2W& l){
    
    ElementLL *p = new ElementLL();
    
    p = l.sentinel->prev;;
    
    
    while(p != l.sentinel){
        
        std:: cout << p->elem.key << "(" << p->elem.value <<"),";
        
        p = p->prev;
    }
    std:: cout << std::endl;
}

void clearList(List2W& l){
    
    ElementLL *p = new ElementLL();
    
    //Empty
    if(l.sentinel->next == l.sentinel && l.sentinel->prev == l.sentinel){
        return;
    }
    
    
    p = l.sentinel->next;
    //Set 1 or higher
    do {
        p = p->next;
       delete p->prev;
     
    } while (p != l.sentinel);
    
    l.sentinel->next = l.sentinel;
    l.sentinel->prev = l.sentinel;
    
    
    
    
    
    
}

void addList(List2W& l1,List2W& l2){

    
    ElementLL *p2 = new ElementLL();
    
    p2 = l2.sentinel->next;
   
    
    //Empty list2
    if(l2.sentinel->next == l2.sentinel && l2.sentinel->prev == l2.sentinel){
        return;
    }
    
    
    do {
        p2 = p2->next;
        
        insertElem(l1,p2->prev->elem);
        
        
    } while (p2 != l2.sentinel);

    clearList(l2);


}

void showBool(bool val){
    if(val)
        cout << "true" << endl;
    else
        cout << "false" << endl;
}

bool isCommand(const string command,const char *mnemonic){
    return command==mnemonic;
}

int main(){
    string line;
    string command;
    List2W *list = NULL;
    int currentL=0;
    int value;
    cout << "START" << endl;
    while(true){
        getline(cin,line);
        std::stringstream stream(line);
        stream >> command;
        if(line=="" || command[0]=='#')
        {
            // ignore empty line and comment
            continue;
        }
        
        // copy line on output with exclamation mark
        cout << "!" << line << endl;;
        
        // change to uppercase
        command[0]=toupper(command[0]);
        command[1]=toupper(command[1]);
        
        // zero-argument command
        if(isCommand(command,"HA")){
            cout << "END OF EXECUTION" << endl;
            break;
        }
        
        if(isCommand(command,"SH")) //*
        {
            showListFromHead(list[currentL]);
            continue;
        }
        
        if(isCommand(command,"ST")) //*
        {
            showListFromTail(list[currentL]);
            continue;
        }
        
        if(isCommand(command,"CL")) //*
        {
            clearList(list[currentL]);
            continue;
        }
        
        if(isCommand(command,"IN")) //*
        {
            init(list[currentL]);
            continue;
        }
        
        // read next argument, one int value
        stream >> value;
        
        if(isCommand(command,"FK"))
        {
            Element elem;
            bool ret=findKey(list[currentL], value, elem);
            if(ret)
                cout << elem.key << '(' << elem.value << ')' << endl;
            else
                cout << "false" << endl;
            continue;
        }
        
        if(isCommand(command,"RK"))
        {
            removeAllKeys(list[currentL],value);
            continue;
        }
        
        if(isCommand(command,"CH"))
        {
            currentL=value;
            continue;
        }
        
        if(isCommand(command,"IE"))
        {
            int variable2;
            stream >> variable2;
            Element elem;
            elem.key=value;
            elem.value=variable2;
            insertElem(list[currentL],elem);
            continue;
        }
        
        if(isCommand(command,"GO"))
        {
            list=new List2W[value];
            continue;
        }
        
        if(isCommand(command,"AD"))
        {
            addList(list[currentL],list[value]);
            continue;
        }
        cout << "wrong argument in test: " << command << endl;
    }
    return 0;
}
