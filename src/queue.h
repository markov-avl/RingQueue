#ifndef RINGQUEUE_QUEUE_H
#define RINGQUEUE_QUEUE_H
#include <iostream>


class Queue {
private:
    static const unsigned int defaultSize = 51;
    unsigned int size;
    unsigned int head{};
    unsigned int tale{};
    int* vector;
public:
    const int SUCCESS = 0;     // функция выполнена успешно
    const int OVERFLOWED = -1; // добавление невозможно, т.к. весь вектор заполнен
    const int EMPTY = -2;      // удаление невозможно, т.к. вектор пуст

    explicit Queue(unsigned int);
    Queue(const Queue &queue);
    ~Queue();
    int add(int);
    int remove();
    void clear();
    [[nodiscard]] unsigned int getLength() const;
    friend std::ostream& operator<<(std::ostream&, const Queue&);
    Queue& operator=(const Queue&);
};


#endif
