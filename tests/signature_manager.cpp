#include "../ecs/signature_manager.hpp"
#include "../include/test_utils.hpp"

struct Type1 {};
struct Type2 {};
struct Type3 {};

void test1() {
    Entity one = 1;
    SignatureManager manager;

    manager.set(one, 0);
    Signature sig = manager.get(one);
    ASSERT_EQUAL(sig, 0);

    Entity two = 2;
    manager.set(two, 0b10);
    sig = manager.get(two);
    ASSERT_EQUAL(sig, 0b10);

    // has set { {2, 0}, { 2, 2 } }

    manager.set_bit<Type1>(one);
    ASSERT_EQUAL(manager.get(one), 0b1);

    manager.set_bit<Type2>(one);
    ASSERT_EQUAL(manager.get(one), 0b11);

    manager.set_bit<Type3>(two);
    ASSERT_EQUAL(manager.get(two), 0b110);
}

int main() {
    test1();
}
