#include "Resource.h"

#include <filesystem>

Resource::Resource(): path("/var/DuckGame/") {}

Resource::BadResource::BadResource(std::string errorMessage):
        std::runtime_error(std::move(errorMessage)) {}

void Resource::setSearchPath(std::string path) { this->path = std::move(path); }

std::string Resource::getResource(const std::string& resource) const {
    std::string resourcePath(path + resource);

    if (std::filesystem::exists(resourcePath) and std::filesystem::is_regular_file(resourcePath))
        return resourcePath;

    throw BadResource("Could not find a resource at " + resourcePath);
}

Resource& Resource::get() {
    static Resource resource;
    return resource;
}