#include "http_client.h"
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl.hpp>  // ← вот этот include обязателен для ssl
#include <regex>
#include <iostream>
#include <memory>  // для std::unique_ptr

namespace beast = boost::beast;
namespace http  = beast::http;
namespace net   = boost::asio;
namespace ssl   = boost::asio::ssl;  // ← namespace для SSL
using tcp       = net::ip::tcp;

bool download_page(const std::string& url_str, std::string& body_out, std::string& error_out)
{
    try {
        // Парсим URL (http или https)
        std::regex url_regex(R"((https?)://([^/:]+)(?::(\d+))?(/.*)?)");
        std::smatch match;
        if (!std::regex_match(url_str, match, url_regex)) {
            error_out = "Invalid URL format";
            return false;
        }

        std::string scheme = match[1].str();
        std::string host   = match[2].str();
        std::string port   = match[3].matched ? match[3].str() : (scheme == "https" ? "443" : "80");
        std::string target = match[4].matched ? match[4].str() : "/";

        std::cout << "[Beast] Scheme: " << scheme << ", host: " << host 
                  << ", port: " << port << ", path: " << target << "\n";

        net::io_context ioc;

        // Для HTTPS используем SSL-контекст
        std::unique_ptr<ssl::stream<beast::tcp_stream>> ssl_stream;
        beast::tcp_stream* plain_stream = nullptr;

        if (scheme == "https") {
            ssl::context ctx(ssl::context::tls_client);
            // Включаем проверку сертификатов (системный trust store)
            ctx.set_verify_mode(ssl::verify_peer);
            ctx.set_default_verify_paths();  // Windows берёт сертификаты из системы

            ssl_stream = std::make_unique<ssl::stream<beast::tcp_stream>>(ioc, ctx);
        } else {
            plain_stream = new beast::tcp_stream(ioc);
        }

        tcp::resolver resolver(ioc);
        auto const results = resolver.resolve(host, port);

        // Подключение
        if (scheme == "https") {
            net::connect(ssl_stream->next_layer().socket(), results.begin(), results.end());
            ssl_stream->handshake(ssl::stream_base::client);
        } else {
            net::connect(plain_stream->socket(), results.begin(), results.end());
        }

        std::cout << "[Beast] Connected successfully\n";

        // Запрос
        http::request<http::string_body> req{http::verb::get, target, 11};
        req.set(http::field::host, host);
        req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

        // Отправка
        if (scheme == "https") {
            http::write(*ssl_stream, req);
        } else {
            http::write(*plain_stream, req);
        }

        // Чтение ответа
        beast::flat_buffer buffer;
        http::response<http::string_body> res;

        if (scheme == "https") {
            http::read(*ssl_stream, buffer, res);
        } else {
            http::read(*plain_stream, buffer, res);
        }

        // Очистка
        if (scheme != "https") {
            delete plain_stream;
        }

        if (res.result() != http::status::ok) {
            error_out = "HTTP status: " + std::to_string(res.result_int()) + " " + std::string(res.reason());
            return false;
        }

        body_out = std::move(res.body());
        std::cout << "[Beast] Downloaded " << body_out.size() << " bytes, Content-Type: "
                  << res[http::field::content_type] << "\n";

        return true;
    }
    catch (const std::exception& e) {
        error_out = std::string("Exception: ") + e.what();
        return false;
    }
}