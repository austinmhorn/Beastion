#include "IntroState.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

IntroState::IntroState(StateMachine& machine, sf::RenderWindow& window, ResourceManager& resources, const bool replace)
    : State{ machine, window, resources, replace }
{
    const auto window_size = sf::Vector2f{ window.getSize() };
    
    // Fill the background with Gray
    m_background.setFillColor({100u, 100u, 100u});
    m_background.setSize(window_size);

    card.setPosition(window_size.x/2.f - card.getSize().x/2.f, window_size.y/2.f - card.getSize().y/2.f);
    card.setFlipAnimationSpeed(4.0);

    std::cout << "IntroState Initialized Successfully" << std::endl;
}

void IntroState::pause()
{
    std::cout << "IntroState Paused" << std::endl;
}

void IntroState::resume()
{
    std::cout << "IntroState Resumed" << std::endl;
}

void IntroState::handleEvent()
{
    for (auto event = sf::Event{}; m_window.pollEvent(event);)
    {        

        card.handleEvent(event);

        switch (event.type)
        {
            case sf::Event::Closed:
                m_machine.quit(); // Terminate state machine
                break;
                
            case sf::Event::MouseMoved:
                m_current_mouse_position = m_window.mapPixelToCoords({ event.mouseMove.x, event.mouseMove.y }); //< Get new mouse position
                break;
                
            case sf::Event::MouseButtonPressed:
                m_current_mouse_position = m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y }); ///< Get location for mouse button press event
                break;
                
            case sf::Event::MouseButtonReleased:
                m_current_mouse_position = m_window.mapPixelToCoords({ event.mouseButton.x, event.mouseButton.y }); ///< Get location for mouse button release event
                break;
                
            case sf::Event::KeyPressed:
                break;
                
            case sf::Event::TextEntered:
                break;
                
            default:
                break;
        }
        
        
    }
}

void IntroState::update()
{
    static const auto clock = sf::Clock{};
    static auto last_frame_time = sf::Time{};
    const auto delta_time = clock.getElapsedTime() - last_frame_time;
    last_frame_time = clock.getElapsedTime();
    
    handleEvent();

    card.update(delta_time);
}

void IntroState::draw()
{
    m_window.clear();
    
    m_window.draw(m_background);

    m_window.draw(card);

    m_window.display();
}
