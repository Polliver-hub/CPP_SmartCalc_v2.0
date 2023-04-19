#include "controller.h"

namespace s21 {
Controller::Controller() {};
Controller::~Controller() {};

Model::TypeInputError Controller::pushBack(char symbol) {
  return model.PushBack(symbol);
}

std::string Controller::ToString() {
    return model.ToString();
}

bool Controller::IsValid() {
    return model.IsValid();
}

Model::CalculationError Controller::SolveEquation(double *result, double x) {
    return model.SolveEquation(result,x);
}

void Controller::Clear() {
    model.Clear();
}

bool Controller::AddNewExp(std::string exp) {
    return model.AddNewExp(exp);
};

}  // namespace s21
