#ifndef LIST_LIB_EXCEPTIONS_H
#define LIST_LIB_EXCEPTIONS_H

#include <exception>

class baseException : public exception {
public:
    baseException(const string &funcName, const string &errorType) {
        errorMsg = errorType + "\nError in \"" + funcName + "\" method\n\n";
    }

    virtual const char *what() const noexcept {
        return errorMsg.c_str();
    }

protected:
    string errorMsg;
};


class memoryException : public baseException {
public:
    memoryException(const string &funcName) : baseException(funcName, "\nError while allocating memory! ") {}
};


class emptyListException : public baseException {
public:
    emptyListException(const string &funcName) : baseException(funcName, "\nCan not delete elem from empty list!") {}
};


class iteratorException : public baseException {
public:
    iteratorException(const string &funcName) : baseException(funcName, "\nNot valid iterator! ") {}
};


class pointerException : public baseException {
public:
    pointerException(const string &funcName) : baseException(funcName, "\nNot valid pointer! ") {}
};


class sizeException: public baseException {
public:
    sizeException(const string &funcName) : baseException(funcName, "\nNot valid size of list! ") {}
};

#endif //LIST_LIB_EXCEPTIONS_H
