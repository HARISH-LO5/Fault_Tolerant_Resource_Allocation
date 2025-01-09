#include <iostream>
#include <memory>
#include <vector>
#include <fstream>
#include <stdexcept>

// Resource States
enum class ResourceState { Idle, InUse, UnderMaintenance };

// Resource class  
class Resource {
public:
    Resource(int id) : id(id), state(ResourceState::Idle) {
        std::cout << "Resource created with ID: " << id << std::endl;
    }
    int getId() const { return id; }
    ResourceState getState() const { return state; }
    void setState(ResourceState newState) { state = newState; }

private:
    int id;
    ResourceState state;
};

// ResourceManager class
class ResourceManager {
public:
    ResourceManager();
    ~ResourceManager();
    void addResource(std::unique_ptr<Resource> resource);
    Resource* allocateResource();
    void releaseResource(Resource* resource);
    void logTransaction(const std::string& message);

private:
    std::vector<std::unique_ptr<Resource>> resources;
    std::ofstream logFile;
};

// ResourceManager class function definitions
ResourceManager::ResourceManager() {
    std::cout << "Opening log file..." << std::endl;
    logFile.open("resource_log.txt", std::ios::out | std::ios::app);
    if (!logFile.is_open()) {
        throw std::runtime_error("Failed to open log file");
    }
    std::cout << "Log file opened successfully." << std::endl;
}

ResourceManager::~ResourceManager() {
    std::cout << "Closing log file..." << std::endl;
    logFile.close();
    std::cout << "Log file closed." << std::endl;
}

void ResourceManager::addResource(std::unique_ptr<Resource> resource) {
    std::cout << "Adding resource with ID: " << resource->getId() << std::endl;
    resources.push_back(std::move(resource));
}

Resource* ResourceManager::allocateResource() {
    std::cout << "Allocating resource..." << std::endl;
    for (auto& resource : resources) {
        std::cout << "Checking resource with ID: " << resource->getId() << " (State: " << static_cast<int>(resource->getState()) << ")" << std::endl;
        if (resource->getState() == ResourceState::Idle) {
            resource->setState(ResourceState::InUse);
            logTransaction("Allocated resource ID: " + std::to_string(resource->getId()));
            std::cout << "Allocated resource with ID: " << resource->getId() << std::endl;
            return resource.get();
        }
    }
    throw std::runtime_error("No available resources");
}

void ResourceManager::releaseResource(Resource* resource) {
    std::cout << "Releasing resource with ID: " << resource->getId() << std::endl;
    resource->setState(ResourceState::Idle);
    logTransaction("Released resource ID: " + std::to_string(resource->getId()));
}

void ResourceManager::logTransaction(const std::string& message) {
    std::cout << "Logging transaction: " << message << std::endl;
    logFile << message << std::endl;
    logFile.flush(); // Ensure the message is written to the file immediately
}

// Main function with additional cases
int main() {
    try {
        ResourceManager manager;
        manager.addResource(std::make_unique<Resource>(1));
        manager.addResource(std::make_unique<Resource>(2));
        manager.addResource(std::make_unique<Resource>(3));

        // Allocate and release resources
        auto resource1 = manager.allocateResource();
        manager.releaseResource(resource1);

        auto resource2 = manager.allocateResource();
        auto resource3 = manager.allocateResource();
        auto resource4 = manager.allocateResource();

        // Release resources
        manager.releaseResource(resource2);
        manager.releaseResource(resource3);

        // Allocate again after releasing
        auto resource5 = manager.allocateResource();
        std::cout << "Successfully allocated resource ID: " << resource5->getId() << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
