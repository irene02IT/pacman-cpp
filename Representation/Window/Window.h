#ifndef INC_2023_PROJECT_IRENE02IT_WINDOW_H
#define INC_2023_PROJECT_IRENE02IT_WINDOW_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <memory>
#include "../../Logic/Utilities/Global.h"

// Window class that incapsulates the sfml window object. It is a singleton class
class Window {
private:
    // constructor and destructor are private to prevent instantiation
    Window();
    Window(const std::string& title, const sf::Vector2u& size);
    ~Window();
    void Setup(const std::string& title, const sf::Vector2u& size);

    void Create(); // Create the window sfml object

    std::shared_ptr<sf::RenderWindow> m_window; // pointer to the window sfml object
    sf::Vector2u m_windowSize;
    std::string m_windowTitle;
    bool m_isFullscreen{};
public:

    // get the unique instance of the window class
    static Window& getInstance() {
        static Window instance(WINDOW_TITLE, sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT));
        return instance;
    }

    // Prevent copy-construction and assignment
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    std::shared_ptr<sf::RenderWindow> GetRenderWindow(); // Return the render window sfml object

    bool IsOpen(); // Check if the window is open
    void Close(); // Close the window
    void Display(); // Display the window
    void Clear(); // Clear the window (set the background color as black)
};


#endif //INC_2023_PROJECT_IRENE02IT_WINDOW_H
