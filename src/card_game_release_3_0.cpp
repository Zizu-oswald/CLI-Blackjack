#include <iostream>
#include <cstdlib>
#include <ctime>
#include <array>

enum class cardRangs
{
    ACE,
    KING,
    QUEEN,
    JACK,
    TEN,
    NINE,
    EIGHT,
    SEVEN,
    SIX,
    FIVE,
    FOUR,
    THREE,
    TWO,
};

enum class cardSuits
{
    DIAMONDS,
    HEARTS,
    SPADES,
    CLUBS,
};

struct Card
{
    cardRangs rang;
    cardSuits suit;
};

std::string getCardName(Card card){
    using namespace std;
    string rangName;
    switch (card.rang)
    {
        case cardRangs::ACE:
            rangName = "Ace ";
            break;
        case cardRangs::KING:
            rangName = "King ";
            break;
        case cardRangs::QUEEN:
            rangName = "Queen ";
            break;
        case cardRangs::JACK:
            rangName = "Jack ";
            break;
        case cardRangs::TEN:
            rangName = "10 ";
            break;
        case cardRangs::NINE:
            rangName = "9 ";
            break;
        case cardRangs::EIGHT:
            rangName = "8 ";
            break;
        case cardRangs::SEVEN:
            rangName = "7 ";
            break;
        case cardRangs::SIX:
            rangName = "6 ";
            break;
        case cardRangs::FIVE:
            rangName = "5 ";
            break;
        case cardRangs::FOUR:
            rangName = "4 ";
            break;
        case cardRangs::THREE:
            rangName = "3 ";
            break;
        case cardRangs::TWO:
            rangName = "2 ";
            break;
    }

    switch (card.suit)
    {
        case cardSuits::DIAMONDS:
            return rangName + "Diamond";
        case cardSuits::HEARTS:
            return rangName + "Heart";
        case cardSuits::CLUBS:
            return rangName + "Club";
        case cardSuits::SPADES:
            return rangName + "Spade";
        default:
            return " ";
    }
}

void printCard(Card card){
    using namespace std;
    
    switch (card.rang)
    {
        case cardRangs::ACE:
            cout << "Ace ";
            break;
        case cardRangs::KING:
            cout << "King ";
            break;
        case cardRangs::QUEEN:
            cout << "Queen ";
            break;
        case cardRangs::JACK:
            cout << "Jack ";
            break;
        case cardRangs::TEN:
            cout << "10 ";
            break;
        case cardRangs::NINE:
            cout << "9 ";
            break;
        case cardRangs::EIGHT:
            cout << "8 ";
            break;
        case cardRangs::SEVEN:
            cout << "7 ";
            break;
        case cardRangs::SIX:
            cout << "6 ";
            break;
        case cardRangs::FIVE:
            cout << "5 ";
            break;
        case cardRangs::FOUR:
            cout << "4 ";
            break;
        case cardRangs::THREE:
            cout << "3 ";
            break;
        case cardRangs::TWO:
            cout << "2 ";
            break;
    }

    switch (card.suit)
    {
        case cardSuits::DIAMONDS:
            cout << "Diamond";
            break;
        case cardSuits::HEARTS:
            cout << "Heart";
            break;
        case cardSuits::CLUBS:
            cout << "Club";
            break;
        case cardSuits::SPADES:
            cout << "Spade";
            break;
    }
}

void printDeck(const std::array<Card, 52> &deck){

    for (Card card : deck){
        printCard(card);
        std::cout << "\n";
    }
}

void swapCard(Card &leftCard, Card &rightCard){
    Card container;
    container = leftCard;
    leftCard = rightCard;
    rightCard = container;
}

void randomizeDeck(std::array<Card, 52> &deck){

    for (int iii = 0; iii < 100; iii++)
    {
        for (Card &card : deck){
            swapCard(card, deck[rand() % 52]);
        }
    }
}

int getCardValue(Card card){
    switch (card.rang){
        case cardRangs::TWO:
            return 2;
        case cardRangs::THREE:
            return 3;
        case cardRangs::FOUR:
            return 4;
        case cardRangs::FIVE:
            return 5;
        case cardRangs::SIX:
            return 6;
        case cardRangs::SEVEN:
            return 7;
        case cardRangs::EIGHT:
            return 8;
        case cardRangs::NINE:
            return 9;
        case cardRangs::TEN:
        case cardRangs::JACK:
        case cardRangs::QUEEN:
        case cardRangs::KING:
            return 10;
        case cardRangs::ACE:
            return 11;
        default:
            return 0;
    }
}

// Проверка наличие туза в карте
void aceCheck(Card &card, int &aceCounter){
    aceCounter += ((card.rang == cardRangs::ACE) ? 1 : 0);
}

// Пребразование туза из 11 в 1 при наличии туза  
void ace11_1(int &aceCounter, int &summ){
    if (aceCounter > 0){
        summ -= 10;
        aceCounter--;
    }
}

int playerPlaying(int &playerSumm, Card *&cardPtr, int aceCounterPlayer, int &multiplier, std::string playerSolution = " ");

int split(Card *&cardPtr, Card firstCard, Card secondCard, int &firstCardSumm, int &secondCardSumm, int &firstCardMultiplier, int &secondCardMultiplier, int bet){
    using namespace std;
    int aceCounterFirst = 0, aceCounterSecond = 0;
    firstCardSumm = getCardValue(firstCard);
    cout << "You have: " << getCardName(firstCard) << " (" << firstCardSumm << ")\n";
    firstCardSumm += getCardValue(*cardPtr);
    aceCheck(*cardPtr, aceCounterFirst);
    ace11_1(aceCounterFirst, firstCardSumm);
    cout << "You take: " << getCardName(*cardPtr++) << " (" << firstCardSumm << ")\n";

    // Игра при сплите 2х тузов
    if ((getCardValue(firstCard) == 11) && (getCardValue(secondCard) == 11)){
        goto skip5;
    }

    playerPlaying(firstCardSumm, cardPtr, aceCounterFirst, firstCardMultiplier);
    if (firstCardSumm == -1){ // Проверка на сдачу игрока первой карты
        cout << "You surrended and lost: " << bet / 2 << "\n";
    }
    if (firstCardSumm > 21)
        cout << "With first card you lost: " << bet * firstCardMultiplier << "\n";

    skip5:
    cout << "\n";

    secondCardSumm = getCardValue(secondCard);
    cout << "You have: " << getCardName(secondCard) << " (" << secondCardSumm << ")\n";
    secondCardSumm += getCardValue(*cardPtr);
    aceCheck(*cardPtr, aceCounterSecond);
    ace11_1(aceCounterSecond, secondCardSumm);
    cout << "You take: " << getCardName(*cardPtr++) << " (" << secondCardSumm << ")\n";

    // Игра при сплите 2х тузов
    if ((getCardValue(firstCard) == 11) && (getCardValue(secondCard) == 11)){
        goto skip6;
    }

    playerPlaying(secondCardSumm, cardPtr, aceCounterSecond, secondCardMultiplier);
    if (secondCardSumm == -1){ // Проверка на сдачу игрока второй карты
        cout << "You surrended and lost: " << bet / 2 << "\n";
    }
    if (secondCardSumm > 21)
        cout << "With second card you lost: " << bet * secondCardMultiplier << "\n";
    
    skip6:
    cout << "\n";
    return 0;
}

int playerPlaying(int &playerSumm, Card *&cardPtr, int aceCounterPlayer, int &multiplier, std::string playerSolution){
    // Игра игрока
    using namespace std;
    while ((playerSolution != "hit") && (playerSolution != "stand") && (playerSolution != "surrend") && (playerSolution != "double")){
        cout << "| hit | stand | double | surrend |\n";
        cin >> playerSolution;
    } 
    
    if (playerSolution == "double"){
        multiplier = 2;
        goto doubleSkip;
    }

    if (playerSolution == "surrend"){
        playerSumm = -1;
        return 0;
    }

    while (playerSolution == "hit"){
        doubleSkip:
        playerSumm += getCardValue(*cardPtr);
        aceCheck(*cardPtr, aceCounterPlayer);
        if (playerSumm > 21){
            ace11_1(aceCounterPlayer, playerSumm);
        }
        cout << "You take: " << getCardName(*cardPtr++) << " (" << playerSumm << ")\n";
        if (playerSumm > 21){
            return 0;    
        }
        do{
        cout << "| hit | stand |\n";
        cin >> playerSolution;
        } while ((playerSolution != "hit") && (playerSolution != "stand"));
    }
    return 0;
}

int playBlackjack(std::array<Card, 52> &deck, int bank){
    using namespace std;
    // Ставка
    long long bet;
    cout << "Your bet: ";
    cin >> bet;
    cout << "\n";
    // Проверка ставки
    while (bet > bank){
        cout << "Your bet bigger then bank, please enter another bet: ";
        cin >> bet;
    }
    while (bet <= 0){
        cout << "You need to bet something, please enter another bet: ";
        cin >> bet;
    }
    
    // Первая строка (первые 2 карты дилера)
    int aceCounterDealer = 0; // Счетчик тузов дилера
    Card *cardPtr = &deck[0];
    Card dealerFirstCard = *cardPtr++;
    aceCheck(dealerFirstCard, aceCounterDealer);
    Card dealerSecondCard = *cardPtr++;
    aceCheck(dealerSecondCard, aceCounterDealer);
    int dealerSumm = getCardValue(dealerFirstCard) + getCardValue(dealerSecondCard);
    if (dealerSumm > 21){
        ace11_1(aceCounterDealer, dealerSumm);
    }
    cout << "Dealer have: " << getCardName(dealerFirstCard) << " + ??? (" << getCardValue(dealerFirstCard) << ")\n";

    // Вторая строка (первые 2 карты игрока)
    int multiplier{1}; // Множитель для double
    int aceCounterPlayer = 0; // Счетчик тузов игрока
    Card playerFirstCard = *cardPtr++;
    aceCheck(playerFirstCard, aceCounterPlayer);
    Card playerSecondCard = *cardPtr++;
    aceCheck(playerSecondCard, aceCounterPlayer);
    int playerSumm = getCardValue(playerFirstCard) + getCardValue(playerSecondCard);
    if (playerSumm > 21){
        ace11_1(aceCounterPlayer, playerSumm);
    }
    cout << "You have: " << getCardName(playerFirstCard) << " + " << getCardName(playerSecondCard) << " (" << playerSumm << ")\n";

    // У игрока блэкджек
    if ((playerSumm == 21) && (getCardValue(dealerFirstCard) < 10)){
        cout << "You win: " << int(bet*1.5) << "\n";
        return int(bet*1.5);
    }
    if ((playerSumm == 21) && (getCardValue(dealerFirstCard) >= 10)){
        string evenMoneySolution;
        cout << "Would you like to take even money on this bet?\n";
        do {
            cout << "yes / no\n";
            cin >> evenMoneySolution;
        } while ((evenMoneySolution != "yes") && (evenMoneySolution != "no"));
        if (evenMoneySolution == "yes"){
            cout << "You win: " << bet << "\n";
            return bet;
        }
        else if ((evenMoneySolution == "no") && (dealerSumm == 21)){
            cout << "Dealer have: " << getCardName(dealerFirstCard) << " + " << getCardName(dealerSecondCard) << " (" << dealerSumm << ")\n";
            cout << "You haven't won anything\n";
            return 0;
        }
        else {
            cout << "Dealer have: " << getCardName(dealerFirstCard) << " + " << getCardName(dealerSecondCard) << " (" << dealerSumm << ")\n";
            cout << "You win: " << int(bet*1.5) << "\n";
            return int(bet * 1.5);
        }

    }

    // У диллера блэкджек с первой десяткой
    if ((getCardValue(dealerFirstCard) == 10) && (getCardValue(dealerSecondCard) == 11)){
        cout << "Dealer have: " << getCardName(dealerFirstCard) << " + " << getCardName(dealerSecondCard) << " (" << dealerSumm << ")\n";
        cout << "Dealer have blackjack, you lost: " << bet << "\n";
        return -bet;
    }

    // Страховка у игрока
    int insurance{0};
    if (getCardValue(dealerFirstCard) == 11){
        string insurenceSolution;
        cout << "Would you like to take incurence on this bet?\n";
        do {
            cout << "yes / no\n";
            cin >> insurenceSolution;
        } while ((insurenceSolution != "yes") && (insurenceSolution != "no"));
        if (dealerSumm == 21){
            if (insurenceSolution == "yes"){
                cout << "Dealer have: " << getCardName(dealerFirstCard) << " + " << getCardName(dealerSecondCard) << " (" << dealerSumm << ")\n";
                cout << "Your insurance has worked\n";
                return 0;
            }
            else {
                cout << "Dealer have: " << getCardName(dealerFirstCard) << " + " << getCardName(dealerSecondCard) << " (" << dealerSumm << ")\n";
                cout << "You lost: " << bet << "\n";
                return -bet;
            }
        }
        else{
            if (insurenceSolution == "yes"){
                cout << "The dealer doesn't have blackjack\n";
                insurance = bet / 2;
            }
            else {
                cout << "The dealer doesn't have blackjack\n";
            }
        }
    }

    // Сплит
    int isSplit = 0;
    string playerSolution = " ";
    if (getCardValue(playerFirstCard) == getCardValue(playerSecondCard)){
        do{
            cout << "| hit | stand | split | surrend |\n";
            cin >> playerSolution;
        } while ((playerSolution != "hit") && (playerSolution != "stand") && (playerSolution != "split") && (playerSolution != "surrend"));
    }

    // Сдача при возможности сплита
    if (playerSolution == "surrend"){
        cout << "You surrended and lost: " << bet / 2 << "\n";
        if (insurance != 0){
            cout << "You lost because of insurance: " << insurance << "\n";
        }
        return ((-bet / 2) - insurance);
    }
    //

    int firstCardSumm{0}, secondCardSumm{0};
    int firstCardMultiplier{0}, secondCardMultiplier{0};
    if (playerSolution == "split"){
        isSplit = 1;
        split(cardPtr, playerFirstCard, playerSecondCard, firstCardSumm, secondCardSumm, firstCardMultiplier, secondCardMultiplier, bet);
        goto skip3;
    }

    // Игра игрока без сплита
    playerPlaying(playerSumm, cardPtr, aceCounterPlayer, multiplier, playerSolution);
    
    // Сдача
    if (playerSumm == -1){
        cout << "You surrended and lost: " << bet / 2 << "\n";
        if (insurance != 0){
            cout << "You lost because of insurance: " << insurance << "\n";
        }
        return ((-bet / 2) - insurance);
    }
    //

    // Игрок сразу перебрал карт
    if (playerSumm > 21){
        cout << "You lost: " << bet * multiplier << "\n";
        if (insurance != 0){
            cout << "You lost because of insurance: " << insurance << "\n";
        }
        return (-bet * multiplier - insurance);
    }

    // Игра дилера
    skip3:
    cout << "Dealer have: " << getCardName(dealerFirstCard) << " + " << getCardName(dealerSecondCard) << " (" << dealerSumm << ")\n";
    while (dealerSumm < 17){
        dealerSumm += getCardValue(*cardPtr);
        aceCheck(*cardPtr, aceCounterDealer);
        if (dealerSumm > 21){
            ace11_1(aceCounterDealer, dealerSumm);
        }
        cout << "Dealer take: " << getCardName(*cardPtr++) << " (" << dealerSumm << ")\n";
    }

    // Результаты
    if (isSplit == 0){ // Результаты без сплита  
        if (dealerSumm > 21){
            cout << "You win: " << bet * multiplier << "\n";
            if (insurance != 0){
                cout << "You lost because of insurance: " << insurance << "\n";
            }
            return (bet * multiplier - insurance);
        }  
        if (playerSumm > dealerSumm){
            cout << "You win: " << bet * multiplier << "\n";
            if (insurance != 0){
                cout << "You lost because of insurance: " << insurance << "\n";
            }
            return (bet * multiplier - insurance);
        }
        if (playerSumm < dealerSumm){
            cout << "You lost: " << bet * multiplier << "\n";
            if (insurance != 0){
                cout << "You lost because of insurance: " << insurance << "\n";
            }
            return (-bet * multiplier - insurance);
        }
        if (playerSumm == dealerSumm){
            cout << "Draw\n";
            if (insurance != 0){
                cout << "You lost because of insurance: " << insurance << "\n";
            }
            return (0 - insurance);      // ничья
        } 
    }
    else{ // Результаты со сплитом
        int total{0};
        if (firstCardSumm == -1){ // Сдача при сплите
            total -= bet / 2;
            goto skip1;
        }
        if (firstCardSumm > 21){
            total -= bet * firstCardMultiplier;
            goto skip1;
        }
        if ((firstCardSumm > dealerSumm) || (dealerSumm > 21)){
            cout << "With first card you win: " << bet * firstCardMultiplier << "\n";
            total += bet * firstCardMultiplier;
            goto skip1;
        }
        if (firstCardSumm < dealerSumm){
            cout << "With first card you lost: " << bet * firstCardMultiplier << "\n";
            total -= bet * firstCardMultiplier;
        }
        if (firstCardSumm == dealerSumm){
            cout << "With first card you draw\n";
        }
        skip1:
        if (secondCardSumm == -1){ // Сдача при сплите
            total -= bet / 2;
            goto skip2;
        }
        if (secondCardSumm > 21){
            total -= bet * secondCardMultiplier;
            goto skip2;
        }
        if ((secondCardSumm > dealerSumm) || (dealerSumm > 21)){
            cout << "With second card you win: " << bet * secondCardMultiplier << "\n";
            total += bet * secondCardMultiplier;
            goto skip2;
        }
        if (secondCardSumm < dealerSumm){
            cout << "With second card you lost: " << bet * secondCardMultiplier << "\n";
            total -= bet * secondCardMultiplier;
        }
        if (secondCardSumm == dealerSumm){
            cout << "With second card you draw\n";
        }
        skip2:
        if (insurance != 0){
            cout << "You lost because of insurance: " << insurance << "\n";
        }
        return (total - insurance);
    }
  
    return 0;
}

int main(){
    using namespace std;
    array<Card, 52> deck;
    srand(static_cast<unsigned int>(time(0)));

    // Формирование колоды
    for (int suit = 0; suit <= (int)cardSuits::CLUBS; suit++){
        for (int rang = 0; rang <= (int)cardRangs::TWO; rang++){
            deck[suit * 13 + rang].rang = (cardRangs)rang;
            deck[suit * 13 + rang].suit = (cardSuits)suit;
        }
    }
    randomizeDeck(deck);

    // Тестировка
    // deck[0].rang = cardRangs::ACE;LOL
    // deck[1].rang = cardRangs::SIX;
    // deck[2].rang = cardRangs::TEN;
    // deck[3].rang = cardRangs::TEN;
    // deck[4].rang = cardRangs::KING;
    // deck[5].rang = cardRangs::KING;

    long long bank;
    cout << "Your banka: ";
    cin >> bank;
    while (bank > 0){
        bank += playBlackjack(deck, bank);
        cout << "\nYour bank: " << bank << "\n";
        randomizeDeck(deck);
    }
    // int a;
    // cin >> a;
}