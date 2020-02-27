#include "BreakoutMain.h"
#include <conio.h>

using namespace std;

int main()
{
    Game myGame;
    if (!myGame.Start()) //did we initialize everything?
    {
        return EXIT_FAILURE;
    }
    return myGame.Update();
    //exit
    return 0;
}

Brick brick; //define a brick object
vector<Brick> Bricks(31, Brick(brick)); //Create our vector(list) of bricks

bool Game::Start() //setting up the game
{
    paddleSoundBuffer.loadFromFile("SFX/paddlebounce.wav");
    wallSoundBuffer.loadFromFile("SFX/wallbounce.wav");
    brickSoundBuffer.loadFromFile("SFX/blockbounce.wav");

    font.loadFromFile("arial.ttf");
    scoreText.setFont(font);
    livesText.setFont(font);
    scoreText.setPosition(0, windowHeight - 50);
    livesText.setPosition(windowWidth - 100, windowHeight - 50);
    scoreText.setCharacterSize(24);
    livesText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    livesText.setFillColor(sf::Color::White);

    sf::VideoMode vMode(windowWidth, windowHeight);
    window.create(vMode, "Breakout!");
    window.setFramerateLimit(60);

    //setting up bricks
    srand(time(NULL));
    for (int i = 0; i < 31; i++)
    {
        Bricks[i].bShape.setSize(sf::Vector2f(100, 50));
        if (i <= 10)
        {
            //Bottom row
            Bricks[i].bShape.setFillColor(sf::Color(rand() % 35 + 180, 0, 0, 255));
            Bricks[i].bShape.setPosition(100 * i, 0);
        }
        else if (i > 20)
        {
            //top row
            Bricks[i].bShape.setFillColor(sf::Color(0, rand() % 35 + 180, 0, 255));
            Bricks[i].bShape.setPosition(100 * (i -21), 100);
        }
        else if (i > 10)
        {
            //middle
            Bricks[i].bShape.setFillColor(sf::Color(0, 0, rand() % 35 + 180, 255));
            Bricks[i].bShape.setPosition(100 * (i - 11), 50);
        }
    }

    //setup borders
    top.setSize(sf::Vector2f(windowWidth, 1));
    top.setPosition(0, 0);
    top.setFillColor(sf::Color::Black);
    bottom.setSize(sf::Vector2f(windowWidth, 1));
    bottom.setPosition(sf::Vector2f(0, windowHeight - 1));
    bottom.setFillColor(sf::Color::Black);
    left.setSize(sf::Vector2f(1, windowHeight));
    left.setPosition(sf::Vector2f(0, 0));
    left.setFillColor(sf::Color::Black);
    right.setSize(sf::Vector2f(1, windowHeight));
    right.setPosition(sf::Vector2f(windowWidth - 1, 0));
    right.setFillColor(sf::Color::Black);

    return true;
}

int Game::Update()
{
    Paddle paddle;
    paddle.pShape.setSize(sf::Vector2f(120.f, 15.f));
    paddle.pShape.setFillColor(sf::Color::Yellow);
    paddle.pShape.setPosition(windowHeight - (windowHeight / 5), windowWidth / 2);
    //setup ball
    Ball ball;
    ball.ballShape.setRadius(ball.ballRadius);
    ball.ballShape.setPosition(paddle.pShape.getPosition().x, paddle.pShape.getPosition().y - 75);
    ball.ballShape.setFillColor(sf::Color::Cyan);
    ball.ballVelocity.x = rand() % 10;
    ball.ballVelocity.y = -5;

    while (window.isOpen())
    {
        //Mouse movement for paddle
        if (sf::Mouse::getPosition(window).x > paddle.pShape.getSize().x / 2 && sf::Mouse::getPosition(window).x < window.getSize().x - paddle.pShape.getSize().x / 2)
        {
            paddle.pShape.setPosition(sf::Mouse::getPosition(window).x - paddle.pShape.getSize().x / 2, paddle.pShape.getPosition().y);
        }

        ball.ballShape.move(ball.ballVelocity);
        //handle ball collisons with borders
        if (top.getGlobalBounds().intersects(ball.ballShape.getGlobalBounds()))
        {
            ball.Bounce(0, top, ball.ballShape);
            sound.setBuffer(wallSoundBuffer);
            sound.play();
        }
        if (bottom.getGlobalBounds().intersects(ball.ballShape.getGlobalBounds()))
        {
            //reset code goes here
            ball.Bounce(0, bottom, ball.ballShape);
            lives -= 1;
            if (lives == 0)
            {
                //game over
                return 1;
            }
        }
        if (left.getGlobalBounds().intersects(ball.ballShape.getGlobalBounds()) ||
            right.getGlobalBounds().intersects(ball.ballShape.getGlobalBounds()))
        {
            ball.Bounce(1, left, ball.ballShape);
            sound.setBuffer(wallSoundBuffer);
            sound.play();
        }
        //paddle and ball collision
        if (paddle.pShape.getGlobalBounds().intersects(ball.ballShape.getGlobalBounds()))
        {
            ball.Bounce(0, paddle.pShape, ball.ballShape);
            sound.setBuffer(paddleSoundBuffer);
            sound.play();
        }

        for (int i = 0; i < Bricks.size(); i++)
        {
            if (Bricks[i].bShape.getGlobalBounds().intersects(ball.ballShape.getGlobalBounds()))
            {
                ball.Bounce(0, Bricks[i].bShape, ball.ballShape);
                Bricks[i].bShape.setPosition(1200, 0);
                score += 1;
                ball.ballVelocity = ball.ballVelocity * 1.03f;
                if (score == 30)
                {
                    return 1;
                }
                sound.setBuffer(brickSoundBuffer);
                sound.play();
            }
        }

        sf::Event event;
        //pollEvent is our window updating
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        window.clear();
        //Draw our bricks
        for (int i = 0; i < Bricks.size(); i++)
        {
            window.draw(Bricks[i].bShape);
        }
        scoreText.setString("Score: " + to_string(score));
        livesText.setString("Lives: " + to_string(lives));
        
        window.draw(scoreText);
        window.draw(livesText);
        window.draw(paddle.pShape);
        window.draw(ball.ballShape);
        window.display();

    }
    return 0;
}