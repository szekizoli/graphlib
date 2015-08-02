#include "graph/function/Function.h"

#include <numeric>
#include "graph/function/FunctionBuilder.h"

namespace graphlib { namespace graph { namespace function {
	void Function::init() {}
	
	const std::string FunctionAdd::NAME{ "ADD" };
	const std::string FunctionConstant::NAME{ "CONSTANT" };
	const std::string FunctionReciprocal::NAME{ "RECIPROCAL" };
	const std::string FunctionInput::NAME{ "INPUT" };
	const std::string FunctionOpposite::NAME{ "OPPOSITE" };
	const std::string FunctionMultiply::NAME{ "MULTIPLY" };

	FunctionAdd FunctionAdd::example(funcexample{});
	FunctionConstant FunctionConstant::example{ funcexample{} };
	FunctionReciprocal FunctionReciprocal::example{ funcexample{} };
	FunctionInput FunctionInput::example{ funcexample{} };
	FunctionOpposite FunctionOpposite::example{ funcexample{} };
	FunctionMultiply FunctionMultiply::example{ funcexample{} };

	//FunctionAdd
	FunctionAdd::FunctionAdd(funcexample)
		{ FunctionBuilder::registerFunction(FunctionAdd::NAME, this); }

	functiondata FunctionAdd::evaluate(const functionlist& input) const {
		return std::accumulate(begin(input), end(input), functiondata{ 0 });
	}

	functionptr FunctionAdd::clone(functiondata) const {
		return std::move(std::make_unique<FunctionAdd>());
	}

	// FunctionConstant
	
	FunctionConstant::FunctionConstant(funcexample) :_value(functiondata{0.0}) {
		FunctionBuilder::registerFunction(FunctionConstant::NAME, this);
	}
	FunctionConstant::FunctionConstant(functiondata value_) : _value(value_)
	{  }
	functiondata FunctionConstant::evaluate(const functionlist&) const {
		return _value;
	}
	functionptr FunctionConstant::clone(functiondata value_) const {
		return std::move(std::make_unique<FunctionConstant>(value_));
	}

	//FunctionReciprocal
	FunctionReciprocal::FunctionReciprocal(funcexample){ 
		FunctionBuilder::registerFunction(FunctionReciprocal::NAME, this); 
	}
	functiondata FunctionReciprocal::evaluate(const functionlist& input) const {
		return input[0] / input[1];
	}
	functionptr FunctionReciprocal::clone(functiondata) const {
		return std::move(std::make_unique<FunctionReciprocal>());
	}

	//FunctionInput
	FunctionInput::FunctionInput(funcexample){
		FunctionBuilder::registerFunction(FunctionInput::NAME, this);
	}
	FunctionInput::FunctionInput(functiondata value_) : _value(value_)
	{  }
	functiondata FunctionInput::evaluate(const functionlist&) const {
		return this->_value;
	}
	functionptr FunctionInput::clone(functiondata value_) const {
		return std::move(std::make_unique<FunctionInput>(value_));
	}
	void FunctionInput::value(functiondata value_) {
		_value = value_;
	}

	//FunctionOpposite
	FunctionOpposite::FunctionOpposite(funcexample){
		FunctionBuilder::registerFunction(FunctionOpposite::NAME, this);
	}
	functiondata FunctionOpposite::evaluate(const functionlist& input) const {
		return input[0] - input[1];
	}
	functionptr FunctionOpposite::clone(functiondata) const {
		return std::move(std::make_unique<FunctionOpposite>());
	}

	//FunctionMultiply
	FunctionMultiply::FunctionMultiply(funcexample){
		FunctionBuilder::registerFunction(FunctionMultiply::NAME, this);
	}
	functiondata FunctionMultiply::evaluate(const functionlist& input) const {
		return std::accumulate(begin(input), end(input), functiondata{ 1.0 }, std::multiplies<functiondata>());
	}
	functionptr FunctionMultiply::clone(functiondata) const {
		return std::move(std::make_unique<FunctionMultiply>());
	}
}}}