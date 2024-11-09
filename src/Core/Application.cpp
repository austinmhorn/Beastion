#include "Application.hpp"

#include "../State/IntroState.hpp"

Application::Application()
    : m_resources( std::filesystem::current_path() )
{
    loadResources();

    u_int screen_width = 0;
    u_int screen_height = 0;
    fetchScreenResolution(screen_width, screen_height);
    
    m_window.create(sf::VideoMode(screen_width * 0.5f, screen_height * 0.6f), "");
    m_window.setFramerateLimit(60);

    m_machine.init( StateMachine::build<IntroState>(m_machine, m_window, m_resources, true) );    
}

Application::Application(u_int width, u_int height, const std::string& title, const sf::Uint32& style, const sf::ContextSettings& settings)
    : m_resources( std::filesystem::current_path() )
{
    loadResources();

    u_int screen_width = 0;
    u_int screen_height = 0;
    fetchScreenResolution(screen_width, screen_height);
    
    m_window.create( sf::VideoMode(width, height), title, style, settings );
    m_window.setFramerateLimit(60);

    m_machine.init( StateMachine::build<IntroState>(m_machine, m_window, m_resources, true) );    
}

void Application::run()
{
    // Main loop
    while (m_machine.running())
    {
        m_machine.nextState();
        m_machine.update();
        m_machine.draw();
    }
}

void Application::loadResources()
{
    m_resources.loadTextures();
}
