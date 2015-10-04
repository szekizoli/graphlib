#ifndef GRAPHLIB_EXECUTOR_EXECUTOR
#define GRAPHLIB_EXECUTOR_EXECUTOR

#include <vector>
#include <map>
#include <stack>
#include "graph/Graph.h"
#include "graph/Node.h"

namespace graphlib { namespace executor {

	class ExecutionResult {
	public:
		ExecutionResult(const std::vector<graph::Value>& r);
		ExecutionResult(std::vector<graph::Value>&& r);
		ExecutionResult(const ExecutionResult& other);
		ExecutionResult(ExecutionResult&& other);
		const graph::Value& operator[](const size_t idx) const;
		size_t size() const { return result.size(); }
	private:
		std::vector<graph::Value> result;
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

	using It = std::vector<graph::NodePtr>::const_iterator;
	ExecutionResult execute(It first, It last);
	ExecutionResult stack_execute(It first, It last);

}}

#endif