#ifndef RINGQUEUE_QUEUE_H
#define RINGQUEUE_QUEUE_H
#include <iostream>
#include <exception>


class AddException: public std::exception {
private:
    std::string error;
public:
    explicit AddException(std::string error);
    const char* what() const noexcept override;
};

class PopException: public std::exception {
private:
    std::string error;
public:
    explicit PopException(std::string error);
    const char* what() const noexcept override;
};


class Queue {
private:
    static const unsigned int defaultSize = 51;
    unsigned int size;
    unsigned int head{};
    unsigned int tale{};
    int* vector;
public:
    explicit Queue(unsigned int);
    Queue(const Queue &queue);
    ~Queue();
    void add(int);
    int pop();
    void clear();
    [[nodiscard]] unsigned int getLength() const;
    friend std::ostream& operator<<(std::ostream&, const Queue&);
    Queue& operator=(const Queue&);

    // test methods
    void printVector();
    int* getVector();
};


#endif
