#ifndef GRAPHLIB_EXECUTOR_EXECUTOR
#define GRAPHLIB_EXECUTOR_EXECUTOR

#include <vector>
#include <map>
#include <stack>
#include "graph/Graph.h"
#include "graph/Node.h"

namespace graphlib { namespace executor {

	struct Result {
		std::vector<graph::Value> memory;
		Result() {}
		Result(size_t size) : memory(size) {}
		Result(const std::vector<graph::Value>& r) : memory(r) {}
		Result(std::vector<graph::Value>&& r) : memory(r) {}
		Result(const Result& x) : memory(x.memory) {}
		Result(Result&& x) : memory(std::move(x.memory)) {}
		typedef graph::Value value_type;
		const graph::Value& operator[](const size_t index) const { return memory[index]; }
		graph::Value& operator[](const size_t index) { return memory[index]; }
		size_t size() const { return memory.size(); }
	};

	template<class It, class Result>
	Result tmpexecute(It first, It last, Result&& result)
	{
		//result.memory.resize(last - first);
		std::vector<Result::value_type> values;
		for (; first != last; ++first) {
			// collecting parameters for function call
			for (const auto& nptr : (*first)->predecessors()) {
				values.push_back(result[nptr->id()]);
			}

			// evaluate
			result[(*first)->id()] = (*first)->function()(values);
			values.clear();
		}
		return std::move(result);
	}

	using It = std::vector<graph::NodePtr>::const_iterator;
	Result execute(It first, It last);
	Result stack_execute(It first, It last);

	// below not used

	struct TmpExecutionResult {
		typedef graph::Value value_type;
		std::vector<graph::Value> memory;
		const graph::Value& operator[](const size_t index) const { return memory[index]; }
	};

	class Instruction {
	public:

	private:

	};

	class Executor {
	public:
		virtual std::map<graph::Label, graph::Value> execute(graph::Graph) = 0; // const
	};

	template <typename T>
	class GenericExecutor : public Executor {
	public:
		virtual std::map<graph::Label, graph::Value> execute(graph::Graph) override;
	private:
		T _executor;
	};

	class SimpleExecutor : public Executor {
	public:
		virtual std::map<graph::Label, graph::Value> execute(graph::Graph) override;
	};
}}

#endif