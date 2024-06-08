#define BOOST_TEST_MODULE mytests
#include <boost/test/included/unit_test.hpp>

#include "fileIO.h"

BOOST_AUTO_TEST_CASE(read_score_from_file_test) {
    FileIO fileIO;
    std::string score;
    BOOST_CHECK_EQUAL(fileIO.readScoreFromFile(score), 0);
    BOOST_CHECK_EQUAL(score, "Your final score: 42");
}

BOOST_AUTO_TEST_CASE(read_score_file_not_found_test) {
    FileIO fileIO;
    std::string score;
    BOOST_CHECK_EQUAL(fileIO.readScoreFromFile(score), -1);
}

BOOST_AUTO_TEST_CASE(write_score_to_file_test) {
    FileIO fileIO;
    BOOST_CHECK_EQUAL(fileIO.writeScoreToFile(42), 0);
}

BOOST_AUTO_TEST_CASE(write_score_exception_test) {
    FileIO fileIO;
    BOOST_CHECK_EQUAL(fileIO.writeScoreToFile(42), -1);
}