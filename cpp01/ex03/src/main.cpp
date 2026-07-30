#include "HumanA.hpp"
#include "HumanB.hpp"
#include "Weapon.hpp"

int main() {
  {
    // 正常系: HumanAはコンストラクタで武器を受け取り、常に武装している
    Weapon club = Weapon("crude spiked club");

    HumanA bob("Bob", club);
    bob.attack();
    club.setType("some other type of club");
    bob.attack();
  }

  {
    // 正常系: HumanBは後から setWeapon() で武器を設定する
    Weapon club = Weapon("crude spiked club");

    HumanB jim("Jim");
    jim.setWeapon(club);
    jim.attack();
    club.setType("some other type of club");
    jim.attack();
  }
  {
    // 異常系: HumanBが武器を所持しないまま attack() する
    HumanB jim("Jim");
    jim.attack();
  }

  return 0;
}
