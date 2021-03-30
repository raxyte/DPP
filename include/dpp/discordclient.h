#pragma once
#include <string>
#include <map>
#include <vector>
#include <variant>
#include <spdlog/fwd.h>
#include <nlohmann/json.hpp>
#include <dpp/wsclient.h>

using json = nlohmann::json;

/* Implements a discord client. Each DiscordClient connects to one shard and derives from a websocket client. */
class DiscordClient : public WSClient
{
public:
	/* Heartbeat interval for sending heartbeat keepalive */
	uint32_t heartbeat_interval;

	/* Last heartbeat */
	time_t last_heartbeat;

	/* Shard ID of this client */
	uint32_t shard_id;

	/* Total number of shards */
	uint32_t max_shards;

	/* Last sequence number received, for resumes and pings */
	uint64_t last_seq;

	/* Discord bot token */
	std::string token;

	/* Privileged gateway intents */
	uint32_t intents;

	/* Discord session id */
	std::string sessionid;

	/* Handle an event (opcode 0) */
	virtual void HandleEvent(const std::string &event, json &j);

	/* Fires every second from the underlying socket I/O loop, used for sending heartbeats */
	virtual void OneSecondTimer();

	/* Opaque logger */
	class spdlog::logger* logger;


	/* Constructor takes shard id, max shards and token */
        DiscordClient(uint32_t _shard_id, uint32_t _max_shards, const std::string &_token, uint32_t intents = 0, class spdlog::logger* _logger = nullptr);

	/* Destructor */
        virtual ~DiscordClient();

	/* Handle JSON from the websocket */
	virtual bool HandleFrame(const std::string &buffer);

	/* Handle a websocket error */
	virtual void Error(uint32_t errorcode);

	/* Start and monitor I/O loop */
	void Run();
};

