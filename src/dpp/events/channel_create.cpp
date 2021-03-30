#include <dpp/discord.h>
#include <dpp/event.h>
#include <string>
#include <iostream>
#include <fstream>
#include <dpp/discordclient.h>
#include <dpp/discord.h>
#include <dpp/cache.h>
#include <dpp/stringops.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void channel_create::handle(class DiscordClient* client, json &j) {
	json& d = j["d"];
	dpp::channel* c = new dpp::channel();
	c->fill_from_json(&d);
	dpp::get_channel_cache()->store(c);
	dpp::guild* g = dpp::find_guild(c->guild_id);
	if (g) {
		g->channels.push_back(c->id);
	}
}

