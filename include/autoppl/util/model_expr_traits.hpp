#pragma once
#include <autoppl/util/concept.hpp>
#include <autoppl/util/type_traits.hpp>

namespace ppl {
namespace util {

/*
 * Base class for all model expressions.
 * It is necessary for all model expressions to
 * derive from this class.
 */
template <class T>
struct ModelExpr : BaseCRTP<T>
{ using BaseCRTP<T>::self; };

/*
 * Checks if DistExpr<T> is base of type T 
 */
template <class T>
inline constexpr bool model_expr_is_base_of_v =
    std::is_base_of_v<ModelExpr<T>, T>;

DEFINE_ASSERT_ONE_PARAM(model_expr_is_base_of_v);

/*
 * Traits for Model Expression classes.
 * dist_value_t      type of value Variable represents during computation
 */
template <class NodeType>
struct model_expr_traits
{
    using dist_value_t = typename NodeType::dist_value_t;
};

// TODO: 
// - pdf and log_pdf remove from interface?
// - how to check if template member function exists (for traverse)?
template <class T>
inline constexpr bool is_model_expr_v = 
    model_expr_is_base_of_v<T> &&
    has_type_dist_value_t_v<T> &&
    has_func_pdf_v<const T> &&
    has_func_log_pdf_v<const T>
    ;

template <class T>
inline constexpr bool assert_is_model_expr_v = 
    assert_model_expr_is_base_of_v<T> &&
    assert_has_type_dist_value_t_v<T> &&
    assert_has_func_pdf_v<const T> &&
    assert_has_func_log_pdf_v<const T>
    ;

} // namespace util
} // namespace ppl
