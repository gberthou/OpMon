#include "Animations.hpp"
#include "MainFrame.hpp"
UNS

namespace Animations {

bool init = false;
sf::Event events;
int ancientTick = 0;
bool continuer = false;
bool joypressed = false;
sf::Texture fen[6];

void initAnims() {
    for(int i = 0; i < 6; i++) {
        ostringstream oss;
        oss << getPath(RESSOURCES_PATH + "animations/winChange/animWindowFrame") << i + 1 << ".png";
        fen[i].loadFromFile(oss.str());
    }
    init = true;
}

void deleteAnims() {
    init = false;
}

/**
 * check if animations has been initialized.
 */
static void anim_check_init() {
    if (!init) {
        handleError("Erreur : Animations non initialisées", true);
    }
}

int animWinOpen(sf::RenderTexture &window, sf::Sprite const &bg) {
    anim_check_init(); //Verification of animation initialization
    //Variables declaration
    sf::Sprite anim[6];
    int ancientChrono = 0;

    //Frame by frame
    for (int i = 0; i < 6; i++) {
        if ((ticks.getElapsedTime().asMilliseconds() - ancientChrono) >= 33) {
            Main::mainframe.window.pollEvent(events);
            ancientChrono = ticks.getElapsedTime().asMilliseconds();
            switch (events.type) {
                RETURN_ON_CLOSE_EVENT
            default:
                break;
            }

            RETURN_ON_ECHAP_EVENT
            anim[i].setTexture(fen[i]);
            window.clear(sf::Color::White);
            window.draw(bg);
            window.draw(anim[i]);

            window.display();
            Main::mainframe.winRefresh();
        } else {
            Utils::wait(200 - (ticks.getElapsedTime().asMilliseconds() - ancientTick));
            i--;
        }
    }
    return 0;
}

int animWinClose(sf::RenderTexture &window, sf::Sprite const &bg) {
    //Se rÃ©ferer aux commentaires de la fonction prÃ©cÃ©dente
    anim_check_init();
    //Variables declaration
    sf::Sprite anim[6];
    int ancientChrono = 0;
    for (int i = 5; i >= 0; i--) {
        if ((ticks.getElapsedTime().asMilliseconds() - ancientChrono) >= 33) {
            Main::mainframe.window.pollEvent(events);
            ancientChrono = ticks.getElapsedTime().asMilliseconds();
            switch (events.type) {
                RETURN_ON_CLOSE_EVENT
            default:
                break;
            }

            RETURN_ON_ECHAP_EVENT

            anim[i].setTexture(fen[i]);

            window.clear(sf::Color::White);

            window.draw(bg);
            window.draw(anim[i]);

            window.display();
            Main::mainframe.winRefresh();
        } else {
            Utils::wait(200 - (ticks.getElapsedTime().asMilliseconds() - ancientTick));
            i++;
        }
    }
    return 0;
}


}
