#pragma once

#include <stdexcept>
#include <string>

class Resource {
    std::string path;

    /**
     * Construct a resource object
     */
    Resource();

public:
    struct BadResource final: std::runtime_error {
        explicit BadResource(std::string errorMessage);
    };

    /**
     * Set the search path
     * @param path the new path to search
     */
    void setSearchPath(std::string path);

    /**
     * Get a resource
     * @return the absolute path to the resource
     * @throws BadResource if the resource was not find
     */
    std::string getResource(const std::string& resource) const;

    /**
     * Get the resource instance
     * @return the resource instance
     */
    static Resource& get();
};
