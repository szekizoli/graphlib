#ifndef GRAPHLIB_EXECUTOR_EXECUTOR
#define GRAPHLIB_EXECUTOR_EXECUTOR

#include <map>
#include "graph/Graph.h"
#include "graph/Node.h"


namespace graphlib { namespace executor {

	class Executor {
	public:
		virtual std::map<graph::Label, graph::functiondata> execute(graph::Graph) = 0; // const
	};

	template <typename _Executor>
	class GenericExecutor : public Executor {
	public:
		virtual std::map<graph::Label, graph::functiondata> execute(graph::Graph) override;
	private:
		_Executor _executor;
	};

	class SimpleExecutor : public Executor {
	public:
		virtual std::map<graph::Label, graph::functiondata> execute(graph::Graph) override;
	};

}}

#endif