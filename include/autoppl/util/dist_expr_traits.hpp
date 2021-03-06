#pragma once
#include <autoppl/util/concept.hpp>
#include <autoppl/util/type_traits.hpp>
#include <autoppl/util/var_traits.hpp>
#include <cstdint>
#include <cstdio>
namespace ppl {
namespace util {

/*
 * Base class for all distribution expressions.
 * It is necessary for all distribution expressions to
 * derive from this class.
 */
template <class T>
struct DistExpr : BaseCRTP<T>
{ 
    using BaseCRTP<T>::self;
    using dist_value_t = double;

    template <typename VarType>
    std::enable_if_t<is_var_v<std::decay_t<VarType>>, dist_value_t> 
    log_pdf(const VarType& var) const {
        dist_value_t value = 0.0;
        for (size_t i = 0; i < var.size(); ++i) {
            value += self().log_pdf(var.get_value(i), i);
        }

        return value;
    }

    template <typename VarType>
    std::enable_if_t<is_var_v<std::decay_t<VarType>>, dist_value_t>
    pdf(const VarType& var) const {
        dist_value_t value = 1.0;
        for (size_t i = 0; i < var.size(); ++i) {
            value *= self().pdf(var.get_value(i), i);
        }

        return value;
    }
};

/*
 * Checks if DistExpr<T> is base of type T 
 */
template <class T>
inline constexpr bool dist_expr_is_base_of_v =
    std::is_base_of_v<DistExpr<T>, T>;

DEFINE_ASSERT_ONE_PARAM(dist_expr_is_base_of_v);

/* 
 * TODO: Samplable distribution expression concept?
 */

/* 
 * TODO: continuous/discrete distribution expression concept?
 */

/*
 * Continuous distribution expressions can be constructed with this type.
 */
using cont_param_t = double;

/*
 * Discrete distribution expressions can be constructed with this type.
 */
using disc_param_t = int64_t;

/*
 * Traits for Distribution Expression classes.
 * value_t      type of value Variable represents during computation
 * dist_value_t type of pdf/log_pdf value
 */
template <class DistExprType>
struct dist_expr_traits
{
    using value_t = typename DistExprType::value_t;
    using dist_value_t = typename DistExprType::dist_value_t;
};

/*
 * A distribution expression is any class that satisfies the following concept:
 */
template <class T>
inline constexpr bool is_dist_expr_v = 
    dist_expr_is_base_of_v<T> &&
    has_type_value_t_v<T> &&
    has_type_dist_value_t_v<T> &&
    // has_func_pdf_v<const T> &&  // removed to allow overloading
    // has_func_log_pdf_v<const T> &&
    has_func_min_v<const T> &&
    has_func_max_v<const T>
    ;

template <class T>
inline constexpr bool assert_is_dist_expr_v = 
    assert_dist_expr_is_base_of_v<T> &&
    assert_has_type_value_t_v<T> &&
    assert_has_type_dist_value_t_v<T> &&
    // assert_has_func_pdf_v<const T> &&  // removed to allow overloading
    // assert_has_func_log_pdf_v<const T> &&
    assert_has_func_min_v<const T> &&
    assert_has_func_max_v<const T>
    ;

} // namespace util
} // namespace ppl
