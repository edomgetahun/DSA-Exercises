#include<iostream>
#include <cstring>
using namespace std;
struct student{
    char name[20];
    student *next;
};
struct student *start = NULL; // this is a head of the list which points to the first node which we're gonna create later

student* create_node(){     // it's helper function which avoids code repetition which might appeared every time we try to insert new nodes
    struct student *p;
    p = new student;
    cout<<"Enter the name of the student: ";
    cin>>p->name;
    p->next = NULL;
    return p;
}

// Insert at the beginning
void insert_beg(student *p){
    student *temp;
    if(start == NULL){
        start = p;
        cout<<"The new node is inserted successfully at the beginning of the list\n";
    }else{
        temp = start;
        start = p;
        p->next = temp;
        cout<<"The new node is inserted successfully at the beginning of the list\n";
    }
}

//Insert at the end
void insert_end(student *p){
    student *q = start;      //a "walking pointer" moving through the nodes.
    if(start == NULL){
        start = p;
        cout<<"The new node is inserted successfully at the end of the list.\n";
    }else{
        while(q->next != NULL){
            q = q->next; 
        }
        q->next = p;
        cout<<"The new node is inserted successfully at the end.\n";
    }
}

// Insert at any given position
void insert_pos(int c, student *p){
    if(c == 1){  
        insert_beg(p);
        return;
    }
    student *q = start;
    for(int i=1; i<c-1; i++){
        if(q == NULL){
            cout << "Cannot insert: less than " << c-1 << " nodes in the list\n";
            return;
        }
        q = q->next;
    }
    if(q == NULL){
        cout << "Cannot insert: position out of bounds\n";
        return;
    }
    p->next = q->next;
    q->next = p;
    cout << "Node inserted successfully\n";
}

// delete the first node
void delete_first(){
    if(start == NULL){
        cout<<"nothing to delete : the list is empty\n";
    }else{
        student *temp = start;
        start = temp->next;
        delete temp;
        cout<<"The first node is deleted successfully\n";
    }
}

// delete at the end
void delete_end(){
     student *q = start;
    if(start == NULL){
        cout<<"nothing to delete : the list is empty\n";
    
    }
    if(start->next== NULL){
            q = start;
            start= NULL;
            delete q;
    }
    else{
        while(q->next->next != NULL){
            q = q->next; 
        }
        student *temp = q->next; // here both of them points to the last node 
        q->next = NULL;   // here break the bond that q->next points which is the last node then assign it to point null
        delete temp;    // here i can safely delete the last node
        cout<<"The last node is deleted successfully\n";
    }
}

// delete at any position
void del_pos(int c){
    if(start == NULL){
        cout<<"The list is empty\n";
        return;
    }
    if(c == 1){ 
        delete_first();
        return;
    }
    student *q = start;
    for(int i=1; i<c; i++){
        q = q->next;
        if(q==NULL){
            cout<<"Node not found\n";
            return;  // stop the whole function immediately
        }
    }
    student *p = q->next;      // the node which gonna be deleted
    q->next = p->next;         // before delete p make sure the previous(the one before deleted node)node next points to the one after deleted node 
    delete p;
    cout<<"Deleted Successfully\n";
}

// Display forward
void display_forward(){
    if(start == NULL){
        cout<<"The list is empty\n";
        return;
    }
    student *q = start;
    cout<<"List of students: ";
    while(q != NULL){
        cout<<q->name<<" -> ";
        q = q->next;
    }
    cout<<"NULL"<<endl;
}

// display backward
void display_backward(){
    if(start == NULL){
        cout << "The list is empty\n";
        return;
    }
    cout << "List of students backward: ";
    
    student *p = start;
    while(p->next != NULL){
        p = p->next;
    }
   
    while(p != start){
        cout<<p->name<<" ->";
        student *q = start;         // q must start from the beginning in each iteration
        while(q->next != p){
            q = q->next;  
        }
    p = q;
    } 
    cout << p->name << " -> NULL" << endl;
}


// search by name 
void search(){
    if(start == NULL){
        cout<<"The list is empty\n";
        return;
    }
    char name[20];
    cout<<"Enter the student name to search: ";
    cin>>name;

    student *q = start;
    int pos = 1;
    bool found = false;
    while(q != NULL){
        if(strcmp(q->name, name) == 0){
            cout<<"Student found at position "<<pos<<": "<<q->name<<endl;
            found = true;
            break;
        }
        q = q->next;
        pos++;
    }
    if(!found){
        cout<<"Student not found in the list"<<endl;
    }
}

int main(){
    int choice, pos;
    student *p;
    do{
        cout<<"\n---MENU ---\n";
        cout<<"1. Insert at beginning\t"<<"6. Delete at position\n";
        cout<<"2. Insert at end\t"<<"7. Display forward\n";
        cout<<"3. Insert at position\t"<<"8. Display backward\n";
        cout<<"4. Delete first node\t"<<"9. Search by name\n";
        cout<<"5. Delete last node\t"<<"0. Exit\n";
        cout<<"Enter your choice: ";
        cin>>choice;

        switch(choice){
            case 1:
                p = create_node(); // p is the returned pointer for the newly created node using the function
                insert_beg(p);
                break;
            case 2:
                p = create_node();
                insert_end(p);
                break;
            case 3:
                cout<<"Enter position to insert: ";
                cin>>pos;
                p = create_node();
                insert_pos(pos, p);
                break;
            case 4:
                delete_first();
                break;
            case 5:
                delete_end();
                break;
            case 6:
                cout<<"Enter position to delete: ";
                cin>>pos;
                del_pos(pos);
                break;
            case 7:
                display_forward();
                break;
            case 8:
                display_backward();
                break;
            case 9:
                search();
                break;
            case 0:
                cout<<"Exiting program."<<endl;
                break;
            default:
                cout<<"Invalid choice! Try again."<<endl;
        }
    }while(choice!=0);
    return 0;
}