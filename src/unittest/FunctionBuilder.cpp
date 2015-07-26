#include "GraphLibTestUtils.hpp"

#include <iostream>

#include "graph\function\Function.h"
#include "graph\function\FunctionBuilder.h"

namespace GraphLibraryTest
{
	using namespace graphlib::graph::function;

	TEST(functionBuilderTests, TestBuildFunctionAdd)
	{
		CREATE_MEMORY_SNAPSHOT{
			FunctionBuilder fb(FunctionAdd::NAME);
			auto function = fb.build();
			ASSERT_TRUE(function.get() != nullptr) << "Built add function is null.";
			EXPECT_EQ(FunctionAdd::NAME, function->name()) << "Name of function doesn't match.";
			auto result = function->evaluate({});
			EXPECT_EQ(result, 0.0) << "Result doesn't match";
			result = function->evaluate({ 1 });
			EXPECT_EQ(result, 1.0) << "Result doesn't match";
			result = function->evaluate({ 1, 2 });
			EXPECT_EQ(result, 3.0) << "Result doesn't match";
			result = function->evaluate({ 1, 2, 3 });
			EXPECT_EQ(result, 6.0) << "Result doesn't match";
			result = function->evaluate({ 1, 2, 3, 4 });
			EXPECT_EQ(result, 10.0) << "Result doesn't match";
			// setting value, has no effect for 
			function->value(3.0);
			result = function->evaluate({ 1 });
			EXPECT_EQ(result, 1.0) << "Result doesn't match";
			result = function->evaluate({ 1, 2 });
			EXPECT_EQ(result, 3.0) << "Result doesn't match";
			result = function->evaluate({ 1, 2, 3 });
			EXPECT_EQ(result, 6.0) << "Result doesn't match";
			result = function->evaluate({ 1, 2, 3, 4 });
			EXPECT_EQ(result, 10.0) << "Result doesn't match";
		} ASSERT_MEMORY_SNAPSHOT
	}

	TEST(functionBuilderTests, TestBuildDescriptorFunctionAdd)
	{
		CREATE_MEMORY_SNAPSHOT{
			std::string type = "ADD";
			FunctionBuilder fb(type);
			const auto descriptor = fb.buildDescriptor();
			EXPECT_EQ(type, descriptor.typeString()) << "TypeString of FunctionAdd is not 'ADD'";
		} ASSERT_MEMORY_SNAPSHOT
	}

	TEST(functionBuilderTests, TestBuildFunctionConstant)
	{
		CREATE_MEMORY_SNAPSHOT{
			FunctionBuilder fb(FunctionConstant::NAME);
			auto function = fb.build(2.0);
			ASSERT_TRUE(function.get() != nullptr) << "Built constant function is null.";
			EXPECT_EQ(FunctionConstant::NAME, function->name()) << "Name of function doesn't match.";
			auto result = function->evaluate({});
			EXPECT_EQ(result, 2.0) << "Result doesn't match";
			result = function->evaluate({ 1 });
			EXPECT_EQ(result, 2.0) << "Result doesn't match";
			result = function->evaluate({ 1, 2 });
			EXPECT_EQ(result, 2.0) << "Result doesn't match";
			result = function->evaluate({ 1, 2, 3 });
			EXPECT_EQ(result, 2.0) << "Result doesn't match";
			result = function->evaluate({ 1, 2, 3, 4 });
			EXPECT_EQ(result, 2.0) << "Result doesn't match";
			// setting value, has no effect for 
			function->value(3.0);
			result = function->evaluate({ 1 });
			EXPECT_EQ(result, 2.0) << "Result doesn't match";
		} ASSERT_MEMORY_SNAPSHOT
	}

	TEST(functionBuilderTests, TestBuildFunctionReciprocal)
	{
		CREATE_MEMORY_SNAPSHOT{
			FunctionBuilder fb(FunctionReciprocal::NAME);
			auto function = fb.build();
			ASSERT_TRUE(function.get() != nullptr) << "Built divide function is null.";
			EXPECT_EQ(FunctionReciprocal::NAME, function->name()) << "Name of function doesn't match.";
			auto result = function->evaluate({ 1, 2 });
			EXPECT_EQ(result, 0.5) << "Result doesn't match";
			result = function->evaluate({ 1, 2, 3 });
			EXPECT_EQ(result, 0.5) << "Result doesn't match";
			result = function->evaluate({ 1, 2, 3, 4 });
			EXPECT_EQ(result, 0.5) << "Result doesn't match";
			// setting value, has no effect for 
			function->value(3.0);
			result = function->evaluate({ 1, 2 });
			EXPECT_EQ(result, 0.5) << "Result doesn't match";
		} ASSERT_MEMORY_SNAPSHOT
	}

	TEST(functionBuilderTests, TestBuildFunctionInput)
	{
		CREATE_MEMORY_SNAPSHOT{
			FunctionBuilder fb(FunctionInput::NAME);
			auto function = fb.build(2.0);
			ASSERT_TRUE(function.get() != nullptr) << "Built input function is null.";
			EXPECT_EQ(FunctionInput::NAME, function->name()) << "Name of function doesn't match.";
			auto result = function->evaluate({});
			EXPECT_EQ(result, 2.0) << "Result doesn't match";
			result = function->evaluate({ 1 });
			EXPECT_EQ(result, 2.0) << "Result doesn't match";
			result = function->evaluate({ 1, 2 });
			EXPECT_EQ(result, 2.0) << "Result doesn't match";
			result = function->evaluate({ 1, 2, 3 });
			EXPECT_EQ(result, 2.0) << "Result doesn't match";
			result = function->evaluate({ 1, 2, 3, 4 });
			EXPECT_EQ(result, 2.0) << "Result doesn't match";
			// setting value, changes the result returned by the function 
			function->value(3.0);
			result = function->evaluate({ 1 });
			EXPECT_EQ(result, 3.0) << "Result doesn't match";
		} ASSERT_MEMORY_SNAPSHOT
	}

	TEST(functionBuilderTests, TestBuildFunctionMultiply)
	{
		CREATE_MEMORY_SNAPSHOT{
			FunctionBuilder fb(FunctionMultiply::NAME);
			auto function = fb.build();
			ASSERT_TRUE(function.get() != nullptr) << "Built add function is null.";
			EXPECT_EQ(FunctionMultiply::NAME, function->name()) << "Name of function doesn't match.";
			auto result = function->evaluate({});
			EXPECT_EQ(result, 1.0) << "Result doesn't match";
			result = function->evaluate({ 1 });
			EXPECT_EQ(result, 1.0) << "Result doesn't match";
			result = function->evaluate({ 1, 2 });
			EXPECT_EQ(result, 2.0) << "Result doesn't match";
			result = function->evaluate({ 1, 2, 3 });
			EXPECT_EQ(result, 6.0) << "Result doesn't match";
			result = function->evaluate({ 1, 2, 3, 4 });
			EXPECT_EQ(result, 24.0) << "Result doesn't match";
			// setting value, has no effect for 
			function->value(3.0);
			result = function->evaluate({ 1 });
			EXPECT_EQ(result, 1.0) << "Result doesn't match";
			result = function->evaluate({ 1, 2 });
			EXPECT_EQ(result, 2.0) << "Result doesn't match";
			result = function->evaluate({ 1, 2, 3 });
			EXPECT_EQ(result, 6.0) << "Result doesn't match";
			result = function->evaluate({ 1, 2, 3, 4 });
			EXPECT_EQ(result, 24.0) << "Result doesn't match";
		} ASSERT_MEMORY_SNAPSHOT
	}

	TEST(functionBuilderTests, TestBuildFunctionOpposite)
	{
		CREATE_MEMORY_SNAPSHOT{
			FunctionBuilder fb(FunctionOpposite::NAME);
			auto function = fb.build();
			ASSERT_TRUE(function.get() != nullptr) << "Built divide function is null.";
			EXPECT_EQ(FunctionOpposite::NAME, function->name()) << "Name of function doesn't match.";
			auto result = function->evaluate({ 1, 2 });
			EXPECT_EQ(result, -1.0) << "Result doesn't match";
			result = function->evaluate({ 1, 2, 3 });
			EXPECT_EQ(result, -1.0) << "Result doesn't match";
			result = function->evaluate({ 1, 2, 3, 4 });
			EXPECT_EQ(result, -1.0) << "Result doesn't match";
			// setting value, has no effect for 
			function->value(3.0);
			result = function->evaluate({ 1, 2 });
			EXPECT_EQ(result, -1.0) << "Result doesn't match";
		} ASSERT_MEMORY_SNAPSHOT
	}
}