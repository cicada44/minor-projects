#include <gtest/gtest.h>
#include "../../src/include/smart_pointers.hpp"

TEST(UniquePtr, RO5) {
    int default_int = 5;

    // Default constructor
    {
        smart_pointers::unique_ptr<int> intptr;
        smart_pointers::unique_ptr<int> intptr2 =
            smart_pointers::make_unique<int>(default_int);

        ASSERT_FALSE(intptr.get());
        ASSERT_TRUE(intptr2.get());
    }

    // Moving
    {
        int* ptr = new int(42);
        smart_pointers::unique_ptr<int> intptr(ptr);

        smart_pointers::unique_ptr<int> movedPtr(std::move(intptr));

        ASSERT_FALSE(intptr.get());
        ASSERT_TRUE(movedPtr.get());
        ASSERT_EQ(*(movedPtr.get()), 42);

        int* ptr1 = new int(10);
        smart_pointers::unique_ptr<int> intptr1(ptr1);

        int* ptr2 = new int(20);
        smart_pointers::unique_ptr<int> intptr2(ptr2);

        intptr1 = std::move(intptr2);

        ASSERT_FALSE(intptr2.get());

        ASSERT_TRUE(intptr1.get());
        ASSERT_EQ(*(intptr1.get()), 20);
    }
}

TEST(UniquePtr, Reset) {
    int* ptr = new int(5);
    smart_pointers::unique_ptr<int> intptr(ptr);

    intptr.reset();

    ASSERT_FALSE(intptr.get());
}

TEST(UniquePtr, Release) {
    int* ptr = new int(42);
    smart_pointers::unique_ptr<int> intptr(ptr);

    int* releasedPtr = intptr.release();

    ASSERT_FALSE(intptr.get());
    ASSERT_TRUE(releasedPtr);
    ASSERT_EQ(*releasedPtr, 42);

    delete releasedPtr;
}

TEST(UniquePtr, ArrowOperator) {
    struct MyStruct {
        int value;
        void setValue(int val) { value = val; }
    };

    smart_pointers::unique_ptr<MyStruct> ptr =
        smart_pointers::make_unique<MyStruct>();

    ptr->setValue(42);

    ASSERT_EQ(ptr->value, 42);
}

TEST(SharedPtr, Constructors) {
    // Default constructor
    {
        smart_pointers::shared_ptr<int> intptr;
        ASSERT_FALSE(intptr.get());
    }

    // Constructor with raw pointer
    {
        int* rawPtr = new int(42);
        smart_pointers::shared_ptr<int> intptr(rawPtr);

        ASSERT_TRUE(intptr.get());
        ASSERT_EQ(*(intptr.get()), 42);
        ASSERT_EQ(intptr.use_count(), 1);
        ASSERT_TRUE(intptr.unique());
    }

    // Copy constructor
    {
        int* rawPtr = new int(42);
        smart_pointers::shared_ptr<int> intptr(rawPtr);
        smart_pointers::shared_ptr<int> copyPtr(intptr);

        ASSERT_EQ(intptr.get(), copyPtr.get());
        ASSERT_EQ(intptr.use_count(), 2);
        ASSERT_FALSE(intptr.unique());
        ASSERT_FALSE(copyPtr.unique());
    }

    // Move constructor
    {
        int* rawPtr = new int(42);
        smart_pointers::shared_ptr<int> intptr(rawPtr);
        smart_pointers::shared_ptr<int> movedPtr(std::move(intptr));

        ASSERT_FALSE(intptr.get());
        ASSERT_TRUE(movedPtr.get());
        ASSERT_EQ(*(movedPtr.get()), 42);
        ASSERT_EQ(movedPtr.use_count(), 1);
        ASSERT_TRUE(movedPtr.unique());
    }
}

TEST(SharedPtr, AssignmentOperators) {
    // Copy assignment operator
    {
        int* rawPtr = new int(42);
        smart_pointers::shared_ptr<int> intptr(rawPtr);
        smart_pointers::shared_ptr<int> copyPtr;
        copyPtr = intptr;

        ASSERT_EQ(intptr.get(), copyPtr.get());
        ASSERT_EQ(intptr.use_count(), 2);
        ASSERT_FALSE(intptr.unique());
        ASSERT_FALSE(copyPtr.unique());
    }

    // Move assignment operator
    {
        int* rawPtr1 = new int(42);
        smart_pointers::shared_ptr<int> intptr1(rawPtr1);

        int* rawPtr2 = new int(10);
        smart_pointers::shared_ptr<int> intptr2(rawPtr2);
        intptr1 = std::move(intptr2);

        ASSERT_FALSE(intptr2.get());
        ASSERT_TRUE(intptr1.get());
        ASSERT_EQ(*(intptr1.get()), 10);
        ASSERT_EQ(intptr1.use_count(), 1);
        ASSERT_TRUE(intptr1.unique());
    }
}

TEST(SharedPtr, Reset) {
    int* rawPtr = new int(42);
    smart_pointers::shared_ptr<int> intptr(rawPtr);

    intptr.reset();

    ASSERT_TRUE(intptr.get() == nullptr);
    ASSERT_FALSE(intptr.unique());
    ASSERT_EQ(intptr.use_count(), 0);
}

TEST(SharedPtr, ArrowOperator) {
    struct MyStruct {
        int value;
        void setValue(int val) { value = val; }
    };

    smart_pointers::shared_ptr<MyStruct> ptr =
        smart_pointers::make_shared<MyStruct>();

    ptr->setValue(42);

    ASSERT_EQ(ptr->value, 42);
}

TEST(SharedPtr, UseCount) {
    int* rawPtr = new int(42);
    smart_pointers::shared_ptr<int> intptr1(rawPtr);
    smart_pointers::shared_ptr<int> intptr2(intptr1);

    ASSERT_EQ(intptr1.use_count(), 2);
    ASSERT_EQ(intptr2.use_count(), 2);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
