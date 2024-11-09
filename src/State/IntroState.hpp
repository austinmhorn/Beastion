#ifndef IntroState_hpp
#define IntroState_hpp

#include <SFML/Graphics/RectangleShape.hpp>

#include "../Core/StateMachine.hpp"

#include "../Entity/Card.hpp"

class ResourceManager;

class IntroState final 
    : public State
{
    public:

        IntroState(StateMachine& machine, sf::RenderWindow& window, ResourceManager& resources, const bool replace = true);

        void pause() override;
        void resume() override;
        void handleEvent() override;
        void update() override;
        void draw() override;
        
    private:
        
        sf::RectangleShape m_background;
        sf::Vector2f       m_current_mouse_position;

        Card card = Card("assets/textures/card/back/back_1.png", "assets/textures/card/face/toad.png");
        
};

#endif /* IntroState_hpp */