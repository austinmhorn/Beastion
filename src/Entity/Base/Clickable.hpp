#ifndef Clickable_hpp
#define Clickable_hpp

#include "Entity.hpp"

#include <SFML/Window/Mouse.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Utf.hpp>

#include <iostream>

static void loadTexture(sf::Texture& texture, const std::string& pathToTextureFile)
{
    std::cout << "Loading texture \"" << pathToTextureFile << "\"" << std::endl;

    try {
        auto const pos = pathToTextureFile.find_last_of('/'); // Find last forward slash occurrence 
        const auto file = pathToTextureFile.substr(pos + 1);  // Extract the remaining substring; Should contain complete file name 

        if ( !texture.loadFromFile(pathToTextureFile) )
            throw std::runtime_error("Failed loading texture file \"" + file + "\"");        
    }
    catch(const std::runtime_error& error) {
        std::cerr << error.what() << std::endl;
        std::cout << "Verify the resource path \"" + pathToTextureFile << "\"" << std::endl;
    }    
}

////////////////////////////////////////////////////////////
/// \class Clickable
/// \ingroup Entities
/// \brief A drawable that can react to mouse click events
////////////////////////////////////////////////////////////
class Clickable 
    : public Entity
{        
    public:
        
        void setPressed(bool pressed) { m_pressed = pressed; }
        bool isPressed() const { return m_pressed; }
        void setClicked(bool clicked) { m_clicked = clicked; }
        bool isClicked() const { return m_clicked; }
        void setMouseIn(bool in) { m_mouse_in = in; }
        bool isMouseIn() const { return m_mouse_in; }

        
        virtual void handleEvent(sf::Event event) = 0;
        virtual void handleKeyEvent(sf::Keyboard::Key key, bool press) = 0;
        virtual void handleTextEvent(sf::Utf32 character) = 0;
        virtual void handleMouseButtonEvent(sf::Mouse::Button button, bool press, int x, int y) = 0;

        virtual void handleMouseMoveEvent(int x, int y) = 0;
        virtual void handleMouseEnter(int x, int y) = 0;
        virtual void handleMouseLeave(int x, int y) = 0;
        virtual void handleMouseClick(sf::Mouse::Button button, int x, int y) = 0;

        virtual bool contains(const sf::Vector2f& point) const = 0;
        virtual void update(sf::Time delta_time) = 0;

    private:

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override = 0;

    protected: 
        
        // Protected class constructors & functions
        Clickable() = default;
        ~Clickable() = default;
        
        Clickable(const Clickable&) = default;
        Clickable& operator=(const Clickable&) = default;
        
        Clickable(Clickable&&) noexcept = default;
        Clickable& operator=(Clickable&&) noexcept = default;

        // Protected member variables
        bool          m_mouse_in : 1;
        bool          m_pressed : 1;
        bool          m_clicked : 1;
};

#endif /* Clickable_hpp */