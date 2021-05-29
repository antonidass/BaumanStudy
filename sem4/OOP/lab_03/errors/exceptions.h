#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>
using namespace std;


class baseException : public exception {
public:
    baseException(string &message) {
        errorMsg = message;
    };

    const char *what() const noexcept override {
        return "Error base.";
    }

    const string &get_info() const noexcept {
        return errorMsg;
    }

protected:
    string errorMsg;
};



class cameraException : public baseException {
public:
    cameraException(string &message) : baseException(message) {};

    const char *what() const noexcept override {
        return "Error in camera. Camera doesn't configured.";
    }
};


class fileException : public baseException {
public:
    fileException(string &message) : baseException(message) {};

    const char *what() const noexcept override {
        return "Error in opening file.";
    }
};



class figureException : public baseException {
public:
    figureException(string &message) : baseException(message) {};

    const char *what() const noexcept override {
        return "Error while building figure.";
    }
};


#endif
