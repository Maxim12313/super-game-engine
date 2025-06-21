#include "../include/ecs/system.hpp"
#include "../include/ecs/coordinator.hpp"

void System::run(Coordinator &coordinator) {
    for (Entity entity : subscribed_entities) {
        runner->run(entity, coordinator);
    }
}
