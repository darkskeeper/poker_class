#include <vector>
#include <iostream>
#include <string>
using namespace std;

const int ONE_SUIT = 13;
const int N_CARDS_HAND = 5;
const int N_CARDS = 52;

enum RANK { FIVE = 3, TEN = 8, JACKET, QUEEN, KING, ACE };
enum SUIT { CLUBS, DIAMONDS, HEARTS, SPADES };

class Hand
{
public:
    Hand();
    Hand(const vector <string> your_cards);
    ~Hand();
    string checks() const;
private:
    vector <int> hand;
    vector <int> cards;
    vector <int> combs;
    int determine_cards(const string current_card) const;
    bool straight_check() const;
    bool flash_check() const;
};

int Hand::determine_cards(const string current_card) const
{
    int rank, suit;
    if (current_card.at(0) <= '9' && current_card.at(0) >= '2')
    {
        rank = current_card.at(0) - '2';//переводим char в int, где rank будет значение (карты - 2), то есть для 5 rank = 3
    }
    else
    {
        switch (current_card.at(0))
        {
        case 'A':
            rank = ACE;
            break;
        case 'J':
            rank = JACKET;
            break;
        case 'K':
            rank = KING;
            break;
        case 'Q':
            rank = QUEEN;
            break;
        case 'T':
            rank = TEN;
            break;
        }
    }
    switch (current_card.at(1))
    {
    case 'C':
        suit = CLUBS;
        break;
    case 'D':
        suit = DIAMONDS;
        break;
    case 'H':
        suit = HEARTS;
        break;
    case 'S':
        suit = SPADES;
        break;
    }
    return rank + ONE_SUIT * suit;
}

Hand::Hand()
{
    hand = vector <int>(N_CARDS_HAND, 0);
    cards = vector <int>(N_CARDS, 0);
    combs = vector <int>(5, 0);
}

Hand::Hand(const vector <string> your_cards)
{
    hand = vector <int>(N_CARDS_HAND, 0);
    cards = vector <int>(N_CARDS, 0);
    combs = vector <int>(5, 0);
    for (int i = 0; i < N_CARDS_HAND; i++)
    {
        hand[i] = determine_cards(your_cards[i]);
        cards[hand[i]] = 1;
    }
    for (int i = 0; i < ONE_SUIT; i++)
    {
        combs[cards[i] + cards[i + (1 * ONE_SUIT)] + cards[i + (2 * ONE_SUIT)] + cards[i + (3 * ONE_SUIT)]]++;
    }

}

Hand::~Hand()
{
}

string Hand::checks() const
{
    if (combs[1] == N_CARDS_HAND)
    {
        if (straight_check())
        {
            if (flash_check())
            {
                if (!cards[0] && !cards[ONE_SUIT] && !cards[2 * ONE_SUIT] && !cards[3 * ONE_SUIT] && (cards[ACE] || cards[ACE + ONE_SUIT] || cards[ACE + ONE_SUIT * 2] || cards[ACE + ONE_SUIT * 3]))
                {
                    return "royal flush";
                }
                else
                {
                    return "straight flush";
                }
            }
            else
            {
                return "straight";
            }
        }
        if (flash_check())
        {
            return "flush";
        }
        return "high card";
    }
    else if (combs[4] == 1)
    {
        return "four of a kind";
    }
    else if (combs[3] == 1)
    {
        if (combs[2] == 1)
        {
            return "full house";
        }
        else
        {
            return "three of a kind";
        }
    }
    else if (combs[2] == 2)
    {
        return "two pairs";
    }
    else
    {
        return "pair";
    }
}

bool Hand::straight_check() const
{
    int min = hand[0] % ONE_SUIT;
    int max = min;
    int before_max = 0;
    int card_rank;
    for (int i = 1; i < N_CARDS_HAND; i++)
    {
        card_rank = hand[i] % ONE_SUIT;
        if (card_rank > max)
        {
            before_max = max;
            max = card_rank;
        }
        else if (card_rank > before_max)
        {
            before_max = card_rank;
        }
        if (card_rank < min)
        {
            min = card_rank;
        }
    }
    if (max - min == 4)
    {
        return true;
    }
    else
    {
        if (max == ACE)
        {
            if (before_max == FIVE)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        return false;
    }
}

bool Hand::flash_check() const
{
    int your_suit = hand[0] / ONE_SUIT;
    for (int i = 1; i < N_CARDS_HAND; i++)
    {
        if (hand[i] / ONE_SUIT != your_suit)
        {
            return false;
        }
    }
}

int main()
{
    int Ntests;
    cin >> Ntests;
    while (Ntests--)
    {
        vector <string> your_cards(N_CARDS_HAND);
        for (int i = 0; i < N_CARDS_HAND; i++)
        {
            cin >> your_cards[i];
        }
        Hand hand_one(your_cards);
        cout << hand_one.checks() << endl;
    }
    return 0;
}