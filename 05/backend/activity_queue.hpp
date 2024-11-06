#include <queue>
#include <string>

class ActivityQueue {
public:
    void logActivity(const std::string& activity);
    std::string popActivity();

private:
    std::queue<std::string> activities;
};
