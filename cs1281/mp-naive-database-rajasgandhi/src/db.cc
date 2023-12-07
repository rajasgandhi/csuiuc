#include "db.hpp"

void Database::CreateTable(const std::string& table_name) {
  tables_.insert(std::make_pair(table_name, new DbTable()));
}

void Database::DropTable(const std::string& table_name) {
  if (!tables_.contains(table_name)) {
    throw std::runtime_error("invalid table_name!");
  }
  delete tables_[table_name];
  tables_.erase(table_name);
}

DbTable& Database::GetTable(const std::string& table_name) {
  return *(tables_.at(table_name));
}

Database::Database(const Database& rhs) {
  for (const auto& table : rhs.tables_) {
    tables_[table.first] = new DbTable(*table.second);
  }
}

Database& Database::operator=(const Database& rhs) {
  if (this == &rhs) {
    return *this;
  }

  for (const auto& entry : tables_) {
    delete entry.second;
  }
  tables_.clear();

  for (const auto& table : rhs.tables_) {
    tables_[table.first] = new DbTable(*table.second);
  }

  return *this;
}

Database::~Database() {
  for (const auto& k_table : tables_) {
    delete k_table.second;
  }
  tables_.clear();
}

std::ostream& operator<<(std::ostream& os, const Database& db) {
  // TODO: insert return statement here
  for (const auto& k_table : db.tables_) {
    os << k_table.first;
  }
  return os;
}
