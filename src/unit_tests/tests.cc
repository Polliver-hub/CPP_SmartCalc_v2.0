#include <gtest/gtest.h>

#include "../model/model.h"

TEST(SmartCalc, empty_valid) {
  s21::Model calc;
  EXPECT_TRUE(calc.Empty());
  EXPECT_TRUE(calc.IsValid());
}

TEST(SmartCalc, push_back_digit_and_valid) {
  s21::Model calc;
  calc.PushBack('5');
  EXPECT_FALSE(calc.Empty());
  EXPECT_TRUE(calc.IsValid());
}

TEST(SmartCalc, clear) {
  s21::Model calc;
  calc.PushBack('5');
  EXPECT_FALSE(calc.Empty());
  EXPECT_TRUE(calc.IsValid());
}

TEST(SmartCalc, solve_one_digit) {
  s21::Model calc;
  calc.PushBack('5');
  EXPECT_TRUE(calc.IsValid());
  double res{};
  calc.SolveEquation(&res, 0);
  EXPECT_EQ(res, 5);
}

TEST(SmartCalc, pop_back) {
  s21::Model calc;
  calc.PushBack('5');
  EXPECT_TRUE(calc.IsValid());
  EXPECT_FALSE(calc.Empty());
  calc.PopBack();
  EXPECT_TRUE(calc.IsValid());
  EXPECT_TRUE(calc.Empty());
}

TEST(SmartCalc, empty_to_string) {
  s21::Model calc;
  calc.PushBack('5');
  EXPECT_TRUE(calc.IsValid());
  EXPECT_FALSE(calc.Empty());
  EXPECT_STREQ(calc.ToString().c_str(), "5");
}

TEST(SmartCalc, addNewExp_valid) {
  s21::Model calc;
  calc.AddNewExp("5+5+5");
  EXPECT_TRUE(calc.IsValid());
  EXPECT_FALSE(calc.Empty());
  EXPECT_STREQ(calc.ToString().c_str(), "5+5+5");
}

TEST(SmartCalc, add_new_exp_no_valid) {
  s21::Model calc;
  calc.AddNewExp("5+5+5-");
  EXPECT_FALSE(calc.IsValid());
  EXPECT_FALSE(calc.Empty());
}

TEST(SmartCalc, solve_and_add_exp) {
  s21::Model calc;
  calc.AddNewExp("5+5+5*5");
  EXPECT_TRUE(calc.IsValid());
  EXPECT_FALSE(calc.Empty());
  double res{};
  calc.SolveEquation(&res, 0);
  EXPECT_DOUBLE_EQ(35, res);
}

TEST(SmartCalc, solve_and_add_exp_with_x) {
  s21::Model calc;
  calc.AddNewExp("x/5+5+5*5");
  EXPECT_TRUE(calc.IsValid());
  EXPECT_FALSE(calc.Empty());
  double res{};
  calc.SolveEquation(&res, 5);
  EXPECT_DOUBLE_EQ(31, res);
}

TEST(SmartCalc, solve_and_add_exp_with_x2) {
  s21::Model calc;
  calc.AddNewExp("x/(5+5+5+5)");
  EXPECT_TRUE(calc.IsValid());
  EXPECT_FALSE(calc.Empty());
  double res{};
  calc.SolveEquation(&res, 40);
  EXPECT_DOUBLE_EQ(2, res);
}

TEST(SmartCalc, solve_exp) {
  s21::Model calc;
  calc.AddNewExp("2^1^45");
  EXPECT_TRUE(calc.IsValid());
  EXPECT_FALSE(calc.Empty());
  double res{};
  EXPECT_EQ(calc.SolveEquation(&res, 0), 0);
  EXPECT_DOUBLE_EQ(2, res);
}

TEST(SmartCalc, solve_exp2) {
  s21::Model calc;
  calc.AddNewExp("s(3,14/5)*c(20)-t(e^2)");
  EXPECT_TRUE(calc.IsValid());
  EXPECT_FALSE(calc.Empty());
  double res{};
  EXPECT_EQ(calc.SolveEquation(&res, 0), 0);
  EXPECT_DOUBLE_EQ(-1.7538672115754665, res);
}

TEST(SmartCalc, solve_exp3) {
  s21::Model calc;
  calc.AddNewExp("i(3.14/5)*o(e/4)-a(e^2)");
  EXPECT_TRUE(calc.IsValid());
  EXPECT_FALSE(calc.Empty());
  double res{};
  EXPECT_EQ(calc.SolveEquation(&res, 0), 0);
  EXPECT_DOUBLE_EQ(-0.87705679937582604, res);
}

TEST(SmartCalc, solve_exp4) {
  s21::Model calc;
  calc.AddNewExp("1+2--3^0");
  EXPECT_TRUE(calc.IsValid());
  EXPECT_FALSE(calc.Empty());
  double res{};
  EXPECT_EQ(calc.SolveEquation(&res, 0), 0);
  EXPECT_DOUBLE_EQ(2, res);
}

TEST(SmartCalc, solve_exp_err) {
  s21::Model calc;
  calc.AddNewExp("q(-1)");
  EXPECT_TRUE(calc.IsValid());
  EXPECT_FALSE(calc.Empty());
  double res{};
  EXPECT_TRUE(calc.SolveEquation(&res, 0) > 0);
}

TEST(SmartCalc, solve_exp_err2) {
  s21::Model calc;
  calc.AddNewExp("i(2)");
  EXPECT_TRUE(calc.IsValid());
  EXPECT_FALSE(calc.Empty());
  double res{};
  EXPECT_TRUE(calc.SolveEquation(&res, 0) > 0);
}

TEST(SmartCalc, solve_exp_err3) {
  s21::Model calc;
  calc.AddNewExp("o(2)");
  EXPECT_TRUE(calc.IsValid());
  EXPECT_FALSE(calc.Empty());
  double res{};
  EXPECT_TRUE(calc.SolveEquation(&res, 0) > 0);
}

TEST(SmartCalc, solve_exp_err4) {
  s21::Model calc;
  calc.AddNewExp("l(-1)");
  EXPECT_TRUE(calc.IsValid());
  EXPECT_FALSE(calc.Empty());
  double res{};
  EXPECT_TRUE(calc.SolveEquation(&res, 0) > 0);
}

TEST(SmartCalc, solve_exp_err5) {
  s21::Model calc;
  calc.AddNewExp("n(-1)");
  EXPECT_TRUE(calc.IsValid());
  EXPECT_FALSE(calc.Empty());
  double res{};
  EXPECT_TRUE(calc.SolveEquation(&res, 0) > 0);
}

TEST(SmartCalc, solve_exp_err6) {
  s21::Model calc;
  calc.AddNewExp("1/0");
  EXPECT_TRUE(calc.IsValid());
  EXPECT_FALSE(calc.Empty());
  double res{};
  EXPECT_TRUE(calc.SolveEquation(&res, 0) > 0);
}

TEST(SmartCalc, solve_exp_err7) {
  s21::Model calc;
  calc.AddNewExp("1m0");
  EXPECT_TRUE(calc.IsValid());
  EXPECT_FALSE(calc.Empty());
  double res{};
  EXPECT_TRUE(calc.SolveEquation(&res, 0) > 0);
}

TEST(SmartCalc, solve_exp5) {
  s21::Model calc;
  calc.AddNewExp("aq128^c25");
  EXPECT_TRUE(calc.IsValid());
  EXPECT_FALSE(calc.Empty());
  double res{};
  calc.SolveEquation(&res, 0);
  EXPECT_DOUBLE_EQ(res, 1.4775093327295221);
}

TEST(SmartCalc, solve_exp6) {
  s21::Model calc;
  calc.AddNewExp("nq6m4");
  EXPECT_TRUE(calc.IsValid());
  EXPECT_FALSE(calc.Empty());
  double res{};
  calc.SolveEquation(&res, 0);
  EXPECT_DOUBLE_EQ(res, 0.8958797346140275);
}

TEST(SmartCalc, solve_exp7) {
  s21::Model calc;
  calc.AddNewExp("+2,5*(-2)");
  EXPECT_TRUE(calc.IsValid());
  EXPECT_FALSE(calc.Empty());
  double res{};
  calc.SolveEquation(&res, 0);
  EXPECT_DOUBLE_EQ(res, -5);
}

TEST(SmartCalc, solve_exp8) {
  s21::Model calc;
  calc.AddNewExp("l256");
  EXPECT_TRUE(calc.IsValid());
  EXPECT_FALSE(calc.Empty());
  double res{};
  calc.SolveEquation(&res, 0);
  EXPECT_DOUBLE_EQ(res, 2.4082399653118496);
}

TEST(SmartCalc, exp_err) {
  s21::Model calc;
  EXPECT_FALSE(calc.AddNewExp("1..2"));
  calc.SolveEquation(nullptr, 0);
}

TEST(SmartCalc, exp_err2) {
  s21::Model calc;
  EXPECT_FALSE(calc.AddNewExp("(*5)"));
}

TEST(SmartCalc, exp_err3) {
  s21::Model calc;
  EXPECT_FALSE(calc.AddNewExp("(5**3)"));
}

TEST(SmartCalc, exp_err4) {
  s21::Model calc;
  EXPECT_FALSE(calc.AddNewExp("5*3)"));
}

TEST(SmartCalc, exp_err5) {
  s21::Model calc;
  EXPECT_FALSE(calc.AddNewExp("(5*)"));
}

TEST(SmartCalc, exp_true) {
  s21::Model calc;
  EXPECT_TRUE(calc.AddNewExp("./5"));
}

TEST(SmartCalc, exp_true2) {
  s21::Model calc;
  EXPECT_TRUE(calc.AddNewExp("/5"));
}

TEST(SmartCalc, exp_true3) {
  s21::Model calc;
  EXPECT_TRUE(calc.AddNewExp("5x5s5.(4.)5(4)"));
}

TEST(SmartCalc, pop_back2) {
  s21::Model calc;
  EXPECT_TRUE(calc.AddNewExp("(4)"));
  calc.PopBack();
  calc.PopBack();
  calc.PopBack();
  EXPECT_TRUE(calc.Empty());
}

TEST(SmartCalc, to_string) {
  s21::Model calc;
  double res = 4;
  calc.SolveEquation(&res, 0);
  EXPECT_EQ(res, 0);
  EXPECT_TRUE(calc.AddNewExp("lnqsicota0.5m"));
  EXPECT_STREQ("loglnsqrtsinasincosacostanatan0.5mod", calc.ToString().c_str());
}

TEST(SmartCalc, to_string_empty) {
  s21::Model calc;
  double res = 4;
  calc.SolveEquation(&res, 0);
  EXPECT_EQ(res, 0);
  EXPECT_STREQ("0", calc.ToString().c_str());
}
