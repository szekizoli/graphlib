#pragma once

#include "graph\function\Function.h"
#include "graph\Graph.h"
#include "graph\GraphBuilder.h"

namespace GraphLibraryTest
{
	using graphlib::graph::function::functiondata;

	graphlib::graph::Graph createTestGraph();
	graphlib::graph::Graph createQuadraticGraph();
	graphlib::graph::Graph createMultiOutputGraph();
	graphlib::graph::Graph createQuadraticGraph(functiondata a, functiondata b, functiondata c);
}