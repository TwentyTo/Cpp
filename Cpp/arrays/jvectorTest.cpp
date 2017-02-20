#include "assert.h"
#include "iostream"

#include "jvectorTest.hpp"
#include "jvector.hpp"
namespace arrays
{
void JVectorTest::RunTests() const {
  TestSize();
  TestIsEmpty();
  TestCapacity();
  TestGetValueAt();
  TestPop();
  TestInsert();
  TestDelete();
  TestRemove();
  TestFind();
  TestTypes();
  std::cout << "All tests passed" << std::endl;
};

void JVectorTest::TestSize() const
{
  arrays::JVector<int> tester;
  assert(tester.Size() == 0);

  int items_to_add = 5;
  for (int i = 0; i < items_to_add; ++i)
  {
        tester.push_back(i + 1);
  }
  assert(tester.Size() == items_to_add);
  std::cout<< "TestSize passed" << std::endl;
}

void JVectorTest::TestIsEmpty() const
{
  arrays::JVector<int> tester;
  assert(tester.IsEmpty());
  std::cout<< "TestIsEmpty passed" << std::endl;
}

void JVectorTest::TestCapacity() const
{
  arrays::JVector<int> tester;

  // test increasing size
  assert(tester.capacity() == arrays::kMinCapacity);
  for (int i = 0; i < 17; ++i) {
    tester.push_back(i + 1);
  }
  assert(tester.capacity() == arrays::kMinCapacity * 2);
  for (int j = 0; j < 20; ++j) {
    tester.push_back(j + 1);
  }
  assert(tester.capacity() == arrays::kMinCapacity * 4);

  // test decreasing size
  for (int k = 0; k < 30; ++k) {
    tester.pop();
  }
  assert(tester.capacity() == arrays::kMinCapacity * 2);

  for (int k = 0; k < 7; ++k) {
    tester.pop();
  }
  assert(tester.capacity() == arrays::kMinCapacity);
  std::cout<< "TestCapacity passed" << std::endl;
}

void JVectorTest::TestGetValueAt() const
{
  arrays::JVector<int> tester;
  tester.push_back(4);
  tester.push_back(9);
  tester.push_back(12);
  assert(tester[0] == 4);
  assert(tester[1] == 9);
  assert(tester[2] == 12);
  std::cout<< "TestGetValueAt passed" << std::endl;
}

void JVectorTest::TestPop() const
{
  arrays::JVector<int> tester;
  tester.push_back(3);

  int popped = tester.pop();
  assert(popped == 3);
  tester.push_back(9);
  tester.push_back(8);

  assert(tester.Size() == 2);
  int popped2 = tester.pop();
  assert(popped2 == 8);
  assert(tester.Size() == 1);
  std::cout<< "TestPop passed" << std::endl;
}

void JVectorTest::TestInsert() const
{
  arrays::JVector<int> tester;
  tester.push_back(5);
  tester.push_back(7);
  tester.push_back(9);
  tester.insert(0, 4);
  assert(tester[0] == 4);
  assert(tester[1] == 5);
  assert(tester[2] == 7);
  assert(tester[3] == 9);
  tester.insert(3, 8);
  assert(tester[3] == 8);
  assert(tester[4] == 9);
  std::cout<< "TestInsert passed" << std::endl;
}

void JVectorTest::TestPrepend() const
{
  arrays::JVector<int> tester;
  tester.push_back(9);
  tester.push_back(8);
  tester.push_back(7);
  tester.prepend(6);
  assert(tester.Size() == 4);
  assert(tester[0] == 6);
  assert(tester[1] == 9);
  assert(tester[3] == 7);
  std::cout << "TestPrepend passed" << std::endl;
}

void JVectorTest::TestDelete() const
{
  arrays::JVector<int> tester;
  tester.push_back(5);
  tester.Delete(0);
  assert(tester.Size() == 0);

  tester.push_back(9);
  tester.push_back(10);
  tester.push_back(11);
  tester.Delete(1);
  assert(tester.Size() == 2);
  assert(tester[0] == 9);
  assert(tester[1] == 11);
  std::cout << "TestDelete passed" << std::endl;
}

void JVectorTest::TestRemove() const
{
  arrays::JVector<int> tester;
  tester.push_back(50);
  tester.push_back(2);
  tester.push_back(50);
  tester.push_back(4);
  tester.push_back(50);
  assert(tester.Size() == 5);
  tester.remove(50);
  assert(tester.Size() == 2);
  assert(tester[0] == 2);
  assert(tester[1] == 4);
  std::cout << "TestRemove passed" << std::endl;
}

void JVectorTest::TestFind() const
{
  arrays::JVector<int> tester;
  tester.push_back(4);
  tester.push_back(7);
  tester.push_back(11);
  assert(tester.find(5) == -1);
  assert(tester.find(4) == 0);
  assert(tester.find(7) == 1);
  assert(tester.find(11) == 2);
  std::cout << "TestFind passed" << std::endl;
}
void JVectorTest::TestTypes() const
{
   arrays::JVector<double> tester;
   tester.push_back(4.31);
   assert(tester[0] == 4.31);
   std::cout << "TestTypes passed" << std::endl;
}
}  
