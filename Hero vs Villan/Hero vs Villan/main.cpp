/* Name: Adrian Marshall		Class: System Software , MW 2:30pm
   Class based mini RPG

	*/
    #include <iostream>
    #include <string>
    #include <cstdlib>
    #include <ctime>
    #include <windows.h>

    using namespace std;


    class Hero
    {
       friend class Villan;

       friend void PickLimb(Hero &Good);
       friend void PickLimb(Villan &Evil);
       friend void Attack(Hero &Attacker, Villan *Defender);      // Function used to Attack
       friend void Attack(Villan *Attacker, Hero &Defender);
       friend bool Dodge(Hero &hero);      // Function used to Dodge( There's a chance you may not dodge the attack)
       friend bool Dodge(Villan *villan);
       friend int TellStory(Hero &Human,Villan &Monster,Villan &Creature);
    public:

       Hero( string name,unsigned int life_points = 100, string cphrase = " ",unsigned int exp = 150,unsigned int Agility = 5);

       void Heroic_intro(Villan *evil,Hero &Me);
       bool IsDead();
       void CheckInventory();   // Check hero's inventory

       int Hero_attacked;
       int Hero_dodged;
       int Hero_missed;

       unsigned int m_Hp;         // Heros health points
       unsigned int m_exp;   // Hero's experince points
       unsigned int m_Agility;

       string m_Name;      // Heros name
       string m_Phrase;   // Hero's catch phrase

       enum Weapons{ FIST = 3,HAMMER = 5, AXE = 10, MAGIC_SWORD = 15 , PHOTON_RAY = 20};   // Weapons the hero can use
       enum Body_Parts{ LEG = 3, ARM = 6, BODY = 10, HEAD = 16};   // Hero's body parts
        Weapons Myweap;      // current weapon
       Body_Parts Mypart;   //body part

    };

    class Villan
    {
       friend class Hero;
       friend void PickLimb(Hero &Good);
       friend void PickLimb(Villan &Evil);
       friend void Attack(Hero &Attacker, Villan *Defender);      // Function used to Attack
       friend void Attack(Villan *Attacker, Hero &Defender);
       friend bool Dodge(Hero &hero);      // Function used to Dodge( There's a chance you may not dodge the attack)
       friend bool Dodge(Villan *villan);
       friend int TellStory(Hero &Human,Villan &Monster, Villan &Creature);
    public:
       Villan(string name,unsigned int life_points = 100, string phrase = " ",unsigned int Agility = 2);

       void Evil_intro(Hero &super,Villan *Me);
       bool IsDead();
       void PickAb();

       int Villan_attacked;
       int Villan_dodged;
       int Villan_missed;

       unsigned int m_Hp;         // Villans health points
       unsigned int m_Agility;
       string m_Name;      //Villans name
       string m_phrase;   // Villans evil phrase

       enum Abilities{ BITE = 4, CUT = 15, PUNCH = 25, THROW = 35};         // Monster Abilities
       enum Body_Parts{ LEG = 4, TENTACLE = 7, BODY = 10, WINGS = 18};      // Monsters body parts
       Abilities Myab;
       Body_Parts Mypart;


    };

    Hero::Hero( string name,unsigned int life_points, string cphrase,unsigned int exp,unsigned int Agility):
    m_Hp(life_points), m_Phrase(cphrase),m_exp(exp),m_Agility(Agility)
    {
       string add = "Captain ";
       m_Name = add + name ;
       Myweap = FIST;
    }
    Villan::Villan(string name,unsigned int life_points, string phrase,unsigned int Agility):
    m_Name(name), m_Hp(life_points), m_phrase(phrase),m_Agility(Agility)
    {}



    // functions
    int Introduction();
    void PlayAgain();
    int TellStory(Hero &Human, Villan &Monster,Villan &Creature);
    void Report(Hero &hero,Villan *villan);

    void Attack(Hero &Attacker, Villan *Defender);
    void Attack(Villan *Attacker, Hero *Defender);
    bool Dodge(Hero &hero);
    bool Dodge(Villan *villan);
    void PickLimb( Hero &Good);
    void PickLimb(Villan *Evil);
    int Hp_level = 100;

    int main()
    {   
       system("cls");

       srand(time(0));

       string n;
       int door;
       

       Hp_level = Introduction();
       
       
       cout << " what is you name ? : ";
       cin >> n;

       Hero Superman(n,Hp_level," I_won't_loose",150,5);
       Villan Molerat("Dr.Rat",Hp_level,"You_will_be_ripped_to_Shreds!!!",1);
       Villan Bigbird("TeraEagle",Hp_level,"I'll_get_you!",3);
       Villan *Evil_monster = 0;

       door = TellStory(Superman,Molerat,Bigbird);

       if(door == 1)
          Evil_monster = &Molerat;      // If user selects door 1, he will fight "Molerat"
       else
          if(door == 2)
             Evil_monster = &Bigbird;      // If user selects door 2, he will fight "Bigbird"

       Superman.Hero_attacked = 0;
       Superman.Hero_dodged = 0;
       Superman.Hero_missed = 0;
       Evil_monster->Villan_attacked = 0;
       Evil_monster->Villan_dodged = 0;
       Evil_monster->Villan_missed = 0;


       cout << " Okay, so you have decided to enter door number " << door << ". Good Luck! \n\n";

       for(string load = "|"; load.size() < 13; )      // a little text loading bar I thought of
       {
          cout << load;
          Sleep(1000);
          load += "|";
       }

       Evil_monster->Evil_intro(Superman,Evil_monster);
       Sleep(5000);
       Superman.Heroic_intro(Evil_monster,Superman);

       while((!Evil_monster->IsDead()) && (!Superman.IsDead()) )
       {
          system("cls");

          int choice = 0;

          cout << Superman.m_Name << " Health points: " << Superman.m_Hp;
          cout << " \tCurrent Weapon: ";

          switch(Superman.Myweap)
          {
		  case 3:
			  cout << "Fist";
			  break;
          case 5:
             cout << "Hammer";
             break;
          case 10:
             cout << "Axe";
             break;
          case 15:
             cout << "Magic Sword";
             break;
          case 20:
             cout << "Photon Ray";
             break;
          default:
             cout << "Fist";
          }
          cout << "\n EXP: " << Superman.m_exp;
          cout << " \t\t Agility: " << Superman.m_Agility << "\n\n";

          cout << Evil_monster->m_Name << " Health Points: " << Evil_monster->m_Hp;

          cout << "\n\n\t\t What do you want to do:  \n\n";
          cout << "1.) Go into inventory \n";
          cout << "2.) Attack!!! \n";
          cout << "3.)Attempt to Dodge enemy's attack \n\n\t\t";
          cout << " Please Select your choice: ";
          cin >> choice;

          switch(choice)
          {
          case 1:
             Superman.CheckInventory();
             break;
          case 2:
             {
             Attack(Superman,Evil_monster);

             if(Evil_monster->m_Hp == 0)
                break;
             else
             Attack(Evil_monster,Superman);
             break;
             }
          case 3:
             {
             Superman.m_Agility += 3;
             Attack(Evil_monster,Superman);
             break;
             }
          default:
             cout << "\n You've entered an invalid choice. \n";
          }

          if(Superman.m_Hp < 50)
          {
             cout << "\n\t Your energy is fading away. You'll parish soon \n";
             system("pause");
          }
          else
             if(Evil_monster->m_Hp < 50)
             {
                cout << " Your almost done. Just give up \n";
                cout << Evil_monster->m_Name << ": Never!!!! \n\n";
                system("pause");
             }
       }

       if(Superman.m_Hp == 0)
       {
          system("cls");
          cout << Evil_monster->m_Name << ": You have failed to save your princess. \n";
          cout << " Maybe you'll see here in the after-life. Hahahahahaha.\n\n";

          cout << "\n  *           *       ||            **********        ********           ||============ ";
          cout << "\n  *           *       ||           *          *      *         *         ||             ";
          cout << "\n  *           *       ||          *           *        *                 ||             ";
          cout << "\n  *           *       ||          *           *          *               ||             ";
          cout << "\n  *           *       ||          *           *            *             ||============ ";
          cout << "\n   *         *        ||           *         *     *          *          ||             ";
          cout << " \n   *********         =======       * * *****       *        *           ||             ";
          cout << "\n                                                     ********            ||============ ";
          cout << " \n                                                                                       ";
       }
       else
          if(Evil_monster->m_Hp == 0)
          {
             system("cls");
             cout << " Ahhhhhhhhhhhhhh....... \n";
             cout <<  Evil_monster->m_Name << " : You have defeated me. You are the first. You are very lu..lu..luck....lucky \n";
             cout << " You have defeated the villan. The princess is now saved and gives much thanks to you. \n\n";

             
          cout << "  *           *       ||      ___    ||     OO   __              || \n";
          cout << "  *           *       ||     *  *    ||     ||   || *      ||    || \n";
          cout << "  *           *       ||    *    *   ||     ||   ||  *     ||    || \n";
          cout << "  *           *       ||   *      *  ||     ||   ||   *    ||    || \n";
          cout << "  *           *       ||  *        * ||     ||   ||    *   ||    || \n";
          cout << "   *         *        || *          *||     ||   ||     *  ||    || \n";
          cout << "    *********         ||             ||     ||   ||      * ||    || \n";
           cout << "                                            ||   ||       *||    @@ \n";
          }
          system("pause");

          Report(Superman,Evil_monster);

    string response;
       cout << "\n\n\t\t Do you want to play again(yes/no) ? ";
       cin >> response;

       if(response == "yes")
          main();
       else
          cout << " Thanks for playing, Hope you enjoyed it ;)  \n\n\n\t\t\t";
       system("pause");
       return 0;
    }

    int Introduction()
    {
       int response = 1;
       cout << " Welcome players....are you ready(y/n)? ";
       Sleep(2000);
       cout << "\n rhetorical question, of course you are. \n";
       cout << " In this game you are a hero and you have to fight a monster.(very simple) \n\n";

       cout << "\n You can set the health levels you will start off with to different levels.\n";
       cout << " Please select a level: \n\n";
       cout << " 1.) 100 Health Points \n";
       cout << " 2.) 200 Health Points \n";
       cout << " 3.) 300 Health Points \n";
       cout << " 4.) 400 Health Points \n";
       cin >> response;

       switch(response)
       {
       case 1:
          response = 100;
          break;
       case 2:
          response = 200;
          break;
       case 3:
          response = 300;
          break;
       case 4:
          response = 400;
          break;
       default:
          {
          response = 100;
          cout << "\n Invalid choice \n";
          cout << " Health was automatically set to 100. \n\n";
          }
       }
       return response;
    }

    void Hero::CheckInventory()
    {
       int choice;
       cout << "\n Welcome to your inventory. Here you can buy weapons. \n";
       cout << "   This is whats in your inventory: \n\n";
       cout << " \t\t Current EXP: " << m_exp << endl;
       cout << "       Item   |   Damage Done | Cost of item \n";
       cout << "   1.) Hammer :    " << 5 << "     \t :155 exp \n";
       cout << "   2.) Axe    :    " << 10 << "    \t : 180 exp \n";
       cout << "   3.) Magic Sword: " << 15 << "    \t : 195 exp \n";
       cout << "   4.) Photon ray: " << 20 << "    \t: 210 exp \n";
       cout << " \n\t\t Please select your choice: ";
       cin >> choice;


       switch(choice)
       {
       case 1:
          {
             if(m_exp >= 155)
             {
             Myweap = HAMMER;
          cout << " \n You are now equiped with a Hammer. \n";
             }
             else
                cout << " \n You don't have enough experience points. Sorry. \n";
          break;
          }
       case 2:
          {
             if(m_exp >= 180)
             {
             Myweap = AXE;
             cout << " \n You are now equiped with an Axe. \n";
             }
             else
                cout << " \n You don't have enough experience points. Sorry. \n";
             break;
          }
       case 3:
          {
             if(m_exp >= 195)
             {
             Myweap = MAGIC_SWORD;
             cout << " \n You are now equiped with a Magic Sword. \n";
             }
             else
                cout << " \n You don't have enough experience points. Sorry. \n";
             break;
          }
       case 4:
          {
             if(m_exp >= 210)
             {
             Myweap = PHOTON_RAY;
             cout << " \n You are now equiped with a Photon Ray. \n";
             }
             else
                cout << " \n You don't have enough experience points. Sorry. \n";
             break;
          }
       default:
          cout << " \n\t You have entered an invalid choice. \n";
       }
       system("pause");
    }
    bool Hero::IsDead()
    {
       if(m_Hp == 0)
          return true;
       else
          return false;
    }

    bool Villan::IsDead()
    {
       if(m_Hp == 0)
          return true;
       else
          return false;
    }

    void PickLimb(Hero &Good)
    {
       int limb = rand() % 4 + 1;

       switch(limb)
       {
       case 1:
          {
          Good.Mypart = Good.LEG;
          break;
          }
       case 2:
          {
          Good.Mypart = Good.ARM;
          break;
          }
       case 3:
          {
          Good.Mypart = Good.BODY;
          break;
          }
       case 4:
          {
          Good.Mypart = Good.HEAD;
          break;
          }
       default:
          cout << "\n A problem Occured. \n";
       }
    }
    void PickLimb(Villan *Evil)
    {
       int limb = rand() % 4 + 1;

       switch(limb)
       {
       case 1:
          {
          Evil->Mypart = Evil->LEG;
          break;
          }
       case 2:
          {
          Evil->Mypart = Evil->TENTACLE;
          break;
          }
       case 3:
          {
          Evil->Mypart = Evil->BODY;
          break;
          }
       case 4:
          {
          Evil->Mypart = Evil->WINGS;
          break;
          }
       default:
          cout << "\n A problem Occured. \n";
       }

    }
    void Villan::PickAb()
    {
       int abil = rand() % 4 + 1;

       switch(abil)
       {
       case 1:
          Myab = BITE;
          break;
       case 2:
          {
          Myab = CUT;
          break;
          }
       case 3:
          {
          Myab = PUNCH;
          break;
          }
       case 4:
          {
          Myab = THROW;
          break;
          }
       default:
          cout << "\n A problem Occured. \n";
       }

    }
    void Attack(Hero &Attacker, Villan *Defender)
    {
       bool Do_dodge = Dodge(Defender);
       PickLimb(Defender);

       string Weapon;
       string limb;

       switch(Attacker.Myweap)
       {
       case 2:
          {
             Weapon = "Fist";
             break;
          }
       case 5:
          {
             Weapon = "Hammer";
             break;
          }
       case 10:
          {
             Weapon = "Axe";
             break;
          }
       case 15:
          {
             Weapon = "Magic_Sword";
             break;
          }
       case 20:
          {
             Weapon = "Photon_Ray";
             break;
          }
	   default:
		   Weapon = "Fist";
		   break;
       }

          switch(Defender->Mypart)
       {
       case 4:
          {
             limb = "Leg";
             break;
          }
       case 7:
          {
             limb = "Tentacle";
             break;
          }
       case 10:
          {
             limb = "Body";
             break;
          }
       case 18:
          {
             limb = "Wings";
             break;
          }
       }

          cout << Attacker.m_Name << ": Take this... \n";
       
       int Damage = Attacker.Myweap * 4;
       
       if(Do_dodge == false)
       {
          Defender->m_Hp -= Damage;
          Attacker.m_exp += 5;
          Defender->Villan_attacked++;

          cout <<"\n\n" << Attacker.m_Name << " has attacked " << Defender->m_Name << " with a(n) " << Weapon << endl;
          cout << " . It Hit " << Defender->m_Name << " Directly in his " << limb << endl;
           cout << Defender->m_Name << " has taken " << Damage << " amount of damage. \n";
       }
       else
       {
          Attacker.m_Agility--;
          Defender->m_Agility += Damage - (Attacker.Myweap + 1);
          Defender->Villan_dodged++;
          Attacker.Hero_missed++;

       cout << "\n\n" << Defender->m_Name << " has dodged your attack........ \n";
       cout << Defender->m_Name << " says: you can't get me. " << Defender->m_phrase << endl;
       }

       if((Defender->m_Hp <= 0) || (Defender ->m_Hp > Hp_level))
          Defender->m_Hp = 0;

       if((Attacker.m_Agility <= 0) || (Attacker.m_Agility > 100))
          Attacker.m_Agility = 0;

       system("pause");

    }
    void Attack(Villan *Attacker, Hero &Defender)
    {
       PickLimb(Defender);
       Attacker->PickAb();
       int Damage = Attacker->Myab;
       string ability;
       string limb;

       switch(Attacker->Myab)
       {
       case 4:
          {
             ability = "Biten";
             break;
          }
       case 15:
          {
             ability = "Cut";
             break;
          }
       case 25:
          {
             ability = "Punched";
             break;
          }
       case 35:
          {
             ability = "Threw";
             break;
          }
       }

          switch(Defender.Mypart)
       {
       case 3:
          {
             limb = "Leg";
             break;
          }
       case 6:
          {
             limb = "Arm";
             break;
          }
       case 10:
          {
             limb = "Body";
             break;
          }
       case 16:
          {
             limb = "Head";
             break;
          }
       }
       bool Do_dodge = Dodge(Defender);
       PickLimb(Attacker);

       cout << "\n\t" << Attacker->m_Name << ": Take this... \n";

       if(Do_dodge == false)
       {
          Defender.m_Hp -= Damage;
          Defender.Hero_attacked++;

          cout << "\n\n" << Attacker->m_Name << " has " << ability << " you, It affected your " << limb << " mostly. \n";
           cout << Defender.m_Name << " has taken (" << Damage << ") amount of damage. \n";
       }
       else
       {
          Attacker->m_Agility--;
          Defender.m_Agility += Damage - (Attacker->Myab + 2);
          Defender.Hero_dodged++;
          Attacker->Villan_missed++;

       cout << "\n\n" << Defender.m_Name << " has dodged the attack........ \n";
       cout << Defender.m_Name << " says: you can't get me. " << Defender.m_Phrase << endl;
       }
       if((Defender.m_Hp <= 0) || (Defender.m_Hp > Hp_level))
          Defender.m_Hp = 0;

       if((Attacker->m_Agility <= 0) || (Attacker->m_Agility > 100))
          Attacker->m_Agility = 0;

       system("pause");

    }

    bool Dodge(Hero &hero)
    {
       bool Dodge = false;
       int num = rand() % 200 + 1;

       num += (num * hero.m_Agility) - num;


       if((num % 2 == 0) && (num >= 100))     // Doge if number is even
          Dodge = true;
       else
          if((num % 2 != 0) && (num < 100))    // if number is odd, don't doge
             Dodge = false;

       return Dodge;
    }
    bool Dodge(Villan *villan)
    {
       bool Dodge = false;
       int num = rand() % 300 + 1;

       num += (num * villan->m_Agility) - num;

       if((num % 2 == 0) && (num <= 100))
          Dodge = true;
       else
          if((num % 2 != 0) && (num > 200))
             Dodge = false;

       return Dodge;
    }

    void Villan::Evil_intro(Hero &super, Villan *Me)      // Evil intro conversation
    {
       system("cls");
       system("color 40");

       cout << "\n\n How dare you come into my territory " << super.m_Name << endl;
       cout << " The princess will be mine and you will never see her again.Hahahahaha \n";
       cout << " All of the other creatures you have fought are weak compared to me. \n";
       cout << " I am the truly evil monster. You will never defeat me.\n";
       cout << " I, " << Me->m_Name << ", will destroy you. \n\n\t";

       system("pause");

    }
    void Hero::Heroic_intro(Villan *evil,Hero &Me)   // Heroic intro conversation
    {
       system("cls");
       system("color 07");

       cout <<Me.m_Name <<  ":  I don't care what you say, I'm going to get her back one way or another. \n";
       cout << " Either you are going to hand her over or I'll defeat you and get her myself.\n\n";
       Sleep(4000);
       cout << " I can already tell that you aren't going to willingly hand her over. \n";
       cout << " Let it be known from that I, " << Me.m_Name << " will defeat " << evil->m_Name << endl;
       cout << " Prepare for battle you ugly beast........\n\t\t\t";
       system("pause");

    }

    int TellStory(Hero &Human, Villan &Monster,Villan &Creature)
    {
       int choice;
       string Yn;

       cout << "\n\n So you, " << Human.m_Name << ".You are a hero in a an unknown forest right now.\n";
       cout << " You have slain most of the monsters so far and now....It is time for your last battle.\n";
       cout << " There is a princess in a castle that you must save. \n";
       cout << " So you have entered a castle and there are two doors. \n";
       cout << " The first door will take you to the dungeon. \n";
       cout << " The second door will take you to the rooftop. \n";
       cout << " Which one will you take??? \n\n\t";
       Sleep(8000);
       cout << " Wait.......There is a little noise coming from both of the doors. \n";
       cout << " Do you want to go closer to hear the noise coming from the doors( y/n)";
       cin >> Yn;

       if((Yn == "y") ||(Yn == "Y") || (Yn == "yes") || (Yn == "Yes"))
       {
          cout << "\n\n" << Human.m_Name << " creeps up to the first door and hears someone whisper.. \" " << Monster.m_phrase<< " \" \n";
          cout << " \n Okay, that was kind of creepy lets go to the second door.....\n";
          cout << Human.m_Name << " creeps up to the second door and hears someone....or something whisper...\n... \" " << Creature.m_phrase << " \" \n";
       }
       else
          if((Yn == "n") || (Yn == "N") || (Yn == "no") || (Yn == "No"))
          {
          cout << "\n Alright then, lets continue. \n\n";
          }

          cout << " \n\n So, Which door do you want to take ? \n";

          cout << " 1.) First door. Leads to the dungen. \n";
          cout << " 2.) Second door. Leads to the rooftop. \n\t\t";
          cout << " type \"1\" for the first door or \"2\" for the second door: ";
          cin >> choice;

          switch(choice)
          {
          case 1:
             return 1;
             break;
          case 2:
             return 2;
             break;
          default:
             cout << " You have made an invalid choice. \n";
          }

    }

    void Report(Hero &hero,Villan *villan)
    {
       system("cls");
       system("color 10");

       string title = "**************Report*************\n\n";

       for(int i = 0; i < title.size(); ++i)
       {
       cout << title[i];
        Sleep(150);
       }

       cout << " \n" << villan->m_Name << " has attacked you " << hero.Hero_attacked << " times.";
       cout << " \n You Dodged " << villan->m_Name << "'s attacks " << hero.Hero_dodged << " times.\n";
       cout << " Your attacks missed " << villan->m_Name << " " << hero.Hero_missed << " times.\n\n\n\t\t";

       cout << " \n You attacked " <<  villan->m_Name << " " << villan->Villan_attacked << " times.";
       cout << " \n The villan dodged your attacks " << villan->Villan_dodged << " times.\n";
       cout << villan->m_Name << " missed " << hero.m_Name << " " << hero.Hero_missed << " times.\n\n\n\t\t";


    }
