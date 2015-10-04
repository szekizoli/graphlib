#include "executor/Executor.h"

#include <vector>
#include <stack>
#include "graph/Algorithms.h"

namespace graphlib { namespace executor {

	template <typename T>
	std::map<graph::Label, graph::Value> GenericExecutor<T>::execute(graph::Graph graph_) {
		return _executor.execute(graph_);
	}

	std::map<graph::Label, graph::Value> SimpleExecutor::execute(graph::Graph) {
		std::vector<graph::Value> memory;
		std::map<graph::Label, graph::Value> result;
		// create order using topological sort
		// based on the order execute nodes
		  // assemble values for the execution
		  // execute
		  // store value in the memory
		// copy results from memory into result
		return std::move(result);
	}

	Result execute(It first, It last) {
		std::vector<graph::Value> mem(last - first, NAN);
		std::vector<graph::Value> values; 
		for (It it = first; it != last; ++it) {
			// collecting parameters for function call
			for (const auto& nptr : (*it)->predecessors()) {
				values.push_back(mem[nptr->id()]);
			}

			// evaluate
			auto value = (*it)->function()(values);
			mem[(*it)->id()] = value;
			values.clear();
		}
		return std::move(Result{ std::move(mem) } );
	}

	Result stack_execute(It first, It last) {
		std::vector<graph::Value> mem(last - first, NAN);
		std::stack<graph::Value> datastack;
		for (first; first != last; ++first) {
			std::vector<graph::Value> values;
			// collecting parameters for function call
			for (size_t i = 0; i < (*first)->predecessorSize(); ++i) {
				values.push_back(datastack.top());
				datastack.pop();
			}

			// evaluate
			auto value = (*first)->function().evaluate(values);
			mem[(*first)->id()] = value;
			for (size_t i = 0; i < (*first)->successorSize(); ++i) {
				datastack.push(value);
			}
		}
		return std::move(Result{ std::move(mem) });
	}
}}

