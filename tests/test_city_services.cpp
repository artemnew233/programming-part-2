#include <gtest/gtest.h>
#include "City.h"
#include "Citizen.h"

// ── City aggregation ─────────────────────────────────────────────────────────

TEST(CityTest, StoresReferencesToIndependentDistricts) {
    City city("TestCity", 100000);
    District d1(1, "North", 10.0);
    District d2(2, "South", 8.0);

    EXPECT_TRUE(city.addDistrict(d1));
    EXPECT_TRUE(city.addDistrict(d2));
    EXPECT_EQ(city.getDistrictCount(), 2);
    ASSERT_NE(city.getDistrictAt(0), nullptr);
    EXPECT_EQ(city.getDistrictAt(0)->getId(), 1);
    EXPECT_EQ(city.getDistrictAt(1)->getId(), 2);
}

TEST(CityTest, DuplicateDistrictRejected) {
    City city("TestCity", 100000);
    District d(1, "North", 10.0);

    EXPECT_TRUE(city.addDistrict(d));
    EXPECT_FALSE(city.addDistrict(d));
    EXPECT_EQ(city.getDistrictCount(), 1);
}

TEST(CityTest, StoresHospitalsAndSchools) {
    City city("TestCity", 100000);
    Hospital h(10, "General", 300, true);
    School   s(20, "School 1", 500, "primary");

    EXPECT_TRUE(city.addHospital(h));
    EXPECT_TRUE(city.addSchool(s));
    EXPECT_EQ(city.getHospitalCount(), 1);
    EXPECT_EQ(city.getSchoolCount(), 1);
}

TEST(CityTest, DuplicateHospitalAndSchoolRejected) {
    City city("TestCity", 0);
    Hospital h(1, "H", 100, true);
    School   s(2, "S", 200, "secondary");

    EXPECT_TRUE(city.addHospital(h));
    EXPECT_FALSE(city.addHospital(h));
    EXPECT_TRUE(city.addSchool(s));
    EXPECT_FALSE(city.addSchool(s));
}

TEST(CityTest, TotalPublicHospitals) {
    City city("TestCity", 0);
    Hospital h1(1, "Public 1",  200, true);
    Hospital h2(2, "Private",    80, false);
    Hospital h3(3, "Public 2",  150, true);

    city.addHospital(h1);
    city.addHospital(h2);
    city.addHospital(h3);
    EXPECT_EQ(city.totalPublicHospitals(), 2);
}

TEST(CityTest, GetDistrictAtOutOfRangeReturnsNull) {
    City city("TestCity", 0);
    EXPECT_EQ(city.getDistrictAt(0),  nullptr);
    EXPECT_EQ(city.getDistrictAt(-1), nullptr);
}

// ── District aggregation ─────────────────────────────────────────────────────

TEST(DistrictTest, AddAndContainsCitizen) {
    District d(1, "Old Town", 12.0);
    Citizen  c(1, "Olena", 30, 1);

    EXPECT_TRUE(d.addCitizen(c));
    EXPECT_TRUE(d.containsCitizen(1));
    EXPECT_EQ(d.getCitizenCount(), 1);
    ASSERT_NE(d.getCitizenAt(0), nullptr);
    EXPECT_EQ(d.getCitizenAt(0)->getId(), 1);
}

TEST(DistrictTest, DuplicateCitizenRejected) {
    District d(1, "Old Town", 12.0);
    Citizen  c(5, "Marko", 25, 1);

    EXPECT_TRUE(d.addCitizen(c));
    EXPECT_FALSE(d.addCitizen(c));
}

TEST(DistrictTest, RemoveCitizenByIdAndObjectStillExists) {
    District d(1, "Riverside", 8.0);
    Citizen  c(7, "Iryna", 40, 1);

    d.addCitizen(c);
    EXPECT_TRUE(d.containsCitizen(7));

    EXPECT_TRUE(d.removeCitizenById(7));
    EXPECT_FALSE(d.containsCitizen(7));
    EXPECT_EQ(d.getCitizenCount(), 0);

    // citizen object itself still exists independently
    EXPECT_EQ(c.getId(), 7);
    EXPECT_EQ(c.getAge(), 40);
}

TEST(DistrictTest, RemoveNonexistentCitizenReturnsFalse) {
    District d(1, "East", 5.0);
    EXPECT_FALSE(d.removeCitizenById(99));
}

TEST(DistrictTest, PopulationDensity) {
    District d(1, "Centre", 4.0);
    Citizen  c1(1, "A", 20, 1);
    Citizen  c2(2, "B", 22, 1);

    d.addCitizen(c1);
    d.addCitizen(c2);
    EXPECT_DOUBLE_EQ(d.populationDensity(), 0.5); // 2 / 4.0
}

// ── Citizen standalone behaviour ─────────────────────────────────────────────

TEST(CitizenTest, IsAdultTrue) {
    Citizen c(1, "Adult", 18, 1);
    EXPECT_TRUE(c.isAdult());
}

TEST(CitizenTest, IsAdultFalse) {
    Citizen c(2, "Minor", 17, 1);
    EXPECT_FALSE(c.isAdult());
}

TEST(CitizenTest, SetDistrictId) {
    Citizen c(1, "Name", 30, 1);
    c.setDistrictId(3);
    EXPECT_EQ(c.getDistrictId(), 3);
}

// ── Hospital standalone behaviour ────────────────────────────────────────────

TEST(HospitalTest, IsLargeHospitalTrue) {
    Hospital h(1, "Big", 201, true);
    EXPECT_TRUE(h.isLargeHospital());
}

TEST(HospitalTest, IsLargeHospitalFalse) {
    Hospital h(2, "Small", 200, false);
    EXPECT_FALSE(h.isLargeHospital());
}

// ── School standalone behaviour ──────────────────────────────────────────────

TEST(SchoolTest, IsPrimaryTrue) {
    School s(1, "P-School", 400, "primary");
    EXPECT_TRUE(s.isPrimary());
}

TEST(SchoolTest, IsPrimaryFalse) {
    School s(2, "Lyceum", 300, "secondary");
    EXPECT_FALSE(s.isPrimary());
}

// ── Aggregation independence ─────────────────────────────────────────────────

TEST(AggregationTest, CitizenExistsAfterDistrictRemovesIt) {
    District d(1, "West", 6.0);
    Citizen  c(42, "Test Citizen", 55, 1);

    d.addCitizen(c);
    d.removeCitizenById(42);

    // The citizen object was not destroyed — it still reports correct data
    EXPECT_EQ(c.getId(),    42);
    EXPECT_EQ(c.getAge(),   55);
    EXPECT_STREQ(c.getFullName(), "Test Citizen");
}

TEST(AggregationTest, DistrictExistsAfterCityGoesOutOfScope) {
    District d(99, "Standalone", 3.0);
    {
        City city("TempCity", 0);
        city.addDistrict(d);
        EXPECT_EQ(city.getDistrictCount(), 1);
    }
    // city is destroyed here, but district is fine
    EXPECT_EQ(d.getId(), 99);
    EXPECT_STREQ(d.getName(), "Standalone");
}
