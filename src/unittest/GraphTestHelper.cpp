#include "GraphTestHelper.h"

namespace GraphLibraryTest
{
	using namespace graphlib::graph;
	using namespace graphlib::graph::function;

	Graph createTestGraph() {
		GraphBuilder gb{};
		Label l0{ L"const" };
		Label l1{ L"oppos" };
		gb.add_node(l0, FunctionConstant::NAME, 1);
		gb.add_node(l1, FunctionOpposite::NAME);
		gb.add_edge(l0, l1);
		return std::move(gb.build());
	}

	Graph createMultiOutputGraph() {
		GraphBuilder gb{};
		auto n_a = gb.add_node(L"a", FunctionConstant::NAME, 1);
		auto n_b = gb.add_node(L"b", FunctionConstant::NAME, 1);
		auto n_c = gb.add_node(L"c", FunctionAdd::NAME);
		auto n_d = gb.add_node(L"d", FunctionConstant::NAME, 1);
		auto n_e = gb.add_node(L"e", FunctionAdd::NAME);
		auto n_f = gb.add_node(L"f", FunctionConstant::NAME, 1);
		auto n_g = gb.add_node(L"g", FunctionAdd::NAME);
		gb.add_edge(n_a, n_c);
		gb.add_edge(n_b, n_c);
		gb.add_edge(n_c, n_e);
		gb.add_edge(n_d, n_e);
		gb.add_edge(n_c, n_g);
		gb.add_edge(n_f, n_g);
		return std::move(gb.build());
	}

	Graph createQuadraticGraph(Value a, Value b, Value c) {
		GraphBuilder gb{};
		auto node_a = gb.add_node(L"A", FunctionInput::NAME, a);
		auto node_b = gb.add_node(L"B", FunctionInput::NAME, b);
		auto node_c = gb.add_node(L"C", FunctionInput::NAME, c);
		auto node_mb = gb.add_node(L"-B", FunctionOpposite::NAME);
		auto node_b2 = gb.add_node(L"B*B", FunctionMultiply::NAME);
		auto node_2 = gb.add_node(L"2", FunctionConstant::NAME, 2);
		auto node_2a = gb.add_node(L"2*a", FunctionMultiply::NAME);
		auto node_1p2a = gb.add_node(L"1/2*a", FunctionReciprocal::NAME);
		auto node_m4 = gb.add_node(L"-4", FunctionConstant::NAME, -4);
		auto node_m4ac = gb.add_node(L"-4AC", FunctionMultiply::NAME);
		auto node_b2m4ac = gb.add_node(L"B*B-4AC", FunctionAdd::NAME);
		auto node_sqrt = gb.add_node(L"Sqrt", FunctionSquareRoot::NAME);
		auto node_msqrt = gb.add_node(L"mSqrt", FunctionOpposite::NAME);
		auto node_mbpsqrt = gb.add_node(L"mbpSqrt", FunctionAdd::NAME);
		auto node_mbmsqrt = gb.add_node(L"mbmSqrt", FunctionAdd::NAME);
		auto node_x1 = gb.add_node(L"X1", FunctionMultiply::NAME);
		auto node_x2 = gb.add_node(L"X2", FunctionMultiply::NAME);

		gb.add_edge(node_2, node_2a);
		gb.add_edge(node_a, node_2a);
		
		gb.add_edge(node_2a, node_1p2a);
		
		gb.add_edge(node_b, node_b2);
		gb.add_edge(node_b, node_b2);
		
		gb.add_edge(node_b, node_mb);
		
		gb.add_edge(node_a, node_m4ac);
		gb.add_edge(node_c, node_m4ac);
		gb.add_edge(node_m4, node_m4ac);
		
		gb.add_edge(node_b2, node_b2m4ac);
		gb.add_edge(node_m4ac, node_b2m4ac);
		
		gb.add_edge(node_b2m4ac, node_sqrt);
		
		gb.add_edge(node_sqrt, node_msqrt);
		
		gb.add_edge(node_sqrt, node_mbpsqrt);
		gb.add_edge(node_mb, node_mbpsqrt);

		gb.add_edge(node_msqrt, node_mbmsqrt);
		gb.add_edge(node_mb, node_mbmsqrt);

		gb.add_edge(node_mbmsqrt, node_x1);
		gb.add_edge(node_1p2a, node_x1);
		gb.add_edge(node_mbpsqrt, node_x2);
		gb.add_edge(node_1p2a, node_x2);

		return std::move(gb.build());
	}

	Graph createQuadraticGraph() {
		return createQuadraticGraph(1.0, 3.0, 2.0);
	}
}