// Lab7_2022.cpp : This file contains the 'main' function. Program execution begins and ends there.
//My attempt at creating a room with a bouncing ball in it :)

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFPhysics.h>

using namespace std;
using namespace sf;
using namespace sfp;

int main() {
	RenderWindow window(VideoMode(800, 600), "Bounce");
	World world(Vector2f(0, 1));

	//this creates the ball
	PhysicsCircle ball;
	ball.setCenter(Vector2f(400, 300));
	ball.setRadius(20);
	ball.setVelocity(Vector2f(.5, 1));
	world.AddPhysicsBody(ball);

	//this is the block at the center
	PhysicsRectangle box;
	box.setStatic(true);
	box.setCenter(Vector2f(400, 300));
	box.setSize(Vector2f(90, 90));
	world.AddPhysicsBody(box);

	//counts how many times the ball hits the box
	int bangCount(1);
	box.onCollision = [&bangCount](PhysicsBodyCollisionResult result) {
		cout << "bang " << bangCount << endl;
		bangCount++; };

	//this is the floor
	PhysicsRectangle floor;
	floor.setSize(Vector2f(800, 20));
	floor.setCenter(Vector2f(400, 590));
	floor.setStatic(true);
	world.AddPhysicsBody(floor);

	//counts how many times the ball hits the floor
	int thudCount(0);
	floor.onCollision = [&thudCount](PhysicsBodyCollisionResult result) {
		cout << "thud " << thudCount << endl;
		thudCount++; };

	//this is the ceiling
	PhysicsRectangle ceiling;
	ceiling.setSize(Vector2f(1600, 20));
	ceiling.setCenter(Vector2f(10, 10));
	ceiling.setStatic(true);
	world.AddPhysicsBody(ceiling);

	//this is the left wall
	PhysicsRectangle wall1;
	wall1.setSize(Vector2f(40, 600));
	wall1.setCenter(Vector2f(5, 300));
	wall1.setStatic(true);
	world.AddPhysicsBody(wall1);

	//this is the right wall
	PhysicsRectangle wall2;
	wall2.setSize(Vector2f(40, 600));
	wall2.setCenter(Vector2f(795, 300));
	wall2.setStatic(true);
	world.AddPhysicsBody(wall2);

	//if the bang count is equal to 3 then the program closes using exit(0);
	if (bangCount == '3')
		return(0);

	Clock clock;
	Time lastTime(clock.getElapsedTime());
	while (true) {
		// calculate MS since last frame
		Time currentTime(clock.getElapsedTime());
		Time deltaTime(currentTime - lastTime);
		int deltaTimeMS(deltaTime.asMilliseconds());
		if (deltaTimeMS > 0) {
			world.UpdatePhysics(deltaTimeMS);
			lastTime = currentTime;
		}
		window.clear(Color(0, 0, 0));
		window.draw(ball);
		window.draw(box);
		window.draw(floor);
		window.draw(ceiling);
		window.draw(wall1);
		window.draw(wall2);
		window.display();
	}
}
