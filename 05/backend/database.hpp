#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

class Database {
public:
    Database(const std::string& url) : dbUrl(url) {}

    json getProduct(const std::string& id);
    bool addProduct(const json& product);
    bool updateProduct(const std::string& id, const json& product);
    bool deleteProduct(const std::string& id);

private:
    std::string dbUrl;
    bool performRequest(const std::string& method, const std::string& endpoint, const json& data = json::object());
};
