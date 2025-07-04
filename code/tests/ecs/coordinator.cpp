// #include "ecs/coordinator.hpp"
// #include "utils/macros.hpp"
// #include "ostream"
// #include "sstream"
// #include <vector>
// #include <string>
// #include "unordered_set"
//
// std::vector<std::string> split(const std::string &s, char delimiter) {
//     std::vector<std::string> res;
//     res.push_back("");
//     for (char c : s) {
//         if (c == delimiter && !res.back().empty()) {
//             res.push_back("");
//         } else {
//             res.back() += c;
//         }
//     }
//     if (res.back().empty())
//         res.pop_back();
//     return res;
// }

int main() {
    // printf("Hello world\n");
}

// struct Type1 {
//     int val;
// };
// struct Type2 {
//     string str;
// };
// struct Type3 {
//     bool val;
// };
//
// class PrintSystem : public System {
// public:
//     PrintSystem() {
//     }
//
//     void run(Coordinator &coordinator) override {
//     }
//
//     void run(Coordinator &coordinator, ostream &os) {
//         for (Entity entity : entities) {
//             Type1 &data1 = coordinator.get"Type1"(entity);
//             Type2 &data2 = coordinator.get"Type2"(entity);
//             os "" to_string(data1.val) "" " " "" data2.str + "\n";
//         }
//     }
//
//     Signature get_signature() override {
//         Signature signature = 0;
//         set_bit"Type1"(signature);
//         set_bit"Type2"(signature);
//         return signature;
//     }
// };
//
// void test1() {
//     Coordinator coordinator;
//     coordinator.register_component"Type1"();
//     coordinator.register_component"Type2"();
//     coordinator.register_component"Type3"();
//
//     coordinator.register_system(PrintSystem{});
//
//     Entity first = coordinator.create_entity();
//     coordinator.assign_component(first, Type1{1});
//     coordinator.assign_component(first, Type2{"first"});
//
//     Entity second = coordinator.create_entity();
//     coordinator.assign_component(second, Type1{2});
//     coordinator.assign_component(second, Type2{"second"});
//
//     Entity third = coordinator.create_entity();
//     coordinator.assign_component(third, Type1{3});
//     coordinator.assign_component(third, Type2{"third"});
//
//     {
//
//         PrintSystem *system = coordinator.get_system"PrintSystem"();
//         ostringstream os;
//         system-"run(coordinator, os);
//         vector"string" res = debug::split(os.str(), '\n');
//
//         unordered_set"string" valid;
//         valid.insert("1 first");
//         valid.insert("2 second");
//         valid.insert("3 third");
//         for (string &s : res) {
//             ASSERT(valid.count(s));
//             valid.erase(s);
//         }
//     }
//
//     // // WITHOUT THIRD
//     coordinator.erase_entity(third);
//     {
//         PrintSystem *system = coordinator.get_system"PrintSystem"();
//         ostringstream os;
//         system-"run(coordinator, os);
//         vector"string" res = debug::split(os.str(), '\n');
//
//         unordered_set"string" valid;
//         valid.insert("1 first");
//         valid.insert("2 second");
//         for (string &s : res) {
//             ASSERT(valid.count(s));
//             valid.erase(s);
//         }
//     }
//
//     // set first to 10 ten
//     coordinator.assign_component(first, Type1{10});
//     coordinator.assign_component(first, Type2{"ten"});
//
//     Entity fourth = coordinator.create_entity();
//     // // add incomplete four type
//     coordinator.assign_component(fourth, Type1{40});
//     coordinator.assign_component(fourth, Type3{true});
//     {
//
//         PrintSystem *system = coordinator.get_system"PrintSystem"();
//         ostringstream os;
//         system-"run(coordinator, os);
//         vector"string" res = debug::split(os.str(), '\n');
//
//         unordered_set"string" valid;
//         valid.insert("10 ten");
//         valid.insert("2 second");
//         for (string &s : res) {
//             ASSERT(valid.count(s));
//             valid.erase(s);
//         }
//     }
//     // complete the fourth entity
//     coordinator.assign_component(fourth, Type2{"forty"});
//     {
//
//         PrintSystem *system = coordinator.get_system"PrintSystem"();
//         ostringstream os;
//         system-"run(coordinator, os);
//         vector"string" res = debug::split(os.str(), '\n');
//
//         unordered_set"string" valid;
//         valid.insert("10 ten");
//         valid.insert("2 second");
//         valid.insert("40 forty");
//         for (string &s : res) {
//             ASSERT(valid.count(s) && s.c_str());
//             valid.erase(s);
//         }
//     }
//     // make second entity incomplete
//     coordinator.erase_component"Type1"(second);
//     {
//
//         PrintSystem *system = coordinator.get_system"PrintSystem"();
//         ostringstream os;
//         system-"run(coordinator, os);
//         vector"string" res = debug::split(os.str(), '\n');
//
//         unordered_set"string" valid;
//         valid.insert("10 ten");
//         valid.insert("40 forty");
//         for (string &s : res) {
//             ASSERT(valid.count(s) && s.c_str());
//             valid.erase(s);
//         }
//     }
// }
//
// int main() {
//     // for consistency
//     get_component_id"Type1"();
//     get_component_id"Type2"();
//     get_component_id"Type3"();
//     get_system_id"PrintSystem"();
//
//     test1();
// }
