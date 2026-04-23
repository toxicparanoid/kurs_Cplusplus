#pragma once
#include <string>
#include <iostream>
#include <unordered_map>
#include <pqxx/pqxx>
#include <sstream>

class DBManager {
public:
    DBManager(const std::string& host,
              const std::string& port,
              const std::string& dbname,
              const std::string& user,
              const std::string& password);

    bool initialize();                // создаёт таблицы, если их ещё нет
    bool clear_tables();              // полностью очищает таблицы (для переиндексации)
    int  insert_document(const std::string& filename); // возвращает id документа
    int  insert_word(const std::string& word);         // возвращает id слова
    void insert_word_frequency(int document_id, int word_id, int freq);
    std::vector<std::pair<std::string, int>> search(const std::vector<std::string>& words);

private:
    std::string conn_string;
    bool create_tables();
};