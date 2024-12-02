#include "Resource.h"

#include <filesystem>

Resource::Resource(): path("/var/DuckGame/") {}

Resource::BadResource::BadResource(const std::string& errorMessage):
        std::runtime_error(errorMessage) {}

void Resource::setSearchPath(std::string path) { this->path = std::move(path); }

std::string Resource::resource(const std::string& resource) const { return path + resource; }

Resource& Resource::get() {
    static Resource resource;
    return resource;
}