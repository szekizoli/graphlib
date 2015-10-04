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
	const std::string FunctionSquareRoot::NAME{ "SQUAREROOT" };

	FunctionAdd FunctionAdd::example(funcexample{});
	FunctionConstant FunctionConstant::example{ funcexample{} };
	FunctionReciprocal FunctionReciprocal::example{ funcexample{} };
	FunctionInput FunctionInput::example{ funcexample{} };
	FunctionOpposite FunctionOpposite::example{ funcexample{} };
	FunctionMultiply FunctionMultiply::example{ funcexample{} };
	FunctionSquareRoot FunctionSquareRoot::example{ funcexample{} };

	//FunctionAdd
	FunctionAdd::FunctionAdd(funcexample)
		{ FunctionBuilder::registerFunction(FunctionAdd::NAME, this); }

	Value FunctionAdd::evaluate(const vector<Value>& input) const {
		return std::accumulate(begin(input), end(input), Value{ 0 });
	}

	function_ptr FunctionAdd::clone(Value) const {
		return std::move(std::make_unique<FunctionAdd>());
	}

	// FunctionConstant
	
	FunctionConstant::FunctionConstant(funcexample) :_value(Value{0.0}) {
		FunctionBuilder::registerFunction(FunctionConstant::NAME, this);
	}
	FunctionConstant::FunctionConstant(Value value_) : _value(value_)
	{  }
	Value FunctionConstant::evaluate(const vector<Value>&) const {
		return _value;
	}
	function_ptr FunctionConstant::clone(Value value_) const {
		return std::move(std::make_unique<FunctionConstant>(value_));
	}

	//FunctionReciprocal
	FunctionReciprocal::FunctionReciprocal(funcexample){ 
		FunctionBuilder::registerFunction(FunctionReciprocal::NAME, this); 
	}
	Value FunctionReciprocal::evaluate(const vector<Value>& input) const {
		return 1 / input[0];
	}
	function_ptr FunctionReciprocal::clone(Value) const {
		return std::move(std::make_unique<FunctionReciprocal>());
	}

	//FunctionInput
	FunctionInput::FunctionInput(funcexample){
		FunctionBuilder::registerFunction(FunctionInput::NAME, this);
	}
	FunctionInput::FunctionInput(Value value_) : _value(value_)
	{  }
	Value FunctionInput::evaluate(const vector<Value>&) const {
		return this->_value;
	}
	function_ptr FunctionInput::clone(Value value_) const {
		return std::move(std::make_unique<FunctionInput>(value_));
	}
	void FunctionInput::value(Value value_) {
		_value = value_;
	}

	//FunctionOpposite
	FunctionOpposite::FunctionOpposite(funcexample){
		FunctionBuilder::registerFunction(FunctionOpposite::NAME, this);
	}
	Value FunctionOpposite::evaluate(const vector<Value>& input) const {
		return 0 - input[0];
	}
	function_ptr FunctionOpposite::clone(Value) const {
		return std::move(std::make_unique<FunctionOpposite>());
	}

	//FunctionMultiply
	FunctionMultiply::FunctionMultiply(funcexample){
		FunctionBuilder::registerFunction(FunctionMultiply::NAME, this);
	}
	Value FunctionMultiply::evaluate(const vector<Value>& input) const {
		return std::accumulate(begin(input), end(input), Value{ 1.0 }, std::multiplies<Value>());
	}
	function_ptr FunctionMultiply::clone(Value) const {
		return std::move(std::make_unique<FunctionMultiply>());
	}

	//FunctionSquareRoot
	FunctionSquareRoot::FunctionSquareRoot(funcexample){
		FunctionBuilder::registerFunction(FunctionSquareRoot::NAME, this);
	}
	Value FunctionSquareRoot::evaluate(const vector<Value>& input) const {
		return sqrt(input[0]);
	}
	function_ptr FunctionSquareRoot::clone(Value) const {
		return std::move(std::make_unique<FunctionSquareRoot>());
	}
}}}