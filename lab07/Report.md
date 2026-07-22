# Laboratory Work No. 7: Inheritance
## Variant 1: Vehicle Hierarchy

### 1. Objective
To acquire practical skills in constructing semantically correct class hierarchies in C++, implementing multilevel inheritance without abstract classes, and using initializer lists and override.

### 2. Problem Statement
Implement a class hierarchy according to the selected variant. The hierarchy must have a depth of 3-4 levels. Branching in width into 2-3 subtypes is allowed within a variant if it is natural for the model. All classes in the hierarchy must have their own state, rather than inherited fields only.

### 3. Class Hierarchy Design
- **Vehicle**: Base class with common attributes (manufacturer, year).
  - **Truck**: Derived from `Vehicle` with `payloadCapacity`.
    - **RefrigeratedTruck**: Derived from `Truck` with `minTemperature`.
  - **PassengerCar**: Derived from `Vehicle` with `passengerCapacity`.

### 4. Implementation Details
- Used public inheritance to represent "is-a" relationships.
- Overrode the `displayInfo()` method at each level using the `override` keyword.
- Used initializer lists to pass arguments to base class constructors.
- Demonstrated polymorphism by using a `std::vector` of `std::unique_ptr<Vehicle>`.
- Analyzed the sizes of objects using `sizeof`.

### 5. Conclusion
The vehicle hierarchy was successfully implemented. Inheritance provides a way to extend and specialize existing classes. The use of `sizeof` confirmed that each derived class adds its own state to the object, increasing its size compared to the base class.
