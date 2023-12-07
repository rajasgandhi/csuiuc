#include <iostream>

#include "db.hpp"
#include "db_table.hpp"

int main() {
  // write informal tests here
  DbTable dbt = DbTable();
  dbt.AddRow(
      std::initializer_list<std::string>({"instructors", "staff", "students"}));
  std::cout << dbt << std::endl;
}