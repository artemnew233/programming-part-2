#include <iostream>
#include "City.h"
#include "Citizen.h"

static void printCitySummary(const City& city) {
    std::cout << "City: " << city.getName()
              << "  (population: " << city.getPopulation() << ")\n";
    std::cout << "  Districts: " << city.getDistrictCount()
              << "  Hospitals: " << city.getHospitalCount()
              << "  Schools: "   << city.getSchoolCount() << "\n\n";

    for (int i = 0; i < city.getDistrictCount(); ++i) {
        const District* d = city.getDistrictAt(i);
        if (d == nullptr) continue;
        std::cout << "  District #" << d->getId()
                  << " \"" << d->getName() << "\""
                  << "  area: " << d->getAreaSqKm() << " km²"
                  << "  citizens: " << d->getCitizenCount()
                  << "  density: " << d->populationDensity() << "/km²\n";
        for (int j = 0; j < d->getCitizenCount(); ++j) {
            const Citizen* c = d->getCitizenAt(j);
            if (c != nullptr) {
                std::cout << "    - [" << c->getId() << "] "
                          << c->getFullName()
                          << " age " << c->getAge()
                          << (c->isAdult() ? "" : " (minor)") << "\n";
            }
        }
    }

    std::cout << "\n  Hospitals:\n";
    for (int i = 0; i < city.getHospitalCount(); ++i) {
        const Hospital* h = city.getHospitalAt(i);
        if (h == nullptr) continue;
        std::cout << "    [" << h->getId() << "] " << h->getName()
                  << "  capacity: " << h->getCapacity()
                  << "  " << (h->getIsPublic() ? "public" : "private")
                  << (h->isLargeHospital() ? "  [LARGE]\n" : "\n");
    }

    std::cout << "\n  Schools:\n";
    for (int i = 0; i < city.getSchoolCount(); ++i) {
        const School* s = city.getSchoolAt(i);
        if (s == nullptr) continue;
        std::cout << "    [" << s->getId() << "] " << s->getName()
                  << "  capacity: " << s->getCapacity()
                  << "  level: " << s->getLevel() << "\n";
    }
    std::cout << "\n";
}

int main() {
    //independent objects
    Citizen c1(1, "Olena Kovalenko",   34, 1);
    Citizen c2(2, "Marko Shevchenko",  15, 1);
    Citizen c3(3, "Iryna Petrenko",    42, 2);
    Citizen c4(4, "Dmytro Bondar",     28, 2);

    Hospital h1(10, "City General Hospital",  350, true);
    Hospital h2(11, "St. Luke's Clinic",       80, false);

    School s1(20, "School No. 5",  600, "primary");
    School s2(21, "Lyceum No. 3",  400, "secondary");

    District d1(1, "Old Town",  12.5);
    District d2(2, "Riverside", 18.0);

    City city("Kharkiv", 1400000);

    //build relationships 
    d1.addCitizen(c1);
    d1.addCitizen(c2);
    d2.addCitizen(c3);
    d2.addCitizen(c4);

    city.addDistrict(d1);
    city.addDistrict(d2);
    city.addHospital(h1);
    city.addHospital(h2);
    city.addSchool(s1);
    city.addSchool(s2);

    // demo
    printCitySummary(city);

    std::cout << "Public hospitals in city: "
              << city.totalPublicHospitals() << "\n";


    d2.removeCitizenById(c3.getId());
    c3.setDistrictId(1);
    d1.addCitizen(c3);

    std::cout << "\nAfter c3 moves to Old Town:\n";
    std::cout << "  Old Town citizens: "   << d1.getCitizenCount() << "\n";
    std::cout << "  Riverside citizens: "  << d2.getCitizenCount() << "\n";
    std::cout << "  c3 still exists independently, age: "
              << c3.getAge() << "\n";

    return 0;
}
