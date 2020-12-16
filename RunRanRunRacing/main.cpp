#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include <SFML/OpenGL.hpp>
#include<SFML/Main.hpp>
#include<SFML/Network.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>

#include"Menu.h"
#include"pauseMenu.h"
#include"HowToPlay.h"

#include<map>
#include<time.h>
#include<iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace sf;
sf::FloatRect texture_rect;
sf::Text distance;
sf::RectangleShape playerOILBar;
sf::RectangleShape playerOILBarBack;
sf::RectangleShape playerHpBar;
sf::RectangleShape playerHpBarBack;
sf::RectangleShape shape;
sf::Font* font;
sf::Text content;
/*sf::Sprite coin;
sf::FloatRect coin_texture;
sf::FloatRect getCoinBounds()
{
    return coin_texture;
}*/

int width = 1024;
int height = 768;
int distanceScore = 0;
unsigned int roadW = 2000;
int segL = 210; //segment length
float camD = 0.84; //camera depth
bool isAlive = false;
bool isGameStarted;
bool ispaused;
bool isHTP = false;
bool isMenu = true;
bool isHS = false;
void updateAndSaveScore();
void initContent(unsigned content_character_size);
void generateObstacles(sf::Sprite[]);
void render(sf::RenderTarget* target);
void drawQuad(RenderWindow& w, Color c, int x1, int y1, int w1, int x2, int y2, int w2)
{

    ConvexShape shape(4);
    shape.setFillColor(c);
    shape.setPoint(0, Vector2f(x1 - w1, y1));
    shape.setPoint(1, Vector2f(x2 - w2, y2));
    shape.setPoint(2, Vector2f(x2 + w2, y2));
    shape.setPoint(3, Vector2f(x1 + w1, y1));
    w.draw(shape);
}

struct Line
{
    float x, y, z; //3d center of line
    float X, Y, W; //screen coord
    float curve, spriteX, clip, scale;
    float oilX;
    Sprite oilSp;
    sf::FloatRect oil_texture;
    Sprite sprite;

    Line()
    {
        oilX = spriteX = curve = x = y = z = 0;
    }

    void project(int camX, int camY, int camZ)
    {
        scale = camD / (z - camZ);
        X = (1 + scale * (x - camX)) * width / 2;
        Y = (1 - scale * (y - camY)) * height / 2;
        W = scale * roadW * width / 2;
    }

    void drawSprite(RenderWindow& app)
    {
        Sprite s = sprite;
        int w = s.getTextureRect().width;
        int h = s.getTextureRect().height;

        float destX = X + scale * spriteX * width / 2;
        float destY = Y + 4;
        float destW = w * W / 266;
        float destH = h * W / 266;

        destX += destW * spriteX; //offsetX
        destY += destH * (-1);    //offsetY

        float clipH = destY + destH - clip;
        if (clipH < 0) clipH = 0;

        if (clipH >= destH) return;
        s.setTextureRect(IntRect(0, 0, w, h - h * clipH / destH));
        s.setScale(destW / w, destH / h);
        s.setPosition(destX, destY);

        texture_rect = s.getGlobalBounds();
        app.draw(s);
    }
    sf::FloatRect getObstacleBounds()
    {
        return texture_rect;
    }
    /*void drawOil(sf::RenderWindow& app)
    {
        sf::Sprite os = oilSp;
        int w = os.getTextureRect().width;
        int h = os.getTextureRect().height;
        float destX = X + scale * oilX * width / 2;
        float destY = Y - 2;
        float destW = w * W / 266;
        float destH = h * W / 266;
        destX += destW * oilX;
        destY += destH * (-1);
        os.setTextureRect(sf::IntRect(0, 0, w, h - h / destH));
        os.setScale(destW / w, destH / h);
        os.setPosition(destX, destY);
        oil_texture = os.getGlobalBounds();
        app.draw(os);
    }*/
    sf::FloatRect getOilBounds()
    {
        return oil_texture;
    }
    float gety() { return y; }
    float getX() { return X; }
    float getY() { return Y; }
    float getW() { return W; }
    float getCurve() { return curve; }


};


int main()
{

    RenderWindow app(VideoMode(width, height), "Run Ran Run Racing!", sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close);
    app.setFramerateLimit(60);

    //menu
    Menu menu(app.getSize().x, app.getSize().y);
    //how to play
    HowToPlay htp(app.getSize().x, app.getSize().y);
    //high score

    //pause
    pauseMenu pausemenu(app.getSize().x / 4, app.getSize().y / 4);

    //scoreboard
    Clock clockForScore;
    float collideTime = 0;

    /*Texture tcoin;
    tcoin.loadFromFile("images/oil-item.png");
    tcoin.setSmooth(true);
    Sprite coin;
    coin.setTexture(tcoin);*/
    //oil drop
    float oilSpawnTimerMax = 20.f;
    float oilSpawnTimer;
    oilSpawnTimer = oilSpawnTimerMax;
    int maxOil = 8;
    bool mouseHeld = false;
    //mark point
    Font font;
    Text mark;
    if (!font.loadFromFile("Fonts/Cascadia.ttf"))
        std::cout << "game failed to load font" << "\n";

    float groundHeight = height / 1.4;
    float gravity = 20.0f;
    bool isJumping = false;
    float moveSpeed = 300.0f;

    sf::Text endText;
    sf::Text scoreEndText;
    sf::Text highscoretext;

    highscoretext.setFont(font);
    highscoretext.setCharacterSize(72);
    highscoretext.setFillColor(sf::Color::White);
    highscoretext.setPosition(app.getSize().x/2  - scoreEndText.getGlobalBounds().width / 2, 450.f);
    highscoretext.setOutlineColor(sf::Color::Black);
    highscoretext.setOutlineThickness(1.f);

   



    distance.setFont(font);
    distance.setCharacterSize(18);
    distance.setFillColor(sf::Color::Black);
    distance.setString("X");
    distance.setPosition(25.f, 25.f);

    

    //----CREATE COLLIDER-------//
    CircleShape collider(30);
    float colliderX = width / 2 - 40;
    float colliderY = height / 2 + 200;
    collider.setPosition(colliderX, colliderY);

    //------PLAYER SETUP--------//
    Vector2i playerSize(210, 350); //size of each frame

    Texture playerFoto;
    playerFoto.loadFromFile("images/man2.png");


    Sprite player(playerFoto);
    player.setPosition(width / 2 - 75, height / 2 - 50);

    int framesNum = 27;
    float animDuration = 0.45; //seconds

    Clock clockForPlayer;
    float deltatime = 0; //for elapsed time

        //----LOAD water----//
    Texture toil;
    toil.loadFromFile("images/oil-item.png");
    toil.setSmooth(true);
    Sprite oilSp;
    oilSp.setTexture(toil);

    //----LOAD SOUNDS-------//
    //àÊÕÂ§¢ÂÑº
    SoundBuffer turnb;
    turnb.loadFromFile("images/turn sound.ogg");
    Sound playJ(turnb);
    //àÊÕÂ§ª¹
    SoundBuffer collisonbuff;
    collisonbuff.loadFromFile("images/hit-hugh.ogg");
    Sound collideSound(collisonbuff);
    //àÊÕÂ§µÃºÁ×Í
    SoundBuffer hss;
    hss.loadFromFile("images/get-HS.ogg");
    Sound hssSound(hss);
    //ÎÔÇ
    SoundBuffer collisonheal;
    collisonheal.loadFromFile("images/heal.ogg");
    Sound healSound(collisonheal);
    //¢Ç´¹éÓ
    SoundBuffer collisonbot;
    collisonbot.loadFromFile("images/bottle.ogg");
    Sound botSound(collisonbot);
    //à¾Å§¾×é¹
    Music gameMusic;
    gameMusic.openFromFile("images/bg-sound.ogg");
    gameMusic.setLoop(true);

    app.setKeyRepeatEnabled(false);
    gameMusic.play();
    /// <summary>
    /// ////////////////////////////////////////////
    /// </summary>
    /// <returns></returns>

    Texture t[50];
    Sprite object[50];
    for (int i = 1; i <= 12; i++)
    {
        t[i].loadFromFile("images/" + std::to_string(i) + ".png");
        t[i].setSmooth(true);
        object[i].setTexture(t[i]);
    }

    Texture bg;
    bg.loadFromFile("images/bg.png");
    bg.setRepeated(true);
    Sprite sBackground(bg);
    sBackground.setTextureRect(IntRect(0, 0, 5000, 411));
    sBackground.setPosition(-200000, -100);
    sBackground.setScale(sf::Vector2f(100.0f, 2.0f));


    Texture bg3;
    bg3.loadFromFile("images/bgmenu3.png");
    Sprite hsBackground(bg3);
    

    float playerX = 0;
    int pos = 0;
    int H = 1500;
    int oil_MAX = 5100;
    int oil;
    oil = oil_MAX;
    int hpMax = 100;
    int hp;
    hp = hpMax;
    std::vector<Line> lines;

    for (int i = 0; i < 20000; i++)
    {
        Line line;
        line.z = i * segL;

        if (i > 300 && i < 700)
        {
            line.curve = 0.5;
        }
        if (i > 1100)
        {
            line.curve = -0.7;
        }
        //object

        if (i < 300 && i % 20 == 0)
        {
            line.spriteX = -1.7; line.sprite = object[5];
        }
        if (i % 17 == 0)
        {
            line.spriteX = 2.0; line.sprite = object[6];
        }
        if (i % 50 == 0)
        {
            line.spriteX = 2.0; line.sprite = object[1];
        }
        if (i > 300 && i % 20 == 0)
        {
            line.spriteX = -1.4; line.sprite = object[2];
        }
        if (i > 800 && i % 20 == 0)
        {
            line.spriteX = -1.5; line.sprite = object[1];
        }
        if (i == 400)
        {
            line.spriteX = -1.6; line.sprite = object[9];
        }
        if (i > 750) line.y = sin(i / 30.0) * 1500;


        //item
        //¢Ç´
        if (i > 200 && (i + 30) % 1000 == 0)
        {
            //lines[i].oilX = 0.5; lines[i].oilSp = object[3];
            line.spriteX = -0.5;
            line.sprite = object[3];
        }
        /*//ËÑÇã¨
        if (i > 200 && (i + 29) % 900 == 0)
        {
            //lines[i].oilX = 0.5; lines[i].oilSp = object[3];
            line.spriteX = -0.2;
            line.sprite = object[7];
        }*/
        //·Õè¡Ñé¹ÂÒÇ
        if (i > 150 && i % 69 == 0)
        {
            //lines[i].oilX = -2.5; lines[i].oilSp = object[3];
            line.spriteX = rand() % 2 - 0.4;
            line.sprite = object[12];
        }
        //ËÔ¹
        if (i > 101 && (i - 21) % 98 == 0)
        {
            //lines[i].oilX = 2.2; lines[i].oilSp = object[3];
            line.spriteX = rand() % 2 - 0.9;
            line.sprite = object[11];
        }
        if (i > 500 && (i - 21) % 199 == 0)
        {
            //lines[i].oilX = 2.2; lines[i].oilSp = object[3];
            line.spriteX = rand() % 2 - 1.4;
            line.sprite = object[8];
        }
        if (i > 1500 && (i - 21) % 399 == 0)
        {
            //lines[i].oilX = 2.2; lines[i].oilSp = object[3];
            line.spriteX = rand() % 2 - 0.6;
            line.sprite = object[10];
        }

        /*
        if (i == 0)
        {
            line.spriteX = -0.5;
            line.sprite = object[3];//itemsp;
        }*/

        /*if (itemsp.getGlobalBounds().intersects(mark.getGlobalBounds()) && i == 0)
        {
            oil_MAX = oil_MAX + 1000;
        }*/
        if (i >= 100000)
        {
            i = 0;
        }
        lines.push_back(line);
    }

    int N = lines.size();

    //oil bar
    playerOILBar.setSize(sf::Vector2f(300.f, 25.f));
    playerOILBar.setFillColor(sf::Color::Blue);
    playerOILBar.setPosition(sf::Vector2f(700.f, 80.f));

    playerOILBarBack = playerOILBar;
    playerOILBarBack.setFillColor(sf::Color(25, 25, 25, 200));

    //hp bar
    playerHpBar.setSize(sf::Vector2f(300.f, 25.f));
    playerHpBar.setFillColor(sf::Color::Red);
    playerHpBar.setPosition(sf::Vector2f(700.f, 30.f));

    playerHpBarBack = playerHpBar;
    playerHpBarBack.setFillColor(sf::Color(25, 25, 25, 200));





    while (app.isOpen())
    {
        distanceScore++;
        std::stringstream ss;
        ss << "Distance : " << distanceScore;
        distance.setString(ss.str());
        int speed = 200;
        oil_MAX--;
        bool jump = false;
        Event e;
        while (app.pollEvent(e))
        {

            if (e.type == Event::Closed)
                app.close();
            if (e.type == Event::KeyReleased)
            {
                isJumping == false;
                if (isMenu == true)
                {
                    switch (e.key.code)
                    {
                    case::sf::Keyboard::W:
                        menu.MoveUp();
                        break;
                    case::sf::Keyboard::S:
                        menu.MoveDown();
                        break;

                    case::sf::Keyboard::Return:
                        switch (menu.GetPressedItem())
                        {
                        case 0:
                            std::cout << "Start" << "\n";
                            isGameStarted = true;
                            isAlive = true;
                            break;

                            break;
                        case 1:
                            std::cout << "How to Play" << "\n";
                            isHTP = true;

                            break;
                        case 2:
                            std::cout << "Scoreboard" << "\n";
                            
                            isHS = true;

                            break;
                        case 3:
                            app.close();
                            break;
                        }case::Keyboard::M:
                            isMenu = true;
                            break;

                    }

                }

                //pause

            }
        }
        //------PLAYER ANIMATION-----------//
        if (isAlive)
        {
            deltatime += clockForPlayer.restart().asSeconds();
            //---Get Current Frame----//
            int animFrame = static_cast<int>((deltatime / animDuration) * framesNum / 2) % (framesNum);

            //---Set Sprite Rectangle Based on Frame---//
            player.setTextureRect(IntRect(animFrame * playerSize.x, 0, playerSize.x, playerSize.y));

            if (Keyboard::isKeyPressed(Keyboard::Right))
            {
                //playerX += 0.1;
                if (collider.getPosition().x < colliderX + 300)
                {
                    collider.move(20, 0); player.move(20, 0);
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::Left))
            {
                //playerX -= 0.1;
                if (collider.getPosition().x > colliderX - 300)
                {
                    collider.move(-20, 0); player.move(-20, 0);
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::O))
            {
                isAlive = false;
                speed = 0;
                updateAndSaveScore();
                distanceScore = distanceScore - 1;
                oil_MAX = oil_MAX + 1;
                if (Keyboard::isKeyPressed(Keyboard::Space))
                {
                    H += 100;
                    isJumping == false;
                    oil_MAX = oil_MAX + 5;
                    // distanceScore = distanceScore - 1;
                }
                isGameStarted = false;
            }
            if (player.getPosition().y < groundHeight && collider.getPosition().y < groundHeight && isJumping == true) {
                player.move(0, gravity);
                collider.move(0, gravity);
            }
            /*if (Keyboard::isKeyPressed(Keyboard::Down))
            {
                distanceScore = distanceScore - 2;
                speed = -200;
            }*/

            if (Keyboard::isKeyPressed(Keyboard::Tab))
            {
                speed *= 3;
                oil_MAX = oil_MAX - 3;
                distanceScore = distanceScore + 3;
            }

            if (Keyboard::isKeyPressed(Keyboard::Space))
            {
                playJ.play();
                if (collider.getPosition().y >= (height / 2 + 100)) {
                    isJumping = true;
                    collider.move(0, -moveSpeed);
                    player.move(0, -moveSpeed);

                }
                //H += 100;
                oil_MAX = oil_MAX - rand() % 5 - 5;
                //distanceScore = distanceScore + 1.5;

            }
        }
        if (H > 1500 && !(H < 1500))
        {
            H = H - 50;
        }
        if (oil_MAX <= 0)
        {
            isAlive = false;
            oil_MAX = 0;
            speed = 0;
            updateAndSaveScore();
            distanceScore = distanceScore - 1;

            if (Keyboard::isKeyPressed(Keyboard::Space))
            {
                H += 100;
                isJumping == false;
                oil_MAX = oil_MAX + 5;
                // distanceScore = distanceScore - 1;
            }
            isGameStarted = false;
        }
        //hp
        if (hpMax <= 0)
        {
            hpMax = 0;
            isAlive = false;
            oil_MAX = oil_MAX + 1;
            speed = 0;
            updateAndSaveScore();
            distanceScore = distanceScore - 1;
            if (Keyboard::isKeyPressed(Keyboard::Space))
            {
                H += 100;
                isJumping == false;
                oil_MAX = oil_MAX + 5;
                //distanceScore = distanceScore - 1;
            }
            isGameStarted = false;
        }
        pos += speed;
        while (pos >= N * segL) pos -= N * segL;
        while (pos < 0) pos += N * segL;

        app.clear(Color(105, 205, 4));
        app.draw(sBackground);
        int startPos = pos / segL;
        int camH = lines[startPos].y + H;
        if (speed > 0) sBackground.move(-lines[startPos].curve * 2, 0);
        if (speed < 0) sBackground.move(lines[startPos].curve * 2, 0);

        if (isAlive)
        {
            if (lines[startPos + 10].getObstacleBounds().intersects(collider.getGlobalBounds()) && (lines[startPos].spriteX == -0.5))
            {
                oil_MAX = oil_MAX + 800;
                hpMax = hpMax + 1;
                botSound.play();
            }
            /*if (lines[startPos + 10].getObstacleBounds().intersects(collider.getGlobalBounds()) && (lines[startPos].spriteX = -0.2))
            {
                hpMax = hpMax + 20;
                healSound.play();
            }*/
            /*if (lines[startPos + 10].getObstacleBounds().intersects(collider.getGlobalBounds()) && (lines[startPos].spriteX = -0.7 ))
            {
                hpMax = hpMax - 1;
                collideSound.play();
            }
            if (lines[startPos + 10].getObstacleBounds().intersects(collider.getGlobalBounds()) && (lines[startPos].spriteX = -0.4))
            {
                hpMax = hpMax - 1;
                collideSound.play();
            }*/
            if (lines[startPos + 100].getObstacleBounds().intersects(collider.getGlobalBounds()))
            {
                hpMax = hpMax - 1;

                collideSound.play();
            }
        }

        int maxy = height;
        float x = 0, dx = 0;


        if (hpMax >= 100)
            hpMax = 100;

        if (oil_MAX >= 5100)
        {
            oil_MAX = 5100;
        }
        //bar
        app.draw(playerHpBarBack);
        app.draw(playerHpBar);
        float hpPercent = static_cast<float>(hpMax / 1);
        playerHpBar.setSize(sf::Vector2f(3.f * hpPercent, playerHpBar.getSize().y));
        app.draw(playerOILBarBack);
        app.draw(playerOILBar);
        float oilPercent = static_cast<float>(oil_MAX / 100);
        playerOILBar.setSize(sf::Vector2f(6.f * oilPercent, playerOILBar.getSize().y));
        ///////draw road////////
        for (int n = startPos; n < startPos + 300; n++)
        {
            Line& l = lines[n % N];
            l.project(playerX * roadW - x, camH, startPos * segL - (n >= N ? N * segL : 0));
            x += dx;
            dx += l.curve;

            l.clip = maxy;
            if (l.Y >= maxy) continue;
            maxy = l.Y;

            Color grass = (n / 3) % 2 ? Color(16, 200, 16) : Color(147, 155, 119);
            Color rumble = (n / 3) % 2 ? Color(255, 255, 255) : Color(0, 0, 0);
            Color road = (n / 3) % 2 ? Color(107, 107, 107) : Color(105, 105, 105);

            Line p = lines[(n - 1) % N]; //previous line

            drawQuad(app, grass, 0, p.Y, width, 0, l.Y, width);
            drawQuad(app, rumble, p.X, p.Y, p.W * 1.2, l.X, l.Y, l.W * 1.2);
            drawQuad(app, road, p.X, p.Y, p.W, l.X, l.Y, l.W);
        }

        ////////draw objects////////
        for (int n = startPos + 300; n > startPos; n--)
            lines[n % N].drawSprite(app);

        
       
        switch (isGameStarted)
        {
        case 0:
            if (isMenu)
            {
                distanceScore = 0;
                oil_MAX = 5100;
                hpMax = 100;
                app.clear();

                menu.draw(app);

                app.display();

                app.clear();
                if (isHTP == true)
                {

                    app.clear();
                    htp.draw(app);
                    app.display();
                    app.clear();
                    isMenu = false;
                }
                if (isHS == true)
                {
                    
                    app.clear();
                    //app.draw(menu.playerText);
                    //app.draw(endText);
                    //app.draw(highscoretext);
                    //app.draw(shape);
                    //app.draw(content);
                    
                    //app.draw(content);
                   // app.draw(scoreEndText);
                    //render(&app);
                   
                    app.draw(hsBackground);
                    //app.clear();
                    isMenu = false;
                    menu.leaderboard->render(&app);
                    app.display();
                    
                    
                }
            }


            break;
        case 1:


            //app.draw(mark); 
            app.draw(player);
            app.draw(distance);

            app.display();

            app.clear();
            break;

        }

        if (isHTP == true)
        {
            switch (e.key.code)
            {
            case::sf::Keyboard::M:
                isMenu = true;
                isHTP = false;
                break;
            default:
                break;
            }
        }
        if (isHS == true)
        {
            switch (e.key.code)
            {
            case::sf::Keyboard::M:
                isMenu = true;
                isHS = false;
                break;
            default:
                break;
            }
        }
    }
    

    return 0;
}
void updateAndSaveScore()
{

    typedef struct NameWithScore {
        std::string name;
        int score;
    } NameWithScore;

    auto compareScores = [](NameWithScore p_1, NameWithScore p_2) {
        return p_1.score > p_2.score;
    };

    std::vector<NameWithScore> namesWithScore;

    NameWithScore currentPlayer;
    currentPlayer.score = distanceScore ;

    namesWithScore.push_back(currentPlayer);

    std::ifstream ifs("images/scores.txt");

    if (ifs.is_open())
    {

        std::string playerScore = "";

        while (ifs >> playerScore)
        {
            NameWithScore temp;
            temp.score = std::stoi(playerScore);
            namesWithScore.push_back(temp);
        }


    }
    ifs.close();

    std::sort(namesWithScore.begin(), namesWithScore.end(), compareScores);

    while (namesWithScore.size() > 5) {
        namesWithScore.pop_back();
    }

    std::fstream ofs;
    ofs.open("score/score.txt", std::ios::out | std::ios::trunc);

    for (auto nameWithScore : namesWithScore) {
        std::cout << "write " << std::endl << nameWithScore.score << std::endl;

        ofs <<  "\t" + std::to_string(nameWithScore.score) + "\n";
    }

    
    ofs.close();
}




void initContent(unsigned content_character_size)
{
    std::ifstream ifs("images/scores.txt");

    if (ifs.is_open())
    {
       
        std::string playerScore = "";

        std::string content1 = "";
        int i = 1;
        while (ifs >> playerScore)
        {
            content1 += ("No." + std::to_string(i) + " "  + " - " + playerScore + "\n");
            ++i;
        }


        content.setFont(*font);
        content.setString(content1);
        content.setCharacterSize(content_character_size);
        content.setFillColor(sf::Color(250, 250, 250, 250));
        content.setPosition(
        shape.getPosition().x + (shape.getGlobalBounds().width / 2.f) - content.getGlobalBounds().width / 2.f,
        shape.getPosition().y + (shape.getGlobalBounds().height / 2.f) - content.getGlobalBounds().height / 2.f + 30.f
        );
        content.setOutlineThickness(1.f);
        content.setOutlineColor(sf::Color::Black);

    }

    ifs.close();

    

}

void Plane(float x, float y, float width, float height, sf::Font* font,
    unsigned header_character_size, unsigned content_character_size)
{

    font = font;
    shape.setPosition(sf::Vector2f(x, y));
    shape.setSize(sf::Vector2f(width, height));
    shape.setFillColor(sf::Color(70, 70, 70, 200));
    shape.setOutlineThickness(1.f);
    shape.setOutlineColor(sf::Color::Black);

    
    initContent(content_character_size);
}


void render(sf::RenderTarget* target)
{
    target->draw(shape);
    //target->draw(header);
    target->draw(content);
}

