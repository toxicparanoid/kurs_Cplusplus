#include <iostream>
#include <pqxx/pqxx>
#include <vector>
#include <sstream>
using namespace std;
using namespace pqxx;

class neto_db {
private:
    string dbname;
    string port;
    string host;
    string user;
    string password;
    connection conn;

    string escape_string(const string& str) {
        string escaped;
        for (char c : str) {
            if (c == '\'') escaped += '\'';
            escaped += c;
        }
        return escaped;
    }

public:
    neto_db(const string& _name, const string& _port, const string& _host,
        const string& _user, const string& _password) :
        dbname("dbname=" + _name + " "),
        port("port=" + _port + " "),
        host("host=" + _host + " "),
        user("user=" + _user + " "),
        password("password=" + _password + " "),
        conn(host + port + dbname + user + password)
    {
        if (!conn.is_open()) {
            throw runtime_error("Не удалось подключиться к БД");
        }
    }

    void create_tables() {
        try {
            work txn(conn);

            txn.exec("CREATE TABLE IF NOT EXISTS clients ("
                "id SERIAL PRIMARY KEY, "
                "first_name VARCHAR(50) NOT NULL, "
                "last_name VARCHAR(50) NOT NULL, "
                "email VARCHAR(100) UNIQUE)");

            txn.exec("CREATE TABLE IF NOT EXISTS client_phones ("
                "id SERIAL PRIMARY KEY, "
                "client_id INTEGER REFERENCES clients(id) ON DELETE CASCADE, "
                "phone VARCHAR(20) UNIQUE)");

            txn.commit();
            cout << "Таблицы успешно созданы" << endl;
        }
        catch (const exception& e) {
            cerr << "Ошибка при создании таблиц: " << e.what() << endl;
        }
    }

    void add_client(const string& first_name, const string& last_name, const string& email) {
        try {
            work txn(conn);
            string query = "INSERT INTO clients (first_name, last_name, email) VALUES ('" +
                escape_string(first_name) + "', '" +
                escape_string(last_name) + "', '" +
                escape_string(email) + "')";
            txn.exec(query);
            txn.commit();
            cout << "Клиент успешно добавлен" << endl;
        }
        catch (const exception& e) {
            cerr << "Ошибка при добавлении клиента: " << e.what() << endl;
        }
    }

    void add_phone(int client_id, const string& phone) {
        try {
            work txn(conn);
            string query = "INSERT INTO client_phones (client_id, phone) VALUES (" +
                to_string(client_id) + ", '" +
                escape_string(phone) + "')";
            txn.exec(query);
            txn.commit();
            cout << "Телефон успешно добавлен" << endl;
        }
        catch (const exception& e) {
            cerr << "Ошибка при добавлении телефона: " << e.what() << endl;
        }
    }

    void update_client(int client_id, const string& first_name = "",
        const string& last_name = "", const string& email = "") {
        try {
            work txn(conn);
            string query = "UPDATE clients SET ";
            vector<string> updates;

            if (!first_name.empty())
                updates.push_back("first_name = '" + escape_string(first_name) + "'");
            if (!last_name.empty())
                updates.push_back("last_name = '" + escape_string(last_name) + "'");
            if (!email.empty())
                updates.push_back("email = '" + escape_string(email) + "'");

            if (!updates.empty()) {
                for (size_t i = 0; i < updates.size(); ++i) {
                    if (i != 0) query += ", ";
                    query += updates[i];
                }
                query += " WHERE id = " + to_string(client_id);
                txn.exec(query);
                txn.commit();
                cout << "Данные клиента обновлены" << endl;
            }
            else {
                cout << "Нечего обновлять" << endl;
            }
        }
        catch (const exception& e) {
            cerr << "Ошибка при обновлении клиента: " << e.what() << endl;
        }
    }

    void delete_phone(const string& phone) {
        try {
            work txn(conn);
            string query = "DELETE FROM client_phones WHERE phone = '" +
                escape_string(phone) + "'";
            txn.exec(query);
            txn.commit();
            cout << "Телефон успешно удален" << endl;
        }
        catch (const exception& e) {
            cerr << "Ошибка при удалении телефона: " << e.what() << endl;
        }
    }

    void delete_client(int client_id) {
        try {
            work txn(conn);
            string query = "DELETE FROM clients WHERE id = " + to_string(client_id);
            txn.exec(query);
            txn.commit();
            cout << "Клиент успешно удален" << endl;
        }
        catch (const exception& e) {
            cerr << "Ошибка при удалении клиента: " << e.what() << endl;
        }
    }

    void find_client(const string& search_term) {
        try {
            work txn(conn);
            string escaped_term = escape_string(search_term);

            string query =
                "SELECT c.id, c.first_name, c.last_name, c.email, p.phone "
                "FROM clients c "
                "LEFT JOIN client_phones p ON c.id = p.client_id "
                "WHERE c.first_name LIKE '%" + escaped_term + "%' "
                "OR c.last_name LIKE '%" + escaped_term + "%' "
                "OR c.email LIKE '%" + escaped_term + "%' "
                "OR p.phone LIKE '%" + escaped_term + "%'";

            result res = txn.exec(query);

            if (res.empty()) {
                cout << "Клиенты не найдены" << endl;
                return;
            }

            cout << "Найденные клиенты:" << endl;
            int current_client = -1;
            for (auto row : res) {
                int client_id = row["id"].as<int>();

                if (client_id != current_client) {
                    current_client = client_id;
                    cout << "ID: " << client_id << ", "
                        << row["first_name"].as<string>() << " "
                        << row["last_name"].as<string>() << ", "
                        << "Email: " << row["email"].as<string>();

                    if (!row["phone"].is_null()) {
                        cout << ", Телефон: " << row["phone"].as<string>();
                    }
                    cout << endl;
                }
                else {
                    if (!row["phone"].is_null()) {
                        cout << "    Доп. телефон: " << row["phone"].as<string>() << endl;
                    }
                }
            }
        }
        catch (const exception& e) {
            cerr << "Ошибка при поиске клиента: " << e.what() << endl;
        }
    }

    void see_all() {
        try {
            work txn(conn);
            string query =
                "SELECT c.id, c.first_name, c.last_name, c.email, p.phone "
                "FROM clients c "
                "LEFT JOIN client_phones p ON c.id = p.client_id "
                "ORDER BY c.id";

            result res = txn.exec(query);

            if (res.empty()) {
                cout << "В базе нет клиентов" << endl;
                return;
            }

            cout << "\nСписок всех клиентов:\n";
            int current_client = -1;
            for (auto row : res) {
                int client_id = row["id"].as<int>();

                if (client_id != current_client) {
                    current_client = client_id;
                    cout << "ID: " << client_id << ", "
                        << row["first_name"].as<string>() << " "
                        << row["last_name"].as<string>() << ", "
                        << "Email: " << row["email"].as<string>();

                    if (!row["phone"].is_null()) {
                        cout << ", Телефон: " << row["phone"].as<string>();
                    }
                    cout << endl;
                }
                else {
                    if (!row["phone"].is_null()) {
                        cout << "    Доп. телефон: " << row["phone"].as<string>() << endl;
                    }
                }
            }
        }
        catch (const exception& e) {
            cerr << "Ошибка при получении списка клиентов: " << e.what() << endl;
        }
    }
};

int main() {
    setlocale(LC_ALL, "rus");
    try {
        neto_db db("always_for_test", "5432", "localhost", "postgres", "2281860Nik");

        db.create_tables();

        string command;
        while (true) {
            cout << "\nКоманды: add_client, add_phone, update_client, delete_phone, delete_client, find, see_all, exit\n";
            cout << "Введите команду: ";
            getline(cin, command);

            if (command == "exit") {
                break;
            }
            else if (command == "add_client") {
                string first_name, last_name, email;
                cout << "Введите имя: ";
                getline(cin, first_name);
                cout << "Введите фамилию: ";
                getline(cin, last_name);
                cout << "Введите email: ";
                getline(cin, email);
                db.add_client(first_name, last_name, email);
            }
            else if (command == "add_phone") {
                int client_id;
                string phone;
                cout << "Введите ID клиента: ";
                cin >> client_id;
                cin.ignore();
                cout << "Введите номер телефона: ";
                getline(cin, phone);
                db.add_phone(client_id, phone);
            }
            else if (command == "update_client") {
                int client_id;
                string first_name, last_name, email;
                cout << "Введите ID клиента: ";
                cin >> client_id;
                cin.ignore();
                cout << "Введите новое имя (или пусто): ";
                getline(cin, first_name);
                cout << "Введите новую фамилию (или пусто): ";
                getline(std::cin, last_name);
                cout << "Введите новый email (или пусто): ";
                getline(cin, email);
                db.update_client(client_id, first_name, last_name, email);
            }
            else if (command == "delete_phone") {
                string phone;
                cout << "Введите номер телефона для удаления: ";
                getline(cin, phone);
                db.delete_phone(phone);
            }
            else if (command == "delete_client") {
                int client_id;
                cout << "Введите ID клиента для удаления: ";
                cin >> client_id;
                db.delete_client(client_id);
                cin.ignore();
            }
            else if (command == "find") {
                string search_term;
                cout << "Введите поисковый запрос: ";
                getline(cin, search_term);
                db.find_client(search_term);
            }
            else if (command == "see_all") {
                db.see_all();
            }
            else {
                cout << "Неизвестная команда\n";
            }
        }
    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << endl;
        return 1;
    }

    return 0;
}