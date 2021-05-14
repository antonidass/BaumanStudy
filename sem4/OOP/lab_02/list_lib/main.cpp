#include <iostream>
#include "list.h"
#include <vector>


void printList(List<int> &list) {
    cout << "list: " << list;
}


void testConstructor() {
    cout << "empty constructor test: ";
    List<int> list1;

    cout << "\narray constructor test: ";
    int arr[] = { 1, 2, 3, 4, 5 };
    List<int> list3(arr, 5);
    printList(list3);

    cout << "wrapped constructor test: ";
    List<int> list4(list3);
    printList(list4);

    cout << "wrapped constructor test2: ";
    List<int> list4_2(list3);
    printList(list4_2);

    cout << "initializer list constructor test : ";
    List<int> list5 = { 5, 4, 3, 123, 43, 65, 33, 2, 1 };
    printList(list5);

    cout << "iterators constructor test: ";
    vector<int> vec = { 1, 2, 32, 121, 3, 4 };

    List<int> list6(vec.begin(), vec.end());
    printList(list6);
    cout << endl;
}


void testBase() {
    List<int> list = { 7, 7, 7 };
    printList(list);
    cout << "is empty test : " << list.isEmpty() << endl;

    List<int> list1 = {1, 1};
    cout << "test swap : " << endl;
    list.swap(list1);
    printList(list);
    printList(list1);

    cout << "\nclear method: ";
    list.clear();
    cout << "is empty test : " << list.isEmpty() << endl;

    cout << "remove test : ";
    list1.remove(list1.begin());
    printList(list1);
}

void testPush() {
    List<int> list = { 7, 7, 7 };
    cout << "pushFront basic number: ";
    list.pushFront(6);
    printList(list);

    List<int> list2 = {};
    cout << "pushFront in empty list: ";
    list2.pushFront(0);
    printList(list2);

    cout << "pushBack basic number ";
    list.pushBack(6);
    printList(list);

    cout << "pushBack in empty list: ";
    list2.clear();
    list2.pushFront(0);
    printList(list2);

    cout << "pushBack for list: ";
    list2.pushBack(list);
    printList(list2);

    cout << "pushFront for list: ";
    list2.pushFront(list);
    printList(list2);
    cout << endl;
}


void testPop() {
    List<int> list = { 7, 7, 7 };
    cout << "popBack basic number: ";
    list.popBack();
    printList(list);

    List<int> list2 = {};
    cout << "popBack empty list: ";

    try {
        list2.popBack();
    } catch (emptyListException &error) {
        cout << error.what();
    }

    cout << "popFront basic number: ";
    list.popBack();
    printList(list);

    cout << "popFront empty list: ";
    try {
        list2.popFront();
    } catch (emptyListException &error) {
        cout << error.what();
    }
    cout << endl;
}

void testInsert() {
    List<int> list = { 7, 7, 7 };
    List<int> list3 = {1, 2, 3 };

    cout << "insert in begin: ";
    auto it = list.begin();
    list.insert(it, 5);
    printList(list);

    cout << "insert in center: ";
    it = list.begin() + 2;
    list.insert(it, 5);
    printList(list);

    List<int> list4;
    cout << "insert in empty list: ";
    it = list4.begin();
    list4.insert(it, 5);
    printList(list4);

    cout << "insert end : ";
    it = list4.end();
    list4.insert(it, 3);
    printList(list4);

    cout << "insert another list : ";
    it = list.begin() + 1;
    list.insert(it, list3);
    printList(list);

    cout << "insert another list with iterators : ";
    it = list.begin();
    ListIterator<int> first = list3.begin();
    ListIterator<int> last = first + 2;

    list.insert(it, first, last);
    printList(list);
}

void testReverse() {
    List<int> list = {1, 2, 3};
    cout << "\nreverse test: ";
    list.reverse();
    printList(list);

    List<int> list2 = {1};
    cout << "\nreverse test one elem: ";
    list2.reverse();
    printList(list2);
    cout << endl;
}

void testOperators() {
    List<int> list = { 1, 2, 3 };
    List<int> list2 = { 1, 2, 3 };

    cout << "\ntest == operator: ";
    if (list == list2) {
        cout << "ok";
    } else {
        cout << "not ok!";
    }

    list.popBack();

    std::cout << "\ntest != operator: ";
    if (list != list2) {
        cout << "ok";
    }
    else {
        cout << "not ok!";
    }

    cout << "test = operator: ";
    list = list2;
    printList(list);

    cout << "test += operator: ";
    list += list2;
    list += 25;
    printList(list);

    printList(list2);
    cout << "test + operator: ";
    list2 = list + list2;
    printList(list2);
}


void testIterators() {
    List<int> list = { 1, 2, 3 };
    const List<int> list2 = { 1, 2, 3 };

    cout << "\ntest iterators: ";
    cout << "test * : ";
    ListIterator<int> it1(list.begin());
    *it1 = 333;
    cout  << *it1 << endl;
    printList(list);

    ++it1;
    it1++;
    *it1 = 12;
    cout << "test ++ : ";
    printList(list);

    cout << "test += : ";
    it1 = list.begin();
    it1 += 2;
    *it1 = 1;
    printList(list);

    List<int> list4 = { 1, 2, 3 };
    auto it4 = list4.begin();

    const auto it2 = list2.begin();
    cout << it2.getCur();

    cout << "\ntest constant iterators: ";
    auto it3 = list.cbegin();
//     *it2 = 111; не работает - это правильно

    cout << "test constant ++";
    it3++;
    ++it3;
    cout << *it3;
}


void testBool() {
    List<int> list = { 1, 2, 3 };

    cout << "\nbool operators test";
    if (list.begin()) {
        cout << "test1 ok ";
    }
    else {
        cout << "test1 not ok";
    }


    cout << "\nbool operators test (constant): ";
    if (list.cbegin()) {
        cout << "test1 ok ";
    } else {
        cout << "test1 not ok ";
    }
}

int main() {
    testConstructor();
    testBase();
    testPush();
    testPop();
    testInsert();
    testReverse();
    testOperators();
    testIterators();
    testBool();
}
