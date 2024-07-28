#include <gtest/gtest.h>
#include "Farbe.hpp"

// Test the default constructor
TEST(FarbeTest, DefaultConstructor)
{
    Farbe color;
    EXPECT_EQ(color[0], 255);
    EXPECT_EQ(color[1], 255);
    EXPECT_EQ(color[2], 255);
}

// Test the parameterized constructor
TEST(FarbeTest, ParameterizedConstructor)
{
    Farbe color(100, 150, 200);
    EXPECT_EQ(color[0], 100);
    EXPECT_EQ(color[1], 150);
    EXPECT_EQ(color[2], 200);
}

// Test the operator[] getter
TEST(FarbeTest, IndexOperatorGetter)
{
    Farbe color(10, 20, 30);
    EXPECT_EQ(color[0], 10);
    EXPECT_EQ(color[1], 20);
    EXPECT_EQ(color[2], 30);
}

// Test the operator[] setter
TEST(FarbeTest, IndexOperatorSetter)
{
    Farbe color;
    color[0] = 50;
    color[1] = 100;
    color[2] = 150;
    EXPECT_EQ(color[0], 50);
    EXPECT_EQ(color[1], 100);
    EXPECT_EQ(color[2], 150);
}

// Test index out of range
TEST(FarbeTest, IndexOutOfRange)
{
    Farbe color;
    EXPECT_THROW(color[-1], std::out_of_range);
    EXPECT_THROW(color[3], std::out_of_range);
}

// Test the toString method
TEST(FarbeTest, ToString)
{
    Farbe color(10, 20, 30);
    EXPECT_EQ(color.toString(), "10 20 30 ");
}

// Test the ausgabe method with LONG_OUTPUT = true
TEST(FarbeTest, AusgabeLongOutput)
{
    testing::internal::CaptureStdout();
    Farbe::LONG_OUTPUT = true;
    Farbe color(10, 20, 30);
    color.ausgabe();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Rotanteil: 10"), std::string::npos);
    EXPECT_NE(output.find("Grünanteil: 20"), std::string::npos);
    EXPECT_NE(output.find("Blauanteil: 30"), std::string::npos);
}

// Test the ausgabe method with LONG_OUTPUT = false
TEST(FarbeTest, AusgabeShortOutput)
{
    testing::internal::CaptureStdout();
    Farbe::LONG_OUTPUT = false;
    Farbe color(10, 20, 30);
    color.ausgabe();
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(output, "10 20 30 ");
}

// Test the addition operator
TEST(FarbeTest, AdditionOperator)
{
    Farbe color1(100, 150, 200);
    Farbe color2(50, 100, 150);
    Farbe result = color1 + color2;
    EXPECT_EQ(result[0], (100 + 50) % 256);
    EXPECT_EQ(result[1], (150 + 100) % 256);
    EXPECT_EQ(result[2], (200 + 150) % 256);
}

// Test the stream insertion operator
TEST(FarbeTest, StreamInsertionOperator)
{
    std::ostringstream oss;
    Farbe color(10, 20, 30);
    Farbe::LONG_OUTPUT = false;
    oss << color;
    EXPECT_EQ(oss.str(), "10 20 30 ");
}

// Test the stream insertion operator with LONG_OUTPUT = true
TEST(FarbeTest, StreamInsertionOperatorLongOutput)
{
    testing::internal::CaptureStdout();
    Farbe color(10, 20, 30);
    Farbe::LONG_OUTPUT = true;
    std::cout << color;
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_NE(output.find("Rotanteil: 10"), std::string::npos);
    EXPECT_NE(output.find("Grünanteil: 20"), std::string::npos);
    EXPECT_NE(output.find("Blauanteil: 30"), std::string::npos);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
