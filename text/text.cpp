#include <array>
#include <cstdlib>
#include "..\text\nums.cpp"
#include "SDL2/SDL_stdinc.h"
#include <algorithm>


class Text {
protected:
    static const int size = 500;
    static constexpr std::array<Uint8, 3> lightgrey  = {217, 217, 217};
    static constexpr std::array<Uint8, 3> lightgreen = {0,   255, 0  };

private:
    std::array<std::array<std::array<Uint8, 3>, 3>, size> press(
        std::array<Uint8, 3> l1,
        std::array<Uint8, 3> l2,
        std::array<Uint8, 3> l3,
        std::array<Uint8, 3> l4,
        std::array<Uint8, 3> l5
    ) {
        
        std::array<std::array<std::array<Uint8, 3>, 3>, size> press {{
            {l1, one,   lightgrey},  {l1, two,   lightgrey}, 
            {l1, three, lightgrey},  {l2, one,   lightgrey}, 
            {l2, three, lightgrey},  {l3, one,   lightgrey},
            {l3, two,   lightgrey},  {l3, three, lightgrey}, 
            {l4, one,   lightgrey},  {l5, one,   lightgrey}, //! p
    
            {l1, five, lightgrey}, {l1, six,   lightgrey}, 
            {l2, five, lightgrey}, {l2, seven, lightgrey}, 
            {l3, five, lightgrey}, {l3, six,   lightgrey}, 
            {l4, five, lightgrey}, {l4, seven, lightgrey}, 
            {l5, five, lightgrey}, {l5, seven, lightgrey}, //! r
    
            {l1, nine,   lightgrey}, {l1, ten,  lightgrey}, 
            {l1, eleven, lightgrey}, {l2, nine, lightgrey}, 
            {l3, nine,   lightgrey}, {l3, ten,  lightgrey}, 
            {l3, eleven, lightgrey}, {l4, nine, lightgrey}, 
            {l5, nine,   lightgrey}, {l5, ten,  lightgrey}, 
            {l5, eleven, lightgrey},                                         //! e
    
            {l1, thirteen, lightgrey}, {l1, fourteen, lightgrey}, 
            {l1, fifteen,  lightgrey}, {l2, thirteen, lightgrey}, 
            {l3, thirteen, lightgrey}, {l3, fourteen, lightgrey}, 
            {l3, fifteen,  lightgrey}, {l4, fifteen,  lightgrey},
            {l5, thirteen, lightgrey}, {l5, fourteen, lightgrey}, 
            {l5, fifteen,  lightgrey},                                             //! s
    
            {l1, seventeen, lightgrey}, {l1, eighteen,  lightgrey}, 
            {l1, nineteen,  lightgrey}, {l2, seventeen, lightgrey}, 
            {l3, seventeen, lightgrey}, {l3, eighteen,  lightgrey},
            {l3, nineteen,  lightgrey}, {l4, nineteen,  lightgrey}, 
            {l5, seventeen, lightgrey}, {l5, eighteen,  lightgrey},
            {l5, nineteen,  lightgrey},                                              //! s
        }};    
        return press;       
    }

    std::array<std::array<std::array<Uint8, 3>, 3>, size> to(
        std::array<Uint8, 3> l1,
        std::array<Uint8, 3> l2,
        std::array<Uint8, 3> l3,
        std::array<Uint8, 3> l4,
        std::array<Uint8, 3> l5
    ) {
        
        std::array<std::array<std::array<Uint8, 3>, 3>, size> to {{
            {l1, fourty_three, lightgrey}, {l1, fourty_four,  lightgrey}, 
            {l1, fourty_five,  lightgrey}, {l2, fourty_three, lightgrey}, 
            {l3, fourty_three, lightgrey}, {l4, fourty_three, lightgrey}, 
            {l5, fourty_three, lightgrey},                                                //! t

            {l1,  fourty_seven, lightgrey}, {l1,  fourty_eight, lightgrey}, 
            {l1,  fourty_nine,  lightgrey}, {l2, fourty_seven, lightgrey}, 
            {l2, fourty_nine,  lightgrey}, {l3, fourty_seven, lightgrey}, 
            {l3, fourty_nine,  lightgrey}, {l4, fourty_seven, lightgrey}, 
            {l4, fourty_nine,  lightgrey}, {l5, fourty_seven, lightgrey}, 
            {l5, fourty_eight, lightgrey}, {l5, fourty_nine,  lightgrey}, //! o
        }};
        return to;
    }

    std::array<std::array<std::array<Uint8, 3>, 3>, size> clear_the_field(
        std::array<Uint8, 3> l1,
        std::array<Uint8, 3> l2,
        std::array<Uint8, 3> l3,
        std::array<Uint8, 3> l4,
        std::array<Uint8, 3> l5
    ) {
        
        std::array<std::array<std::array<Uint8, 3>, 3>, size> clear_the_field {{
            {l1, fifty_two,  lightgrey}, {l1, fifty_three, lightgrey},
            {l1, fifty_four, lightgrey}, {l2, fifty_two,   lightgrey}, 
            {l3, fifty_two,  lightgrey}, {l4, fifty_two,   lightgrey},
            {l5, fifty_two,  lightgrey}, {l5, fifty_three, lightgrey},
            {l5, fifty_four, lightgrey},                                               //! c

             {l1,  fifty_six,  lightgrey}, {l2, fifty_six,   lightgrey},
            {l3, fifty_six,   lightgrey}, {l4, fifty_six,   lightgrey},
            {l5, fifty_six,   lightgrey}, {l5, fifty_seven, lightgrey},
            {l5, fifty_eight, lightgrey},                                                //! l

            {l1, sixty,     lightgrey}, {l1, sixty_one, lightgrey}, 
            {l1, sixty_two, lightgrey}, {l2, sixty,     lightgrey}, 
            {l3, sixty,     lightgrey}, {l3, sixty_one, lightgrey}, 
            {l3, sixty_two, lightgrey}, {l4, sixty,     lightgrey}, 
            {l5, sixty,     lightgrey}, {l5, sixty_one, lightgrey}, 
            {l5, sixty_two, lightgrey},                                              //! e

            {l1, sixty_four, lightgrey}, {l1, sixty_five, lightgrey},
            {l1, sixty_six,  lightgrey}, {l2, sixty_four, lightgrey},
            {l2, sixty_six,  lightgrey}, {l3, sixty_four, lightgrey},
            {l3, sixty_five, lightgrey}, {l3, sixty_six,  lightgrey},
            {l4, sixty_four, lightgrey}, {l4, sixty_six,  lightgrey},
            {l5, sixty_four, lightgrey}, {l5, sixty_six,  lightgrey}, //! a

            {l1, sixty_eight, lightgrey}, {l1, sixty_nine, lightgrey}, 
            {l2, sixty_eight, lightgrey}, {l2, seventy,    lightgrey}, 
            {l3, sixty_eight, lightgrey}, {l3, sixty_nine, lightgrey}, 
            {l4, sixty_eight, lightgrey}, {l4, seventy,    lightgrey}, 
            {l5, sixty_eight, lightgrey}, {l5, seventy,    lightgrey}, //! r

            {l1, seventy_three, lightgrey}, {l1, seventy_four,  lightgrey}, 
            {l1, seventy_five,  lightgrey}, {l2, seventy_three, lightgrey}, 
            {l3, seventy_three, lightgrey}, {l4, seventy_three, lightgrey}, 
            {l5, seventy_three, lightgrey},                                                  //! t

            {l1, seventy_seven, lightgrey}, {l1, seventy_nine,  lightgrey},
            {l2, seventy_seven, lightgrey}, {l2, seventy_eight, lightgrey}, 
            {l2, seventy_nine,  lightgrey}, {l3, seventy_seven, lightgrey}, 
            {l3, seventy_eight, lightgrey}, {l3, seventy_nine,  lightgrey},
            {l4, seventy_seven, lightgrey}, {l4, seventy_nine,  lightgrey},
            {l5, seventy_seven, lightgrey}, {l5, seventy_nine,  lightgrey}, //! h

            {l1, eighty_one,   lightgrey}, {l1, eighty_two, lightgrey}, 
            {l1, eighty_three, lightgrey}, {l2, eighty_one, lightgrey}, 
            {l3, eighty_one,   lightgrey}, {l3, eighty_two, lightgrey}, 
            {l3, eighty_three, lightgrey}, {l4, eighty_one, lightgrey}, 
            {l5, eighty_one,   lightgrey}, {l5, eighty_two, lightgrey}, 
            {l5, eighty_three, lightgrey},                                               //! e

            {l1, eighty_five,  lightgrey}, {l1, eighty_six,  lightgrey}, 
            {l1, eighty_seven, lightgrey}, {l2, eighty_five, lightgrey}, 
            {l3, eighty_five,  lightgrey}, {l3, eighty_six,  lightgrey}, 
            {l3, eighty_seven, lightgrey}, {l4, eighty_five, lightgrey}, 
            {l5, eighty_five,  lightgrey},                                                //! f
            
            {l1, ninety,     lightgrey}, {l1, ninety_one, lightgrey}, 
            {l1, ninety_two, lightgrey}, {l2, ninety_one, lightgrey},
            {l3, ninety_one, lightgrey}, {l4, ninety_one, lightgrey},
            {l5, ninety,     lightgrey}, {l5, ninety_one, lightgrey}, 
            {l5, ninety_two, lightgrey},                                               //! i

             {l1, ninety_four, lightgrey},  {l1, ninety_five, lightgrey}, 
             {l1, ninety_six,  lightgrey}, {l2, ninety_four, lightgrey}, 
            {l3, ninety_four, lightgrey}, {l3, ninety_five, lightgrey}, 
            {l3, ninety_six,  lightgrey}, {l4, ninety_four, lightgrey}, 
            {l5, ninety_four, lightgrey}, {l5, ninety_five, lightgrey}, 
            {l5, ninety_six,  lightgrey},                                                 //! e

            {l1, ninety_eight, lightgrey}, {l2, ninety_eight, lightgrey},
            {l3, ninety_eight, lightgrey}, {l4, ninety_eight, lightgrey},
            {l5, ninety_eight, lightgrey}, {l5, ninety_nine,  lightgrey},
            {l5, one_hundred,  lightgrey},                                                  //! l

            {l1, one_hundred_two, lightgrey}, {l1, one_hundred_three, lightgrey},
            {l2, one_hundred_two, lightgrey}, {l2, one_hundred_four,  lightgrey},
            {l3, one_hundred_two, lightgrey}, {l3, one_hundred_four,  lightgrey},
            {l4, one_hundred_two, lightgrey}, {l4, one_hundred_four,  lightgrey},
            {l5, one_hundred_two, lightgrey}, {l5, one_hundred_three, lightgrey}  //! d
        }};
        return clear_the_field;
    }

protected:
    std::array<std::array<std::array<Uint8, 3>, 3>, size> words(int type=1, int line=1) {
        std::array<Uint8, 3> l1;
        std::array<Uint8, 3> l2;
        std::array<Uint8, 3> l3;
        std::array<Uint8, 3> l4;
        std::array<Uint8, 3> l5;
        if (line == 1) {
            l1 = one;
            l2 = two;
            l3 = three;
            l4 = four;
            l5 = five;
        } else if ( line == 2 ) {
            l1 = eight;
            l2 = nine;
            l3 = ten;
            l4 = eleven;
            l5 = twelve;
        }else if ( line == 3 ) {
            l1 = fifteen;
            l2 = sixteen;
            l3 = seventeen;
            l4 = eighteen;
            l5 = nineteen;
        }else if ( line == 4 ) {
            l1 = twenty_two;
            l2 = twenty_three;
            l3 = twenty_four;
            l4 = twenty_five;
            l5 = twenty_six;
        };

        if (type == 1) {
            return press(l1, l2, l3, l4, l5);
        } else if (type == 2) {
            return to(l1, l2, l3, l4, l5);
        } else {
            return clear_the_field(l1, l2, l3, l4, l5);
        }
    }

    std::array<std::array<std::array<Uint8, 3>, 3>, size> get_1st_line() {
        std::array<std::array<std::array<Uint8, 3>, 3>, size> press = words(1, 1);
        std::array<std::array<std::array<Uint8, 3>, 3>, size> to    = words(2, 1);

        std::array<std::array<std::array<Uint8, 3>, 3>, size> first_line = {{
            // press 
            {one,   twenty_two,   lightgreen}, {one,   twenty_three, lightgreen}, 
            {one,   twenty_four,  lightgreen}, {two,   twenty_two,   lightgreen},
            {two,   twenty_four,  lightgreen}, {three, twenty_two,   lightgreen}, 
            {three, twenty_three, lightgreen}, {three, twenty_four,  lightgreen},
            {four,  twenty_four,  lightgreen}, {five,  twenty_four,  lightgreen}, //! q
    
            // to
                                                                                                                
            {one,   fifty_two,   lightgrey}, {one,   fifty_three, lightgrey}, 
            {one,   fifty_four,  lightgrey}, {two,   fifty_two,   lightgrey},
            {two,   fifty_four,  lightgrey}, {three, fifty_two,   lightgrey}, 
            {three, fifty_three, lightgrey}, {three, fifty_four,  lightgrey},
            {four,  fifty_four,  lightgrey}, {five,  fifty_four,  lightgrey}, //! q
    
            {one,   fifty_six,   lightgrey}, {one,   fifty_eight, lightgrey},
            {two,   fifty_six,   lightgrey}, {two,   fifty_eight, lightgrey},
            {three, fifty_six,   lightgrey}, {three, fifty_eight, lightgrey},
            {four,  fifty_six,   lightgrey}, {four,  fifty_eight, lightgrey}, 
            {five,  fifty_six,   lightgrey}, {five,  fifty_seven, lightgrey},
            {five,  fifty_eight, lightgrey},                                                   //! u
    
            {one,   sixty,     lightgrey}, {one,  sixty_one, lightgrey}, 
            {one,   sixty_two, lightgrey}, {two,  sixty_one, lightgrey},
            {three, sixty_one, lightgrey}, {four, sixty_one, lightgrey},
            {five,  sixty,     lightgrey}, {five, sixty_one, lightgrey}, 
            {five,  sixty_two, lightgrey},                                                //! i
            
            {one,   sixty_four, lightgrey}, {one,  sixty_five, lightgrey}, 
            {one,   sixty_six,  lightgrey}, {two,  sixty_five, lightgrey}, 
            {three, sixty_five, lightgrey}, {four, sixty_five, lightgrey}, 
            {five,  sixty_five, lightgrey},                                                 //! t
        }};

        size_t start_position = 10;
        std::copy(to.begin(), to.end(), first_line.begin() + start_position);

        std::copy(press.begin(), press.end(), first_line.begin());
    
        return first_line;
    }

    std::array<std::array<std::array<Uint8, 3>, 3>, size> get_2st_line() {
        std::array<std::array<std::array<Uint8, 3>, 3>, size> press = words(1, 1);
        std::array<std::array<std::array<Uint8, 3>, 3>, size> to    = words(2, 1);

        std::array<std::array<std::array<Uint8, 3>, 3>, size> second_line = {{
             {eight,  twenty_two,  lightgreen}, {eight,  twenty_three, lightgreen}, 
             {eight,  twenty_four, lightgreen}, {nine,   twenty_two,   lightgreen}, 
             {ten,    twenty_two,  lightgreen}, {ten,    twenty_three, lightgreen}, 
             {ten,    twenty_four, lightgreen}, {eleven, twenty_four,  lightgreen},
             {twelve, twenty_two,  lightgreen}, {twelve, twenty_three, lightgreen}, 
            {twelve, twenty_four, lightgreen},                                                     //! s

            {eight,  twenty_six,   lightgreen},  {eight,  twenty_seven, lightgreen}, 
            {eight,  twenty_eight, lightgreen},  {nine,   twenty_six,   lightgreen}, 
            {nine,   twenty_eight, lightgreen},  {ten,    twenty_six,   lightgreen},
            {ten,    twenty_seven, lightgreen},  {ten,    twenty_eight, lightgreen}, 
            {eleven, twenty_six,   lightgreen},  {twelve, one,          lightgreen}, //! p

            {eight,  thirty,     lightgreen}, {eight,  thirty_one, lightgreen},
            {eight,  thirty_two, lightgreen}, {nine,   thirty,     lightgreen},
            {nine,   thirty_two, lightgreen}, {ten,    thirty,     lightgreen},
            {ten,    thirty_one, lightgreen}, {ten,    thirty_two, lightgreen},
            {eleven, thirty,     lightgreen}, {eleven, thirty_two, lightgreen},
            {twelve, thirty,     lightgreen}, {twelve, thirty_two, lightgreen}, //! a

            {eight,  thirty_four, lightgreen}, {eight,  thirty_five, lightgreen},
            {eight,  thirty_six,  lightgreen}, {nine,   thirty_four, lightgreen}, 
            {ten,    thirty_four, lightgreen}, {eleven, thirty_four, lightgreen},
            {twelve, thirty_four, lightgreen}, {twelve, thirty_five, lightgreen},
            {twelve, thirty_six,  lightgreen},                                                     //! c

            {eight,  thirty_eight, lightgreen}, {eight,  thirty_nine,  lightgreen}, 
            {eight,  fourty,       lightgreen}, {nine,   thirty_eight, lightgreen}, 
            {ten,    thirty_eight, lightgreen}, {ten,    thirty_nine,  lightgreen}, 
            {ten,    fourty,       lightgreen}, {eleven, thirty_eight, lightgreen}, 
            {twelve, thirty_eight, lightgreen}, {twelve, thirty_nine,  lightgreen}, 
            {twelve, fourty,       lightgreen},                                                      //! e

        }};

        return second_line;        
    }

    std::array<std::array<std::array<Uint8, 3>, 3>, size> get_3st_line() {

    }

    std::array<std::array<std::array<Uint8, 3>, 3>, size> get_4st_line() {

    }

public:
    std::array<std::array<std::array<Uint8, 3>, 3>, size> get_text() {
        std::array<std::array<std::array<Uint8, 3>, 3>, size> first_line  = get_1st_line();
        std::array<std::array<std::array<Uint8, 3>, 3>, size> second_line = get_2st_line();
        std::array<std::array<std::array<Uint8, 3>, 3>, size> third_line  = get_3st_line();
        std::array<std::array<std::array<Uint8, 3>, 3>, size> fourth_line = get_4st_line();
        
    }
};



