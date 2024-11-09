#ifndef Card_hpp
#define Card_hpp

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Clock.hpp>

#include "Base/Clickable.hpp"


class Card
    : public Clickable
{
    public:

        Card(const std::string& pathToBackTexture, const std::string& pathToFaceTexture);
        ~Card() = default;

        /// Mutators
        void setPosition(const sf::Vector2f& position);
        void setPosition(float x, float y);
        const sf::Vector2f& getPosition() const;
        void setSize(const sf::Vector2f& size);
        const sf::Vector2f getSize() const;
        void setFlipAnimationSpeed(float speed);
        float getFlipAnimationSpeed() const;
        void flip();






        /// Accessors
        virtual bool contains(const sf::Vector2f& point) const override;

        /// Main Event Function
        virtual void handleEvent(sf::Event event) override;

        /// Keyboard Interaction Functions
        virtual void handleKeyEvent(sf::Keyboard::Key key, bool press) override;
        virtual void handleTextEvent(sf::Utf32 character) override;

        /// Mouse Interaction Functions
        virtual void handleMouseMoveEvent(int x, int y) override;
        virtual void handleMouseEnter(int x, int y) override;
        virtual void handleMouseLeave(int x, int y) override;
        virtual void handleMouseClick(sf::Mouse::Button button, int x, int y) override;
        virtual void handleMouseButtonEvent(sf::Mouse::Button button, bool press, int x, int y) override;

        // Update Functions
        virtual void update(sf::Time delta_time) override;

    private:

        void playFlipAnimation(sf::Time delta_time);
        void adjustFlipAnimation();

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        
        sf::Sprite  m_sprite;
        sf::Vector2f m_size;

        sf::Texture m_back;
        sf::Texture m_face;

        bool m_face_down;
        bool m_is_animating_flip;
        bool m_needs_texture_swap;

        bool  m_flip_anim_scale_down_complete;
        float m_flip_anim_anchor;
        float m_flip_anim_rescale_factor;
        float m_flip_anim_speed;
};

#endif /* Card_hpp */