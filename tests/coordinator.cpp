#include "../ecs/coordinator.hpp"
#include "../include/test_utils.hpp"
#include <ostream>
#include <sstream>
#include <unordered_set>

struct Type1 {
    int val;
};
struct Type2 {
    string str;
};
struct Type3 {
    bool val;
};

class PrintSystem : public System {
public:
    PrintSystem() {
    }

    void run(Coordinator &coordinator, ostream &os) {
        for (Entity entity : subscribed_entities) {
            Type1 &data1 = coordinator.get_component<Type1>(entity);
            Type2 &data2 = coordinator.get_component<Type2>(entity);
            os << to_string(data1.val) << " " << data2.str + "\n";
        }
    }

    Signature get_signature() override {
        Signature signature = 0;
        signature = signature_utils::set_bit<Type1>(signature);
        signature = signature_utils::set_bit<Type2>(signature);
        return signature;
    }
};

void test1() {
    Coordinator coordinator;
    coordinator.register_component<Type1>();
    coordinator.register_component<Type2>();
    coordinator.register_component<Type3>();

    coordinator.register_system(PrintSystem{});

    Entity first = coordinator.create_entity();
    coordinator.set_component(first, Type1{1});
    coordinator.set_component(first, Type2{"first"});

    Entity second = coordinator.create_entity();
    coordinator.set_component(second, Type1{2});
    coordinator.set_component(second, Type2{"second"});

    PrintSystem *system = coordinator.get_system<PrintSystem>();
    system->run(coordinator, cout);
}

int main() {
    // for consistency
    id_utils::get_component_id<Type1>();
    id_utils::get_component_id<Type2>();

    test1();
}
