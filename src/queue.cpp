#include "queue.h"


AddException::AddException(std::string error) {
    this->error = std::move(error);
}

const char* AddException::what() const noexcept {
    return this->error.c_str();
}


PopException::PopException(std::string error) {
    this->error = std::move(error);
}

const char* PopException::what() const noexcept {
    return this->error.c_str();
}


Queue::Queue(unsigned int size) {
    this->size = size > 0 ? size + 1 : defaultSize; // TODO: проверить, что будет, если size = 1?
    this->vector = new int[this->size]{};
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

void Queue::add(int value) {
    if (head == (tale + 2) % size) {
        throw AddException("Queue overflowed");
    }
    tale = (tale + 1) % size;
    vector[tale] = value;
}

int Queue::pop() {
    if (getLength() == 0) {
        throw PopException("Queue is empty");
    }
    unsigned int nowHead = head;
    head = (head + 1) % size;
    return vector[nowHead];
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

void Queue::printVector() {
    for (unsigned int i = 0; i < size; ++i) {
        if (i == tale && i == head) {
            std::cout << "talehead" << "\t";
        } else if (i == tale) {
            std::cout << "tale" << "\t\t";
        } else if (i == head) {
            std::cout << "head" << "\t\t";
        } else {
            if (i == size - 1) {
                std::cout << "extra" << "\t\t";
            } else {
                std::cout << i << "\t\t\t";
            }
        }
    }
    std::cout << std::endl;
    for (unsigned int i = 0; i < size; ++i) {
        std::cout << vector[i] << "\t\t\t";
    }
    std::cout << std::endl;
    std::cout << "Length: " << getLength() << std::endl << std::endl;
}

int *Queue::getVector() {
    return vector;
}