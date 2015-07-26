#include "Executor.h"

#include <vector>

namespace graphlib { namespace executor {

	template <typename _Executor>
	std::map<graph::Label, graph::functiondata> GenericExecutor<_Executor>::execute(graph::Graph graph_) {
		return _executor.execute(graph_);
	}

	std::map<graph::Label, graph::functiondata> SimpleExecutor::execute(graph::Graph) {
		std::vector<graph::functiondata> memory;
		std::map<graph::Label, graph::functiondata> result;
		return std::move(result);
	}
}}

