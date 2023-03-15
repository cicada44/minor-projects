#include <gtest/gtest.h>

#include <libbook/Book.hpp>
#include <libstore/BookStore.hpp>

#include <optional>

#include <iostream>

TEST(BookStore, Accessors)
{
    BookStore bs(
            {Book{"1-1-1", "A", 10, 20},
             Book{"1-1-2", "B", 11, 30},
             Book{"1-1-3", "C", 12, 40},
             Book{"1-1-4", "D", 13, 50},
             Book{"1-1-5", "E", 14, 60},
             Book{"1-1-1", "F", 15, 70},
             Book{"1-2-1", "G", 16, 80},
             Book{"1-3-1", "A", 17, 90},
             Book{"2-1-1", "B", 18, 100},
             Book{"3-1-1", "C", 19, 110},
             Book{"4-1-1", "D", 20, 120},
             Book{"5-5-5", "A", 21, 130}});

    // get_revenue
    {
        ASSERT_EQ(bs.get_revenue(), (171));
    }

    // avg_price
    {
        ASSERT_LE(bs.avg_price(), 15.5455);
    }

    // most_frequent_author
    {
        ASSERT_EQ(bs.most_frequent_author(), "A");
    }

    // max_pages & max_pages_book
    {
        ASSERT_EQ(bs.max_pages(), 130);
        ASSERT_EQ(bs.max_pages_book().get_isbn(), "5-5-5");
    }

    // []
    {
        ASSERT_EQ(bs[0].get_isbn(), "1-1-1");
        ASSERT_EQ(bs[5].get_isbn(), "1-2-1");
        ASSERT_EQ(bs[10].get_isbn(), "5-5-5");
    }
}

TEST(BookStore, Finders)
{
    BookStore bs(
            {Book{"1-1-1", "A", 10, 20},
             Book{"1-1-2", "B", 11, 30},
             Book{"1-1-3", "C", 12, 40},
             Book{"1-1-4", "D", 13, 50},
             Book{"1-1-5", "E", 14, 60},
             Book{"1-1-1", "F", 15, 70},
             Book{"1-2-1", "G", 16, 80},
             Book{"1-3-1", "A", 17, 90},
             Book{"2-1-1", "B", 18, 100},
             Book{"3-1-1", "C", 19, 110},
             Book{"4-1-1", "D", 20, 120},
             Book{"5-5-5", "A", 21, 130}});

    // contains
    {
        ASSERT_EQ(bs.contains("3-1-1"), true);
        ASSERT_EQ(bs.contains("1-1-1"), true);
        ASSERT_EQ(bs.contains("4-1-1"), true);

        ASSERT_EQ(bs.contains("9-1-1"), false);
        ASSERT_EQ(bs.contains("9-1-1"), false);
        ASSERT_EQ(bs.contains("9-1-1"), false);
    }

    // find_book
    {
        ASSERT_EQ(bs.find_book("1-1-1").value().get_author(), "A");
        ASSERT_EQ(bs.find_book("1-1-2").value().get_author(), "B");
        ASSERT_EQ(bs.find_book("1-1-3").value().get_author(), "C");
        ASSERT_EQ(bs.find_book("1-2-1").value().get_author(), "G");

        ASSERT_THROW(bs.find_book("1").value(), std::bad_optional_access);
        ASSERT_THROW(bs.find_book("2").value(), std::bad_optional_access);
        ASSERT_THROW(bs.find_book("3").value(), std::bad_optional_access);
    }
}

TEST(BookStore, Modifiers)
{
    BookStore bs(
            {Book{"1-1-1", "A", 10, 20},
             Book{"1-1-2", "B", 11, 30},
             Book{"1-1-3", "C", 12, 40},
             Book{"1-1-4", "D", 13, 50},
             Book{"1-1-5", "E", 14, 60},
             Book{"1-1-1", "F", 15, 70},
             Book{"1-2-1", "G", 16, 80},
             Book{"1-3-1", "A", 17, 90},
             Book{"2-1-1", "B", 18, 100},
             Book{"3-1-1", "C", 19, 110},
             Book{"4-1-1", "D", 20, 120},
             Book{"5-5-5", "A", 21, 130}});

    // Add book
    {
        // bs.add_book(Book{"5-5-5", "A", 21, 130});
        // bs.add_book(Book{"6-6-6", "A", 21, 130});
    }
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
