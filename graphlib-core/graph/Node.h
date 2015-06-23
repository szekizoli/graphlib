#ifndef GRAPHLIB_GRAPH_NODE_NODE_H
#define GRAPHLIB_GRAPH_NODE_NODE_H

#include <memory>
#include <string>

#include "function\Function.h"

namespace graphlib { namespace graph {
		using std::weak_ptr;
		using std::string;
		using namespace graphlib::graph::function;

		// Descripes a node in terms of persistence and visualization
		class NodeDescriptor
		{
		public:
			NodeDescriptor(string typeString = "NONE", string color = "#0099AA", string shape = "roundrectangle") :
				_typeString(typeString), _color(color), _shape(shape) {}
			string typeString() const { return _typeString; }
			string shape() const { return _shape; }
			string color() const { return _color; }
		private:
			string _typeString;
			string _shape;
			string _color;
		};

		class Node;
		using NodeList    = std::vector < Node >;
		using NodePtr     = const Node*;
		using NodePtrList = std::vector < NodePtr >;

		template<typename _Id>
		class NodeBase {
		public:
			using NodeBasePtr = const NodeBase*;
			virtual std::vector<NodeBasePtr> predecessors() const = 0;
			virtual std::vector<NodeBasePtr> successors() const = 0;
			virtual NodeBasePtr predecessor(std::size_t) const = 0;
			virtual NodeBasePtr successor(std::size_t) const = 0;
			virtual std::size_t predecessor_size() const = 0;
			virtual std::size_t successor_size() const = 0;
			virtual _Id id() const = 0;
		};

		template<typename _Function, typename _Id>
		class ExecutableNode : public NodeBase<_Id> {
		public:
			using NodeBasePtr = const ExecutableNode*;
		};

		class ScheduleableNode {
		public:
			using ScheduleableNodePtr = const ScheduleableNode*;
			virtual std::vector<ScheduleableNodePtr> predecessors() const = 0;
			virtual std::vector<ScheduleableNodePtr> successors() const = 0;
			virtual ScheduleableNodePtr predecessor(std::size_t) const = 0;
			virtual ScheduleableNodePtr successor(std::size_t) const = 0;
			virtual std::size_t predecessor_size() const = 0;
			virtual std::size_t successor_size() const = 0;
			virtual unsigned cptime() const = 0;
			// id
		};

		using GraphId = unsigned;
		using Label = std::wstring;
		using Func = Function;
		using FuncPtr = std::unique_ptr < Function > ;

		class Node final
		{
			// new interface
		public:
			using nodeptr = const Node*;
			Node();
			Node(GraphId id_, Label label_, FuncPtr&& func_, NodeDescriptor descriptor_);
			Node(const Node& other) = delete;
			Node(Node&& other);
			Node& operator=(const Node& other) = delete;
			Node& operator=(Node&& other);
			virtual ~Node() = default;

			GraphId id() const { return _id; }
			Label label() const { return _label; }
			const Func& function() const { return *_function.get(); }
			const NodeDescriptor& descriptor() const { return _descriptor; }
			const vector<Node>& predecessors() const { return _predecessors; }
			const vector<Node>& successors() const { return _successors; }
			nodeptr predecessor(std::size_t i) const { return &_predecessors[i]; }
			nodeptr successor(std::size_t i) const { return &_successors[i]; }
			size_t predecessor_size() const { return _predecessors.size(); }
			size_t successor_size() const { return _successors.size(); }

		private:
			GraphId _id;
			Label _label;
			NodeDescriptor _descriptor;
			FuncPtr _function;
			vector<Node> _predecessors;
			vector<Node> _successors;

			void predecessors(vector<nodeptr>);
			void successors(vector<nodeptr>);
		};

		// for building node
		class NodeDefinition{

		};
}}
#endif