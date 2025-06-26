#include "../include/ecs/signature_manager.hpp"
#include "../include/utils/test_utils.hpp"

struct Type1 {};
struct Type2 {};
struct Type3 {};

void test1() {
    Entity one = 1;
    SignatureManager manager;

    manager.set(one);
    Signature sig = manager[one];
    ASSERT_EQUAL(sig, 0);

    Entity two = 2;
    manager.assign(two, 0b10);
    sig = manager[two];
    ASSERT_EQUAL(sig, 0b10);

    // has set { {2, 0}, { 2, 2 } }

    manager.set_bit<Type1>(one);
    ASSERT_EQUAL(manager[one], 0b1);

    manager.set_bit<Type2>(one);
    ASSERT_EQUAL(manager[one], 0b11);

    manager.set_bit<Type3>(two);
    ASSERT_EQUAL(manager[two], 0b110);
}

void test2() {
    SignatureManager manager;

    Entity first = 0;
    manager.set_bit<Type3>(first);
    ASSERT_EQUAL(manager[first], 0b100);

    Entity second = 1;
    manager.set_bit<Type2>(second);
    ASSERT_EQUAL(manager[second], 0b10);
}

int main() {
    // to set for consistency
    internal::get_component_id<Type1>();
    internal::get_component_id<Type2>();
    internal::get_component_id<Type3>();

    test1();
    test2();
}
