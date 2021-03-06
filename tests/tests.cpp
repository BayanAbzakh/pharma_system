#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "C:\c++\la project\main.cpp"

TEST_CASE("checking the main functions of class inventory") {

    inventory give_me_a_name;
    CHECK(inventory().getPrice() == 300);
    CHECK(inventory().getId() == "4");
    CHECK(inventory().getName()== "Tramal" );
    CHECK(inventory().getType() == "OTC");
}


TEST_CASE("checking the functions of class order") {
    order ord;
    CHECK(ord.delete_order() == 2);
    CHECK(ord.display_orders() == 1);
}

TEST_CASE("checking the main functions of class inventory") {

inventory give_me_a_name;
CHECK(inventory().getPrice() == 200);
CHECK(inventory().getId() == "5");
CHECK(inventory().getPrice() == 140);
CHECK(inventory().getId() == "12");
CHECK(inventory().getName()== "Nabilet (5mg)" );
CHECK(inventory().getType() == "OTC");
}

TEST_CASE("checking the functions of class order") {
    order ord;
    CHECK(ord.delete_order() == 1);
    CHECK(ord.display_orders() == 6);
}
