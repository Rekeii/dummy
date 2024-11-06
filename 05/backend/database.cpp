#include "database.hpp"
#include <iostream>
#include <curl/curl.h> // Requires libcurl for HTTP requests

bool Database::performRequest(const std::string& method, const std::string& url, const json& data) {
    CURL *curl;
    CURLcode res;

    // Initialize CURL
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
    if (!curl) {
        std::cerr << "CURL initialization failed!" << std::endl;
        return false;
    }

    // Set the URL for the request
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

    // Set the HTTP method (GET, POST, PUT, DELETE)
    if (method == "POST") {
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");

        // Convert the JSON object to a string for the POST body
        std::string jsonData = data.dump();
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonData.c_str());
    } else if (method == "GET") {
        curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
    } else if (method == "PUT") {
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
        std::string jsonData = data.dump();
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonData.c_str());
    } else if (method == "DELETE") {
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "DELETE");
    }

    // Set headers (optional, you can add more headers if necessary)
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    // Perform the request
    res = curl_easy_perform(curl);

    // Check for errors
    if (res != CURLE_OK) {
        std::cerr << "CURL request failed: " << curl_easy_strerror(res) << std::endl;
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        return false;
    }

    // Optionally, you can handle the response here and check status code
    long httpCode = 0;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
    if (httpCode != 200) {
        std::cerr << "Error: Received non-OK HTTP code " << httpCode << std::endl;
        curl_easy_cleanup(curl);
        curl_global_cleanup();
        return false;
    }

    // Clean up CURL and global resources
    curl_easy_cleanup(curl);
    curl_global_cleanup();

    return true;  // Request was successful
}

json Database::getProduct(const std::string& id) {
    return performRequest("GET", "/products/" + id);
}

bool Database::addProduct(const json& product) {
    return performRequest("POST", "/products", product);
}

bool Database::updateProduct(const std::string& id, const json& product) {
    return performRequest("PUT", "/products/" + id, product);
}

bool Database::deleteProduct(const std::string& id) {
    return performRequest("DELETE", "/products/" + id);
}
