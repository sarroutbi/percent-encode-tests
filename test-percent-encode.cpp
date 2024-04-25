#include "gtest/gtest.h"
#include "percent-encode.h"

const char* URL_EXAMPLE = "This is an example of a #string";
const char* URL_EXAMPLE_ENCODED = "This%20is%20an%20example%20of%20a%20%23string";

TEST(
    PercentTestBasicDummyTest,
    GivenWhenThen) {
  EXPECT_EQ("1", "1");
}

TEST(
    PercentTestEncodingCheck,
    GivenTwoStringsWhenGeneratedWithDifferentMethodsTheyWorkAppropriately) {
  const char* a = percent_encode(URL_EXAMPLE, strlen(URL_EXAMPLE));
  const char* b = printf_percent_encode(URL_EXAMPLE, strlen(URL_EXAMPLE));
  for (int i=0; i<std::max(strlen(a), strlen(b)); ++i) {
    EXPECT_EQ(a[i], b[i]);
    EXPECT_EQ(a[i], URL_EXAMPLE_ENCODED[i]);
  }
  EXPECT_EQ(strlen(a), strlen(b));
}


int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
