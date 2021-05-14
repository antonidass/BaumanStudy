#ifndef LIST_LIB_EXCEPTIONS_H
#define LIST_LIB_EXCEPTIONS_H

#include <exception>
#include "chrono"
#include "ctime"
#include <string>

class baseException : public exception {
public:
    baseException(const string &funcName, string time, const string &errorType) {
        errorMsg = errorType + "\nError in \"" + funcName + "\" method\n\n" + "Error time = " + time;
    }

    virtual const char *what() const noexcept {
        return errorMsg.c_str();
    }

protected:
    string errorMsg;
};


class memoryException : public baseException {
public:
    memoryException(const string &funcName, string time) : baseException(funcName,time, "\nError while allocating memory! ") {}
};


class emptyListException : public baseException {
public:
    emptyListException(const string &funcName, string time) : baseException(funcName, time, "\nCan not delete elem from empty list!") {}
};


class iteratorException : public baseException {
public:
    iteratorException(const string &funcName, string time) : baseException(funcName, time, "\nNot valid iterator! ") {}
};


class pointerException : public baseException {
public:
    pointerException(const string &funcName, string time) : baseException(funcName, time, "\nNot valid pointer! ") {}
};


class sizeException: public baseException {
public:
    sizeException(const string &funcName, string time) : baseException(funcName, time, "\nNot valid size of list! ") {}
};

#endif //LIST_LIB_EXCEPTIONS_H
