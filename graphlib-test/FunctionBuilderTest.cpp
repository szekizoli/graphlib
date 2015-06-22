#include "stdafx.h"
#include "GraphLibTestUtils.hpp"

#include <iostream>

#include "graph\function\Function.h"
#include "graph\function\FunctionBuilder.h"

namespace GraphLibraryTest
{
	using namespace graphlib::graph::function;

	TEST_CLASS(FunctionBuilderTest)
	{
	public:
		TEST_CLASS_INITIALIZE(InitFunctionBuilderTest) {
			Function::init();
		}

		TEST_METHOD(TestBuildFunctionAdd)
		{ CREATE_MEMORY_SNAPSHOT{
			FunctionBuilder fb("ADD");
			auto function = fb.build();
			Assert::IsNotNull(function.get(), L"Built add function is null.", LINE_INFO());
			auto result = function->evaluate({ });
			Assert::AreEqual(result, 0.0, L"Result doesn't match", LINE_INFO());
			result = function->evaluate({ 1 });
			Assert::AreEqual(result, 1.0, L"Result doesn't match", LINE_INFO());
			result = function->evaluate({ 1, 2});
			Assert::AreEqual(result, 3.0, L"Result doesn't match", LINE_INFO());
			result = function->evaluate({ 1, 2, 3 });
			Assert::AreEqual(result, 6.0, L"Result doesn't match", LINE_INFO());
			result = function->evaluate({ 1, 2, 3, 4 });
			Assert::AreEqual(result, 10.0, L"Result doesn't match", LINE_INFO());
			// setting value, has no effect for 
			function->value(3.0);
			result = function->evaluate({ 1 });
			Assert::AreEqual(result, 1.0, L"Result doesn't match", LINE_INFO());
			result = function->evaluate({ 1, 2 });
			Assert::AreEqual(result, 3.0, L"Result doesn't match", LINE_INFO());
			result = function->evaluate({ 1, 2, 3 });
			Assert::AreEqual(result, 6.0, L"Result doesn't match", LINE_INFO());
			result = function->evaluate({ 1, 2, 3, 4 });
			Assert::AreEqual(result, 10.0, L"Result doesn't match", LINE_INFO());
		} ASSERT_MEMORY_SNAPSHOT }

		TEST_METHOD(TestBuildDescriptorFunctionAdd)
		{ CREATE_MEMORY_SNAPSHOT{
			std::string type = "ADD";
			FunctionBuilder fb(type);
			const auto descriptor = fb.buildDescriptor();
			Assert::AreEqual(type, descriptor.typeString(), L"TypeString of FunctionAdd is not 'ADD'", LINE_INFO());
		} ASSERT_MEMORY_SNAPSHOT }

		TEST_METHOD(TestBuildFunctionConstant)
		{ CREATE_MEMORY_SNAPSHOT{
			FunctionBuilder fb("CONSTANT");
			auto function = fb.build(2.0);
			Assert::IsNotNull(function.get(), L"Built constant function is null.", LINE_INFO());
			auto result = function->evaluate({});
			Assert::AreEqual(result, 2.0, L"Result doesn't match", LINE_INFO());
			result = function->evaluate({ 1 });
			Assert::AreEqual(result, 2.0, L"Result doesn't match", LINE_INFO());
			result = function->evaluate({ 1, 2 });
			Assert::AreEqual(result, 2.0, L"Result doesn't match", LINE_INFO());
			result = function->evaluate({ 1, 2, 3 });
			Assert::AreEqual(result, 2.0, L"Result doesn't match", LINE_INFO());
			result = function->evaluate({ 1, 2, 3, 4 });
			Assert::AreEqual(result, 2.0, L"Result doesn't match", LINE_INFO());
			// setting value, has no effect for 
			function->value(3.0);
			result = function->evaluate({ 1 });
			Assert::AreEqual(result, 2.0, L"Result doesn't match", LINE_INFO());
		} ASSERT_MEMORY_SNAPSHOT }

		TEST_METHOD(TestBuildFunctionDivide)
		{ CREATE_MEMORY_SNAPSHOT{
			FunctionBuilder fb("DIVIDE");
			auto function = fb.build();
			Assert::IsNotNull(function.get(), L"Built divide function is null.", LINE_INFO());
			auto result = function->evaluate({ 1, 2 });
			Assert::AreEqual(result, 0.5, L"Result doesn't match", LINE_INFO());
			result = function->evaluate({ 1, 2, 3 });
			Assert::AreEqual(result, 0.5, L"Result doesn't match", LINE_INFO());
			result = function->evaluate({ 1, 2, 3, 4 });
			Assert::AreEqual(result, 0.5, L"Result doesn't match", LINE_INFO());
			// setting value, has no effect for 
			function->value(3.0);
			result = function->evaluate({ 1, 2 });
			Assert::AreEqual(result, 0.5, L"Result doesn't match", LINE_INFO());
		} ASSERT_MEMORY_SNAPSHOT }

		TEST_METHOD(TestBuildFunctionInput)
		{ CREATE_MEMORY_SNAPSHOT{
			FunctionBuilder fb("INPUT");
			auto function = fb.build(2.0);
			Assert::IsNotNull(function.get(), L"Built input function is null.", LINE_INFO());
			auto result = function->evaluate({});
			Assert::AreEqual(result, 2.0, L"Result doesn't match", LINE_INFO());
			result = function->evaluate({ 1 });
			Assert::AreEqual(result, 2.0, L"Result doesn't match", LINE_INFO());
			result = function->evaluate({ 1, 2 });
			Assert::AreEqual(result, 2.0, L"Result doesn't match", LINE_INFO());
			result = function->evaluate({ 1, 2, 3 });
			Assert::AreEqual(result, 2.0, L"Result doesn't match", LINE_INFO());
			result = function->evaluate({ 1, 2, 3, 4 });
			Assert::AreEqual(result, 2.0, L"Result doesn't match", LINE_INFO());
			// setting value, changes the result returned by the function 
			function->value(3.0);
			result = function->evaluate({ 1 });
			Assert::AreEqual(result, 3.0, L"Result doesn't match", LINE_INFO());
		} ASSERT_MEMORY_SNAPSHOT }

		TEST_METHOD(TestBuildFunctionMultiply)
		{ CREATE_MEMORY_SNAPSHOT{
			FunctionBuilder fb("MULTIPLY");
			auto function = fb.build();
			Assert::IsNotNull(function.get(), L"Built add function is null.", LINE_INFO());
			auto result = function->evaluate({ });
			Assert::AreEqual(result, 1.0, L"Result doesn't match", LINE_INFO());
			result = function->evaluate({ 1 });
			Assert::AreEqual(result, 1.0, L"Result doesn't match", LINE_INFO());
			result = function->evaluate({ 1, 2});
			Assert::AreEqual(result, 2.0, L"Result doesn't match", LINE_INFO());
			result = function->evaluate({ 1, 2, 3 });
			Assert::AreEqual(result, 6.0, L"Result doesn't match", LINE_INFO());
			result = function->evaluate({ 1, 2, 3, 4 });
			Assert::AreEqual(result, 24.0, L"Result doesn't match", LINE_INFO());
			// setting value, has no effect for 
			function->value(3.0);
			result = function->evaluate({ 1 });
			Assert::AreEqual(result, 1.0, L"Result doesn't match", LINE_INFO());
			result = function->evaluate({ 1, 2 });
			Assert::AreEqual(result, 2.0, L"Result doesn't match", LINE_INFO());
			result = function->evaluate({ 1, 2, 3 });
			Assert::AreEqual(result, 6.0, L"Result doesn't match", LINE_INFO());
			result = function->evaluate({ 1, 2, 3, 4 });
			Assert::AreEqual(result, 24.0, L"Result doesn't match", LINE_INFO());
		} ASSERT_MEMORY_SNAPSHOT }

		TEST_METHOD(TestBuildFunctionSubtract)
		{ CREATE_MEMORY_SNAPSHOT{
			FunctionBuilder fb("SUBTRACT");
			auto function = fb.build();
			Assert::IsNotNull(function.get(), L"Built divide function is null.", LINE_INFO());
			auto result = function->evaluate({ 1, 2 });
			Assert::AreEqual(result, -1.0, L"Result doesn't match", LINE_INFO());
			result = function->evaluate({ 1, 2, 3 });
			Assert::AreEqual(result, -1.0, L"Result doesn't match", LINE_INFO());
			result = function->evaluate({ 1, 2, 3, 4 });
			Assert::AreEqual(result, -1.0, L"Result doesn't match", LINE_INFO());
			// setting value, has no effect for 
			function->value(3.0);
			result = function->evaluate({ 1, 2 });
			Assert::AreEqual(result, -1.0, L"Result doesn't match", LINE_INFO());
		} ASSERT_MEMORY_SNAPSHOT }
	};
}