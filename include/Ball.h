class Ball
{
private:
    float X;
    float Y;
    sf::Vector2f velocity;
public:
    Ball(float px, float py);
    void draw(sf::RenderTarget &pTarget);
};
