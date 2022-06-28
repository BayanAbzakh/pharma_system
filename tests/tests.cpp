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