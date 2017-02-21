#pragma once

#include <memory>

namespace arrays {

namespace
{
static const int kMinCapacity = 16;
static const int kGrowthFactor = 2;
static const int kShrinkFactor = 4;
}

template <typename T>
class JVector {
public:
   JVector();
   JVector(int capacity);
   const T operator[](int index);
   inline const int Size() const
   {
      return mSize;
   }
   bool const IsEmpty() const
   {
      return mSize == 0;
   }
   inline const int capacity() const
   {
      return mCapacity;
   }
   void push_back(T value);
   T get(int index) const;
   const T pop();
   void insert(int index, T value);
   void prepend(T value);
   void Delete(int index);
   void remove(T value);
   int find(T value) const;
 private:
   int DetermineCapacity(int capacity) const;
   void ResizeForSize(int candidate_size);
   void IncreaseSize();
   void DecreaseSize();

   int mCapacity;
   int mSize;
   std::shared_ptr<T> mData;
};

template <typename T>
JVector<T>::JVector()
   : mCapacity(kMinCapacity)
   , mSize(0)
{
    mData = std::shared_ptr<T>(new T[mCapacity], std::default_delete<T[]>());
}

template <typename T>
JVector<T>::JVector(int capacity) 
   : mSize(0) 
{
   if (capacity < 1)
   {
      std::cerr << "Cannot make vector of that size" << std::endl;
      exit(EXIT_FAILURE);
   }

   int true_capacity = DetermineCapacity(capacity);

   mCapacity = true_capacity;
   mData = std::shared_ptr<T[]>(new T[mCapacity], std::default_delete<T[]>());
}

template <typename T>
const T JVector<T>::operator[](int index)
{
   return get(index);
}

template <typename T>
int JVector<T>::DetermineCapacity(int capacity) const
{
  int true_capacity = kMinCapacity;
  while (capacity > true_capacity / kGrowthFactor) 
  {
    true_capacity *= kGrowthFactor;
  }
  return true_capacity;
}

template <typename T>
void JVector<T>::push_back(T value)
{
   ResizeForSize(mSize + 1);
   mData.get()[mSize] = value;
   ++mSize;
}

template <typename T>
void JVector<T>::ResizeForSize(int candidate_size)
{
   if (mSize < candidate_size)
   {
      if (mSize == mCapacity)
      {
        IncreaseSize();
      }
   }
   else
   { 
      if (mSize > candidate_size)
      {
         if (mSize < mCapacity / kShrinkFactor)
         {
            DecreaseSize();
         }
      }
   }
}

template <typename T>
void JVector<T>::IncreaseSize()
{
   int old_capacity = mCapacity;
   int new_capacity = DetermineCapacity(old_capacity);

   if (old_capacity != new_capacity)
   {
      std::shared_ptr<T> new_data(new T[new_capacity], std::default_delete<T[]>());

      for (int i = 0; i < mSize; ++i)
      {
         new_data.get()[i] = mData.get()[i];
      }

      mData = std::move(new_data);
      mCapacity = new_capacity;
   }
}

template <typename T>
void JVector<T>::DecreaseSize()
{
   int old_capacity = mCapacity;
   int new_capacity = old_capacity / 2;

   if (new_capacity < kMinCapacity)
   {
      new_capacity = kMinCapacity;
   }

   if (new_capacity != old_capacity)
   {
      std::shared_ptr<T> new_data(new T[new_capacity], std::default_delete<T[]>());

      for (int i = 0; i < mSize; ++i)
      {
         new_data.get()[i] = mData.get()[i];
      }

      mData = std::move(new_data);
      mCapacity = new_capacity;
   }
}

template <typename T>
T JVector<T>::get(int index) const
{
   if (index < 0 or index >= mSize) {
      std::cout << "Index out of bounds." << std::endl;
      exit(EXIT_FAILURE);
   }

   return mData.get()[index];
}

template <typename T>
const T JVector<T>::pop()
{
   if (mSize == 0) {
      std::cout << "Nothing to pop." << std::endl;
      exit(EXIT_FAILURE);
   }

   int value = mData.get()[mSize - 1];

   ResizeForSize(mSize - 1);

   --mSize;

   return value;
}

template <typename T>
void JVector<T>::insert(int index, T value)
{
   if (index < 0 or index >= mSize) {
    std::cout << "Index out of bounds." << std::endl;
    exit(EXIT_FAILURE);
   }

   ResizeForSize(mSize + 1);

   for (int i = mSize; i > index; --i) {
    mData.get()[i] = mData.get()[i - 1];
   }

   mData.get()[index] = value;

   ++mSize;
}

template <typename T>
void JVector<T>::prepend(T value)
{
  insert(0, value);
}

template <typename T>
void JVector<T>::Delete(int index)
{
   if (index < 0 or index >= mSize) {
      std::cout << "Index out of bounds." << std::endl;
      exit(EXIT_FAILURE);
   }

   ResizeForSize(mSize - 1);

   for (int i = index; i < mSize - 1; i++)
   {
      mData.get()[i] = mData.get()[i + 1];
   }

   --mSize;
}

template <typename T>
void JVector<T>::remove(T value)
{
   for (int i = 0; i < mSize; ++i)
   {
      if (mData.get()[i] == value)
      {
         Delete(i);
         --i;
      }
   }
}

template <typename T>
int JVector<T>::find(T value) const
{
   int found_index = -1;

   for (int i = 0; i < mSize; ++i)
   {
      if (mData.get()[i] == value)
      {
         found_index = i;
         break;
      }
   }
   return found_index;
}
}
