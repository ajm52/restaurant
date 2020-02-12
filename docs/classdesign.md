# Class Design Considerations (EffectiveCpp 3rdEd, Meyers)

1. How should objects of your new type be created and destroyed?
   • influences how objects of this type are created, destroyed, allocated and deallocated.

2. How should object initialization differ from object assignment?
   • determines behavior of and differences between constructors and assignment operators.

3. What does it mean for objects of your new type to be passed by value?
   • recall that the copy constructor defines how pass-by-value is implemented for a type.

4. What are the restrictions on legal values for your new type?
   • typically, only some combinations of values are valid for a class's data members; these are the invariants that the class must maintain via error checking and exception throwing.

5. Does your new type fit into an inheritance graph?
   • if so, the type is constrained by the design of those classes, notably by virtual/non-virtual functions. A class to be inherited from should always have a virtual destructor.

6. What kind of type conversions are allowed for your new type?
   • consider implicit and explicit type conversions; should any of these be allowed? If so, they must be implemented.

7. What operators and functions make sense for your new type?
   • this determines what functions will be declared within this class; some will be member functions, and some may not.

8. What standard functions should be disallowed?
   • for example, should the class be uncopyable? Consider declaring functions as private.

9. Who should have access to the members of your new type?
   • this determines which members are public/protected/private, as well as whether any classes should be friends or nested composition-style.

10. What is the "undeclared interface" of your new type?
    • what does it promise in terms of performance, exception safety, and resource usage? These promises will constrain implementation.

11. How general is your new type?
    • Perhaps you're defining a family of types, rather than a single type. If so, you'll want to define a class template instead.

12. Is a new type really what you need?
    • What is the motivation for having a new class, and could the desired functionality be accomplished otherwise more easily?
