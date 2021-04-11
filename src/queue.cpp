#include "queue.h"


Queue::Queue(unsigned int size) {
    this->size = size > 0 ? size + 1 : defaultSize; // TODO: проверить, что будет, если size = 1?
    this->vector = new int[this->size];
    this->clear();
}

Queue::Queue(const Queue &queue) {
    this->size = queue.size;
    this->vector = new int[this->size];
    this->head = queue.head;
    this->tale = queue.tale;
    for (unsigned int i = queue.head; i % queue.size != (queue.tale + 1) % queue.size; ++i) {
        this->vector[i % queue.size] = queue.vector[i % queue.size];
    }
}

Queue::~Queue() {
    delete[] vector;
}

int Queue::add(int value) {
    if (head == (tale + 2) % size) {
        return OVERFLOWED;
    }
    tale = (tale + 1) % size;
    vector[tale] = value;
    return SUCCESS;
}

int Queue::remove() {
    if (getLength() == 0) {
        return EMPTY;
    }
    head = (head + 1) % size;
    return SUCCESS;
}

void Queue::clear() {
    this->head = 0;
    this->tale = this->size - 1;
}

unsigned int Queue::getLength() const {
    return (size - head + tale + 1) % size;
}

std::ostream &operator<<(std::ostream &out, const Queue &queue) {
    if (queue.getLength() == 0) {
        out << "Empty queue";
    } else {
        out << queue.vector[queue.head];
        for (unsigned int i = queue.head + 1; i % queue.size != (queue.tale + 1) % queue.size; ++i) {
            out << ", " << queue.vector[i % queue.size];
        }
    }
    return out;
}

// TODO: что будет, если присвоить пустую очередь?
Queue &Queue::operator=(const Queue &queue) {
    this->head = 0;
    if (queue.getLength() == 0) {
        this->tale = this->size - 1;
    } else if (this->size > queue.getLength()) {
        this->tale = queue.getLength() - 1;
        for (unsigned int i = queue.head, j = 0; i % queue.size != (queue.tale + 1) % queue.size; ++i, ++j) {
            this->vector[j] = queue.vector[i % queue.size];
        }
    } else {
        this->tale = this->size - 2;
        for (unsigned int i = queue.head, j = 0; j <= this->tale; ++i, ++j) {
            this->vector[j] = queue.vector[i % queue.size];
        }
    }
    return *this;
}


