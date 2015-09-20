#include "graph/GraphBuilder.h"

#include <sstream>
#include <stdexcept>

#include "graph/function/FunctionBuilder.h"

namespace graphlib { namespace graph {

	NodeReference::NodeReference() {}

	NodeReference::NodeReference(GraphBuilder* builder_, NodeId id_) : _id(id_), _builder(builder_)
	{
	}

	NodeReference::NodeReference(NodeReference&& other) : _id(other._id), _builder(other._builder)
	{
	}

	NodeBuilder::NodeBuilder() {}

	NodeBuilder::NodeBuilder(NodeBuilder&& other) 
		: _id(other._id), _label(other._label), _function_name(other._function_name), _value(other._value), _descriptor(other._descriptor) {
		this->_builder = other._builder;
		other._builder = nullptr;
	}

	NodeBuilder::NodeBuilder(GraphBuilder* builder_, NodeId id_, Label label_, string function_name_, functiondata value_, NodeDescriptor descriptor_)
		: _builder(builder_), _id(id_), _label(label_), _function_name(function_name_), _value(value_), _descriptor(descriptor_)
	{
	}

	NodeBuilder& NodeBuilder::operator = (NodeBuilder&& other) {
		this->_id = other._id;
		this->_label = other._label;
		this->_function_name = other._function_name;
		this->_value = other._value;
		this->_descriptor = other._descriptor;
		this->_builder = other._builder;
		other._builder = nullptr;
		return *this;
	}
	
	NodeId NodeBuilder::id() const {
		return _id;
	}

	GraphBuilder* NodeBuilder::graph_builder() const {
		return _builder;
	}

	Node NodeBuilder::build() const {
		auto func = FunctionBuilder(_function_name).build(_value);
		return std::move(Node{ _id, _label, std::move(func), _descriptor });
	}

	bool validate_node_builders(const NodeReference& left, const NodeReference& right) {
		return left.graph_builder() == right.graph_builder();
	}

	Label with_parenthesis(Label label, bool add_parenthesis) {
		return add_parenthesis ? L"(" + label + L")" : label;
	}

	unsigned priority(string function_name) {
		if (function_name == FunctionInput::NAME || function_name == FunctionConstant::NAME) {
			return 3;
		}
	
		if (function_name == FunctionMultiply::NAME) {
			return 2;
		}

		return 1;
	}

	Label prepare_label(const NodeBuilder& left, const NodeBuilder& right, string function_name, Label operation)
	{
		auto left_prio = priority(left.function_name());
		auto right_prio = priority(right.function_name());
		auto op_prio = priority(function_name);
		return with_parenthesis(left.label(), left_prio < op_prio) + operation + with_parenthesis(right.label(), right_prio < op_prio);
	}

	NodeReference general_operator(NodeReference left_ref, NodeReference right_ref, string function_name, Label operation)
	{
		if (!validate_node_builders(left_ref, right_ref)) {
			throw std::logic_error("Nodes from different graph builders cannot be added");
		}
		GraphBuilder* gb = left_ref.graph_builder();
		NodeBuilder& left = gb->_nodes[left_ref.id()];
		NodeBuilder& right = gb->_nodes[right_ref.id()];
		if (left.function_name() == function_name) {
			gb->addEdge(right_ref, left_ref);
			Label label{ prepare_label(left, right, function_name, operation) };
			left.label(label);
			return left_ref;
		}

		if (right.function_name() == function_name) {
			gb->addEdge(left_ref, right_ref);
			Label label{ prepare_label(left, right, function_name, operation) };
			right.label(label);
			return right_ref;
		}

		Label label{ prepare_label(left, right, function_name, operation) };
		NodeReference node_ref = gb->addNode(label, function_name);
		gb->addEdge(left_ref, node_ref);
		gb->addEdge(right_ref, node_ref);
		return node_ref;
	}

	NodeReference operator+(NodeReference left_ref, NodeReference right_ref) {
		return general_operator(left_ref, right_ref, FunctionAdd::NAME, L"+");
	}

	NodeReference operator*(NodeReference left_ref, NodeReference right_ref) {
		return general_operator(left_ref, right_ref, FunctionMultiply::NAME, L"*");
	}

	NodeReference operator-(NodeReference left_ref, NodeReference right_ref) {
		if (!validate_node_builders(left_ref, right_ref)) {
			throw std::logic_error("Nodes from different graph builders cannot be added");
		}

		GraphBuilder* gb = left_ref.graph_builder();
		Label opposite_label = L"-(" + gb->_nodes[right_ref.id()].label() + L")";
		NodeReference opposite_node = gb->addNode(opposite_label, FunctionOpposite::NAME);
		gb->addEdge(right_ref, opposite_node);
		NodeBuilder& left = gb->_nodes[left_ref.id()];
		if (left.function_name() == FunctionAdd::NAME) {
			gb->addEdge(opposite_node, left_ref);
			left.label(Label{ left.label() + opposite_label });
			return left_ref;
		}

		Label add_label{ with_parenthesis(left.label(), true) + opposite_label };
		NodeReference node_ref = gb->addNode(add_label, FunctionAdd::NAME);
		gb->addEdge(left_ref, node_ref);
		gb->addEdge(opposite_node, node_ref);
		return node_ref;
	}

	NodeReference operator/(NodeReference left_ref, NodeReference right_ref) {
		if (!validate_node_builders(left_ref, right_ref)) {
			throw std::logic_error("Nodes from different graph builders cannot be added");
		}

		GraphBuilder* gb = left_ref.graph_builder();
		Label reciproc_label = L"/(" + gb->_nodes[right_ref.id()].label() + L")";
		NodeReference reciproc_node = gb->addNode(reciproc_label, FunctionReciprocal::NAME);
		gb->addEdge(right_ref, reciproc_node);
		NodeBuilder& left = gb->_nodes[left_ref.id()];
		if (left.function_name() == FunctionMultiply::NAME) {
			gb->addEdge(reciproc_node, left_ref);
			left.label(Label{ left.label() + reciproc_label });
			return left_ref;
		}

		Label multiply_label{ with_parenthesis(left.label(), true) + reciproc_label };
		NodeReference node_ref = gb->addNode(multiply_label, FunctionMultiply::NAME);
		gb->addEdge(left_ref, node_ref);
		gb->addEdge(reciproc_node, node_ref);
		return node_ref;
	}

	NodeReference operator-(NodeReference node) {
		GraphBuilder* gb = node.graph_builder();
		Label label = L"(-" + gb->_nodes[node.id()].label() + L")";
		NodeReference minus_node = gb->addNode(label, FunctionOpposite::NAME);
		gb->addEdge(node, minus_node);
		return minus_node;
	}

	NodeReference sqrt(NodeReference node) {
		GraphBuilder* gb = node.graph_builder();
		Label label = L"sqrt(" + gb->_nodes[node.id()].label() + L")";
		NodeReference sqrt_node = gb->addNode(label, FunctionSquareRoot::NAME);
		gb->addEdge(node, sqrt_node);
		return sqrt_node;
	}

	NodeReference GraphBuilder::addNode(Label label_, std::string function_name_, functiondata value_) {
		NodeId id{ this->_nodes.size() };
		this->_nodes.emplace_back(NodeBuilder{ this, id, label_, function_name_, value_, NodeDescriptor{ function_name_ } });
		this->_ids[label_] = id;
		return NodeReference{ this, id };
	}

	//NodeBuilder GraphBuilder::addNode(Label label_, functionptr&& function_) {
	//	NodeId id{ this->_nodes.size() };
	//	//NodeBuilder node{ id, this };
	//	std::string function_name = function_->name();
	//	//this->_nodes.emplace_back(Node(id, label_, std::move(function_), NodeDescriptor{ function_name }));
	//	this->_ids[label_] = id;
	//	// 
	//	return NodeBuilder{ this, id, label_, std::move(function_), NodeDescriptor{ function_name } };
	//}

	bool GraphBuilder::addEdge(NodeReference from, NodeReference to) {
		auto size = this->_nodes.size();
		if (from.id() >= size || to.id() >= size) {
			return false;
		}
		this->doAddEdge(from.id(), to.id());
		return true;
	}

	bool GraphBuilder::addEdge(Label label_from, Label label_to) {
		NodeBuilder from;
		if (!resolve_node(label_from, from)) {
			return false;
		}
		NodeBuilder to;
		if (!resolve_node(label_to, to)) {
			return false;
		}

		this->doAddEdge(from.id(), to.id());
		return true;
	}

	void GraphBuilder::doAddEdge(NodeId from, NodeId to) {
		_edges.push_back(std::make_pair(from, to));
	}

	bool GraphBuilder::resolve_node(Label label, NodeBuilder& id) {
		auto it = this->_ids.find(label);
		if (it == this->_ids.end()) {
			return false;
		}

		id._id = it->second;
		return true;
	}

	Graph GraphBuilder::build() {
		// adding edges before creating the graph
		vector<Node> nodes;
		for (const auto& builder : this->_nodes) {
			nodes.emplace_back(builder.build());
		}
		for (const pair<NodeId, NodeId>& edge : _edges) {
			Node* n1 = &nodes[edge.first];
			Node* n2 = &nodes[edge.second];
			n1->addSuccessor(n2);
			n2->addPredecessor(n1);
		}
		return Graph(std::move(nodes));
	}
}}