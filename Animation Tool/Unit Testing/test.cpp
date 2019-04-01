#include "pch.h"

#define private public
#define protected public

#include "QuadPart.h"

TEST(TestCaseName, TestName) {
	EXPECT_EQ(1, 1);
	EXPECT_TRUE(true);
}

TEST(QuadPartTests, Position) {
	float l_Value = 50.f;
	QuadPart l_QuadPart;
	l_QuadPart.SetPosition(sf::Vector2f(l_Value, l_Value));
	float x = l_QuadPart.m_Position.x;
	float y = l_QuadPart.m_Position.y;
	EXPECT_FLOAT_EQ(50.f, x);
	EXPECT_FLOAT_EQ(50.f, y);
}


int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();

	system("pause");
	return 0;
}