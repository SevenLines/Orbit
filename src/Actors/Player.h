//
// Created by mk on 18.01.16.
//

#ifndef ORBIT2_PLAYER_H
#define ORBIT2_PLAYER_H


#include "Rocket.h"
#include "Way.h"

class Player : public Rocket {

public:
    Player(Resources &resources);
    spTextField edtInfo;
protected:
    virtual void doUpdate(const UpdateState &us) override;

public:
    virtual void toggleLanded(bool is_landed) override;

    spWay playerWay;
};
typedef oxygine::intrusive_ptr<Player> spPlayer;

#endif //ORBIT2_PLAYER_H
