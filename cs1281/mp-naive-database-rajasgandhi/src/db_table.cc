#include "db_table.hpp"

const unsigned int kRowGrowthRate = 2;

void DbTable::AddColumn(const std::pair<std::string, DataType>& col_desc) {
  if (col_descs_.size() == row_col_capacity_) {
    row_col_capacity_ *= kRowGrowthRate;
    for (auto& row : rows_) {
      void** new_row = new void*[row_col_capacity_];
      for (size_t i = 0; i < col_descs_.size(); ++i) {
        new_row[i] = row.second[i];
      }
      delete[] row.second;
      row.second = new_row;
    }
  }
  col_descs_.push_back(col_desc);
  for (auto& row : rows_) {
    switch (col_desc.second) {
    case DataType::kString:
      row.second[col_descs_.size() - 1] = new std::string("");
      break;
    case DataType::kInt:
      row.second[col_descs_.size() - 1] = new int(0);
      break;
    case DataType::kDouble:
      row.second[col_descs_.size() - 1] = new double(0.0);
      break;
    }
  }
}

void DbTable::DeleteColumnByIdx(unsigned int col_idx) {
  if (col_idx >= col_descs_.size() || col_idx < 0) {
    throw std::out_of_range("Column index out of range.");
  }

  if (col_descs_.size() == 1 && !rows_.empty()) {
    throw std::runtime_error(
        "A table with at least one row must have at least one column.");
  }

  for (auto& row : rows_) {
    switch (col_descs_.at(col_idx).second) {
    case DataType::kString:
      delete static_cast<std::string*>(row.second[col_idx]);
      break;
    case DataType::kInt:
      delete static_cast<int*>(row.second[col_idx]);
      break;
    case DataType::kDouble:
      delete static_cast<double*>(row.second[col_idx]);
      break;
    }
    for (size_t i = col_idx; i < col_descs_.size() - 1; ++i) {
      row.second[i] = row.second[i + 1];
    }
    row.second[col_descs_.size() - 1] = nullptr;
  }
  col_descs_.erase(col_descs_.begin() + col_idx);
}

void DbTable::AddRow(const std::initializer_list<std::string>& col_data) {
  if (col_data.size() != col_descs_.size()) {
    throw std::invalid_argument(
        "Number of items in col_data must match the number of columns.");
  }

  void** new_row = new void*[row_col_capacity_];

  unsigned int col_idx = 0;
  for (const std::string& data : col_data) {
    DataType type = col_descs_[col_idx].second;
    if (type == DataType::kString) {
      new_row[col_idx] = new std::string(data);
    } else if (type == DataType::kInt) {
      new_row[col_idx] = new int(std::stoi(data));
    } else if (type == DataType::kDouble) {
      new_row[col_idx] = new double(std::stod(data));
    }
    col_idx++;
  }

  rows_[next_unique_id_] = new_row;
  next_unique_id_++;
}

void DbTable::DeleteRowById(unsigned int id) {
  if (rows_.find(id) == rows_.end()) {
    throw std::out_of_range("Row with the specified ID not found.");
  }

  for (size_t i = 0; i < col_descs_.size(); ++i) {
    switch (col_descs_[i].second) {
    case DataType::kString:
      delete static_cast<std::string*>(rows_[id][i]);
      break;
    case DataType::kInt:
      delete static_cast<int*>(rows_[id][i]);
      break;
    case DataType::kDouble:
      delete static_cast<double*>(rows_[id][i]);
      break;
    }
  }
  delete[] rows_[id];
  rows_.erase(id);
}

DbTable::DbTable(const DbTable& rhs) {
  void** new_row = nullptr;
  next_unique_id_ = rhs.next_unique_id_;
  row_col_capacity_ = rhs.row_col_capacity_;
  col_descs_ = rhs.col_descs_;

  for (const auto& entry : rhs.rows_) {
    try {
      new_row = new void*[row_col_capacity_];

    } catch (std::runtime_error& e) {
      throw std::invalid_argument("invalid arg");
    }
    for (size_t i = 0; i < col_descs_.size(); ++i) {
      void* value_add = nullptr;
      DataType type = col_descs_[i].second;
      switch (type) {
      case DataType::kString:
        value_add = static_cast<void*>(
            new std::string(*static_cast<std::string*>(entry.second[i])));
        break;
      case DataType::kInt:
        value_add =
            static_cast<void*>(new int(*static_cast<int*>(entry.second[i])));
        break;
      case DataType::kDouble:
        value_add = static_cast<void*>(
            new double(*static_cast<double*>(entry.second[i])));
        break;
      }
      new_row[i] = value_add;
    }
    rows_.insert({entry.first, new_row});
  }
}

DbTable& DbTable::operator=(const DbTable& rhs) {
  if (this == &rhs) return *this;
  for (auto& row : rows_) {
    for (size_t i = 0; i < col_descs_.size(); ++i) {
      switch (col_descs_[i].second) {
      case DataType::kString:
        delete static_cast<std::string*>(row.second[i]);
        break;
      case DataType::kInt:
        delete static_cast<int*>(row.second[i]);
        break;
      case DataType::kDouble:
        delete static_cast<double*>(row.second[i]);
        break;
      }
    }
    delete[] row.second;
  }
  rows_.clear();
  next_unique_id_ = rhs.next_unique_id_;
  row_col_capacity_ = rhs.row_col_capacity_;
  col_descs_ = rhs.col_descs_;
  for (const auto& row : rhs.rows_) {
    void** new_row = new void*[row_col_capacity_];
    for (size_t i = 0; i < col_descs_.size(); ++i) {
      switch (col_descs_[i].second) {
      case DataType::kString:
        new_row[i] = new std::string(*static_cast<std::string*>(row.second[i]));
        break;
      case DataType::kInt:
        new_row[i] = new int(*static_cast<int*>(row.second[i]));
        break;
      case DataType::kDouble:
        new_row[i] = new double(*static_cast<double*>(row.second[i]));
        break;
      }
    }
    rows_[row.first] = new_row;
  }
  return *this;
}

DbTable::~DbTable() {
  for (auto& row : rows_) {
    for (size_t i = 0; i < col_descs_.size(); ++i) {
      switch (col_descs_[i].second) {
      case DataType::kString:
        delete static_cast<std::string*>(row.second[i]);
        break;
      case DataType::kInt:
        delete static_cast<int*>(row.second[i]);
        break;
      case DataType::kDouble:
        delete static_cast<double*>(row.second[i]);
        break;
      }
    }
    delete[] row.second;
  }
}

std::ostream& operator<<(std::ostream& os, const DbTable& table) {
  for (size_t i = 0; i < table.col_descs_.size(); ++i) {
    os << table.col_descs_[i].first << "(";
    if (table.col_descs_[i].second == DataType::kString) {
      os << "std::string)";
    } else if (table.col_descs_[i].second == DataType::kInt) {
      os << "int)";
    } else if (table.col_descs_[i].second == DataType::kDouble) {
      os << "double)";
    }
    if (i < table.col_descs_.size() - 1) {
      os << ", ";
    } else {
      os << "\n";
    }
  }

  for (const auto& entry : table.rows_) {
    void** row_array = entry.second;
    for (size_t col_idx = 0; col_idx < table.col_descs_.size(); col_idx++) {
      DataType type = table.col_descs_[col_idx].second;
      switch (type) {
      case DataType::kString:
        os << *(static_cast<std::string*>(row_array[col_idx]));
        break;
      case DataType::kInt:
        os << *(static_cast<int*>(row_array[col_idx]));
        break;
      case DataType::kDouble:
        os << *(static_cast<double*>(row_array[col_idx]));
        break;
      }
      if (col_idx < table.col_descs_.size() - 1) {
        os << ", ";
      }
    }
    os << std::endl;
  }

  return os;
}
