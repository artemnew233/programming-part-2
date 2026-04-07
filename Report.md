# Laboratory Work No. 5: Aggregation
## Variant 1: University Structure

### 1. Objective
To acquire practical skills in implementing the aggregation relationship between classes in C++, using smart pointers (`std::shared_ptr`), and organizing the project structure.

### 2. Problem Statement
Implement an object-oriented model of a university structure using aggregation. The model should include classes for `University`, `Department`, `Professor`, `Student`, and `Course`. The university aggregates departments, which in turn aggregate professors and courses. Students are enrolled in courses but are not owned by them.

### 3. Class Design
- **University**: The main container that holds a collection of departments.
- **Department**: Represents a faculty or department, holding professors and courses.
- **Professor**: Represents a teaching staff member.
- **Course**: Represents an academic course, which has a professor and a list of enrolled students.
- **Student**: Represents a student who can enroll in multiple courses.

### 4. Implementation Details
- Used `std::shared_ptr` to manage the lifecycle of objects and represent aggregation (where objects can exist independently).
- Followed the recommended project structure with `public/` for headers and `private/` for implementations.
- Implemented a demonstration scenario in `main.cpp`.

### 5. Conclusion
The aggregation relationship was successfully implemented. Unlike composition, aggregation allows the parts (Professors, Students, Courses) to exist independently of the whole (University, Department). Smart pointers provide a safe way to manage these shared references.
