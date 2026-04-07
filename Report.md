# Laboratory Work No. 6: Composition
## Variant 1: Car Assembly

### 1. Objective
To acquire practical skills in implementing the composition relationship between classes in C++, ensuring the "whole" object manages the lifecycle of its "parts".

### 2. Problem Statement
Implement an object-oriented model of a car system using composition. The model should include classes for `Car`, `Engine`, `Wheel`, `Seat`, and `Transmission`. The car is the "whole" object and consists of integral parts such as an engine, transmission, seats, and wheels.

### 3. Class Design
- **Car**: The main object that owns its parts.
- **Engine**: Represents the car's power source.
- **Wheel**: Represents the car's wheels (4 per car).
- **Seat**: Represents the car's interior seats.
- **Transmission**: Represents the car's gearbox.

### 4. Implementation Details
- Composition was implemented by including part objects as data members of the `Car` class.
- The parts are created and destroyed along with the `Car` object.
- The car's constructor initializes its parts using initializer lists.
- Followed the recommended project structure with `public/` for headers and `private/` for implementations.

### 5. Conclusion
The composition relationship was successfully implemented. Unlike aggregation, composition implies that the parts are an integral part of the whole and their lifecycle is tied to the whole object. This model accurately reflects a car assembly where the engine and transmission are parts of the car.
