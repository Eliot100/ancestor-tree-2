#include "doctest.h"
#include "FamilyTree.hpp"
// #include <string>
// #include <iostream>;

/*
 * @author Eli, Ron and Tal
 *
 */
 family::Tree addFamily(){
	 family::Tree T ("Yosef");
	 T.addFather("Yosef", "Yaakov") 
	 .addMother("Yosef", "Rachel")   
	 .addFather("Yaakov", "Isaac")
	 .addMother("Yaakov", "Rivka")
	 .addFather("Rachel", "Bob")
	 .addMother("Rachel", "Rut")
	 .addFather("Isaac", "Avraham")
	 .addMother("Isaac", "Noy")
	 .addFather("Rivka", "Terah")
	 .addMother("Rivka", "lee")
	 .addFather("Bob", "Ranan")
	 .addMother("Bob", "Michela")
	 .addFather("Rut", "Ran")
	 .addMother("Rut", "Mor")
	 .addFather("Ran", "Ron")
	 .addMother("Ran", "Miriam")
     .addFather("Miriam", "More")
     .addMother("Miriam", "Moria")
     .addMother("More", "Nurit");

	 return T;
 }
 
TEST_CASE(" Check relation ") {
	family::Tree T = addFamily();
	
	CHECK( T.relation("Yosef") == "me" );
	CHECK( T.relation("Yaakov") == "father" );
	CHECK( T.relation("Rachel") == "mother" );
	CHECK( T.relation("Isaac") == "grandfather" );
	CHECK( T.relation("Rivka") == "grandmother" ); //5
	CHECK( T.relation("Bob") == "grandfather" );
	CHECK( T.relation("Rut") == "grandmother" );
	CHECK( T.relation("Avraham") == "great-grandfather" );
	CHECK( T.relation("Noy") == "great-grandmother" );
	CHECK( T.relation("Terah") == "great-grandfather" );//10
	CHECK( T.relation("lee") == "great-grandmother" );
	CHECK( T.relation("Ranan") == "great-grandfather" );
	CHECK( T.relation("Michela") == "great-grandmother" );
	CHECK( T.relation("Ran") == "great-grandfather" );
	CHECK( T.relation("Mor") == "great-grandmother" );//15
	CHECK( T.relation("Ron") == "great-great-grandfather" );
	CHECK( T.relation("Miriam") == "great-great-grandmother" );
	CHECK( T.relation("Rom") == "unrelated" );
	CHECK( T.relation("Michel") == "unrelated" );
	CHECK( T.relation("lene") == "unrelated" );//20
	CHECK( T.relation("Ruti") == "unrelated" );
	CHECK( T.relation("Rotem") == "unrelated" );
}

TEST_CASE(" Check find ") {
	family::Tree T = addFamily();
	CHECK( T.find("me") == "Yosef" );
	CHECK( T.find("father") == "Yaakov" );
	CHECK( T.find("mother") == "Rachel" );//25
	CHECK( ( T.find("grandfather") == "Isaac" || T.find("grandfather") == "Bob" ) ); 
	CHECK( ( T.find("grandmother") == "Rivka" || T.find("grandmother") == "Rut" ) );
	CHECK(( (T.find("great-grandfather") == "Avraham" || T.find("great-grandfather") == "Terah") 
		|| (T.find("great-grandfather") == "Ranan" || T.find("great-grandfather") == "Ran") ));
	CHECK(( (T.find("great-grandmother") == "Noy" || T.find("great-grandmother") == "lee" )
		|| ( T.find("great-grandmother") == "Michela" || T.find("great-grandmother") == "Mor" ) ));
	CHECK( T.find("great-great-grandfather") == "Ron" );//30
	CHECK( T.find("great-great-grandmother") == "Miriam" ); 
	CHECK( T.find("me") == "Yaakov" );
	CHECK( T.find("father") == "Miriam" );
	CHECK( T.find("grandfather") == "Miriam" );
	CHECK( T.find("great-great-grandmother") == "Noy" ); //35
	CHECK( T.find("great-great-grandmother") == "Ron" ); 
	CHECK( T.find("great-great-grandmother") == "Ran" ); 
	CHECK( T.find("great-great-grandmother") == "Terah" ); 
	CHECK( ( T.find("grandfather") == "Bob" || T.find("grandfather") == "Ran" ) ); 
	CHECK( ( T.find("grandmother") == "Terah" || T.find("grandmother") == "Mor" ) );//40
}
 
 
TEST_CASE(" Check remove") {
 	family::Tree T = addFamily();

	T.remove("Rotem");
	CHECK( T.relation("Rotem") == "unrelated" );
	T.remove("Rachel");
	CHECK( T.relation("Rachel") == "unrelated" );
	T.remove("Avraham");
	CHECK( T.relation("Avraham") == "unrelated" );
	T.remove("Michela");
	CHECK( T.relation("Michela") == "unrelated" );
	T.remove("Rivka");
	CHECK( T.relation("Rivka") == "unrelated" );//45
	T.remove("Miriam");
	CHECK( T.relation("Miriam") == "unrelated" );
	T.remove("Mor");
	CHECK( T.relation("Mor") == "unrelated" );
	T.remove("Rotem");
	CHECK( T.relation("Rut") == "unrelated" );
	T.remove("Rut");
	CHECK( T.relation("Rotem") == "unrelated" );
	T.remove("Yosef");
	CHECK( T.relation("Yosef") == "unrelated" );//50
	T.remove("Isaac");
	CHECK( T.relation("Isaac") == "unrelated" );
	T.remove("Noy");
	CHECK( T.relation("Noy") == "unrelated" );
	T.remove("Avraham");
	CHECK( T.relation("Avraham") == "unrelated" );
	T.remove("Bob");
	CHECK( T.relation("Bob") == "unrelated" );
	T.remove("Ranan");
	CHECK( T.relation("Ranan") == "unrelated" );//55
	
	CHECK( T.find("great-great-grandfather") == "Ron" );
	CHECK( T.find("great-great-grandmother") == "Miriam" ); 
	CHECK( T.find("me") == "Yaakov" );
	CHECK( T.find("father") == "Miriam" );
	CHECK( T.find("grandfather") == "Miriam" );//60
	CHECK( T.find("great-great-grandmother") == "Noy" ); 
	CHECK( T.find("great-great-grandmother") == "Ron" ); 
	CHECK( T.find("great-great-grandmother") == "Ran" ); 
	CHECK( T.find("great-great-grandmother") == "Terah" ); 
	CHECK( T.find("great-great-grandmother") == "Miriam" ); //65
}
TEST_CASE(" first case ") {
    family::Tree T = addFamily();
            CHECK(T.relation("More") == "More");
    T.remove("More");
            CHECK(T.relation("More") == "unrelated");
    T.remove("Nurit");
            CHECK(T.relation("Nurit") == "unrelated");
            CHECK(T.relation("") == "unrelated");
            CHECK(T.find("great-great-great-grandfather") == "Terah");//70
            CHECK(T.find("great-great-grandfather") == "Avraham");
            CHECK(T.relation("afik") == "unrelated");
            CHECK(T.relation("taltal") == "unrelated");
            CHECK(T.relation("yuvali") == "unrelated");
            CHECK(T.relation("shuval") == "unrelated");
            CHECK(T.relation("morya") == "unrelated");
            CHECK(T.relation("tomery") == "unrelated");
            CHECK(T.relation("adiy") == "unrelated");
            CHECK(T.relation("edean") == "unrelated");
            CHECK(T.relation("lelus") == "unrelated");//80
    T.remove("Ranan");
            CHECK(T.relation("Ranan") == "unrelated");
    T.remove("Michela");
            CHECK(T.relation("Michela") == "unrelated");
    T.remove("Rut");
            CHECK(T.relation("Rut") == "unrelated");
    T.remove("Mor");
            CHECK(T.relation("Mor") == "unrelated");
    T.remove("Ran");
            CHECK(T.relation("Ran") == "unrelated");
    T.remove("Miriam");
            CHECK(T.relation("Miriam") == "unrelated");
    T.remove("Mor");
            CHECK(T.relation("Mor") == "unrelated");
    T.remove("Rotem");
            CHECK(T.relation("Rut") == "unrelated");
    T.remove("Rut");
            CHECK(T.relation("Rotem") == "unrelated");
    T.remove("Yosef");
            CHECK(T.relation("Yosef") == "unrelated");//90
    T.remove("Isaac");
            CHECK(T.relation("Isaac") == "unrelated");
    T.remove("Noy");
            CHECK(T.relation("Noy") == "unrelated");
    T.remove("Avraham");
            CHECK(T.relation("Avraham") == "unrelated");
    T.remove("Bob");
            CHECK(T.relation("Bob") == "unrelated");
    T.remove("More");
            CHECK(T.relation("More") == "unrelated");
            CHECK( !(T.find("great-great-grandfather") == "Ron") );
            CHECK( !( T.find("great-great-grandmother") == "Miriam" ));
            CHECK( !( T.find("me") == "Yaakov" ));
            CHECK( !(T.find("father") == "Miriam") );
            CHECK( !( T.find("grandfather") == "Miriam" ));//100

}
