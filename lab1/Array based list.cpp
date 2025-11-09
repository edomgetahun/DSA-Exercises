//Simple array-based list supporting insert, append, remove, and traverse operations.
#include <iostream>
using namespace std;
const int DefaultListSize = 100;

class AList {
private:
    int* listArray;   
    int maxSize;      
    int listSize;     
    int curr;         

public:
    AList(int size = DefaultListSize) {
        if (size <= 0) size = DefaultListSize;
        maxSize = size;
        listSize = curr = 0;
        listArray = new int[maxSize];
    }

    ~AList() {
        delete[] listArray;
    }

    void clear() {
        delete[] listArray;
        listSize = curr = 0;
        listArray = new int[maxSize];
    }

    void setStart() { 
        curr = 0; 
    }

    void setEnd() { curr = listSize; }
    
    void prev() { 
        if (curr > 0) curr--; 
    }

    void next() { 
        if (curr < listSize) curr++; 
    }

    int length() const { 
        return listSize;
     }

    bool setPos(int pos) {
        if (pos >= 0 && pos <= listSize) {
            curr = pos;
            return true;
        }
        return false;
    }

    bool getValue(int &outValue) const {
        if (listSize == 0) return false;
        if (curr < 0 || curr >= listSize) {
            return false;
        }
        outValue = listArray[curr];
        return true;
    }

    // Insert item at current position
    bool insert(int item) {
        if (listSize >= maxSize) return false; 
        for (int i = listSize; i > curr; --i)
            listArray[i] = listArray[i - 1];
        listArray[curr] = item;
        listSize++;
        return true;
    }

    // Append item to the end
    bool append(int item) {
        if (listSize >= maxSize) {
            return false;
        }
        listArray[listSize++] = item;
        return true;
    }

    // Remove current element and return it via reference
     bool remove(int &outValue) {
        if (listSize == 0) {
            return false;
        }
        if (curr < 0 || curr >= listSize) {
            return false;
        }

        outValue = listArray[curr];

        for (int i = curr; i < listSize - 1; ++i) {
            listArray[i] = listArray[i + 1];    // shift elements down
        }
        listSize--;
        if (curr > listSize) {   //If curr goes beyond the last element, move it to the end position
            curr = listSize;
        }
        return true;
    }

    // Return the current position index
    int currPos() const {
        return curr;
    }

    // Print list contents and show current position
    void printList() const {
        cout << "[";
        for (int i = 0; i < listSize; ++i) {
            if (i == curr) {
                cout << "| "; // Show or mark the current position before this element
            }

            cout << listArray[i];

            if (i != listSize - 1) {
                cout << ", ";
            }

            if (i == curr) {
                cout << " ";
            }
        }

        if (curr == listSize) {
            cout << " |"; 
        }

        cout << "] (size=" << listSize << ", curr=" << curr << ")\n";
    }
};


int main() {
    AList myList(10); 
    myList.append(10);
    myList.append(20);
    myList.append(30);
    cout << "After appends: ";
    myList.printList(); 

    myList.setPos(1);
    myList.insert(15); 
    cout << "After insert 15 at pos 1: ";
    myList.printList(); 

    int val;
    if (myList.getValue(val)) {
        cout << "Current value at pos " << myList.currPos() << " = " << val << "\n";
    }

    
    if (myList.remove(val)) {
        cout << "Removed value = " << val << "\n";
    }
    cout << "After remove: ";
    myList.printList();

    myList.setEnd();
    myList.append(40);
    cout << "After append 40 at end: ";
    myList.printList();

    cout << "Traverse: ";
    for (myList.setStart(); myList.currPos() < myList.length(); myList.next()) {
        int x;
        if (myList.getValue(x)) {
            cout << x << " ";
        }
    }
    cout << "\n";

    return 0;
}
