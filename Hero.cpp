#include "Hero.h"

using namespace std;

Hero::Hero() {
    string name;
    int strength, charisma, speed;

    cout << "Choose a name for your hero: ";
    cin >> name;
    this->setName(name);

    while(true) {
        int remaining_power = this->max_start_power;
        strength = -1;
        charisma = -1;
        speed = -1;
        cout << "You can spend " << remaining_power << " points on powers";
        cout << endl;
        while (strength < 0 or strength > remaining_power) {
            cout << "Starting strength should be (max: " << remaining_power;
            cout << "): ";
            cin >> strength;
        }
        remaining_power -= strength;
        while (charisma < 0 or charisma > remaining_power) {
            cout << "Starting charisma should be (max: " << remaining_power;
            cout << "): ";
            cin >> charisma;
        }
        remaining_power -= charisma;
        while (speed < 0 or speed > remaining_power) {
            cout << "Starting speed should be (max: " << remaining_power;
            cout << "): ";
            cin >> speed;
        }
        remaining_power -= speed;

        cout << "You set strength " << strength << ", charisma " << charisma;
        cout << " and speed " << speed << endl;
        cout << "You have " << remaining_power << " remaning points" << endl;
        char answer = 'a';
        while (answer != 'y' or answer != 'n') {
            cout << "Would like to keep this setting? (y/n)";
            cin >> answer;
        }
        if (answer == 'y') break;
    }
    this->setStrength(strength);
    this->setCharisma(charisma);
    this->setSpeed(speed);
    this->inventory = new Inventory(2*strength);
    money = 0;
    this->equipped.reserve(5);
}

int Hero::getMoney() {
    return this->money;
}

void Hero::addMoney(int money) {
    this->money += money;
}

int Hero::getStrength() {
    int strength = Person::getStrength();
    for (unsigned int i = 0; i < this->equipped.size(); ++i)
        strength += this->equipped[i]->getStrengthMod();
    return strength;
}

int Hero::getCharisma() {
    int charisma = Person::getCharisma();
    for (unsigned int i = 0; i < this->equipped.size(); ++i)
        charisma += this->equipped[i]->getCharismaMod();
    return charisma;
}

int Hero::getSpeed() {
    int speed = Person::getSpeed();
    for (unsigned int i = 0; i < this->equipped.size(); ++i)
        speed += this->equipped[i]->getSpeedMod();
    return speed;
}

vector<Item*> Hero::getEquipped() {
    return this->equipped;
}

void Hero::setEquipped(Item* item) {
    for (unsigned int i = 0; i < this->equipped.size(); ++i)
        if (item->getName() == this->equipped[i]->getName())
            return;
    bool set = false;
    for (unsigned int i = 0; i < this->equipped.size(); ++i) {
        if (item->getType() == "hand") {
            if (this->equipped[i]->getType() == "hand")
                for (unsigned int j = i + 1; j < this->equipped.size(); ++j)
                    if (this->equipped[j]->getType() == "hand") {
                        cout << "Your hands are already full, do you wish to ";
                        cout << "switch new item:" << endl;
                        item->printInfo();
                        cout << "For item" << endl << "1) ";
                        this->equipped[i]->printInfo();
                        cout << "2) ";
                        this->equipped[j]->printInfo();
                        char answer = 'a';
                        while (answer != '1' or answer != '2' or
                               answer != 'n') {
                            cout << "Your choice is (1/2/n): ";
                            cin >> answer;
                        }
                        if (answer == '1')
                            this->equipped[i] = item;
                        else if (answer == '2')
                            this->equipped[j] = item;
                        set = true;
                        break;
                    }
        }
        else if (item->getType() == this->equipped[i]->getType()) {
            cout << "Your " << item->getType() << " is already being used";
            cout << ", do you want to use the new item:" << endl;
            item->printInfo();
            cout << "Details of item being used: " << endl;
            this->equipped[i]->printInfo();
            char answer = 'a';
            while (answer != 'y' or answer != 'n') {
                cout << "Your choice is (y/n): ";
                cin >> answer;
            }
            if (answer == 'y')
                this->equipped[i] = item;
            set = true;
        }
        if (set == true) break;
    }
    if (not set)
        this->equipped.push_back(item);
}

void Hero::unsetEquipped(string name) {
    for (unsigned int i = 0; i < this->equipped.size(); ++i)
        if (this->equipped[i]->getName() == name)
            this->equipped.erase(this->equipped.begin()+i);
}

void Hero::printEquipped() {
    cout << endl << "==================================================";
    cout << endl << "These items you have equipped:" << endl;
    cout << "Item name: Strength/Charisma/Speed/Special/Type" << endl;
    for (unsigned int i = 0; i < this->equipped.size(); ++i)
        this->equipped[i]->printInfo();
    cout << "==================================================" << endl;
    cout << endl;
}

int Hero::getAction() {
    cout << "Do you want to:" << endl;
    cout << "1) Attack upper body" << endl;
    cout << "2) Attack lower body" << endl;
    cout << "3) Defend upper body" << endl;
    cout << "4) Defend lower body" << endl;
    cout << "5) Flee from fight" << endl;
    int answer = 0;
    while (answer < 1 or answer > 5) {
        cout << "Pick one option (1-5): ";
        cin >> answer;
    }
    return answer;
}

bool Hero::fightWithNPC(NPC* being) {
    cout << "You are entering the duel." << endl;
    int npc_life = 100, hero_life = 100;
    if (this->inventory->isItemInInventory(being->getWeakness()->getName())) {
        cout << "You have an item that NPC has weakness to." << endl;
        npc_life = 0;
    }
    srand(time(NULL));
    while (npc_life > 0 and hero_life > 0) {
        int hero_action = this->getAction();
        if (hero_action == 5) {
            cout << "You are fleeing a fight and might loose some money." << endl;
            if (this->getSpeed() <= being->getSpeed())
                this->money -= being->getStrength();
            break;
        }
        int npc_action = rand() % 4 + 1;
        if (this->getSpeed() > being->getSpeed())
            switch (hero_action) {
                case 1:
                    if (npc_action == 3) {
                        npc_life -= (int) round(this->getStrength() *
                                                (this->getSpeed() /
                                                 (this->getSpeed() +
                                                  being->getSpeed())));
                        cout << "NPC didn't cover fast enough" << endl;
                    }
                    else {
                        npc_life -= this->getStrength();
                        cout << "NPC didn't cover the right place" << endl;
                    }
                    break;
                case 2:
                    if (npc_action != 4) {
                        npc_life -= this->getStrength();
                        cout << "NPC didn't cover the right place" << endl;
                    }
                    else {
                        npc_life -= (int) round(this->getStrength() *
                                                (this->getSpeed() /
                                                 (this->getSpeed() +
                                                  being->getSpeed())));
                        cout << "NPC didn't cover fast enough" << endl;
                    }
                    break;
                case 3:
                    if (npc_action == 2) {
                        hero_life -= being->getStrength();
                        cout << "Hero didn't cover the right place" << endl;
                    }
                    else if (npc_action == 1)
                        cout << "NPC didn't attack fast enough" << endl;
                    else cout << "Both combatants are hiding" << endl;
                    break;
                case 4:
                    if (npc_action == 1) {
                        hero_life -= being->getStrength();
                        cout << "Hero didn't cover the right place" << endl;
                    }
                    else if (npc_action == 2)
                        cout << "NPC didn't attack fast enough" << endl;
                    else cout << "Both combatants are hiding" << endl;
                    break;
            }
        else if (this->getSpeed() < being->getSpeed())
            switch (npc_action) {
                case 1:
                    if (hero_action == 3) {
                        hero_life -= (int) round(being->getStrength() *
                                                 (being->getSpeed() /
                                                  (being->getSpeed() +
                                                   this->getSpeed())));
                        cout << "Hero didn't cover fast enough" << endl;
                    }
                    else {
                        hero_life -= being->getStrength();
                        cout << "Hero didn't cover the right place" << endl;
                    }
                    break;
                case 2:
                    if (hero_action != 4) {
                        hero_life -= being->getStrength();
                        cout << "Hero didn't cover the right place" << endl;
                    }
                    else {
                        hero_life -= (int) round(being->getStrength() *
                                                 (being->getSpeed() /
                                                  (being->getSpeed() +
                                                   this->getSpeed())));
                        cout << "Hero didn't cover fast enough" << endl;
                    }
                    break;
                case 3:
                    if (hero_action == 2) {
                        npc_life -= this->getStrength();
                        cout << "NPC didn't cover the right place" << endl;
                    }
                    else if (hero_action == 1)
                        cout << "Hero didn't attack fast enough" << endl;
                    else cout << "Both combatants are hiding." << endl;
                    break;
                case 4:
                    if (hero_action == 1) {
                        npc_life -= this->getStrength();
                        cout << "NPC didn't cover the right place" << endl;
                    }
                    else if (hero_action == 2)
                        cout << "Hero didn't attack fast enough" << endl;
                    else cout << "Both combatants are hiding." << endl;
                    break;
            }
        else {
            if (hero_action == npc_action and hero_action < 3)
                cout << "Weapons clashed in the air." << endl;
            else if (hero_action > 2 and npc_action > 2)
                cout << "Both combatants are hiding." << endl;
            else if ((hero_action == 1 and npc_action != 3) or
                    (hero_action == 2 and npc_action != 4)) {
                npc_life -= this->getStrength();
                cout << "NPC didn't cover the right place" << endl;
            }
            else if ((npc_action == 1 and hero_action != 3) or
                     (npc_action == 2 and hero_action != 4)) {
                hero_life -= being->getStrength();
                cout << "Hero didn't cover the right place" << endl;
            }
            else cout << "Damage was deflected" << endl;
        }
        cout << "Current health is:" << endl;
        cout << "Hero: "<< hero_life << endl;
        cout << "NPC: " << npc_life << endl;
    } // while loop
    if (hero_life > 0 and npc_life <= 0) {
        int random_money = rand() % 50 + 10;
        cout << "NPC dropped " << random_money << " money." << endl;
        this->money += random_money;
        Item* dropped_item = being->getSpecialItem();
        if (dropped_item) {
            cout << "NPC also dropped this item:" << endl;
            dropped_item->printInfo();
            this->inventory->addItem(dropped_item);
        }
    }
    else if (hero_life <= 0)
        this->resetHero();

    if (npc_life > 0) return false;
    else return true;
}

bool Hero::talkWithNPC(NPC* being) {
    cout << "Interaction with NPC is about to begin." << endl;
    int hostility = being->getHostility();
    bool npc_solved = false, fight = true;
    srand(time(NULL));
    Item* beings_item = being->getSpecialItem();
    int beings_item_value;
    if (beings_item)
        beings_item_value = beings_item->getStrengthMod() +
                beings_item->getCharismaMod() + beings_item->getSpeedMod();
    else beings_item_value = 0;
    while (hostility < this->getCharisma() * 2) {
        if (hostility < 0) {
            cout << "NPC is now your friend and you can continue." << endl;
            npc_solved = true;
            break;
        }
        cout << endl << this->questions[rand() % this->questions.size()];
        pair<string, int> option1, option2, option3;
        option1 = this->answers[rand() % this->answers.size()];
        option2 = this->answers[rand() % this->answers.size()];
        option3 = this->answers[rand() % this->answers.size()];
        cout << "1) " << option1.first << endl;
        cout << "2) " << option2.first << endl;
        cout << "3) " << option3.first << endl;
        cout << "4) Leave this conversation." << endl;
        bool trade = false;
        if (hostility < this->getCharisma() and beings_item) {
            cout << "5) Buy item that this creature holds." << endl;
            cout << "Item: ";
            beings_item->printInfo();
            cout << "For price: " << beings_item_value * hostility;
            trade = true;
        }
        int answer = 0;
        while (answer < 1 or (answer > 4 and !trade) or (answer > 5 and trade)) {
            cout << "Choose answer (1-";
            if (trade) cout << "5): ";
            else cout << "4): ";
            cin >> answer;
        }
        switch (answer)
        {
            case 1:
                hostility += option1.second;
                break;
            case 2:
                hostility += option2.second;
                break;
            case 3:
                hostility += option3.second;
                break;
            case 4:
                fight = false;
                break;
            case 5:
                if (this->money < beings_item_value * hostility)
                    cout << "Inssuficient funds" << endl;
                else {
                    this->money -= beings_item_value * hostility;
                    this->inventory->addItem(beings_item);
                    fight = false;
                    npc_solved = true;
                }
                break;
        }
        if (!fight) break;
    }
    if (!npc_solved and fight) {
        cout << "NPC is too angry at you now, so he's attacking you." << endl;
        npc_solved = this->fightWithNPC(being);
    }
    return npc_solved;
}

void Hero::resetHero() {
    cout << "Hero was reset to original state, you can continue ";
    cout << "with your adventure." << endl;
    delete this->inventory;
    this->inventory = new Inventory(2*this->getStrength());
    this->money = 0;
    this->equipped.erase(this->equipped.begin(), this->equipped.end());
    this->equipped.reserve(5);
}

Hero::~Hero() {
    delete this->inventory;
}

vector<string> Hero::questions =
        {"What are doing in here?", "What do you want from me?",
         "Who dares to bother me?", "Look who's there.",
         "What a weird creature!", "Who are you, mortal?",
         "Are you looking for something?", "How can I help you?",
         "?#~đĐ['$Ł*>##&&@đĐ?!?!?!", "Oook?", "Wassssssssuuuuuuuuuup?",
         "Would you like a jelly baby?", "What do people mean when "
                 "they talk about things?",
         "What does this mean to the average man on the street?",
         "Do you always walk like that?", "Welcome to 101st competition of "
                 "Upper Class Twit of the Year.",
         "My brain hurts.", "Nice day, isn't it?",
         "I wonder what other people use for aftershave lotion.",
         "One of the cross beams has gone out askew on the treadle.",
         "I didn't expect this kind of spanish inquisition.",
         "We were wondering if we could borrow your head for a piece "
                 "of animation.",
         "It certainly makes charted acountancy a much more interesting job.",
         "What kind of sorcery is this?", "Stop it, it makes me giddy.",
         "Are you suggesting coconuts migrate?", "None shall pass.",
         "We want...a shrubbery.", "What is your name?", "What is your quest.",
         "What is your favorite color.", "What is the air speed velocity of "
                 "an unladen swallow?"}; // 32

vector<pair<string, int>> Hero::answers =
        {{"Oook!", -4}, {"My brain hurts too!", -2}, {"Hello sweetie.", 3},
         {"Nobody expects the spanish inquisition!", 5},
         {"Yes it is a very nice day", -9}, {"Can point me to the end?", 3},
         {"What?!", 1}, {"Yes, I would like a jelly baby.", -7},
         {"Do you have something to eat?", 3}, {"You have something I want.", 4},
         {"Your Highness is very kind.", -5}, {"Burn with me!", 10},
         {"Would you like to see my... Nudge, nudge, wink, wink.", 2},
         {"Indeed.", -1}, {"Very funny.", -2}, {"Christmas crackers!", -3},
         {"I'am looking for princess Peach.", 1}, {"Did you see that dragon?", -2},
         {"I'm sorry, I'm so so sorry.", -3}, {"Are you an Upper Class Twit?", 4},
         {"Are you my mummy?", -3}, {"Can we be friends on facebook?", 5},
         {"Would you like a cup of tea?", -1}, {"This is a late parrot.", 1},
         {"And now for something completely different.", -4},
         {"A larch.", -1}, {"I'am Arthur, king of the Brittons", 1},
         {"I seek the finest and bravest soldiers to join me in my cause.", -4},
         {"'Tis but a scratch", 1}, {"All right, we call it a draw.", -2},
         {"Would you like a banana? Bananas are good.", -3},
         {"On the second thought, let's not go to Camelot, it's a silly place", -4},
         {"Message for you sir.", -1}, {"Hahaaa!!", 1}, {"Oh bloody hell.", -1},
         {"Bless this holy handgranade.", -2}, {"Seek the holy grail.", -1},
         {"What do you mean, African or European swallow?", -2},
         {"It is elementary, my dear Watson.", -2}, {"Bite my shiny metal ass", 2},
         {"Quite correct.", -1}, {"Resistance is futile.", 2},
         {"God save the Queen!", -2}, {"Carrot juice, carrot juice, carrot juice.", -2},
         {"Spam, spam, spam!", -1}, {"Me don't cares", 2}, {"Exterminate!", 3},
         {"Delete!", 2}, {"It's bigger on the inside.", -1},
         {"You are lowering the IQ of the whole street.", 3},
         {"Would you like to see my server room?", 2}, {"You shall not pass.", 1},
         {"I will lend you my hamster.", -2}, {"Let's have some wine.", -3},
         {"Let's have some whine.", 3}, {"This is not Jim Beam.", 1},
         {"He's dead, Jim.", -1}, {"I cannae change the laws of physics.", -2},
         {"Gosh, I hate killing people.", 2}}; // 59
