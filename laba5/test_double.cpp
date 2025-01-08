#include <iostream>
#include <gtest/gtest.h>
#include "DoubleList.hpp"

TEST(TestDouble, DefaultConstructor) {
	DoubleList<int> obj;
	ASSERT_TRUE(obj.empty());
	ASSERT_EQ(obj.begin(), nullptr);
	ASSERT_EQ(obj.end(), nullptr);
	// что за счётчик?
}

TEST(TestDouble, CopyConstructor) {
	DoubleList<int> initial;
	initial.push_back(1);
	initial.push_back(2);
	initial.push_back(3);
	DoubleList<int> copy = initial;
	ASSERT_NE(&copy, &initial);
	ASSERT_FALSE(copy.empty());
	for (auto it1 = initial.begin(), it2 = copy.begin();; ++it1, ++it2) {
		bool e1 = it1.empty(), e2 = it2.empty();
		if (e1 && e2) break;
		ASSERT_TRUE(!(e1 ^ e2)) <<
		"One of iterators exhausted before other.\nMaybe not all values were copied";
		ASSERT_EQ(*it1, *it2) << "All elements of copy should be the same (copied) as of initial";
	}
	(void)initial.pop_front();
	ASSERT_EQ(copy.front(), 1) << "Changing initial should not reflect on copy";
}

TEST(TestDouble, Destructor) {
	DoubleList<int> *initial = new DoubleList<int>();
	initial->push_back(1);
	initial->push_back(2);
	initial->push_back(3);
	delete initial;
	// idk imagine valgrind there
	SUCCEED() << "How to check that?";
}

TEST(TestDouble, push_front) {
	DoubleList<int> obj;
	obj.push_front(1);
	ASSERT_TRUE(obj.begin() != nullptr);
	ASSERT_EQ(*obj.begin(), 1);
	obj.push_front(2);
	auto it = obj.begin();
	ASSERT_TRUE(it != nullptr);
	ASSERT_EQ(*it, 2);
	++it;
	ASSERT_EQ(*it, 1);
}

TEST(TestDouble, push_back) {
	DoubleList<int> obj;
	obj.push_back(1);
	auto it1 = obj.begin();
	ASSERT_TRUE(it1 != nullptr);
	ASSERT_EQ(*it1, 1);
	++it1;
	ASSERT_EQ(it1, obj.end());
	obj.push_back(2);
	auto it = obj.begin();
	ASSERT_TRUE(it != nullptr);
	ASSERT_EQ(*it, 1);
	++it;
	ASSERT_NE(it, nullptr);
	ASSERT_EQ(*it, 2);
	++it;
	ASSERT_EQ(it, obj.end());
}

TEST(TestDouble, insert) {
	DoubleList<int> obj;
	obj.insert(0, 10); // 10
	ASSERT_EQ(obj.front(), 10);
	obj.insert(0, 13); // 13 10
	ASSERT_EQ(obj.front(), 13);
	ASSERT_EQ(obj[1], 10);
	obj.insert(1, 20); // 13 20 10
	ASSERT_EQ(obj.size(), 3);
	ASSERT_EQ(obj[0], 13);
	ASSERT_EQ(obj[1], 20);
	ASSERT_EQ(obj[2], 10);
	obj.insert(3, 40); // 13 20 10 40
	ASSERT_EQ(obj.size(), 4);
	ASSERT_EQ(obj[0], 13);
	ASSERT_EQ(obj[1], 20);
	ASSERT_EQ(obj[2], 10);
	ASSERT_EQ(obj[3], 40);
}

TEST(TestDouble, pop_front) {
	DoubleList<int> obj;
	ASSERT_NO_THROW(obj.pop_front());
	obj.push_back(1);
	obj.pop_front();
	ASSERT_TRUE(obj.empty());
	obj.push_back(1);
	obj.push_back(2);
	obj.pop_front();
	ASSERT_FALSE(obj.empty());
	ASSERT_EQ(obj[0], 2);
	ASSERT_NE(obj.begin(), nullptr);
	ASSERT_EQ(*obj.begin(), 2);
}

TEST(TestDouble, pop_back) {
	DoubleList<int> obj;
	ASSERT_NO_THROW(obj.pop_back());
	obj.push_back(1);
	obj.pop_back();
	ASSERT_TRUE(obj.empty());
	obj.push_back(1);
	ASSERT_EQ(obj.back(), 1);
	obj.push_back(2);
	ASSERT_EQ(obj.back(), 2);
	ASSERT_EQ(obj[0], 1);
	ASSERT_EQ(obj[1], 2);
	obj.pop_back();
	ASSERT_FALSE(obj.empty());
	ASSERT_EQ(obj.back(), 1);
}

TEST(TestDouble, front) {
	DoubleList<int> obj;
	ASSERT_ANY_THROW(obj.front());
	obj.push_back(123);
	ASSERT_EQ(obj.front(), 123);
}

TEST(TestDouble, back) {
	DoubleList<int> obj;
	ASSERT_ANY_THROW(obj.back());
	obj.push_back(123);
	ASSERT_EQ(obj.back(), 123);
}

TEST(TestDouble, size) {
	DoubleList<int> obj;
	ASSERT_EQ(obj.size(), 0);
	obj.push_back(1);
	ASSERT_EQ(obj.size(), 1);
	obj.push_back(2);
	ASSERT_EQ(obj.size(), 2);
}

TEST(TestDouble, indexing) {
	DoubleList<int> obj;
	ASSERT_ANY_THROW(obj[0]);
	ASSERT_ANY_THROW(obj[15]);
	obj.push_back(1);
	obj.push_back(2);
	obj.push_back(3);
	ASSERT_EQ(obj[0], 1);
	ASSERT_EQ(obj[1], 2);
	ASSERT_EQ(obj[2], 3);
	ASSERT_ANY_THROW(obj[15]);
}

TEST(TestDouble, iterators) {
	DoubleList<int> obj{0, 1, 2};
	int i = 0;
	for (auto it = obj.begin(); it != obj.end(); ++it, i++)
		ASSERT_EQ(*it, i);
	auto it = obj.begin();
	++it;
	++it;
	--it;
	ASSERT_EQ(*it, 1);
}

TEST(TestDouble, Add500) {
	DoubleList<int> obj;
	ASSERT_EQ(obj.size(), 0);
	for (int i = 0; i < 500; i++)
		obj.push_back(i);
	ASSERT_EQ(obj.size(), 500);
	ASSERT_EQ(obj[400], 400);
}
