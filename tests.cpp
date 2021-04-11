// tests framework: https://github.com/google/googletest
#include <iostream>
#include "gtest/gtest.h"
#include "queue.h"


TEST(QueueAdd, FullQueueRingAdding) {
    // делаем круги в полных очередях, пока не сделаем полный круг
    for (unsigned int size = 1; size <= 10; ++size) {
        auto queue = Queue(size);

        // заполняем очередь полностью
        for (int i = 0; i < size; ++i) {
            queue.add(i + 1);
            EXPECT_EQ(queue.getVector()[i], i + 1);
        }
        // проверяем, что действительно добавлено size элементов
        EXPECT_EQ(queue.getLength(), size);

        // делаем 1 полный круг с заполенной полностью очередью и проверяем каждый элемент очереди
        unsigned int index = 1;
        auto value = int(size);
        for (int i = 0; i < size + 2; ++i) {
            queue.pop();
            queue.add(++value);
            for (unsigned int j = index, k = 0; k < size; ++j, ++k) {
                EXPECT_EQ(queue.getVector()[j % (size + 1)], value - size + k + 1);
            }
            EXPECT_EQ(queue.getLength(), size);
            index = (index + 1) % (size + 1);
        }
    }
}

TEST(QueueAdd, HalfQueueRingAdding) {
    // делаем круги в заполненных наполовину очередях, пока не сделаем полный круг
    // (для 1 не работает, т.к. очередь сначала ничем не заполняется, а затем происходит вызов метода pop)
    for (unsigned int size = 2; size <= 10; ++size) {
        auto queue = Queue(size);
        auto halfSize = size / 2;

        // заполняем очередь наполовину
        for (int i = 0; i < halfSize; ++i) {
            queue.add(i + 1);
            EXPECT_EQ(queue.getVector()[i], i + 1);
        }
        // проверяем, что действительно добавлено halfSize элементов
        EXPECT_EQ(queue.getLength(), halfSize);

        // делаем 1 полный круг с заполенной наполовину очередью и проверяем каждый элемент очереди
        unsigned int index = 1;
        auto value = int(halfSize);
        for (int i = 0; i < size + 2; ++i) {
            queue.pop();
            queue.add(++value);
            for (unsigned int j = index, k = 0; k < halfSize; ++j, ++k) {
                EXPECT_EQ(queue.getVector()[j % (size + 1)], value - halfSize + k + 1);
            }
            EXPECT_EQ(queue.getLength(), halfSize);
            index = (index + 1) % (size + 1);
        }
    }
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}