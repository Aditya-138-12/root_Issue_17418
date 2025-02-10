#include "gtest/gtest.h"
#include "TF1.h"
#include "ROOT/TestSupport.hxx"
#include <cmath>

#include "TFormula.h"

using namespace ROOT;

// Test that autoloading works (ROOT-9840)
TEST(TFormula, Interp)
{
  TFormula f("func", "TGeoBBox::DeclFileLine()");
}

// Test for TFormula Extended syntax support
TEST(TFormulaPolTest, BasicPolynomialConstruction) {
    
    TFormula f1("f1", "pol1");
    EXPECT_EQ(f1.GetExpFormula(), TString("([p0]+[p1]*x)"));
    
    TFormula f2("f2", "pol2");
    EXPECT_EQ(f2.GetExpFormula(), TString("([p0]+[p1]*x+[p2]*TMath::Sq(x))"));
}

TEST(TFormulaPolTest, VariablePolynomials) {
    
    TFormula f1("f1", "pol1(y,0)");
    EXPECT_EQ(f1.GetExpFormula(), TString("([p0]+[p1]*y)"));
    
    TFormula f2("f2", "pol2(z,0)");
    EXPECT_EQ(f2.GetExpFormula(), TString("([p0]+[p1]*z+[p2]*TMath::Sq(z))"));
}

TEST(TFormulaPolTest, ParameterPlaceholders) {
    
    TFormula f1("f1", "pol1(x,[5])");
    EXPECT_EQ(f1.GetExpFormula(), TString("([p5]+[p6]*x)"));
}

TEST(TFormulaPolTest, NumericEvaluation) {
    
    TF1 f1("f1", "pol1(x,0)");
    f1.SetParameters(1.0, 2.0);  // f(x) = 1 + 2x
    
    EXPECT_NEAR(f1.Eval(0.0), 1.0, 1e-10);
    EXPECT_NEAR(f1.Eval(1.0), 3.0, 1e-10);
}

TEST(TFormulaPolTest, ConstantPolynomial) {
    
    TFormula f1("f1", "pol0(x,5)");
    EXPECT_EQ(f1.GetExpFormula(), TString("[p5]"));
}

TEST(TFormulaPolTest, CompoundExpressions) {
    
    TFormula f1("f1", "pol1(x,0) + pol1(y,2)");
    EXPECT_EQ(f1.GetExpFormula(), TString("([p0]+[p1]*x)+([p2]+[p3]*y)"));
}