#ifndef GRAPHLIB_GRAPH_FUNCTIONBUILDER
#define GRAPHLIB_GRAPH_FUNCTIONBUILDER

#include <memory>
#include <string>
#include <map>

#include "graph/function/Function.h"
#include "graph/function/FunctionDescriptor.h"

namespace graphlib { namespace graph { namespace function {

	using FunctionPtr = std::unique_ptr < Function > ;

	class FunctionBuilder {
	public:
		FunctionBuilder(std::string type_);
		FunctionBuilder(const FunctionBuilder&) = delete;
		FunctionBuilder& operator=(const FunctionBuilder&) = delete;
		static void registerFunction(std::string, const Function*);
		static void registerDescriptor(std::string, FunctionDescriptor);
		FunctionBuilder& color(std::string);
		FunctionBuilder& shape(std::string);
		FunctionPtr build(Value value_ = 0.0);
		FunctionDescriptor buildDescriptor();
		static FunctionPtr create(std::string type_, Value value_ = 0.0);
	private:
		static std::map < std::string, const Function* >& registered();
		static std::map < std::string, const FunctionDescriptor >& descriptors();
		const std::string _type;
		std::string _shape;
		std::string _color;
	};

}}}

#endif