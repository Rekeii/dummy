#include <iostream>
#include "database.hpp" // Include your Database class header
#include <pistache/endpoint.h>
#include <memory> // Include for std::shared_ptr

using namespace Pistache;

class InventoryApi : public Http::Handler {
public:
    HTTP_PROTOTYPE(InventoryApi)

    void onRequest(const Http::Request& request, Http::ResponseWriter response) override {
        // Handle requests here
        response.send(Http::Code::Ok, "Inventory API is up and running!");
    }
};

int main() {
    // Initialize Pistache API server
    Port port(9080);
    Address addr(Ipv4::any(), port);
    Http::Endpoint server(addr);
    
    std::cout << "Server running on port " << port << std::endl;

    // Wrap handler in shared_ptr
    auto handler = std::make_shared<InventoryApi>();  // Use shared_ptr

    server.init();
    server.setHandler(handler);  // Now passing a shared_ptr
    server.serve();
    
    return 0;
}
