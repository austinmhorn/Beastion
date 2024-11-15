#ifndef State_hpp
#define State_hpp

#include <memory>

namespace sf
{
    class RenderWindow;
}

class StateMachine;
class ResourceManager;

class State
{
public:
    
    State(StateMachine& machine, sf::RenderWindow& window, ResourceManager& resources, const bool replace = true);
    virtual ~State() = default;
    
    State(const State&) = delete;
    State& operator=(const State&) = delete;
    
    State(State&&) noexcept = delete;
    State& operator=(State&&) noexcept = delete;
    
    virtual void pause() = 0;
    virtual void resume() = 0;
    virtual void handleEvent() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;
    
    std::unique_ptr<State> next();
    [[nodiscard]] bool replace() const;
    
protected:
    
    StateMachine&          m_machine;
    sf::RenderWindow&      m_window;
    ResourceManager&       m_resources;
    std::unique_ptr<State> m_next;
    bool                   m_replace;
};

#endif /* State_hpp */
