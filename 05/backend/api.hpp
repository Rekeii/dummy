#include <pistache/endpoint.h>
#include "database.hpp"
#include "activity_queue.hpp"

class RestApi {
public:
    RestApi(Database& db, ActivityQueue& queue);
    void init();
    void start();

private:
    Database& database;
    ActivityQueue& activityQueue;
    Pistache::Http::Endpoint endpoint;
    void setupRoutes();
};
