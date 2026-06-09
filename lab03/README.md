# Lab 03 — A Simple C++ Class and UML Basics
## Variant 12 — `MovieTicket`

**Course:** Programming. Part 2  
**Department:** Computer Engineering and Programming, NTU "KhPI"  

---

## 1. Topic, Purpose, and Assignment Statement

**Topic:** Designing a simple C++ class with encapsulation, constructors, access
methods, and a UML class diagram in PlantUML.

**Purpose:** To reinforce the basic concepts of object-oriented programming in C++,
learn how to design a simple class, represent its interface in UML, and connect the
diagram with a real implementation.

**Assignment (Variant 12 — MovieTicket):**  
Implement the `MovieTicket` class that describes a ticket in a cinema booking system.
The class must encapsulate the relevant data fields and provide both a full educational
interface and a design-analysis section identifying redundant access methods.

---

## 2. Brief Theoretical Notes

### Class and Encapsulation

A **class** in C++ combines data (fields/attributes) and behaviour (methods) into a
single unit. The key principle is **encapsulation** — hiding internal state from the
outside world and controlling access via a well-defined public interface.

Fields are typically declared `private`, meaning only class methods can read or modify
them directly. External code must go through:

- **Constructors** — to create and initialise an object.
- **Getters** (`get…()`) — to read field values.
- **Setters** (`set…()`) — to modify field values, optionally with validation.
- **Domain methods** — higher-level operations with business meaning.

The `m_` prefix used throughout this implementation is a common convention to
distinguish member (instance) variables from local variables.

### UML Class Diagram

A UML class diagram represents a class as a rectangle with three compartments:
1. Class name (top).
2. Attributes (middle) — access modifier + name : type.
3. Methods (bottom) — access modifier + name(params) : return type.

Access modifiers: `+` = `public`, `-` = `private`.

### PlantUML

PlantUML is a text-based tool for generating UML diagrams from `.puml` source
files. Diagrams can be exported to `.png`, `.svg`, or `.pdf` images.

---

## 3. Specification — Variant 12

**Class:** `MovieTicket`  
**Description:** A ticket in a cinema booking system.

### Fields

| Field              | Type     | Constraint            |
|--------------------|----------|-----------------------|
| `m_hallNumber`     | `int`    | ≥ 1 (clamped)         |
| `m_seatNumber`     | `int`    | ≥ 1 (clamped)         |
| `m_price`          | `double` | > 0.0 (clamped to 0)  |
| `m_booked`         | `bool`   | —                     |
| `m_durationMinutes`| `int`    | > 0 (clamped to 1)    |

### Required Methods

| Method | Signature | Description |
|--------|-----------|-------------|
| Constructor | `MovieTicket(int, int, double, bool, int)` | Initialises all fields with validation |
| Book | `void book()` | Sets booked = true if not already booked |
| Cancel | `void cancelBooking()` | Sets booked = false if currently booked |
| Premium check | `bool isPremium() const` | Returns `price > 200.0` |
| Discounted price | `double discountedPrice(double) const` | Price after % discount |
| Long movie | `bool isLongMovie() const` | Returns `durationMinutes > 120` |

---

## 4. Initial UML Class Diagram

See `uml/MovieTicket.puml` for the PlantUML source.  
See `assets/MovieTicket.svg` for the generated diagram.

```
+----------------------------------------------------------+
|                      MovieTicket                         |
+----------------------------------------------------------+
| - m_hallNumber      : int                                |
| - m_seatNumber      : int                                |
| - m_price           : double                             |
| - m_booked          : bool                               |
| - m_durationMinutes : int                                |
+----------------------------------------------------------+
| + MovieTicket(hallNumber, seatNumber, price,             |
|               booked, durationMinutes)                   |
| + getHallNumber()      const : int                       |
| + getSeatNumber()      const : int                       |
| + getPrice()           const : double                    |
| + getBooked()          const : bool                      |
| + getDurationMinutes() const : int                       |
| + setHallNumber(value : int)       : void                |
| + setSeatNumber(value : int)       : void                |
| + setPrice(value : double)         : void                |
| + setBooked(value : bool)          : void                |
| + setDurationMinutes(value : int)  : void                |
| + book()                           : void                |
| + cancelBooking()                  : void                |
| + isPremium()                const : bool                |
| + discountedPrice(percent)   const : double              |
| + isLongMovie()              const : bool                |
+----------------------------------------------------------+
```

---

## 5. Selected Code Fragments

### Header file — `include/MovieTicket.hpp`

```cpp
#pragma once

class MovieTicket {
public:
    MovieTicket(int hallNumber, int seatNumber, double price,
                bool booked, int durationMinutes);

    int    getHallNumber()      const;
    int    getSeatNumber()      const;
    double getPrice()           const;
    bool   getBooked()          const;
    int    getDurationMinutes() const;

    void setHallNumber(int value);
    void setSeatNumber(int value);
    void setPrice(double value);
    void setBooked(bool value);
    void setDurationMinutes(int value);

    void   book();
    void   cancelBooking();
    bool   isPremium()                     const;
    double discountedPrice(double percent) const;
    bool   isLongMovie()                   const;

private:
    int    m_hallNumber;
    int    m_seatNumber;
    double m_price;
    bool   m_booked;
    int    m_durationMinutes;
};
```

### Key method implementations — `src/MovieTicket.cpp`

```cpp
// Constructor — validates all fields at creation time
MovieTicket::MovieTicket(int hallNumber, int seatNumber, double price,
                         bool booked, int durationMinutes)
    : m_hallNumber(hallNumber >= 1 ? hallNumber : 1),
      m_seatNumber(seatNumber >= 1 ? seatNumber : 1),
      m_price(price > 0.0 ? price : 0.0),
      m_booked(booked),
      m_durationMinutes(durationMinutes > 0 ? durationMinutes : 1)
{}

void MovieTicket::book() {
    if (!m_booked) { m_booked = true; }
}

void MovieTicket::cancelBooking() {
    if (m_booked) { m_booked = false; }
}

bool MovieTicket::isPremium() const {
    return m_price > 200.0;
}

double MovieTicket::discountedPrice(double percent) const {
    if (percent < 0.0)   percent = 0.0;
    if (percent > 100.0) percent = 100.0;
    return m_price * (1.0 - percent / 100.0);
}

bool MovieTicket::isLongMovie() const {
    return m_durationMinutes > 120;
}
```

---

## 6. Program Testing

The test program (`src/main.cpp`) creates a `MovieTicket` object and systematically
demonstrates all methods:

| Test step | Action | Expected result |
|-----------|--------|-----------------|
| Initial state | `MovieTicket(3, 15, 120.0, false, 95)` | Booked: no; Premium: no; Long: no |
| First `book()` | Set booked to true | Booked: yes |
| Second `book()` | No effect (already booked) | Booked: yes (unchanged) |
| `discountedPrice(10.0)` | 10% off 120.0 | 108.0 |
| `discountedPrice(25.0)` | 25% off 120.0 | 90.0 |
| `setPrice(250.0)` | Update price | `isPremium()` → yes |
| `setDurationMinutes(148)` | Update duration | `isLongMovie()` → yes |
| `cancelBooking()` | Cancel booking | Booked: no |
| Second `cancelBooking()` | No effect | Booked: no (unchanged) |
| Invalid constructor args | `MovieTicket(-5, 0, -99.0, false, -10)` | All fields clamped to minimums |

**Sample output:**
```
=== Initial ticket state ===
Hall number    : 3
Seat number    : 15
Price          : 120
Booked         : no
Duration (min) : 95
Premium        : no
Long movie     : no

=== Booking the ticket ===
Booked after book()        : yes
Booked after 2nd book()    : yes

=== Discounted prices (base: 120) ===
10% discount  : 108
25% discount  : 90
50% discount  : 60

=== After setPrice(250.0) ===
New price : 250
Premium   : yes

=== After setDurationMinutes(148) ===
Duration (min) : 148
Long movie     : yes

=== Cancelling the booking ===
Booked after cancelBooking()     : no
Booked after 2nd cancelBooking() : no

=== Edge-case ticket (invalid arguments) ===
Hall (expected 1)     : 1
Seat (expected 1)     : 1
Price (expected 0.0)  : 0
Duration (expected 1) : 1
```

---

## 7. Which Getters and Setters Are Unnecessary Here, and Why

### Unnecessary Setters

#### `setHallNumber(int value)`

**Risk:** Hall number is part of the ticket's immutable identity. A cinema ticket
for Hall 3 should never be reassigned to Hall 5 after it has been issued. Exposing
this setter allows external code to silently change the hall assignment of an already-
booked ticket, which could cause two tickets to reference the same (hallNumber,
seatNumber) pair with different content — breaking the object invariant.

**Better design:** Make `m_hallNumber` read-only after construction. Keep only the
getter.

---

#### `setSeatNumber(int value)`

**Risk:** Same argument as `setHallNumber`. Seat assignment is fixed when the ticket
is issued. Allowing post-construction seat reassignment can produce booking conflicts
if two `MovieTicket` objects end up with the same (hall, seat) combination.

**Better design:** Remove the setter; provide only `getSeatNumber()`.

---

#### `setBooked(bool value)`

**Risk:** This is the most dangerous setter in the class. It bypasses the business
logic embedded in `book()` and `cancelBooking()`. A caller can write
`ticket.setBooked(false)` to "cancel" a booking without going through any validation
or notification path. In a real system this would skip refund processing, seat
availability updates, and audit logging. The raw `bool` setter reduces booking state
management to a trivial flag toggle and defeats the purpose of having domain methods.

**Better design:** Remove `setBooked()` entirely. Booking state must only be changed
through `book()` and `cancelBooking()`.

---

#### `setDurationMinutes(int value)`

**Risk:** Movie duration is a property of the scheduled screening, not of an
individual ticket. Every ticket for the same screening must show the same duration.
Allowing individual tickets to have different durations (by calling this setter) leads
to data inconsistency. If duration can change, it should be updated at the "screening"
level, not per-ticket.

**Better design:** Remove the setter. Duration is set at construction and stays fixed.

---

### Setter That Is Reasonable to Keep

#### `setPrice(double value)`

Price adjustment can be a legitimate operation (last-minute promotions, walk-up
pricing, managerial overrides). Keeping `setPrice()` is justified — though in a
production system it could be replaced by a more descriptive method like
`applyPromotion(double newPrice)` to make the intent clearer.

---

### Summary Table

| Method | Keep? | Reason |
|--------|-------|--------|
| `setHallNumber()` | ✗ Remove | Identity field — immutable after creation |
| `setSeatNumber()` | ✗ Remove | Identity field — immutable after creation |
| `setPrice()` | ✓ Keep | Legitimate pricing adjustments |
| `setBooked()` | ✗ Remove | Bypasses `book()`/`cancelBooking()` logic |
| `setDurationMinutes()` | ✗ Remove | Screening property, not per-ticket |

---

## 8. Updated UML Diagram After Interface Simplification

See `uml/MovieTicket_improved.puml` and `assets/MovieTicket_improved.svg`.

```
+----------------------------------------------------------+
|             MovieTicket  [improved interface]            |
+----------------------------------------------------------+
| - m_hallNumber      : int                                |
| - m_seatNumber      : int                                |
| - m_price           : double                             |
| - m_booked          : bool                               |
| - m_durationMinutes : int                                |
+----------------------------------------------------------+
| + MovieTicket(hallNumber, seatNumber, price,             |
|               booked, durationMinutes)                   |
| + getHallNumber()      const : int                       |
| + getSeatNumber()      const : int                       |
| + getPrice()           const : double                    |
| + getBooked()          const : bool                      |
| + getDurationMinutes() const : int                       |
|                                                          |
| + setPrice(value : double)         : void    ← only one  |
|                                                          |
| + book()                           : void                |
| + cancelBooking()                  : void                |
| + isPremium()                const : bool                |
| + discountedPrice(percent)   const : double              |
| + isLongMovie()              const : bool                |
+----------------------------------------------------------+
```

---

## 9. Conclusions

This lab demonstrated the core principles of OOP in C++:

1. **Encapsulation** — all fields are `private`; the only way to affect them from
   outside is through the controlled public interface.
2. **Constructor validation** — invalid field values are clamped at creation time,
   making it impossible to construct an object in an illegal state.
3. **Domain methods vs. raw setters** — `book()` and `cancelBooking()` are
   meaningfully richer than a raw `setBooked(bool)`. They carry intent and can be
   extended with notifications or validation without changing the calling code.
4. **Minimal interface principle** — the improved diagram retains only one setter
   (`setPrice`) and replaces the rest with read-only getters + domain methods. This
   reduces the risk of misuse and makes the class easier to reason about.
5. **UML as a design tool** — building both the initial and the improved UML diagrams
   made the interface redundancies immediately visible at a glance.

---

## Project Structure

```
lab03/
├── CMakeLists.txt
├── include/
│   └── MovieTicket.hpp
├── src/
│   ├── MovieTicket.cpp
│   └── main.cpp
├── uml/
│   ├── MovieTicket.puml           (full educational interface)
│   └── MovieTicket_improved.puml  (simplified interface)
├── assets/
│   ├── MovieTicket.svg            (diagram image — full)
│   └── MovieTicket_improved.svg   (diagram image — improved)
└── README.md
```

## Build Instructions

```bash
mkdir build && cd build
cmake ..
make
./lab03
```

Or without CMake:

```bash
g++ -std=c++17 -Wall -Iinclude src/MovieTicket.cpp src/main.cpp -o lab03
./lab03
```
