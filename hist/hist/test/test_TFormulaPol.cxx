#include "gtest/gtest.h"
#include "TFormula.h"
#include "TF1.h"
#include "ROOT/TestSupport.hxx"
#include <cmath>

using namespace ROOT;

class TFormulaPolTest : public ::testing::Test {
protected:
    void SetUp() override {
        TestSupport::CheckDiagsRAII diags;
    }
};

TEST(TFormulaPolTest, BasicPolynomialConstruction) {
    TestSupport::CheckDiagsRAII diags;
    
    TFormula f1("f1", "pol1");
    EXPECT_EQ(f1.GetExpFormula(), TString("([p0]+[p1]*[p0]+[p1]*x)"));
    
    TFormula f2("f2", "pol2");
    EXPECT_EQ(f2.GetExpFormula(), TString("([p0]+[p1]*[p0]+[p1]*x+[p2]*TMath::Sq(x))"));
}

TEST(TFormulaPolTest, VariablePolynomials) {
    TestSupport::CheckDiagsRAII diags;
    
    TFormula f1("f1", "pol1(y,0)");
    EXPECT_EQ(f1.GetExpFormula(), TString("([p0]+[p1]*y)"));
    
    TFormula f2("f2", "pol2(z,0)");
    EXPECT_EQ(f2.GetExpFormula(), TString("([p0]+[p1]*z+[p2]*TMath::Sq(z))"));
}

TEST(TFormulaPolTest, ParameterPlaceholders) {
    TestSupport::CheckDiagsRAII diags;
    
    TFormula f1("f1", "pol1(x,[5])");
    EXPECT_EQ(f1.GetExpFormula(), TString("([p5]+[p6]*x)"));
}

TEST(TFormulaPolTest, NumericEvaluation) {
    TestSupport::CheckDiagsRAII diags;
    
    TF1 f1("f1", "pol1(x,0)");
    f1.SetParameters(1.0, 2.0);  // f(x) = 1 + 2x
    
    EXPECT_NEAR(f1.Eval(0.0), 1.0, 1e-10);
    EXPECT_NEAR(f1.Eval(1.0), 3.0, 1e-10);
}

TEST(TFormulaPolTest, ConstantPolynomial) {
    TestSupport::CheckDiagsRAII diags;
    
    TFormula f1("f1", "pol0(x,5)");
    EXPECT_EQ(f1.GetExpFormula(), TString("[p5]"));
}

TEST(TFormulaPolTest, CompoundExpressions) {
    TestSupport::CheckDiagsRAII diags;
    
    TFormula f1("f1", "pol1(x,0) + pol1(y,2)");
    EXPECT_EQ(f1.GetExpFormula(), TString("([p0]+[p1]*x)+([p2]+[p3]*y)"));
}