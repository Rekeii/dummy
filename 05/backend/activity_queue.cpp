#include "activity_queue.hpp"

void ActivityQueue::logActivity(const std::string& activity) {
    activities.push(activity);
}

std::string ActivityQueue::popActivity() {
    if (!activities.empty()) {
        std::string activity = activities.front();
        activities.pop();
        return activity;
    }
    return "";
}
