#include "client_processor.h"
#include "fight.h"
#include "gamedata.h"
#include "rng.h"

#include <iostream>

using namespace nibaclient;

client_processor::client_processor() { session.state = nibashared::gamestate::prelogin; }

void client_processor::process(nibashared::message_register &req) {
    if (req.success) {
        std::cout << "success" << std::endl;
    } else {
        std::cout << "unable to register" << std::endl;
    }
}

void client_processor::process(nibashared::message_login &req) {
    if (req.success) {
        std::cout << "success" << std::endl;
        session.userid = req.id;
        session.state = nibashared::gamestate::selectchar;
        std::cout << "your characters: " << std::endl;
        for (auto &c : req.characters) {
            std::cout << c << std::endl;
        }
        session.charid = 0;
    } else {
        std::cout << "failed to login" << std::endl;
    }
}

void nibaclient::client_processor::process(nibashared::message_fight &req) {
    nibashared::rng_client rng(std::move(req.generated));
    auto [self_fightable, enemy_fightable] = nibashared::prep_fight(session.charid, req.enemyid);
    nibashared::fight fight(std::move(self_fightable), std::move(enemy_fightable));
    std::cout << fight.go(rng) << " wins" << std::endl;
}

const nibashared::sessionstate &client_processor::get_session() { return session; }