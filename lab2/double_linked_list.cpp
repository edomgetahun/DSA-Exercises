#include<iostream>
#include <cstring>
using namespace std;
struct student{
    char name[20];
    int age;
    student *next;
    student *prev;
};
struct student *start = NULL; 
student* create_node(){     // it's helper function which avoids code repetition which might appeared every time we try to insert new nodes
    struct student *p;
    p = new student;
    cout<<"Enter the name of the student: ";
    cin>>p->name;
    cout<<"Enter the age: ";
    cin>>p->age;
    p->next = NULL;
    p->prev = NULL;
    return p;
}

void insert_beg(student *p){
    if(start == NULL){
        start = p;
        cout<<"node inserted successfully at the beginning";
    }else{
        student *temp = start;
        start = p;
        temp->prev = p;
        p->next = temp;
        cout<<"\nnode inserted successfully at the beginning";
    }
}

void insert_end(student *p){
    if(start == NULL){
        start = p;
        cout<<"node inserted successfully at the end";
    }else{
        student *temp = start;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = p;
        p->prev = temp;
        cout<<"node inserted successfully at the end";
    }
}

void insert_after(student *p, int c){
    if(c == 1){  
        insert_beg(p);
        return;
    }
    student * temp = start;
    for(int i=1; i<c-1; i++){
        if(temp == NULL){
            cout << "Cannot insert: less than " << c-1 << " nodes in the list\n";
            return;
        }
        temp = temp->next;
    }
    if(temp == NULL){
        cout << "Cannot insert: position out of bounds\n";
        return;
    }
    p->next = temp->next;
    p->next->prev = p;
    temp->next = p;
    p->prev = temp;
    cout<<"\nnode inserted successfully at position  "<<c<<endl;
}

void display_forward(){
    if(start == NULL){
        cout<<"The list is empty\n";
        return;
    }
    student *temp = start;
    cout<<"\n List Forward\n";
    while(temp != NULL){
        cout<<"Name: "<<temp->name<<" Age: "<<temp->age<<"->";
        temp = temp->next;
    }
    cout<<"NULL";
}

void display_backward(){
   if(start == NULL){
        cout<<"The list is empty\n";
        return;
    }
    student *temp = start;
    while(temp->next != NULL){
        temp = temp->next;
    }
    cout<<"\n List Backward\n";
    while(temp != NULL){
        cout<< temp->name <<":"<<temp->age<<" -> ";
        temp = temp->prev;
    }
    cout<<"NULL"<<endl;
}

void del_beg(){
    if(start == NULL){
        cout<<"Can't delete: list is empty\n";
        return;
    }
    student *temp = start;
    if(temp->next == NULL){      // handle if the list has only 1 node
        delete temp;
        start = NULL;
        cout<<"\nnode Deleted from the begining";
        return;
    }else{
        start = start->next;
        start->prev = NULL;
    }
    delete temp;
    cout<<"Node deleted from beginning\n";
}


void del_end(){
    if(start == NULL){
        cout<<"Can't delete: list is empty\n";
        return;
    }
    
    if(start->next == NULL){  // handle if the list has only 1 node
        delete start;
        start = NULL;
        cout<<"\nnode Deleted from the end";
        return;
    } 
    student *temp = start;
    while(temp->next != NULL){
        temp= temp->next;
    }
    student *prevnode = temp->prev;
    prevnode->next = NULL;
    delete temp;
    cout<<"The node deleted successfully.";  
}

void del_after_pos(int c){
    if(start == NULL){
        cout<<"The list is empty\n";
        return;
    }
    if(c<= 0){
        cout<<"Invalid position";
        return;
    }
    if(c == 1){ 
        del_beg();
        return;
    }
    student *temp = start;
    for(int i = 1; i< c-1; i++){
        temp = temp->next;
    } 
    student *q = temp->next;
    temp->next = q -> next;
    temp->next->prev = temp;
    delete q;
    cout<<"The node at position  "<< c << "deleted successfully";
}

int main(){
    int choice, pos;
    student *p;
    do{
        cout<<"\n---MENU ---\n";
        cout<<"1. Insert at beginning\t"<<"6. Delete at position\n";
        cout<<"2. Insert at end\t"<<"7. Display forward\n";
        cout<<"3. Insert at position\t"<<"8. Display backward\n";
        cout<<"4. Delete first node\t"<<"0. Exit\n";
        cout<<"5. Delete last node\n";
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
                insert_after(p, pos);
                break;
            case 4:
                del_beg();
                break;
            case 5:
                del_end();
                break;
            case 6:
                cout<<"Enter position to delete: ";
                cin>>pos;
                del_after_pos(pos);
                break;
            case 7:
                display_forward();
                break;
            case 8:
                display_backward();
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

