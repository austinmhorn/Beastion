#ifndef Application_hpp
#define Application_hpp

#include <SFML/Graphics/RenderWindow.hpp>

#include "StateMachine.hpp"
#include "ResourceManager.hpp"

class Application
{
public:
    
    Application();
    Application(u_int window_width, u_int window_height, const std::string& title, const sf::Uint32& style = sf::Style::Default, const sf::ContextSettings& settings = sf::ContextSettings());

    ~Application() = default;
    
    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;
    
    Application(Application&&) noexcept = delete;
    Application& operator=(Application&&) noexcept = delete;

    void run();
        
private:

    void loadResources();

    StateMachine     m_machine;
    sf::RenderWindow m_window;
    ResourceManager  m_resources;
};

#endif /* Application_hpp */
