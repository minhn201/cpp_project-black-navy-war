
# Black Navy War Game

## Build/Installation

Let `$TOP_DIR` denote the directory containing this README file.  
Let `$INSTALL_DIR` denote the directory into which this software is to be installed.  

To build and install the software, use the commands:
```bash
cd $TOP_DIR
cmake -H. -Btmp_cmake -DCMAKE_INSTALL_PREFIX=$INSTALL_DIR
cmake --build tmp_cmake --clean-first --target install
```

To run a demonstration, use the command:
```bash
$INSTALL_DIR/bin/demo
```

## Description

Black Navy War is a game application based on an online flash game that simulates simple 2D battles between black and red factions. The objective for both sides is to deploy naval units to destroy each other's bases. There are different types of units, each with varying strengths and costs. The key to destroying an opponent’s base is to utilize different types of units to work together strategically. The application is simplified, with units' graphic designs made of simple rectangular shapes that engage without exchanging bullets when within range.

## Units

- **Patrol Boat:** Engages other surface ships and airborne units using machine guns. Vulnerable to submarine attacks. It is weak, nimble, and cheap to deploy.
- **Destroyer:** Engages other surface ships and airborne units using machine guns, and uses depth charges against submarines.
- **Submarine:** Equipped with torpedoes to engage surface ships and other submarines. Vulnerable to air attacks.
- **Bomber:** Engages surface ships and airborne units using torpedoes. It has no anti-air capability.
- **Helicopter:** Engages surface ships and aircraft using machine guns, and uses depth charges against submarines.

## Upgrades

- **Supply Line:** Increases the rate of supply added to resources available during the game.
- **Repair Equipment:** Increases the rate of base repairs after damage.
- **Resource Warehouse:** Increases the capacity to store resources.
- **Enhance Vitality:** Increases the base health capacity.

## Software Use

- Use the left/right arrow keys to move across the battlefield. It is not recommended to resize the application window.
- Select the unit you want to purchase by clicking on the respective button in the left column of the GUI at the bottom of the game. You can also use the keys `1, 2, 3, 4, 5` to purchase a patrol boat, destroyer, submarine, bomber, and helicopter respectively.
- Choose the upgrades you want to make for the base and war economy by selecting the button options in the right column of the GUI. You can only upgrade up to three times to prevent exceeding the maximum upgrade cost. You can also use the keys `Z, X, C, and V` to upgrade the supply line, repair equipment, resource warehouse, and enhance vitality respectively.
- The amount of resources available is displayed at the top of the right column where the upgrade options are. Each unit purchase or upgrade will subtract the cost from the resources, which are constantly increased at a steady rate until reaching the full resource capacity.
