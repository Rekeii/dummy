#include <napi.h>
#include "../../backend/database.hpp"
#include <nlohmann/json.hpp>  // Include nlohmann/json if not already included

Database db("http://localhost:5984");

// Utility function to convert Napi::String to std::string
std::string napiStringToStdString(const Napi::String& napiString) {
    return napiString.Utf8Value();
}

Napi::Value GetProduct(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    std::string id = napiStringToStdString(info[0].As<Napi::String>());
    json product = db.getProduct(id);
    return Napi::String::New(env, product.dump());
}

Napi::Value AddProduct(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    // Convert Napi::String to std::string for json parsing
    std::string jsonString = napiStringToStdString(info[0].As<Napi::String>());
    json product = json::parse(jsonString);  // Parse the string into a JSON object
    bool success = db.addProduct(product);
    return Napi::Boolean::New(env, success);
}

Napi::Value UpdateProduct(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    std::string id = napiStringToStdString(info[0].As<Napi::String>());
    std::string jsonString = napiStringToStdString(info[1].As<Napi::String>());
    json product = json::parse(jsonString);  // Parse the string into a JSON object
    bool success = db.updateProduct(id, product);
    return Napi::Boolean::New(env, success);
}

Napi::Value DeleteProduct(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    std::string id = napiStringToStdString(info[0].As<Napi::String>());
    bool success = db.deleteProduct(id);
    return Napi::Boolean::New(env, success);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    exports.Set(Napi::String::New(env, "getProduct"), Napi::Function::New(env, GetProduct));
    exports.Set(Napi::String::New(env, "addProduct"), Napi::Function::New(env, AddProduct));
    exports.Set(Napi::String::New(env, "updateProduct"), Napi::Function::New(env, UpdateProduct));
    exports.Set(Napi::String::New(env, "deleteProduct"), Napi::Function::New(env, DeleteProduct));
    return exports;
}

NODE_API_MODULE(addon, Init)
