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
    map<string, string> where_conditions_; // условия where
public:
    SqlSelectQueryBuilder() = default;

    SqlSelectQueryBuilder& AddColumn(const string& column) noexcept {
        columns_.push_back(column);
        return *this;
    }

    SqlSelectQueryBuilder& AddColumns(const vector<string>& columns) noexcept {
        columns_.insert(columns_.end(), columns.begin(), columns.end());
        return *this;
    }

    SqlSelectQueryBuilder& AddFrom(const string& table) noexcept {
        table_ = table;
        return *this;
    }

    SqlSelectQueryBuilder& AddWhere(const string& key, const string& value) noexcept {
        where_conditions_[key] = value;
        return *this;
    }

    SqlSelectQueryBuilder& AddWhere(const map<string, string>& kv) noexcept {
        where_conditions_.insert(kv.begin(), kv.end());
        return *this;
    }

    string BuildQuery() const {
        string query = "SELECT ";

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
    
    SqlSelectQueryBuilder query_builder2;
    vector<string> columns = {"name", "phone", "age"};
    query_builder2.AddColumns(columns);
    query_builder2.AddFrom("students");
    map<string, string> conditions = {{"id", "42"}, {"name", "John"}};
    query_builder2.AddWhere(conditions);

    string query2 = query_builder2.BuildQuery();
    assert(query2 == "SELECT name, phone, age FROM students WHERE id=42 AND name=John;");

    cout << query2 << endl;

    // пример без столбцов
    SqlSelectQueryBuilder query_builder3;
    query_builder3.AddFrom("users").AddWhere({{"age", "25"}, {"city", "Moscow"}});
    cout << query_builder3.BuildQuery() << endl;

    return 0;
}