#include <gtest/gtest.h>
#include <vector>

#include "../../src/calculator/tokenize.h"

void Equal(const std::vector<std::shared_ptr<IToken>>& fact, const std::vector<std::shared_ptr<IToken>>& expected) {
    ASSERT_EQ(fact.size(), expected.size());
    for (size_t i = 0; i < fact.size(); ++i) {
        ASSERT_TRUE(fact[i] == expected[i]);
    }
}

TEST(Tokenize, Empty) {
    {  // Empty string
        auto res = tokenize("");
        Equal(res, {});
    }

    {  // String of spaces
        auto res = tokenize("    ");
        Equal(res, {});
    }
}

TEST(Tokenize, Basic) {
    {  // one token
        auto res = tokenize("+");
        Equal(res, {std::make_shared<PlusToken>()});
    }

    {  // one token trailing spaces
        auto res = tokenize("   +  ");
        Equal(res, {std::make_shared<PlusToken>()});
    }

    {  // two tokens
        auto res = tokenize("+ +");
        Equal(res, {std::make_shared<PlusToken>(), std::make_shared<PlusToken>()});
    }

    {  // two tokens trailing spaces
        auto res = tokenize("   +   +   ");
        Equal(res, {std::make_shared<PlusToken>(), std::make_shared<PlusToken>()});
    }

    {  // solution has all required tokens
        auto res = tokenize("  +  - *  ,  /  log  abs (   sqrt 1  PI) ^ x     sin cos tan  cot E!  ");
        Equal(res, {std::make_shared<PlusToken>(), std::make_shared<MinusToken>(), std::make_shared<MultiplyToken>(), 
                    std::make_shared<CommaToken>(), std::make_shared<DivideToken>(), std::make_shared<LogToken>(), 
                    std::make_shared<AbsToken>(), std::make_shared<OpeningBracketToken>(), std::make_shared<SqrtToken>(), 
                    std::make_shared<NumberToken>(1), std::make_shared<NumberToken>(PI), std::make_shared<ClosingBracketToken>(),
                    std::make_shared<PowToken>(), std::make_shared<VariableToken>(), std::make_shared<SinToken>(), 
                    std::make_shared<CosToken>(), std::make_shared<TanToken>(), std::make_shared<CotToken>(),
                    std::make_shared<NumberToken>(E), std::make_shared<FactorialToken>()});
    }
}

/*TEST(Tokenize, Unknown) {
    {  // Simple case
        auto res = tokenize("  aba caba  # .  ");
        Equal(res, {UnknownToken{"aba"}, UnknownToken{"caba"}, UnknownToken{"#"}, UnknownToken{"."}});
    }

    {  // Mix of tokens
        auto res = tokenize(" ++ -- *+ absmin minmax *3 sqr1 ");
        Equal(res, {UnknownToken{"++"}, UnknownToken{"--"}, UnknownToken{"*+"}, UnknownToken{"absmin"},
                    UnknownToken{"minmax"}, UnknownToken{"*3"}, UnknownToken{"sqr1"}});
    }

    {  // Case sensitivity
        auto res = tokenize(" Min MAX AbS  sqR  ");
        Equal(res, {UnknownToken{"Min"}, UnknownToken{"MAX"}, UnknownToken{"AbS"}, UnknownToken{"sqR"}});
    }
}

TEST(Tokenize, Numbers) {
    ASSERT_FALSE(Token(NumberToken{11}) == Token(NumberToken{42}));

    {  // Simple case
        auto res = tokenize("  123 1  2 3 12  ");
        Equal(res, {NumberToken{123}, NumberToken{1}, NumberToken{2}, NumberToken{3}, NumberToken{12}});
    }

    {  // Positives and negatives
        auto res = tokenize("  +11  -33 -0  +0  11+  12- 23-4 1+1-1 ");
        Equal(res, {NumberToken{11}, NumberToken{-33}, NumberToken{0}, NumberToken{0}, UnknownToken{"11+"},
                    UnknownToken{"12-"}, UnknownToken{"23-4"}, UnknownToken{"1+1-1"}});
    }

    {  // Mixed
        auto res = tokenize(" + 11 - 12 + +11 - -12");
        Equal(res, {PlusToken{}, NumberToken{11}, MinusToken{}, NumberToken{12}, PlusToken{}, NumberToken{11},
                    MinusToken{}, NumberToken{-12}});
    }
}
*/
int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
