//
// Created by loghin on 30.01.2021.
//

#include "Menu.h"
#include "Util.h"

void Menu::init () noexcept {
    this->createComponents();
    this->alignComponents();
    this->adjustComponents();
    this->styleComponents();
    this->connectComponents();
}

#include <iostream>
void Menu::createComponents () noexcept {
    this->generalLayout = new QVBoxLayout ( nullptr );
    this->centralButtonsLayout = new QVBoxLayout ( nullptr );

    this->playButton = new QPushButton (this->playButtonText, this);
    this->statisticsButton = new QPushButton (this->statisticsButtonText, this);
    this->tutorialButton = new QPushButton (this->tutorialButtonText, this);

    this->rightButtonsLayout = new QHBoxLayout (nullptr);

    this->profileButton = new QPushButton (this->profileButtonText, this);
    this->settingsButton = new QPushButton (this->settingsButtonText, this);

    this->leftButtonsLayout = new QHBoxLayout (nullptr); ///?

    this->friendsButton = new QPushButton (this->friendsButtonText, this);
    this->inboxButton = new QPushButton (this->inboxButtonText, this);
    this->shopButton = new QPushButton (this->shopButtonText, this);

    this->exitButtonLayout = new QHBoxLayout (nullptr);

    this->exitButton = new QPushButton (this->exitButtonText, this);
}

void Menu::alignComponents() noexcept {
    this->setLayout ( this->generalLayout );

    //// add layout in layout
    //// primul e cel mai sus
    this->generalLayout->addItem( this->rightButtonsLayout );
    this->generalLayout->addItem( this->centralButtonsLayout );
    this->generalLayout->addItem( this->leftButtonsLayout );
    this->generalLayout->addItem( this->exitButtonLayout );

    //// add widget in layout
    this->centralButtonsLayout->addWidget( this->playButton );
    this->centralButtonsLayout->addWidget( this->statisticsButton );
    this->centralButtonsLayout->addWidget( this->tutorialButton );

    this->rightButtonsLayout->addWidget( this->profileButton );
    this->rightButtonsLayout->addWidget( this->settingsButton );

    this->leftButtonsLayout->addWidget( this->friendsButton );
    this->leftButtonsLayout->addWidget( this->inboxButton );
    this->leftButtonsLayout->addWidget( this->shopButton );

    this->exitButtonLayout->addWidget( this->exitButton );

    this->generalLayout->setAlignment(this->rightButtonsLayout, Qt::AlignTop | Qt::AlignRight);
    this->generalLayout->setAlignment(this->centralButtonsLayout, Qt::AlignHCenter | Qt::AlignTop);
    this->generalLayout->setAlignment(this->leftButtonsLayout, Qt::AlignLeft | Qt::AlignBottom);
    this->generalLayout->setAlignment(this->exitButtonLayout, Qt::AlignRight | Qt::AlignBottom);
//    this->generalLayout->setAlignment(this->centralButtonsLayout, Qt::AlignHCenter | Qt::AlignCenter); //todo : place back when inbox section is added
}

void Menu::adjustComponents () noexcept {

}

void Menu::styleComponents() noexcept {
//    this->playButton->setStyleSheet(
//        "QPushButton {"
//        "   border-style: outset;"
//        "   border-width: 5px;"
//        "   border-color: red;"
//        "   border-radius: 5px;"
//        "   height: 200px;"
//        "   width: 200px;"
//        "}"
//        ""
//        "QPushButton:hover {"
//        "   border-style: solid;"
//        "}"
//        ""
//        "QPushButton:pressed {"
//        "   border-style: inset;"
//        "}"
//    );

    auto buttonStyle = Util::getStyle("GeneralButton.css"); // se construieste un string din Util::getStyle, se copiaza intr-ul alt string, se distruge string-ul initial
    //    auto buttonStyle = Util::getStyle("GeneralButton.css").c_str(); // se construieste un string din Util::getStyle, se obtine c_str(), se distruge obiectul

    auto exitButtonStyle = Util::getStyle("ExitButton.css");
    auto optionsButtonStyle = Util::getStyle("OptionsButtons.css");
/**
 *
 * 1. auto buttonStyle = Util::getStyle("GeneralButton.css);
 *          buttonStyle     |   Util::getStyle(...);
 *  DataType std::string    |  std::string
 *  Obj      s2             |  s1
 *  Ptr      p2             |  p1
 *
 *  Distrugem string-ul din functie, distrugem p1.
 *  p2 ramane in pace
 *
 * 2. auto buttonStyle = Util::getStyle("GeneralButton.css).c_str();
 *          buttonStyle     |   Util::getStyle(...);
 *  DataType const char *   | std::string
 *  Obj      ?              | s1
 *  Ptr      p1             | p1
 *  Distrugem string-ul din functie, distrugem p1
 *  buttonStyle avea valoarea p1, se distruge si el
 */

    this->playButton->setStyleSheet(buttonStyle.c_str());
    this->statisticsButton->setStyleSheet(buttonStyle.c_str());
    this->tutorialButton->setStyleSheet(buttonStyle.c_str());

    this->friendsButton->setStyleSheet(optionsButtonStyle.c_str());
    this->shopButton->setStyleSheet(optionsButtonStyle.c_str());
    this->inboxButton->setStyleSheet(optionsButtonStyle.c_str());
    this->profileButton->setStyleSheet(optionsButtonStyle.c_str());
    this->settingsButton->setStyleSheet(optionsButtonStyle.c_str());

    this->exitButton->setStyleSheet(exitButtonStyle.c_str());
}

void Menu::connectComponents() noexcept {
    // []           ()              {}
    // inline func  func params     func def
    // [] <- capture block, iau variabile din context

    // connect emitator + eveniment -> program
    // cand un emitator triggeruieste un eveniment, se apeleaza functia in program
    //
    // daca in functia apelata, capturam obiectul curent, se transforma in functie de tip

    // emitator + eveniment -> obiect + receiver
    // sender event object receiver
    // sender SIGNAL reicever SLOT

//    auto callback = [this] () {
//        this->statisticsButton->hide();
//        static int pressCount = 0; // variabila locala, dar se comporta ca o globala
//        if ( pressCount % 2 == 0)
//            std::cout << "Hello World\n";
//        else
//            std::cout << "Buna Siua\n";
//
//        pressCount ++;
//    };
//
//    connect ( this->playButton, & QPushButton::clicked, callback );
//
//    // varianta 2 -> sender SIGNAL receiver SLOT
//
//    connect ( this->playButton, SIGNAL(clicked()), this, SLOT(onPlayClick()) );


    auto howToPlayCallback = [this] () noexcept -> void {
        emit this->howToPlay();
    };

    connect ( this->tutorialButton, & QPushButton::clicked, howToPlayCallback );
}

//void Menu::onPlayClick() noexcept {
//    this->tutorialButton->hide();
//}

Menu::~Menu () noexcept {
    // undo what has been done in align
    this->centralButtonsLayout->removeWidget (this->playButton);
    this->centralButtonsLayout->removeWidget (this->statisticsButton);
    this->centralButtonsLayout->removeWidget (this->tutorialButton);

    this->rightButtonsLayout->removeWidget(this->profileButton);
    this->rightButtonsLayout->removeWidget(this->settingsButton);

    this->generalLayout->removeItem(this->centralButtonsLayout);
    this->generalLayout->removeItem(this->rightButtonsLayout);

    // undo what has been done in create
    delete this->centralButtonsLayout;
    delete this->generalLayout;

    delete this->playButton;
    delete this->statisticsButton;
    delete this->tutorialButton;

    delete this->rightButtonsLayout;

    delete this->profileButton;
    delete this->settingsButton;
}