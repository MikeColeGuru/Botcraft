#include "TestManager.hpp"
#include "MinecraftServer.hpp"
#include "Utils.hpp"

#include <catch2/catch_test_macros.hpp>

#include <botcraft/AI/SimpleBehaviourClient.hpp>
#include <botcraft/AI/Tasks/BaseTasks.hpp>

#include <sstream>

TEST_CASE("say")
{
	std::unique_ptr<Botcraft::SimpleBehaviourClient> bot = SetupTestBot<Botcraft::SimpleBehaviourClient>();

	bot->SyncAction(Botcraft::Say, "Hello, world!");
	const std::string& botname = bot->GetNetworkManager()->GetMyName();

	REQUIRE_NOTHROW(MinecraftServer::GetInstance().WaitLine(".*: (?:\\[Not Secure\\] )?[[<]" + botname + "[>\\]] Hello, world!.*", 2000));
}

bool IsLitRedstoneLamp(const Botcraft::Block* block)
{
	if (block == nullptr)
	{
		return false;
	}
#if PROTOCOL_VERSION > 340
	return block->GetBlockstate()->GetName() == "minecraft:redstone_lamp" && block->GetBlockstate()->GetVariableValue("lit") == "true";
#else
	return block->GetBlockstate()->GetName() == "minecraft:lit_redstone_lamp";
#endif
}

TEST_CASE("interact")
{
	std::unique_ptr<Botcraft::SimpleBehaviourClient> bot = SetupTestBot<Botcraft::SimpleBehaviourClient>();

	const Botcraft::Position lever = TestManager::GetInstance().GetCurrentOffset() + Botcraft::Position(1, 1, 1);
	const Botcraft::Position lamp = lever - Botcraft::Position(0, 1, 0);

	bot->SyncAction(Botcraft::InteractWithBlock, lever, Botcraft::PlayerDiggingFace::Up, true);

	std::shared_ptr<Botcraft::World> world = bot->GetWorld();

	REQUIRE(Botcraft::WaitForCondition([&]()
		{
			std::lock_guard<std::mutex> lock(world->GetMutex());
			const Botcraft::Block* block = world->GetBlock(lamp);
			return IsLitRedstoneLamp(block);
		}, 2000));
}
