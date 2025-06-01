# Bucket List
- Doxygen
- Consider separate container optimized for flag components for systems with no real data
- unwrapping some code (more implementation, less function calls)
- inheritance vs enum switching
- functional programming 
- interfaces 
- sparse bitstring signature vs packed array directly with types
- be more deliberate with the contains checks. Leave for the leafs, the intermediates wrappers should not check
- consideer looking into perfect forwarding with rvalue + lvalue handling for systems and others
- consider placement of if checks and whether to use ASSERTions instead, decide what guarantees we want

# Design Choices
- use unique_ptr or reference for system_maanger in coordinator? ptr extra indirection, reference pollutes constructor
- force all systems to be run from coordinator and must be all run() from coordinator and T() default constructed or just define get and set, more flexible, more complicated call site

# In Progress
- game coordinator, handling erasing entity with signature, component, system recognizing
- much testing
- cyclic dependencies, decide how to manager systems etc
- tests and decide on the flexibility

