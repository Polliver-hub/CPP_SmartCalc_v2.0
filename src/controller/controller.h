#ifndef SRC_CONTROLLER_CONTROLLER_H_
#define SRC_CONTROLLER_CONTROLLER_H_

#include "../model/model.h"

namespace s21 {
class Controller {
 public:
  Controller();
  ~Controller();

  Model::TypeInputError pushBack(char symbol);

  std::string ToString();

  bool IsValid();

  Model::CalculationError SolveEquation(double *result, double x);

  void Clear();

  bool AddNewExp(std::string exp);

 private:
  Model model;
};
}  // namespace s21

#endif  // SRC_CONTROLLER_CONTROLLER_H_
