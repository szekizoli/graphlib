#include "executor/Executor.h"

#include <vector>
#include <stack>
#include "graph\algorithms.h"

namespace graphlib { namespace executor {

	ExecutionResult::ExecutionResult(const std::vector<graph::functiondata>& r) : result(r) 
	{
	}

	ExecutionResult::ExecutionResult(std::vector<graph::functiondata>&& r) : result(r)
	{
	}

	ExecutionResult::ExecutionResult(const ExecutionResult& other) : result(other.result)
	{
	}

	ExecutionResult::ExecutionResult(ExecutionResult&& other)
	{
		std::swap(result, other.result);
	}

	const graph::functiondata& ExecutionResult::operator[](const size_t idx) const {
		return this->result[idx];
	}

	template <typename _Executor>
	std::map<graph::Label, graph::functiondata> GenericExecutor<_Executor>::execute(graph::Graph graph_) {
		return _executor.execute(graph_);
	}

	std::map<graph::Label, graph::functiondata> SimpleExecutor::execute(graph::Graph) {
		std::vector<graph::functiondata> memory;
		std::map<graph::Label, graph::functiondata> result;
		// create order using topological sort
		// based on the order execute nodes
		  // assemble values for the execution
		  // execute
		  // store value in the memory
		// copy results from memory into result
		return std::move(result);
	}

	ExecutionResult execute(It first, It last) {
		std::vector<graph::functiondata> mem(last - first, NAN);
		graph::function::datalist data;
		for (It it = first; it != last; ++it) {
			// collecting parameters for function call
			for (const auto& nptr : (*it)->predecessors()) {
				data.push_back(mem[nptr->id()]);
			}

			// evaluate
			auto value = (*it)->function().evaluate(data);
			mem[(*it)->id()] = value;
			data.clear();
		}
		return std::move(ExecutionResult{ std::move(mem) });
	}

	ExecutionResult stack_execute(It first, It last) {
		std::vector<graph::functiondata> mem(last - first, NAN);
		std::stack<graph::functiondata> datastack;
		for (It it = first; it != last; ++it) {
			graph::function::datalist data;
			// collecting parameters for function call
			for (size_t i = 0; i < (*it)->predecessorSize(); ++i) {
				data.push_back(datastack.top());
				datastack.pop();
			}

			// evaluate
			auto value = (*it)->function().evaluate(data);
			mem[(*it)->id()] = value;
			for (size_t i = 0; i < (*it)->successorSize(); ++i) {
				datastack.push(value);
			}
		}
		return std::move(ExecutionResult{ std::move(mem) });
	}
}}

