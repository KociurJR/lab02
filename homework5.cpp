#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

sf::RectangleShape create_wall(sf::Vector2f size, sf::Vector2f position, sf::Texture& texture, sf::IntRect textureRect) {
    sf::RectangleShape wall(size);
    wall.setTexture(&texture);
    wall.setTextureRect(textureRect);
    wall.setPosition(position);
    return wall;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    sf::Texture texture_grass;
    if (!texture_grass.loadFromFile("grass.png")) return 1;
    texture_grass.setRepeated(true);

    sf::Sprite grass;
    grass.setTexture(texture_grass);
    grass.setTextureRect(sf::IntRect(0, 0, 800, 600));

    sf::Texture texture_wall;
    if (!texture_wall.loadFromFile("wall.png")) return 1;
    texture_wall.setRepeated(true);

    sf::Texture texture_guy;
    if (!texture_guy.loadFromFile("guy.png")) return 1;

    sf::Sprite guy;
    guy.setTexture(texture_guy);
    guy.setPosition(50.0, 50.0);

    std::vector<sf::RectangleShape> walls = {
                                             create_wall({30.0, 300.0}, {150.0, 50.0}, texture_wall, {0, 0, 90, 600}),
                                             create_wall({250.0, 30.0}, {200.0, 100.0}, texture_wall, {0, 0, 500, 90}),
                                             create_wall({30.0, 200.0}, {450.0, 150.0}, texture_wall, {0, 0, 90, 400}),
                                             create_wall({200.0, 30.0}, {250.0, 300.0}, texture_wall, {0, 0, 500, 90}),
                                             create_wall({30.0, 250.0}, {100.0, 350.0}, texture_wall, {0, 0, 90, 500}),
                                             create_wall({300.0, 30.0}, {120.0, 550.0}, texture_wall, {0, 0, 600, 90}),
                                             create_wall({30.0, 100.0}, {600.0, 400.0}, texture_wall, {0, 0, 90, 300}),
                                             create_wall({200.0, 30.0}, {500.0, 500.0}, texture_wall, {0, 0, 500, 90}),
                                             create_wall({30.0, 150.0}, {700.0, 300.0}, texture_wall, {0, 0, 90, 400}),
                                             create_wall({150.0, 30.0}, {600.0, 200.0}, texture_wall, {0, 0, 500, 90}),
                                             create_wall({30.0, 100.0}, {350.0, 50.0}, texture_wall, {0, 0, 90, 200}),
                                             create_wall({100.0, 30.0}, {100.0, 200.0}, texture_wall, {0, 0, 300, 90}),
                                             };

    const float guy_speed = 0.09;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Vector2f movement(0.0, 0.0);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))  movement.x -= guy_speed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) movement.x += guy_speed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))    movement.y -= guy_speed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))  movement.y += guy_speed;

        sf::FloatRect nextBounds = guy.getGlobalBounds();
        nextBounds.left += movement.x;
        nextBounds.top  += movement.y;

        sf::FloatRect windowBounds(0.0, 0.0, window.getSize().x, window.getSize().y);

        bool collides = false;
        for (const auto& wall : walls) {
            if (wall.getGlobalBounds().intersects(nextBounds)) {
                collides = true;
                break;
            }
        }

        if (!collides &&
            windowBounds.contains(nextBounds.left, nextBounds.top) &&
            windowBounds.contains(nextBounds.left + nextBounds.width, nextBounds.top + nextBounds.height)) {
            guy.move(movement);
        }

        window.clear(sf::Color::Black);
        window.draw(grass);
        window.draw(guy);
        for (auto& wall : walls)
            window.draw(wall);
        window.display();
    }

    return 0;
}
