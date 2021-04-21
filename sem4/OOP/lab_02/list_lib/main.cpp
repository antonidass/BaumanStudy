#include <iostream>
#include "list.h"
#include <vector>


void print_list(const List<int> &list) {
    cout << "list: " << list << endl;
}


void testConstructor() {
    cout << "empty constructor test: ";
    List<int> list1;

    cout << "\narray constructor test: ";
    int arr[] = { 1, 2, 3, 4, 5 };
    List<int> list3(arr, 5);
    print_list(list3);

    cout << "wrapped constructor test: ";
    List<int> list4(list3);
    print_list(list4);

    cout << "wrapped constructor test2: ";
    List<int> list4_2(list3);
    print_list(list4_2);

    cout << "initializer list constructor test : ";
    List<int> list5 = { 5, 4, 3, 123, 43, 65, 33, 2, 1 };
    print_list(list5);

    cout << "iterators constructor test: ";
    vector<int> vec = { 1, 2, 32, 121, 3, 4 };

    List<int> list6(vec.begin(), --vec.end());
    print_list(list6);
    cout << endl;
}


void testBase() {
    List<int> list = { 7, 7, 7 };
    print_list(list);
    cout << "is empty test : " << list.isEmpty() << endl;

    List<int> list1 = {1, 1};
    cout << "test swap : " << endl;
    list.swap(list1);
    print_list(list);
    print_list(list1);

    cout << "\nclear method: ";
    list.clear();
    cout << "is empty test : " << list.isEmpty() << endl;

    cout << "remove test : ";
    list1.remove(7);
    print_list(list1);
}

void testPush() {
    List<int> list = { 7, 7, 7 };
    cout << "pushFront basic number: ";
    list.pushFront(6);
    print_list(list);

    List<int> list2 = {};
    cout << "pushFront in empty list: ";
    list2.pushFront(0);
    print_list(list2);

    cout << "pushBack basic number ";
    list.pushBack(6);
    print_list(list);

    cout << "pushBack in empty list: ";
    list2.clear();
    list2.pushFront(0);
    print_list(list2);

    cout << "pushBack for list: ";
    list2.pushBack(list);
    print_list(list2);

    cout << "pushFront for list: ";
    list2.pushFront(list);
    print_list(list2);
    cout << endl;
}


void testPop() {
    List<int> list = { 7, 7, 7 };
    cout << "popBack basic number: ";
    list.popBack();
    print_list(list);

    List<int> list2 = {};
    cout << "popBack empty list: ";

    try {
        list2.popBack();
    } catch (emptyListException &error) {
        cout << error.what();
    }

    cout << "popFront basic number: ";
    list.popBack();
    print_list(list);

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

    cout << "\ninsert in begin: ";
    ListIterator<int> it = list.begin();
    list.insert(it, 5);
    print_list(list);

    cout << "\ninsert another list : ";
    it = list.begin() + 2;
    list.insert(it, list3);
    print_list(list);
    cout << endl;
}

void testReverse() {
    List<int> list = {1, 2, 3 };
    cout << "\nreverse test: ";
    list.reverse();
    print_list(list);

    List<int> list2 = {1};
    cout << "\nreverse test one elem: ";
    list2.reverse();
    print_list(list2);
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

    cout << "\ntest = operator: ";
    list = list2;
    print_list(list);

    cout << "\ntest += operator: ";
    list += list2;
    list += 25;
    print_list(list);
}


void testIterators() {
    List<int> list = { 1, 2, 3 };
    List<int> list2 = { 1, 2, 3 };

    cout << "\ntest iterators: ";
    auto it1 = list.begin();
    *it1 = 333;
    *(++it1 + 1) = 111;
    print_list(list);

    cout << "\ntest constant iterators: ";
    auto it2 = list.cbegin();
//     *it2 = 111; не работает - это правильно
    ++it2++;

    cout << *it2 << endl;
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

    if (list.end()) {
        cout << "test2 not ok";
    }
    else {
        cout << "test2 ok";
    }

    cout << "\nbool operators test (constant): ";
    if (list.cbegin()) {
        cout << "test1 ok ";
    } else {
        cout << "test1 not ok ";
    }

    if (list.cend()) {
        cout << "test2 not ok";
    } else {
        cout << "test2 ok";
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
