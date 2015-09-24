#include "GraphTestHelper.h"

namespace GraphLibraryTest
{
	using namespace graphlib::graph;
	using namespace graphlib::graph::function;

	Graph createTestGraph() {
		GraphBuilder gb{};
		Label l0{ L"const" };
		Label l1{ L"oppos" };
		gb.addNode(l0, FunctionConstant::NAME, 1);
		gb.addNode(l1, FunctionOpposite::NAME);
		gb.addEdge(l0, l1);
		return std::move(gb.build());
	}

	Graph createMultiOutputGraph() {
		GraphBuilder gb{};
		auto n_a = gb.addNode(L"a", FunctionConstant::NAME, 1);
		auto n_b = gb.addNode(L"b", FunctionConstant::NAME, 1);
		auto n_c = gb.addNode(L"c", FunctionAdd::NAME);
		auto n_d = gb.addNode(L"d", FunctionConstant::NAME, 1);
		auto n_e = gb.addNode(L"e", FunctionAdd::NAME);
		auto n_f = gb.addNode(L"f", FunctionConstant::NAME, 1);
		auto n_g = gb.addNode(L"g", FunctionAdd::NAME);
		gb.addEdge(n_a, n_c);
		gb.addEdge(n_b, n_c);
		gb.addEdge(n_c, n_e);
		gb.addEdge(n_d, n_e);
		gb.addEdge(n_c, n_g);
		gb.addEdge(n_f, n_g);
		return std::move(gb.build());
	}

	Graph createQuadraticGraph(functiondata a, functiondata b, functiondata c) {
		GraphBuilder gb{};
		auto node_a = gb.addNode(L"A", FunctionInput::NAME, a);
		auto node_b = gb.addNode(L"B", FunctionInput::NAME, b);
		auto node_c = gb.addNode(L"C", FunctionInput::NAME, c);
		auto node_mb = gb.addNode(L"-B", FunctionOpposite::NAME);
		auto node_b2 = gb.addNode(L"B*B", FunctionMultiply::NAME);
		auto node_2 = gb.addNode(L"2", FunctionConstant::NAME, 2);
		auto node_2a = gb.addNode(L"2*a", FunctionMultiply::NAME);
		auto node_1p2a = gb.addNode(L"1/2*a", FunctionReciprocal::NAME);
		auto node_m4 = gb.addNode(L"-4", FunctionConstant::NAME, -4);
		auto node_m4ac = gb.addNode(L"-4AC", FunctionMultiply::NAME);
		auto node_b2m4ac = gb.addNode(L"B*B-4AC", FunctionAdd::NAME);
		auto node_sqrt = gb.addNode(L"Sqrt", FunctionSquareRoot::NAME);
		auto node_msqrt = gb.addNode(L"mSqrt", FunctionOpposite::NAME);
		auto node_mbpsqrt = gb.addNode(L"mbpSqrt", FunctionAdd::NAME);
		auto node_mbmsqrt = gb.addNode(L"mbmSqrt", FunctionAdd::NAME);
		auto node_x1 = gb.addNode(L"X1", FunctionMultiply::NAME);
		auto node_x2 = gb.addNode(L"X2", FunctionMultiply::NAME);

		gb.addEdge(node_2, node_2a);
		gb.addEdge(node_a, node_2a);
		
		gb.addEdge(node_2a, node_1p2a);
		
		gb.addEdge(node_b, node_b2);
		gb.addEdge(node_b, node_b2);
		
		gb.addEdge(node_b, node_mb);
		
		gb.addEdge(node_a, node_m4ac);
		gb.addEdge(node_c, node_m4ac);
		gb.addEdge(node_m4, node_m4ac);
		
		gb.addEdge(node_b2, node_b2m4ac);
		gb.addEdge(node_m4ac, node_b2m4ac);
		
		gb.addEdge(node_b2m4ac, node_sqrt);
		
		gb.addEdge(node_sqrt, node_msqrt);
		
		gb.addEdge(node_sqrt, node_mbpsqrt);
		gb.addEdge(node_mb, node_mbpsqrt);

		gb.addEdge(node_msqrt, node_mbmsqrt);
		gb.addEdge(node_mb, node_mbmsqrt);

		gb.addEdge(node_mbmsqrt, node_x1);
		gb.addEdge(node_1p2a, node_x1);
		gb.addEdge(node_mbpsqrt, node_x2);
		gb.addEdge(node_1p2a, node_x2);

		return std::move(gb.build());
	}

	Graph createQuadraticGraph() {
		return createQuadraticGraph(1.0, 3.0, 2.0);
	}
}