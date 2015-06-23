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
			Assert::AreEqual(expected_size, n.predecessorSize(), L"", LINE_INFO());
			Assert::AreEqual(expected_size, n.successorSize(), L"", LINE_INFO());
		} ASSERT_MEMORY_SNAPSHOT }

		TEST_METHOD(TestSimpleNodeDefinition)
		{ CREATE_MEMORY_SNAPSHOT {
			NodeDefinition nd(L"test-node", std::make_unique<FunctionAdd>(), NodeDescriptor());
			Node n = nd.createNode(0);
			unsigned expected_value = 0;
			Assert::AreEqual(expected_value, n.id(), L"", LINE_INFO());
			std::wstring expected_label = L"test-node";
			Assert::AreEqual(expected_label, n.label(), L"", LINE_INFO());
			Assert::AreEqual(expected_value, n.predecessorSize(), L"", LINE_INFO());
			Assert::AreEqual(expected_value, n.successorSize(), L"", LINE_INFO());
		} ASSERT_MEMORY_SNAPSHOT }
	};
}