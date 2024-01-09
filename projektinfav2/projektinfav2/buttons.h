class button {
public:
    button(float x, float y, float width, float height, const std::string& text, const sf::Font& font)
        : position(x, y), size(width, height), textString(text, font) {
        buttonShape.setPosition(position);
        buttonShape.setSize(size);
        buttonShape.setFillColor(sf::Color::Green);

        textString.setCharacterSize(20);
        textString.setFillColor(sf::Color::White);

        updateTextPosition();
    }

    void draw(sf::RenderWindow& window) {
        window.draw(buttonShape);
        window.draw(textString);
    }

    bool isClicked(sf::RenderWindow& window) {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        if (buttonShape.getGlobalBounds().contains(mousePos)) {
            buttonShape.setFillColor(sf::Color::Red);

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                return true;
            }
        }
        else {
            buttonShape.setFillColor(sf::Color::Green);
        }

        return false;
    }

    void setText(const std::string& text) {
        textString.setString(text);
        updateTextPosition();
    }

    void changeText(const std::string& newText) {
        textString.setString(newText);
        updateTextPosition();
    }

private:
    void updateTextPosition() {
        sf::FloatRect textBounds = textString.getLocalBounds();
        float textX = position.x + (size.x - textBounds.width) / 2;
        float textY = position.y + (size.y - textBounds.height) / 2;
        textString.setPosition(textX, textY);
    }

private:
    sf::Vector2f position;
    sf::Vector2f size;
    sf::RectangleShape buttonShape;
    sf::Text textString;
};