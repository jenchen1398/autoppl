#pragma once
#include <cmath>
#include <autoppl/util/traits.hpp>
#include <cassert>

namespace ppl {

/*
 * Mock state class for testing purposes.
 */
enum class MockState {
    data,
    parameter
};

/*
 * Mock Variable class that should meet the requirements
 * of is_var_v.
 */
struct MockParam : util::ParamLike<MockParam> {

    using value_t = double;
    using pointer_t = double*;
    using const_pointer_t = const double*;

    void set_value(value_t x) { value_ = x; }
    value_t get_value(size_t) const { return value_; }
    constexpr size_t size() const { return 1; }

    void set_storage(pointer_t ptr) {ptr_ = ptr;}

private:
    value_t value_ = 0.0;
    pointer_t ptr_ = nullptr;
};

struct MockData : util::DataLike<MockData>
{
    using value_t = double;
    using pointer_t = double*;
    using const_pointer_t = const double*;

    value_t get_value(size_t) const { 
        return value_;
    }

    constexpr size_t size() const { return 1; }

private:
    value_t value_ = 0.0;
};


/*
 * Mock variable classes that fulfill 
 * var_traits requirements, but do not fit the rest.
 */
struct MockParam_no_convertible : util::Var<MockParam>
{
    using value_t = double;
    using pointer_t = double*;
    using const_pointer_t = const double*;
};

struct MockData_no_convertible : util::Var<MockData> {
    using value_t = double;
    using pointer_t = double*;
    using const_pointer_t = const double*;
};

/*
 * Mock Variable Expression class that should meet the requirements
 * of is_var_expr_v.
 */
struct MockVarExpr : util::VarExpr<MockVarExpr>
{
    using value_t = double;
    value_t get_value(size_t) const { 
        return x_; 
    }

    constexpr size_t size() const { return 1; }

    /* not part of API */
    MockVarExpr(value_t x = 0.)
        : x_{x}
    {}
    void set_value(value_t x) {x_ = x;}

private:
    value_t x_ = 0.;
};

/*
 * Mock variable expression classes that fulfill 
 * var_expr_traits requirements, but do not fit the rest.
 */
struct MockVarExpr_no_convertible : util::VarExpr<MockVarExpr>
{
    using value_t = double;
};

/*
 * Mock distribution expression class that should meet the requirements
 * of is_dist_expr_v.
 */
struct MockDistExpr : util::DistExpr<MockDistExpr>
{
    using value_t = double;

    using base_t = util::DistExpr<MockDistExpr>;
    using dist_value_t = typename base_t::dist_value_t;
    using base_t::pdf;
    using base_t::log_pdf;

    dist_value_t pdf(value_t x, size_t=0) const { return x; }

    dist_value_t log_pdf(value_t x, size_t=0) const { return std::log(x); }

    value_t min(size_t=0) const { return 0.; }
    value_t max(size_t=0) const { return 1.; }
};

/*
 * Mock distribution expression classes that fulfill 
 * dist_expr_traits requirements, but do not fit the rest.
 */
struct MockDistExpr_no_pdf : 
    util::DistExpr<MockDistExpr_no_pdf>, 
    public MockDistExpr
{
private:
    using MockDistExpr::pdf;
};

struct MockDistExpr_no_log_pdf : public MockDistExpr
{
private:
    using MockDistExpr::log_pdf;
};

/*
 * Mock binary operation node for testing purposes.
 */
struct MockBinaryOp
{
	// mock operation -- returns the sum 
	static double evaluate(double x, double y) {
		return x + y;
	}
};

/*
 * TODO:
 * Mock model expression clases that should meet the 
 * requirements of is_model_expr_v.
 * Additionally, MockEqNode should satisfy is_eq_node_expr_v.
 */

} // namespace ppl
