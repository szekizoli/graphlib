#ifndef GRAPHLIB_TEST_UTILS_HPP
#define GRAPHLIB_TEST_UTILS_HPP

#define _CRTDBG_MAP_ALLOC
#include <malloc.h>
#include <stdlib.h>
#include <crtdbg.h>

#include "gtest/gtest.h"

#include "graph\function\Function.h"
#include "graph\Graph.h"
#include "graph\GraphBuilder.h"

// only do memory leak check in debug mode
#ifdef _DEBUG

#define MEMORY_LEAK_CHECK(code) { \
			_CrtMemState s1, s2, s3; \
			_CrtMemCheckpoint(&s1); \
			{ code } \
			_CrtMemCheckpoint(&s2); \
			int leaked = _CrtMemDifference(&s3, &s1, &s2); \
			Assert::IsTrue(leaked == 0, L"Memory leak!", LINE_INFO());\
			}

#define CREATE_MEMORY_SNAPSHOT _CrtMemState s1, s2, s3; _CrtMemCheckpoint(&s1);

#define ASSERT_MEMORY_SNAPSHOT _CrtMemCheckpoint(&s2); \
			int leaked = _CrtMemDifference(&s3, &s1, &s2); \
			EXPECT_EQ(0, leaked) << "Memory leak!";
#else
#define MEMORY_LEAK_CHECK(code) code
#define CREATE_MEMORY_SNAPSHOT
#define ASSERT_MEMORY_SNAPSHOT
#endif

#endif // GRAPHLIB_TEST_UTILS_HPP


