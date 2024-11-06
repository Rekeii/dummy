#include "api.hpp"
#include <pistache/router.h>

RestApi::RestApi(Database& db, ActivityQueue& queue)
    : database(db), activityQueue(queue), endpoint(Pistache::Address(Pistache::Ipv4::any(), Pistache::Port(9080))) {}

void RestApi::setupRoutes() {
    using namespace Pistache::Rest;

    Routes::Get(router, "/product/:id", Routes::bind(&RestApi::handleGetProduct, this));
    Routes::Post(router, "/product", Routes::bind(&RestApi::handleAddProduct, this));
    Routes::Put(router, "/product/:id", Routes::bind(&RestApi::handleUpdateProduct, this));
    Routes::Delete(router, "/product/:id", Routes::bind(&RestApi::handleDeleteProduct, this));
}

void RestApi::start() {
    Pistache::Http::Endpoint::Options options;
    options.threads(1);
    endpoint.init(options);
    setupRoutes();
    endpoint.setHandler(router.handler());
    endpoint.serve();
}

void RestApi::handleGetProduct(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    std::string id = request.param(":id").as<std::string>();
    json product = database.getProduct(id);
    response.send(Pistache::Http::Code::Ok, product.dump());
}

void RestApi::handleAddProduct(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    auto product = json::parse(request.body());
    if (database.addProduct(product)) {
        activityQueue.logActivity("Product added: " + product["name"].get<std::string>());
        response.send(Pistache::Http::Code::Created, "Product added");
    } else {
        response.send(Pistache::Http::Code::Internal_Server_Error, "Failed to add product");
    }
}

void RestApi::handleUpdateProduct(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    std::string id = request.param(":id").as<std::string>();
    auto product = json::parse(request.body());
    if (database.updateProduct(id, product)) {
        activityQueue.logActivity("Product updated: " + id);
        response.send(Pistache::Http::Code::Ok, "Product updated");
    } else {
        response.send(Pistache::Http::Code::Internal_Server_Error, "Failed to update product");
    }
}

void RestApi::handleDeleteProduct(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
    std::string id = request.param(":id").as<std::string>();
    if (database.deleteProduct(id)) {
        activityQueue.logActivity("Product deleted: " + id);
        response.send(Pistache::Http::Code::Ok, "Product deleted");
    } else {
        response.send(Pistache::Http::Code::Internal_Server_Error, "Failed to delete product");
    }
}
