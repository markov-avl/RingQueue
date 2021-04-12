#include "queue.h"

/*
 * При чрезмерном добавлении (метод add) возникает ошибка AddException
 * При удалении (метод pop) в пустой очереди возникает ошибка PopException
 */

// Чтобы вывести структуру очереди, можно воспользоваться методом printVector

int main() {
    // пример теста
    auto queue = Queue(5);
    queue.printVector();
    queue.add(10);
    queue.add(20);
    queue.printVector();
    queue.pop();
    queue.printVector();
    return 0;
}
