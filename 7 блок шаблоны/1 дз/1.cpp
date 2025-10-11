#include <cassert>
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

class SqlSelectQueryBuilder {
private:
    vector<string> columns_; // список столбцов
    string table_; // название таблицы
    map<string, string> where_conditions_; // условия wheress
public:
    SqlSelectQueryBuilder() = default;

    SqlSelectQueryBuilder& AddColumn(const std::string& column) noexcept {
        columns_.push_back(column);
        return *this;
    }

    SqlSelectQueryBuilder& AddColumns(const std::vector<std::string>& columns) noexcept {
        columns_.insert(columns_.end(), columns.begin(), columns.end());
        return *this;
    }

    SqlSelectQueryBuilder& AddFrom(const std::string& table) noexcept {
        table_ = table;
        return *this;
    }

    SqlSelectQueryBuilder& AddWhere(const std::string& key, const std::string& value) noexcept {
        where_conditions_[key] = value;
        return *this;
    }

    SqlSelectQueryBuilder& AddWhere(const std::map<std::string, std::string>& kv) noexcept {
        where_conditions_.insert(kv.begin(), kv.end());
        return *this;
    }

    std::string BuildQuery() const {
        std::string query = "SELECT ";

        if (columns_.empty()) {
            query += "*";
        } else {
            for (size_t i = 0; i < columns_.size(); ++i) {
                query += columns_[i];
                if (i < columns_.size() - 1) {
                    query += ", ";
                }
            }
        }

        if (!table_.empty()) {
            query += " FROM " + table_;
        }

        if (!where_conditions_.empty()) {
            query += " WHERE ";
            size_t i = 0;
            for (const auto& [key, value] : where_conditions_) {
                query += key + "=" + value;
                if (i < where_conditions_.size() - 1) {
                    query += " AND ";
                }
                ++i;
            }
        }
        query += ";";
        return query;
    }
};

int main() {
    SqlSelectQueryBuilder query_builder;
    query_builder.AddColumn("name").AddColumn("phone");
    query_builder.AddFrom("students");
    query_builder.AddWhere("id", "42").AddWhere("name", "John");

    string query = query_builder.BuildQuery();
    assert(query == "SELECT name, phone FROM students WHERE id=42 AND name=John;");

    cout << query << endl;

    // пример без столбцов
    SqlSelectQueryBuilder query_builder2;
    query_builder2.AddFrom("users").AddWhere("age", "25");
    cout << query_builder2.BuildQuery() << endl;

    return 0;
}