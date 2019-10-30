#include <gtest/gtest.h>

#include "mylibrary/my_class.h"

TEST(AdditionTest, AddTwoNumbers)
{
  // ARRANGE
  MyLibrary::MyClass myClass;
  const int expectedSum = 5;

  // ACT
  const int result = myClass.sum(2,3);

  // ASSERT
  EXPECT_EQ(result, expectedSum);
}