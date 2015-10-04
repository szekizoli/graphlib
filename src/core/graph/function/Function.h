#ifndef GRAPHLIB_GRAPH_FUNCTION
#define GRAPHLIB_GRAPH_FUNCTION

#include <memory>
#include <string>
#include <vector>

namespace graphlib { namespace graph { namespace function {

	using std::vector;

	namespace {
		struct funcexample{};
	}

	using Value = double;
	class Function;
	using function_ptr = std::unique_ptr < Function > ;

	class Function : public std::unary_function<vector<Value>, Value> {
	public:
		// evaluates the function
		virtual Value evaluate(const vector<Value>& input) const = 0;
		virtual function_ptr clone(Value) const = 0;
		virtual std::string name() const = 0;
		virtual void value(Value) {}
		virtual ~Function() {}
		static void init();
	};

	class FunctionAdd : public Function {
	public:
		FunctionAdd() = default;
		FunctionAdd(funcexample);
		FunctionAdd(const FunctionAdd&) = delete;
		FunctionAdd(const FunctionAdd&&) = delete;
		FunctionAdd& operator=(const FunctionAdd&) = delete;
		FunctionAdd& operator=(const FunctionAdd&&) = delete;
		virtual std::string name() const override { return FunctionAdd::NAME; }
		virtual Value evaluate(const vector<Value>& input) const override;
		virtual function_ptr clone(Value _value = 0.0) const override;

		Value operator()(const vector<Value>& input) const;

		static const std::string NAME;
	private:
		static FunctionAdd example;
	};

	class FunctionConstant : public Function {
	public:
		FunctionConstant(Value value_);
		FunctionConstant(funcexample);
		FunctionConstant(const FunctionConstant&) = delete;
		FunctionConstant(const FunctionConstant&&) = delete;
		FunctionConstant& operator=(const FunctionConstant&) = delete;
		FunctionConstant& operator=(const FunctionConstant&&) = delete;
		virtual std::string name() const override { return FunctionConstant::NAME; }
		virtual Value evaluate(const vector<Value>& input) const override;
		virtual function_ptr clone(Value _value = 0.0) const override;
	
		Value operator()(const vector<Value>& input) const ;

		static const std::string NAME;
	private:
		static FunctionConstant example;
		const Value _value;
	};

	class FunctionReciprocal : public Function {
	public:
		FunctionReciprocal() = default;
		FunctionReciprocal(funcexample);
		FunctionReciprocal(const FunctionReciprocal&) = delete;
		FunctionReciprocal(const FunctionReciprocal&&) = delete;
		FunctionReciprocal& operator=(const FunctionReciprocal&) = delete;
		FunctionReciprocal& operator=(const FunctionReciprocal&&) = delete;
		virtual std::string name() const override { return FunctionReciprocal::NAME; }
		virtual Value evaluate(const vector<Value>& input) const override;
		virtual function_ptr clone(Value _value = 0.0) const override;

		Value operator()(const vector<Value>& input) const;

		static const std::string NAME;
	private:
		static FunctionReciprocal example;
	};

	class FunctionInput : public Function {
	public:
		FunctionInput(Value value_ = 0);
		FunctionInput(funcexample);
		FunctionInput(const FunctionInput&) = delete;
		FunctionInput(const FunctionInput&&) = delete;
		FunctionInput& operator=(const FunctionInput&) = delete;
		FunctionInput& operator=(const FunctionInput&&) = delete;
		virtual std::string name() const override { return FunctionInput::NAME; }
		void value(Value value_) override;
		virtual Value evaluate(const vector<Value>& input) const override;
		virtual function_ptr clone(Value _value = 0.0) const override;
	
		Value operator()(const vector<Value>& input) const;

		static const std::string NAME;
	private:
		Value _value;
		static FunctionInput example;
	};

	class FunctionOpposite : public Function {
	public:
		FunctionOpposite() = default;
		FunctionOpposite(funcexample);
		FunctionOpposite(const FunctionOpposite&) = delete;
		FunctionOpposite(const FunctionOpposite&&) = delete;
		FunctionOpposite& operator=(const FunctionOpposite&) = delete;
		FunctionOpposite& operator=(const FunctionOpposite&&) = delete;
		virtual std::string name() const override { return FunctionOpposite::NAME; }
		virtual Value evaluate(const vector<Value>& input) const override;
		virtual function_ptr clone(Value _value = 0.0) const override;
	
		Value operator()(const vector<Value>& input) const;

		static const std::string NAME;
	private:
		static FunctionOpposite example;
	};

	class FunctionMultiply : public Function {
	public:
		FunctionMultiply() = default;
		FunctionMultiply(funcexample);
		FunctionMultiply(const FunctionMultiply&) = delete;
		FunctionMultiply(const FunctionMultiply&&) = delete;
		FunctionMultiply& operator=(const FunctionMultiply&) = delete;
		FunctionMultiply& operator=(const FunctionMultiply&&) = delete;
		virtual std::string name() const override { return FunctionMultiply::NAME; }
		virtual Value evaluate(const vector<Value>& input) const override;
		virtual function_ptr clone(Value _value = 0.0) const override;

		Value operator()(const vector<Value>& input) const;

		static const std::string NAME;
	private:
		static FunctionMultiply example;
	};

	class FunctionSquareRoot : public Function {
	public:
		FunctionSquareRoot() = default;
		FunctionSquareRoot(funcexample);
		FunctionSquareRoot(const FunctionSquareRoot&) = delete;
		FunctionSquareRoot(const FunctionSquareRoot&&) = delete;
		FunctionSquareRoot& operator=(const FunctionSquareRoot&) = delete;
		FunctionSquareRoot& operator=(const FunctionSquareRoot&&) = delete;
		virtual std::string name() const override { return FunctionSquareRoot::NAME; }
		virtual Value evaluate(const vector<Value>& input) const override;
		virtual function_ptr clone(Value _value = 0.0) const override;

		Value operator()(const vector<Value>& input) const;

		static const std::string NAME;
	private:
		static FunctionSquareRoot example;
	};
}}}

#endif