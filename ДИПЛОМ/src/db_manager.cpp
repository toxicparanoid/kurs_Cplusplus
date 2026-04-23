#include "db_manager.h"

DBManager::DBManager(const std::string& host,
                     const std::string& port,
                     const std::string& dbname,
                     const std::string& user,
                     const std::string& password)
{
    conn_string = "host=" + host +
                  " port=" + port +
                  " dbname=" + dbname +
                  " user=" + user +
                  " password=" + password;
}

bool DBManager::initialize() {
    try {
        pqxx::connection c(conn_string);
        if (!c.is_open()) {
            std::cerr << "[DB] Failed to open connection for initialization.\n";
            return false;
        }
        std::cout << "[DB] Initializing database schema...\n";
        return create_tables();
    } catch (const std::exception& e) {
        std::cerr << "[DB] Initialization error: " << e.what() << std::endl;
        return false;
    }
}

bool DBManager::create_tables() {
    try {
        pqxx::connection c(conn_string);
        pqxx::work txn(c);

        txn.exec0(R"(
            CREATE TABLE IF NOT EXISTS documents (
                id SERIAL PRIMARY KEY,
                filename TEXT UNIQUE NOT NULL
            );
        )");

        txn.exec0(R"(
            CREATE TABLE IF NOT EXISTS words (
                id SERIAL PRIMARY KEY,
                word TEXT UNIQUE NOT NULL
            );
        )");

        txn.exec0(R"(
            CREATE TABLE IF NOT EXISTS word_documents (
                id SERIAL PRIMARY KEY,
                document_id INT REFERENCES documents(id),
                word_id INT REFERENCES words(id),
                frequency INT NOT NULL,
                UNIQUE(document_id, word_id)
            );
        )");

        txn.commit();
        std::cout << "[DB] Tables created successfully.\n";
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[DB] Table creation error: " << e.what() << std::endl;
        return false;
    }
}

bool DBManager::clear_tables() {
    try {
        pqxx::connection c(conn_string);
        pqxx::work txn(c);
        txn.exec0("TRUNCATE TABLE word_documents, words, documents RESTART IDENTITY CASCADE;");
        txn.commit();
        std::cout << "[DB] Tables were cleared.\n";
        return true;
    } catch (const std::exception& e) {
        std::cerr << "[DB] Clear tables error: " << e.what() << std::endl;
        return false;
    }
}

int DBManager::insert_document(const std::string& filename) {
    try {
        pqxx::connection c(conn_string);
        pqxx::work txn(c);
        txn.exec0("INSERT INTO documents (filename) VALUES (" + txn.quote(filename) + ") ON CONFLICT (filename) DO NOTHING;");
        auto res = txn.exec("SELECT id FROM documents WHERE filename = " + txn.quote(filename) + ";");
        txn.commit();
        if (!res.empty()) {
            return res[0][0].as<int>();
        }
        return -1;
    } catch (const std::exception& e) {
        std::cerr << "[DB] insert_document error: " << e.what() << std::endl;
        return -1;
    }
}

int DBManager::insert_word(const std::string& word) {
    try {
        pqxx::connection c(conn_string);
        pqxx::work txn(c);
        txn.exec0("INSERT INTO words (word) VALUES (" + txn.quote(word) + ") ON CONFLICT (word) DO NOTHING;");
        auto res = txn.exec("SELECT id FROM words WHERE word = " + txn.quote(word) + ";");
        txn.commit();
        if (!res.empty()) {
            return res[0][0].as<int>();
        }
        return -1;
    } catch (const std::exception& e) {
        std::cerr << "[DB] insert_word error: " << e.what() << std::endl;
        return -1;
    }
}

void DBManager::insert_word_frequency(int document_id, int word_id, int freq) {
    try {
        pqxx::connection c(conn_string);
        pqxx::work txn(c);
        txn.exec0("INSERT INTO word_documents (document_id, word_id, frequency) VALUES (" +
                  txn.quote(document_id) + ", " + txn.quote(word_id) + ", " + txn.quote(freq) + ")"
                  " ON CONFLICT (document_id, word_id) DO UPDATE SET frequency = word_documents.frequency + " + txn.quote(freq) + ";");
        txn.commit();
    } catch (const std::exception& e) {
        std::cerr << "[DB] insert_word_frequency error: " << e.what() << std::endl;
    }
}

std::vector<std::pair<std::string, int>> DBManager::search(const std::vector<std::string>& words) {
    std::vector<std::pair<std::string, int>> results;
    if (words.empty()) return results;

    try {
        pqxx::connection c(conn_string);
        pqxx::work txn(c);

        std::stringstream in_list;
        for (size_t i = 0; i < words.size(); ++i) {
            if (i > 0) in_list << ",";
            in_list << txn.quote(words[i]);
        }

        std::string sql = R"(
            SELECT d.filename, SUM(wd.frequency) as total_freq
            FROM word_documents wd
            JOIN words w ON wd.word_id = w.id
            JOIN documents d ON wd.document_id = d.id
            WHERE w.word IN ()" + in_list.str() + R"()
            GROUP BY d.filename
            HAVING COUNT(DISTINCT w.word) = )" + txn.quote(static_cast<int>(words.size())) + R"(
            ORDER BY total_freq DESC
            LIMIT 10;
        )";

        auto res = txn.exec(sql);
        txn.commit();

        for (auto const& row : res) {
            std::string filename = row["filename"].as<std::string>();
            int freq = row["total_freq"].as<int>();
            results.emplace_back(filename, freq);
        }
    } catch (const std::exception& e) {
        std::cerr << "[DB] Search error: " << e.what() << std::endl;
    }
    return results;
}