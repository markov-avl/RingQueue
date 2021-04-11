// tests framework: https://github.com/google/googletest
#include <iostream>
#include "gtest/gtest.h"
#include "queue.h"


TEST(QueueAdd, FullRingAdding) {
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

        // делаем 1 полный круг с заполенной полностью очередью
        auto index = size;
        for (int i = 0; i < size + 2; ++i) {
            queue.pop();
            queue.add(int(index + 1));
            EXPECT_EQ(queue.getVector()[index % (size + 1)], int(index + 1));
            EXPECT_EQ(queue.getLength(), size);
            ++index;
        }
    }
}

TEST(QueueAdd, HalfRingAdding) {
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

        // делаем 1 полный круг с заполенной наполовину очередью
        auto index = halfSize;
        for (int i = 0; i < size + 2; ++i) {
            queue.pop();
            queue.add(int(index + 1));
            EXPECT_EQ(queue.getVector()[index % (size + 1)], int(index + 1));
            EXPECT_EQ(queue.getLength(), halfSize);
            ++index;
        }
    }
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}