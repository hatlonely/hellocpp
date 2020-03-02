#include <curl/curl.h>
#include <gtest/gtest.h>
#include <iostream>

TEST(testLibcurl, caseVersion) {
    std::cout << curl_version() << std::endl;
}

static size_t WriteToStream(void *ptr, size_t size, size_t nmemb, std::stringstream *stream) {
    stream->write((const char *)ptr, size * nmemb);
    return size * nmemb;
}

struct HTTPRequest {
    std::string                        url;
    std::map<std::string, std::string> data;
    std::map<std::string, std::string> params;
    std::map<std::string, std::string> headers;
    std::map<std::string, std::string> cookies;
    std::string                        body;

    HTTPRequest(std::string url) : url(url) {}
};

struct HTTPResponse {
    std::string error;
    int         status;
    std::string headers;
    std::string body;
};

HTTPResponse HTTPGet(const HTTPRequest &req) {
    HTTPResponse res;

    auto curl = curl_easy_init();
    if (!curl) {
        res.error = "curl easy init failed";
        return res;
    }

    struct curl_slist *req_header = nullptr;
    req_header                    = curl_slist_append(req_header, "Accept: text/css,*/*;q=0.1");
    req_header                    = curl_slist_append(req_header, "accept-language: zh-CN,zh;q=0.9,en;q=0.8");

    std::stringstream res_body;
    std::stringstream res_header;
    curl_easy_setopt(curl, CURLOPT_URL, req.url.c_str());
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, req_header);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteToStream);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &res_body);
    curl_easy_setopt(curl, CURLOPT_HEADERFUNCTION, WriteToStream);
    curl_easy_setopt(curl, CURLOPT_HEADERDATA, &res_header);

    auto code = curl_easy_perform(curl);
    if (code != CURLE_OK) {
        curl_easy_cleanup(curl);
        curl_slist_free_all(req_header);
        std::stringstream ss;
        ss << "curl_easy_perform failed. code [" << code << "]";
        res.error = ss.str();
        return res;
    }

    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &res.status);
    curl_easy_cleanup(curl);
    curl_slist_free_all(req_header);
    res.body    = res_body.str();
    res.headers = res_header.str();

    return res;
}

TEST(testLibcurl, caseCrulEasy) {
    auto res = HTTPGet(HTTPRequest("www.baidu.com"));
    std::cout << res.status << std::endl;
    std::cout << res.headers << std::endl;
    std::cout << res.body << std::endl;
}
