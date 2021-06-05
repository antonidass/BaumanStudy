#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include "string"
#include "exception"

class BaseException : public std::exception{
public:
    explicit BaseException(std::string &msg) : _msg(msg) { }

    const char *what() const noexcept override {
        return "Error";
    }

    const std::string &getInformation() const noexcept {
        return _msg;
    }

protected:
    std::string _msg;
};

class CamException : public BaseException {
public:
    explicit CamException(std::string &msg) : BaseException(msg) { }

    const char *what() const noexcept override {
        return "Doesn't added camera";
    }
};

class SourceException : public BaseException {
public:
    explicit SourceException(std::string &msg) : BaseException(msg) { }
    const char *what() const noexcept override {
        return "Error in load source";
    }
};

class FigureException : public BaseException {
public:
    explicit FigureException(std::string &msg) : BaseException(msg) { }
    const char *what() const noexcept override {
        return "Error while building model";
    }
};

#endif
