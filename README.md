# NOTES

# Bucket List
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
- force all systems to be run from coordinator and must be all run() from coordinator 
and T() default constructed or just define get and set, more flexible, more complicated call site
- consider checking system contains with system maanger signatures vs subscribed_entities.contains checks. 
First has better cache but second simpler implementation with different cases cases considering dynamic adding / deleting
- Use static_cast and member function vs inheritance virtual function lookup. Speed diff?

# In Progress
- game coordinator, handling erasing entity with signature, component, system recognizing
- much testing
- cyclic dependencies, decide how to manager systems etc
- tests and decide on flexibility
- better system for detecting whether a component or system is registered or not yet
- make registering multiple times harmless
- better logging when accidentally use unregistered type. Checkout the assert 
and see if you can print the type that was passed in

