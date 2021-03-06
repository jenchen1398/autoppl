#include "gtest/gtest.h"
#include <autoppl/expression/variable/variable_viewer.hpp>
#include <testutil/mock_types.hpp>

namespace ppl {
namespace expr {

struct variable_viewer_fixture : ::testing::Test
{
protected:
    using value_t = typename MockParam::value_t;
    MockParam var;
    VariableViewer<MockParam> x = var;
};

TEST_F(variable_viewer_fixture, ctor)
{
    static_assert(util::assert_is_var_expr_v<VariableViewer<MockParam>>);
}

TEST_F(variable_viewer_fixture, convertible_value)
{
    var.set_value(1.);
    EXPECT_EQ(x.get_value(0), 1.);

    // Tests if viewer correctly reflects any changes that happened in var.
    var.set_value(-3.14);
    EXPECT_EQ(x.get_value(0), -3.14);
}

} // namespace expr
} // namespace ppl
