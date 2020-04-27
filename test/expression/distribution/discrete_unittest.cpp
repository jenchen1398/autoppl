#include <autoppl/expression/distribution/discrete.hpp>
#include <testutil/mock_types.hpp>
#include <testutil/sample_tools.hpp>
#include <cmath>
#include <array>

#include "gtest/gtest.h"

namespace ppl {
namespace expr {

struct discrete_dist_fixture : ::testing::Test {
protected:
    using value_t = typename MockVarExpr::value_t;

    std::vector<MockVarExpr> weights {MockVarExpr{0.1}, MockVarExpr{0.2}, MockVarExpr{0.3}, MockVarExpr{0.4}}; 
   
    Discrete<MockVarExpr> dist1 =  {MockVarExpr{0.1}, MockVarExpr{0.2}, MockVarExpr{0.3}, MockVarExpr{0.4}}; 
    Discrete<MockVarExpr> dist2;
    Discrete<MockVarExpr> dist3 = Discrete(weights.begin(), weights.end());
};

TEST_F(discrete_dist_fixture, ctor){
    static_assert(util::assert_is_dist_expr_v<Discrete<MockVarExpr>>);
}

TEST_F(discrete_dist_fixture, discrete_check_params) {
    EXPECT_DOUBLE_EQ(dist1.weights(0), static_cast<value_t>(weights[0]));
    EXPECT_DOUBLE_EQ(dist1.weights(1), static_cast<value_t>(weights[1]));
    EXPECT_DOUBLE_EQ(dist1.weights(2), static_cast<value_t>(weights[2]));
    EXPECT_DOUBLE_EQ(dist1.weights(3), static_cast<value_t>(weights[3]));

    EXPECT_DOUBLE_EQ(dist3.weights(0), static_cast<value_t>(weights[0]));
    EXPECT_DOUBLE_EQ(dist3.weights(1), static_cast<value_t>(weights[1]));
    EXPECT_DOUBLE_EQ(dist3.weights(2), static_cast<value_t>(weights[2]));
    EXPECT_DOUBLE_EQ(dist3.weights(3), static_cast<value_t>(weights[3]));
}

TEST_F(discrete_dist_fixture, default_cstor_test){
    EXPECT_DOUBLE_EQ(dist2.weights(0), 1.0);
    EXPECT_DOUBLE_EQ(dist2.pdf(0), 1.0);
}

TEST_F(discrete_dist_fixture, sanity_Discrete_test) {
    EXPECT_EQ(dist1.weights(0), weights[0]);
    EXPECT_EQ(dist1.weights(1), weights[1]);
    EXPECT_EQ(dist1.weights(2), weights[2]);
    EXPECT_EQ(dist1.weights(3), weights[3]);
}

TEST_F(discrete_dist_fixture, simple_Discrete) {
    EXPECT_DOUBLE_EQ(dist1.pdf(0), dist1.weights(0));
    EXPECT_DOUBLE_EQ(dist1.pdf(1), dist1.weights(1));
    EXPECT_DOUBLE_EQ(dist1.pdf(2), dist1.weights(2));
    EXPECT_DOUBLE_EQ(dist1.pdf(3), dist1.weights(3));
    
}

TEST_F(discrete_dist_fixture, Discrete_sampling) {
    std::random_device rd{};
    std::mt19937 gen{rd()};
    
    for (int i = 0; i < 100; i++) {
        int sample = dist1.sample(gen);
        EXPECT_TRUE(sample == 0 || sample == 1 || sample == 2 || sample == 3);
    }
}

TEST_F(discrete_dist_fixture, sanity_Discrete_iter_test) {
    EXPECT_EQ(dist3.weights(0), weights[0]);
    EXPECT_EQ(dist3.weights(1), weights[1]);
    EXPECT_EQ(dist3.weights(2), weights[2]);
    EXPECT_EQ(dist3.weights(3), weights[3]);
}

TEST_F(discrete_dist_fixture, simple_Discrete_iter) {
    EXPECT_DOUBLE_EQ(dist3.pdf(0), dist3.weights(0));
    EXPECT_DOUBLE_EQ(dist3.pdf(1), dist3.weights(1));
    EXPECT_DOUBLE_EQ(dist3.pdf(2), dist3.weights(2));
    EXPECT_DOUBLE_EQ(dist3.pdf(3), dist3.weights(3));
    
}

TEST_F(discrete_dist_fixture, Discrete_sampling_iter) {
    std::random_device rd{};
    std::mt19937 gen{rd()};
    
    for (int i = 0; i < 100; i++) {
        int sample = dist3.sample(gen);
        EXPECT_TRUE(sample == 0 || sample == 1 || sample == 2 || sample == 3);
    }
}
} // namespace expr
} // namespace ppl
