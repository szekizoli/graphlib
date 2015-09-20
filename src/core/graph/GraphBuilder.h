#ifndef GRAPHLIB_GRAPH_GRAPHBUILDER_H 
#define GRAPHLIB_GRAPH_GRAPHBUILDER_H

#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "graph/Node.h"
#include "graph/Graph.h"

namespace graphlib { namespace graph {

	using std::pair;
	using std::string;

	class NodeReference {
	public:
		NodeReference();
		NodeReference(GraphBuilder* builder_, NodeId id_);
		NodeReference(const NodeReference& other) = default;
		NodeReference(NodeReference&& other);
		NodeId id() const { return _id; }
		GraphBuilder* graph_builder() const { return _builder; }
	private:
		NodeId        _id;
		GraphBuilder* _builder;
	};

	class NodeBuilder {
	public:
		NodeBuilder(GraphBuilder* builder_, NodeId id_, Label label_, string function_name_, functiondata value_, NodeDescriptor descriptor_);
		NodeBuilder(const NodeBuilder& other) = default;
		NodeBuilder(NodeBuilder&& other);
		NodeBuilder& operator=(const NodeBuilder& other) = default;
		NodeBuilder& operator=(NodeBuilder&& other);
		NodeId id() const;
		Label label() const { return _label; }
		void label(const Label& label_) { _label = label_; }
		string function_name() const { return _function_name; }
		GraphBuilder* graph_builder() const;
		Node build() const;
		//friend NodeBuilder& operator+(NodeBuilder& left, functiondata right);
	private:
		friend class GraphBuilder;
		NodeBuilder();
		NodeId         _id;
		Label          _label;
		NodeDescriptor _descriptor;
		functiondata   _value;
		string         _function_name;
		GraphBuilder*  _builder;
	};

	bool validate_node_builders(const NodeBuilder& left, const NodeBuilder& right);

	class GraphBuilder {
	public:
		NodeReference addNode(Label label_, std::string functionName_, functiondata value_ = 0.0);
		NodeReference addNode(Label label_, functionptr&& function_);
		bool addEdge(NodeReference from, NodeReference to);
		bool addEdge(Label from, Label to);bool resolveNode(Label label, NodeBuilder& id);
		friend NodeReference operator+(NodeReference left, NodeReference right);
		friend NodeReference operator-(NodeReference left, NodeReference right);
		friend NodeReference operator*(NodeReference left, NodeReference right);
		friend NodeReference operator/(NodeReference left, NodeReference right);
		friend NodeReference operator-(NodeReference node);
		friend NodeReference sqrt(NodeReference node);
		Graph build();
	private:
		vector<NodeBuilder> _nodes;
		vector<pair<NodeId, NodeId>> _edges;
		std::map<Label, NodeId> _ids;
		bool resolve_node(Label label, NodeBuilder& id);
		void doAddEdge(NodeId from, NodeId to);
		friend NodeReference general_operator(NodeReference left, NodeReference right, string function_name, Label operation);
	};

}}

#endif