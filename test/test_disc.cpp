#include "gtest/gtest.h"
#include <autoppl/expression/distribution/discrete.hpp>
#include <autoppl/expr_builder.hpp>
#include <testutil/mock_types.hpp>


namespace ppl {


int main() {
    std::vector<MockVarExpr> weights {MockVarExpr{1}, MockVarExpr{2}, MockVarExpr{3}, MockVarExpr{4}}; 
    
    auto dist1 = Discrete(weights); 
    std::cout << dist.pdf(0) << std::end;
}


}
