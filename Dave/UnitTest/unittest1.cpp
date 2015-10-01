#include "stdafx.h"
#include "CppUnitTest.h"
#include <SFML/Graphics.hpp>
#include "block.h"
#include "Vector2D.h"
#include "Collidable.h"
#include "Collision.h"
#include "Movable.h"
#include "Npc.h"
#include "Player.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{		
	TEST_CLASS(BlockTest) //!< test class for Blocks
	{
	public:
		/*
		TEST_METHOD(setBlockTest) //!< setBlock test function
		{
			
			
			Block b;
			sf::Texture texture;
			texture.loadFromFile("testimg.png");
			b.setBlock(1,50,50, texture);
			b.getHits();
			b.getSpecial();
			b.getiMass();
			b.getElasticity();
			
			Assert::AreEqual(b.getPos().getX(), 50.f);
			Assert::AreEqual(b.getPos().getY(), 50.f);
			Assert::AreEqual(b.getiMass(), 0.f);
			Assert::AreEqual(b.getHits(), 1);
			Assert::AreEqual(b.getElasticity(), 0.01f);
			Assert::IsFalse(b.getSpecial());
			
			
		}
		*/
		TEST_METHOD(setSpecialTest) //!< setSpecial test function
		{
			Block b;
			b.setSpecial(true);

			Assert::IsTrue(b.getSpecial());
		}
		/*
		TEST_METHOD(setHitsTest) //!< setHits test function
		{
			Block b;
			b.setHits(3);

			Assert::AreEqual(b.getHits(),3);
		}

	//};

	//TEST_CLASS(CollidableTest)  //!< test class for Collidable objects
//	{
	//public:
		
		TEST_METHOD(setSizeTest) //!< setSize test function
		{
			Collidable c;
			c.setSize(Vector2D(5.f,7.f));

			Assert::AreEqual(c.getSize().getX(), 5.f);
			Assert::AreEqual(c.getSize().getY(), 7.f);
		}

		TEST_METHOD(setiMassTest) //!< setiMass test function
		{
			Collidable c;
			c.setiMass(0.8f);

			Assert::AreEqual(c.getiMass(), 0.8f);
		}

		TEST_METHOD(setElasticityTest) //!< setElasticity test function
		{
			Collidable c;
			c.setElasticity(1.5f);

			Assert::AreEqual(c.getElasticity(), 1.3f);
		}
		
		TEST_METHOD(setNormalTest) //!< setNormal test function
		{
			Collidable c;
			c.setNormal(Vector2D(0.f,1.f));

			Assert::AreEqual(c.getNormal().getX(), 0.f);
			Assert::AreEqual(c.getNormal().getY(), 1.f);
		}
		
		TEST_METHOD(setDestroyableTest) //!< setDestroyable test function
		{
			Collidable c;
			c.setDestroyable(true);

			Assert::IsTrue(c.getDestroyable());
		}

//	};
//	TEST_CLASS(MovableTest) //!< Test class for movable objects
	//{
//	public:
		
		TEST_METHOD(setPosTest)
		{
				Movable m;
				m.setPos(Vector2D(200.f,500.f));

				Assert::AreEqual(m.getPos().getX(), 200.f);
				Assert::AreEqual(m.getPos().getY(), 500.f);
		}

		TEST_METHOD(setVelTest)
		{
				Movable m;
				m.setVel(Vector2D(20.f,30.f));

				Assert::AreEqual(m.getVel().getX(), 20.f);
				Assert::AreEqual(m.getVel().getY(), 30.f);
		}

		TEST_METHOD(setAccTest)
		{
				Movable m;
				m.setAcc(Vector2D(0.f,10.f));

				Assert::AreEqual(m.getAcc().getX(), 0.f);
				Assert::AreEqual(m.getAcc().getY(), 10.f);
		}
		
		
		TEST_METHOD(setPlayableTest)
		{
			Movable m;
			m.setPlayable(true);
			
			Assert::IsTrue(m.getPlayable());
		}

		TEST_METHOD(setAnimatePropertiesTest)
		{
			Movable m;
			m.setAnimateProperties(4, 20, 30, 1);
			Assert::AreEqual(m.getCols(), 4);
			Assert::AreEqual(m.getImageHeight(), 20.f);
			Assert::AreEqual(m.getImageWidth(), 30.f);
			Assert::AreEqual(m.getAnimDelay(), 1.f);
		}

	//};

//	TEST_CLASS(NpcTest) //!< test class for NPC's 
//	{
	//public:
		
		TEST_METHOD(NpcConstructorTest)
		{
			Npc npc;
			
			Assert::AreEqual(npc.getiMass(), 0.5f);
			Assert::AreEqual(npc.getElasticity(), 0.5f);
			Assert::AreEqual(npc.getAcc().getX(), 0.f);
			Assert::AreEqual(npc.getAcc().getY(), 5.f);
		}

	//};

	//TEST_CLASS(PlayerTest) //!< test class for Player
	//{
	//public:
		
		TEST_METHOD(playerConstructorTest)
		{
			Player p;

			Assert::AreEqual(p.getAcc().getX(), 0.f);
			Assert::AreEqual(p.getAcc().getY(), 5.0f);
			Assert::AreEqual(p.getiMass(), 0.2f);
			Assert::AreEqual(p.getElasticity(), 0.2f);
			Assert::IsTrue(p.getPlayable());
			Assert::AreEqual(p.getAnimDelay(), 0.3f);
			
		}
		*/
	};
}