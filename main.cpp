#include "queue.h"

int main() {
    auto queue = Queue(5);
    queue.add(5);
    queue.add(8);
    queue.add(3);
    queue.add(3);
    queue.add(3);

    Queue queueCopy = Queue(4);
    queueCopy = queue;
    queueCopy.add(1);
    queueCopy.add(9);
    queueCopy.remove();
    queueCopy.add(564);
    queueCopy.add(324);

    std::cout << queue << std::endl;
    std::cout << queueCopy << std::endl;

    std::cout << queue.getLength() << std::endl;
    std::cout << queueCopy.getLength() << std::endl;

    return 0;
}
