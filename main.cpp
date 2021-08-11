#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <array>
#include <stdio.h>
#include <sstream>
#include <unordered_set>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <Thor/Shapes/ConcaveShape.hpp>
#include <earcut.hpp/include/mapbox/earcut.hpp>

#define roundz(x,d) ((floor(((x)*pow(10,d))+.5))/pow(10,d))
using namespace std;

class Utilities {

public:

    int Signum(float x)
    {
        if (x > 0) return 1;
        else return -1;
    }

    int Get_line_intersection(float p0_x, float p0_y, float p1_x, float p1_y,
        float p2_x, float p2_y, float p3_x, float p3_y, float* i_x, float* i_y)
    {
        float s1_x, s1_y, s2_x, s2_y;
        s1_x = p1_x - p0_x;     s1_y = p1_y - p0_y;
        s2_x = p3_x - p2_x;     s2_y = p3_y - p2_y;

        float s, t;
        s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / (-s2_x * s1_y + s1_x * s2_y);
        t = (s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / (-s2_x * s1_y + s1_x * s2_y);

        if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
        {
            // Collision detected
            if (i_x != NULL)
                *i_x = p0_x + (t * s1_x);
            if (i_y != NULL)
                *i_y = p0_y + (t * s1_y);
            return 1;
        }

        return 0; // No collision
    }

    bool doOverlap(sf::Vector2f l1, sf::Vector2f r1, sf::Vector2f l2, sf::Vector2f r2)
{
 
    // To check if either rectangle is actually a line
    // For example :  l1 ={-1,0}  r1={1,1}  l2={0,-1}
    // r2={0,1}
 
    if (l1.x == r1.x || l1.y == r1.y || l2.x == r2.x
        || l2.y == r2.y) {
        // the line cannot have positive overlap
        return false;
    }
 
    // If one rectangle is on left side of other
    if (l1.x >= r2.x || l2.x >= r1.x)
        return false;
 
    // If one rectangle is above other
    if (r1.y >= l2.y || r2.y >= l1.y)
        return false;
 
    return true;
}

    bool DoesRectOverlap(vector<vector<sf::VertexArray>> rectangles, sf::Vector2f v1, sf::Vector2f v2)
    {
        for (auto& rect : rectangles) 
        {
            if (doOverlap(rect[0][0].position, rect[2][0].position, v1, v2))
            {
                return true;
            }
        }
        return false;
    }

    vector<sf::VertexArray> ExtractSegmentsFromQuad(sf::VertexArray quad)
    {
        vector<sf::VertexArray> segments;
        sf::VertexArray s1(sf::Lines, 2);
        s1[0].position = quad[0].position;
        s1[1].position = quad[1].position;
        segments.push_back(s1);

        sf::VertexArray s2(sf::Lines, 2);
        s2[0].position = quad[1].position;
        s2[1].position = quad[2].position;
        segments.push_back(s2);

        sf::VertexArray s3(sf::Lines, 2);
        s3[0].position = quad[2].position;
        s3[1].position = quad[3].position;
        segments.push_back(s3);

        sf::VertexArray s4(sf::Lines, 2);
        s4[0].position = quad[3].position;
        s4[1].position = quad[0].position;
        segments.push_back(s4);

        return segments;
    }

    bool IsInScreen(sf::RenderWindow& window, sf::CircleShape shape)
    {
        return shape.getPosition().x >= 0 &&
            shape.getPosition().x < window.getSize().x&&
            shape.getPosition().y >= 0 &&
            shape.getPosition().y < window.getSize().y;
    }

    sf::Vector2f sumVector(sf::Vector2f v1, sf::Vector2f v2)
    {
        sf::Vector2f vect(v1.x + v2.x, v1.y + v2.y);
        return vect;
    }

    sf::Vector2f randomSpeed()
    {
        sf::Vector2f speed_vect(-1 + (rand() % 3), -1 + (rand() % 3));
        return speed_vect;
    }

};

class TextureUtilities {
public:
    sf::Texture LoadTexture(string textureName)
    {
        sf::Texture texture;
        if (!texture.loadFromFile(textureName))
        {
            cout << "Error";
        }
        return texture;
    }

    sf::Texture BlankTexture(int width, int height)
    {
        sf::Texture texture;
        if (!texture.create(width, height))
        {
            cout << "Error";
        }
        return texture;
    }

};

int main()
{
    sf::Font font;
    font.loadFromFile("arial.ttf");
    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    int radious = max(window.getSize().x, window.getSize().y) * 2;
    Utilities utils;
    srand((unsigned)time(NULL));
    vector<sf::VertexArray> lines;
    vector<vector<sf::VertexArray>> allSegmentsOfQuads; //TODO: basterebbe un vector<sf::VertexArray> brutto rincoglionito
    int numberOfBoxes = 5;

    sf::VertexArray wall(sf::Quads, 4);
    int x1;
    int x2;
    int y1;
    int y2;
    x1 = rand() % window.getSize().x;
    x2 = x1 + rand() % (window.getSize().x - x1);
    y1 = rand() % window.getSize().y;
    y2 = y1 + rand() % (window.getSize().y - y1);

    wall[0].position = sf::Vector2f(x1, y2);
    wall[1].position = sf::Vector2f(x1, y1);
    wall[2].position = sf::Vector2f(x2, y1);
    wall[3].position = sf::Vector2f(x2, y2);

    vector<sf::VertexArray> segmentsOfQuad = utils.ExtractSegmentsFromQuad(wall);
    allSegmentsOfQuads.push_back(segmentsOfQuad);

    for (int i = 0; i < numberOfBoxes-1; i++)
    {     
        bool built = false;
        int x1;
        int x2;
        int y1;
        int y2;

        while (!built)
        {
            x1 = rand() % window.getSize().x;
            x2 = x1 + rand() % (window.getSize().x - x1);
            y1 = rand() % window.getSize().y;
            y2 = y1 + rand() % (window.getSize().y - y1);

            sf::Vector2f v1(x1, y2);
            sf::Vector2f v2(x1, y1);
            sf::Vector2f v3(x2, y1);
            sf::Vector2f v4(x2, y2);
            if (utils.DoesRectOverlap(allSegmentsOfQuads, v1, v3))
            {
                built = false;
            }
            else
            {
                built = true;
            }
        }

        wall[0].position = sf::Vector2f(x1, y2);
        wall[1].position = sf::Vector2f(x1, y1);
        wall[2].position = sf::Vector2f(x2, y1);
        wall[3].position = sf::Vector2f(x2, y2);
        segmentsOfQuad = utils.ExtractSegmentsFromQuad(wall);
        allSegmentsOfQuads.push_back(segmentsOfQuad);

    }

    sf::VertexArray externalWall(sf::Quads, 4);
    externalWall[0].position = sf::Vector2f(0, 0);
    externalWall[1].position = sf::Vector2f(window.getSize().x, 0);
    externalWall[2].position = sf::Vector2f(window.getSize().x, window.getSize().y);
    externalWall[3].position = sf::Vector2f(0, window.getSize().y);
    segmentsOfQuad = utils.ExtractSegmentsFromQuad(externalWall);
    allSegmentsOfQuads.push_back(segmentsOfQuad);

    sf::Mouse mouse;
    window.setMouseCursorVisible(false);
    sf::CircleShape circle(10);
    circle.setFillColor(sf::Color::Yellow);

    // run the program as long as the window is open

    while (window.isOpen())
    {
        lines.clear();
        circle.setPosition(sf::Vector2f(mouse.getPosition(window).x - circle.getRadius(), mouse.getPosition(window).y - circle.getRadius()));
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        sf::VertexArray right(sf::Lines, 2);
        right[0].position = sf::Vector2f(window.getSize().x, 0);
        right[0].position = sf::Vector2f(window.getSize().x, window.getSize().y);

        for (auto& segments : allSegmentsOfQuads)
        {
            for (auto& segment : segments)
            {
                for (int i = 0; i < 2; i++)
                {
                    sf::VertexArray line(sf::Lines, 2);
                    line[0].position = sf::Vector2f(mouse.getPosition(window));
                    line[1].position = segment[i].position;

                    float d_omega = 0.05f;
                    float angle = atan((float)(mouse.getPosition(window).y - segment[i].position.y) / (float)(mouse.getPosition(window).x - segment[i].position.x));

                    sf::VertexArray lineFollowing1(sf::Lines, 2);
                    lineFollowing1[0].position = sf::Vector2f(mouse.getPosition(window));
                    sf::VertexArray lineFollowing2(sf::Lines, 2);
                    lineFollowing2[0].position = sf::Vector2f(mouse.getPosition(window));

                    if (mouse.getPosition(window).x < segment[i].position.x)
                    {
                        lineFollowing1[1].position = sf::Vector2f(
                            mouse.getPosition(window).x + 2 * window.getSize().x * cos(angle + d_omega),
                            mouse.getPosition(window).y + 2 * window.getSize().x * sin(angle + d_omega)
                        );
                        lineFollowing2[1].position = sf::Vector2f(
                            mouse.getPosition(window).x + 2 * window.getSize().x * cos(angle - d_omega),
                            mouse.getPosition(window).y + 2 * window.getSize().x * sin(angle - d_omega)
                        );
                    }
                    else
                    {
                        lineFollowing1[1].position = sf::Vector2f(
                            mouse.getPosition(window).x - 2 * window.getSize().x * cos(angle + d_omega),
                            mouse.getPosition(window).y - 2 * window.getSize().x * sin(angle + d_omega)
                        );
                        lineFollowing2[1].position = sf::Vector2f(
                            mouse.getPosition(window).x - 2 * window.getSize().x * cos(angle - d_omega),
                            mouse.getPosition(window).y - 2 * window.getSize().x * sin(angle - d_omega)
                        );
                    }
                    lines.push_back(lineFollowing1);
                    lines.push_back(lineFollowing2);
                    lines.push_back(line);
                }

            }
        }


        for (auto& line : lines)
        {
            line[0].position = sf::Vector2f(mouse.getPosition(window));
            float potential_x_intersect;
            float potential_y_intersect;

            for (auto& segments : allSegmentsOfQuads) {
                for (auto& segment : segments)
                {
                    if (utils.Get_line_intersection(line[0].position.x, line[0].position.y, line[1].position.x, line[1].position.y,
                        segment[0].position.x, segment[0].position.y, segment[1].position.x, segment[1].position.y,
                        &potential_x_intersect,
                        &potential_y_intersect))
                    {
                        line[1].position = sf::Vector2f(potential_x_intersect, potential_y_intersect);
                    }
                    window.draw(segment);
                }
            }
        }

        vector<std::pair<float, sf::Vector2f>> clockwisePoints;
        for (auto& line : lines)
        {
            float angle = atan2((float)(mouse.getPosition(window).x - line[1].position.x), (float)(mouse.getPosition(window).y - line[1].position.y));
            std::pair<float, sf::Vector2f> angleAndPoint{ angle, line[1].position };
            clockwisePoints.push_back(angleAndPoint);
        }

        std::sort(clockwisePoints.begin(), clockwisePoints.end(), [](const auto& first, const auto& second)
            {
                return first.first < second.first;
            });


        using Coord = double;
        using N = uint32_t;
        using Point = std::array<Coord, 2>;
        std::vector<std::vector<Point>> polygon;
        vector<Point> ps;

        for (auto& c : clockwisePoints)
        {
            Point p = { (Coord)c.second.x, (Coord)c.second.y };
            ps.push_back(p);
        }
        polygon.push_back(ps);

        std::vector<N> indices = mapbox::earcut<N>(polygon);

        for (int i = 0; i < indices.size(); i += 3)
        {
            sf::ConvexShape triangle;
            triangle.setFillColor(sf::Color::White);
            triangle.setPointCount(3);
            triangle.setPoint(0, sf::Vector2f(ps[indices[i]][0], ps[indices[i]][1]));
            triangle.setPoint(1, sf::Vector2f(ps[indices[i+1]][0], ps[indices[i+1]][1]));
            triangle.setPoint(2, sf::Vector2f(ps[indices[i+2]][0], ps[indices[i+2]][1]));
            window.draw(triangle);
        }

        //window.draw(shape);
        //for (auto& line : lines)
        //{
        //    line[0].color = sf::Color::Red;
        //    line[1].color = sf::Color::Red;
        //    window.draw(line);
        //}

        //for (int i = 0; i < clockwisePoints.size()-1; i++)
        //{
        //    sf::VertexArray side(sf::Lines, 2);
        //    side[0].position = sf::Vector2f(clockwisePoints[i].second);
        //    side[1].position = sf::Vector2f(clockwisePoints[i+1].second);
        //    side[0].color = sf::Color::Green;
        //    side[1].color = sf::Color::Green;
        //    window.draw(side);
        //}

        window.draw(circle);
        // end the current frame
        window.display();
    }

    return 0;
}




