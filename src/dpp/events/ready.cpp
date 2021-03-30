#include <dpp/discord.h>
#include <dpp/event.h>
#include <string>
#include <iostream>
#include <fstream>
#include <dpp/discordclient.h>
#include <dpp/discord.h>
#include <dpp/cache.h>
#include <dpp/stringops.h>
#include <spdlog/spdlog.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void ready::handle(class DiscordClient* client, json &j) {
	client->logger->info("Shard {}/{} ready!", client->shard_id, client->max_shards);
	client->sessionid = j["d"]["session_id"];
}

