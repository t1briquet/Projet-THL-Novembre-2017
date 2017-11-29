#include "link.h"

using namespace std;

#define WINLEN 800
#define WINHEI 600
#define XMID WINLEN/2
#define YMID WINHEI/2



int displayG(vector<vector<pair<int,double> > > funcs)

//int displayG(vector<pair<int,double> > f, vector<pair<int,double> > g)

{

    // création de la fenêtre

    int ratio=50;
    int xOri=XMID;
    int yOri=YMID;
    sf::RenderWindow window(sf::VideoMode(WINLEN, WINHEI), "Projet THL");
    /*if(xmin == xmax){
        ratio = 50;
        xOri = XMID;
    }
    else{
        ratio = 800/(xmax-xmin);
        xOri = -xmin*ratio;
    }*/
    /*sf::Font font;
    if(!font.loadFromFile("extrabold.ttf")){
        cerr<<"no font file found"<<endl;
    }*/

    // on fait tourner le programme tant que la fenêtre n'a pas été fermée
    while (window.isOpen())
    {
        // on traite tous les évènements de la fenêtre qui ont été générés depuis la dernière itération de la boucle
        sf::Event event;
        while (window.pollEvent(event))
        {
            // fermeture de la fenêtre lorsque l'utilisateur le souhaite
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::A){
                    ratio++;
                }
                if (event.key.code == sf::Keyboard::Z){
                    ratio--;
                }
                switch(event.key.code){
                    case sf::Keyboard::Add:
                        ratio++;
                        break;
                    case sf::Keyboard::Equal:
                        ratio++;
                        break;
                    case sf::Keyboard::Subtract:
                        if(ratio <= 1){break;}
                        ratio--;
                        break;
                    case sf::Keyboard::Dash:
                        if(ratio <= 1){break;}
                        ratio--;
                        break;
                    case sf::Keyboard::Left:
                        xOri--;
                        break;
                    case sf::Keyboard::Right:
                        xOri++;
                        break;
                    case sf::Keyboard::Up:
                        yOri--;
                        break;
                    case sf::Keyboard::Down:
                        yOri++;
                        break;
                    default :
                        break;
               }     
                
            }
        }
        
        // effacement de la fenêtre en noir
            window.clear(sf::Color::White);

            sf::VertexArray axes(sf::Lines, 4);
            axes[0].position = sf::Vector2f(xOri, 0);
            axes[1].position = sf::Vector2f(xOri, WINHEI);
            axes[2].position = sf::Vector2f(0, yOri);
            axes[3].position = sf::Vector2f(WINLEN, yOri);

            axes[0].color = sf::Color::Red;
            axes[1].color = sf::Color::Red;
            axes[2].color = sf::Color::Red;
            axes[3].color = sf::Color::Red;
            window.draw(axes);

            for (auto f : funcs){
                window.draw(plot(f, xOri, yOri, ratio));
            }
             
            sf::VertexArray grads(sf::Lines, 2);

            for (int i=0;i<WINLEN;i++){
                double y = (yOri-i)/(ratio*1.);
                double x = (i-xOri)/(ratio*1.);
                if(y== (int)y){
                    grads[0].position = sf::Vector2f(xOri-1, i);
                    grads[1].position = sf::Vector2f(xOri-5, i);
                    grads[0].color = sf::Color::Red;
                    grads[1].color = sf::Color::Red;
                    window.draw(grads);
                }
                if(x== (int)x){
                    grads[0].position = sf::Vector2f(i, yOri+1);
                    grads[1].position = sf::Vector2f(i, yOri+5);
                    grads[0].color = sf::Color::Red;
                    grads[1].color = sf::Color::Red;
                    window.draw(grads);
                }
            }
            
           

            /*sf::RectangleShape pos;
            pos.setSize(sf::Vector2f(150,50));
            pos.setPosition(10, WINHEI - 60);
            pos.setFillColor(sf::Color::White);
            pos.setOutlineColor(sf::Color::Black);
            pos.setOutlineThickness(1);
            window.draw(pos);*/

        // fin de la frame courante, affichage de tout ce qu'on a dessiné
        window.display();
    }

    return 0;
}

sf::VertexArray plot(vector<pair<int,double> > f, int xOri, int yOri,int ratio){
    sf::VertexArray courbe(sf::LinesStrip, WINLEN);
            for(int i=0; i<WINLEN;i++){
                double x = (i-xOri)/(ratio*1.);
                double y = function_eval(f,x);
                int yA = y*ratio;
                courbe[i].position = sf::Vector2f(i ,yOri - yA);
                courbe[i].color = sf::Color::Green;
            }
    return courbe;
}