#pragma once
#include <cassert>
#include <random>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <autoppl/util/var_expr_traits.hpp>
#include <autoppl/util/dist_expr_traits.hpp>

namespace ppl {
namespace expr {
    
template <typename weight_type>
struct Discrete : util::DistExpr<Discrete<weight_type>>
{
    static_assert(util::assert_is_var_expr_v<weight_type>);

    using value_t = util::disc_param_t;
    using weight_value_t = typename util::var_expr_traits<weight_type>::value_t; 
    using dist_value_t = double;

    Discrete() { weights_ = {1}; } 

    Discrete(std::initializer_list<weight_type> weights)
        : weights_{ weights } 
        { normalize_weights(weights_.begin(), weights_.end()); }

    template <class Iter>
    Discrete(Iter begin, Iter end)
        : weights_{ begin, end } 
        { normalize_weights(weights_.begin(), weights_.end()); }

    template <class GeneratorType>
    value_t sample(GeneratorType& gen) const
    {
        std::discrete_distribution dist(weights_.begin(), weights_.end()); 
        return dist(gen); 
    }

    dist_value_t pdf(value_t i) const
    {
        assert( i >= 0 && i <  weights_.size() );
        return weights(i) ;

    } 

    dist_value_t log_pdf(value_t i) const
    {
        assert( i >= 0 && i < weights_.size() );
        return std::log(weights(i));
    }

    inline weight_value_t weights(value_t i) const { return static_cast<weight_value_t>(weights_[i]); }
    weight_value_t min() const { 
        return 0; 
    }
    weight_value_t max() const { 
        return weights_.size() - 1;
    }

    
   private:
    std::vector<weight_type> weights_;
    template <class Iter> 
    void normalize_weights(Iter begin, Iter end){
        // check that weights are positive, not empty, sort and normalize the weights
        assert(std::distance(begin, end) > 0); 
        assert(std::all_of(begin, end, [](const weight_type& w_var){ return w_var.get_value() > 0; }));
        weight_value_t total = std::accumulate(begin, end, 0.0, 
            [] (int tmp_total, weight_type weight) { return tmp_total + weight.get_value(); });
        std::for_each(begin, end, [total](weight_type& w_var){w_var.set_value(w_var.get_value() / total); }); 
    }
};

template<typename Iter> Discrete(Iter,Iter) -> Discrete<typename Iter::value_type>;

} // namespace expr
} // namespace ppl

