#ifndef GRAPHLIB_GRAPH_GRAPHBUILDER_H 
#define GRAPHLIB_GRAPH_GRAPHBUILDER_H

#include <map>
#include <memory>
#include <string>
#include <vector>

#include "graph/Node.h"
#include "graph/Graph.h"

namespace graphlib { namespace graph {

	class NodeBuilder {
	public:
		NodeBuilder(NodeId id_, GraphBuilder* builder_);
		NodeId id() const;
		GraphBuilder* graph_builder() const;
	private:
		friend class GraphBuilder;
		NodeBuilder();
		NodeId _id;
		GraphBuilder* _builder;
	};

	class GraphBuilder {
	public:
		NodeBuilder addNode(Label label_, std::string functionName_, functiondata value_ = 0.0);
		NodeBuilder addNode(Label label_, functionptr&& function_);
		bool addEdge(NodeBuilder from, NodeBuilder to);
		bool addEdge(Label from, Label to);bool resolveNode(Label label, NodeBuilder& id);
		Graph build();
	private:
		vector<Node> _nodes;
		std::map<Label, NodeId> _ids;
		bool resolve_node(Label label, NodeBuilder& id);
		void doAddEdge(NodeId from, NodeId to);
	};

}}

#endif