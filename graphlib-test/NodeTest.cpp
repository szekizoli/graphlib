#include "stdafx.h"
#include "GraphLibTestUtils.hpp"

#include <iostream>

#include "graph\function\Function.h"
#include "graph\Node.h"

namespace GraphLibraryTest
{
	using namespace graphlib::graph;
	using namespace graphlib::graph::function;

	TEST_CLASS(FunctionBuilderTest)
	{
	public:
		TEST_CLASS_INITIALIZE(InitFunctionBuilderTest) {
			Function::init();
		}

		TEST_METHOD(TestEmptyNode)
		{ CREATE_MEMORY_SNAPSHOT {
			Node n;
			unsigned expected_size = 0;
			Assert::AreEqual(expected_size, n.predecessor_size(), L"", LINE_INFO());
			Assert::AreEqual(expected_size, n.successor_size(), L"", LINE_INFO());
		} ASSERT_MEMORY_SNAPSHOT }
	};
}