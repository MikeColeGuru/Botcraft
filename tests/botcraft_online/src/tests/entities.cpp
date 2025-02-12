#include "TestManager.hpp"
#include "MinecraftServer.hpp"
#include "Utils.hpp"

#include <botcraft/Game/Entities/EntityManager.hpp>
#include <botcraft/Game/Entities/entities/Entity.hpp>
#include <botcraft/Game/Entities/entities/monster/CreeperEntity.hpp>
#include <botcraft/Game/Inventory/InventoryManager.hpp>

#include <botcraft/AI/Tasks/EntitiesTasks.hpp>

#include <catch2/catch_test_macros.hpp>

#include <sstream>

TEST_CASE("summoning")
{
	const std::vector<std::string> types = {
		"cow",
		"horse",
		"villager",
		"witch"
	};
	std::unique_ptr<Botcraft::ManagersClient> bot = SetupTestBot();
	const Botcraft::Vector3<double> pos = Botcraft::Vector3<double>(1.5, 0, 1.5) + TestManager::GetInstance().GetCurrentOffset();

	for (const auto& t : types)
	{
		SECTION(t)
		{
			std::stringstream command;
			command
				<< "summon" << " "
				<< t << " "
				<< pos.x << " "
				<< pos.y << " "
				<< pos.z << " "
				<< "{NoAI:1b,PersistenceRequired:1b}";
			MinecraftServer::GetInstance().SendLine(command.str());
#if PROTOCOL_VERSION > 340
			MinecraftServer::GetInstance().WaitLine(".*?: Summoned new.*", 2000);
#else
			MinecraftServer::GetInstance().WaitLine(".*?: Object successfully summoned.*", 2000);
#endif
			std::shared_ptr<Botcraft::EntityManager> entity_manager = bot->GetEntityManager();
			std::shared_ptr<Botcraft::Entity> entity;
			// Wait for the entity to be registered on bot side
			REQUIRE(Botcraft::WaitForCondition([&]()
				{
					std::lock_guard<std::mutex> lock(entity_manager->GetMutex());
					for (const auto& [k, v] : entity_manager->GetEntities())
					{
						if (v->GetPosition().SqrDist(pos) < 0.2)
						{
							entity = v;
							return true;
						}
					}
					return false;
				}, 2000));
			REQUIRE(entity != nullptr);
			CHECK(entity->GetName() == t);
		}
	}
}

TEST_CASE("entity interact")
{
	std::unique_ptr<Botcraft::SimpleBehaviourClient> bot = SetupTestBot<Botcraft::SimpleBehaviourClient>();
	const std::string& botname = bot->GetNetworkManager()->GetMyName();
	const Botcraft::Vector3<double> pos = Botcraft::Vector3<double>(1.5, 0, 1.5) + TestManager::GetInstance().GetCurrentOffset();

	// Give flint and steel to bot
	MinecraftServer::GetInstance().SendLine("give " + botname + " flint_and_steel");
	MinecraftServer::GetInstance().WaitLine(".*?: (?:Given|Gave 1) \\[Flint and Steel\\](?: \\* 1)? to " + botname + ".*", 2000);
	Botcraft::WaitForCondition([&]()
		{
			std::lock_guard<std::mutex> lock(bot->GetInventoryManager()->GetMutex());
			return !bot->GetInventoryManager()->GetHotbarSelected().IsEmptySlot();
		}, 2000);

	// Wait for the entity to be registered on bot side
	std::shared_ptr<Botcraft::EntityManager> entity_manager = bot->GetEntityManager();
	std::shared_ptr<Botcraft::Entity> entity;
	REQUIRE(Botcraft::WaitForCondition([&]()
		{
			std::lock_guard<std::mutex> lock(entity_manager->GetMutex());
			for (const auto& [k, v] : entity_manager->GetEntities())
			{
				if (v->GetPosition().SqrDist(pos) < 0.2)
				{
					entity = v;
					return true;
				}
			}
			return false;
		}, 2000));
	REQUIRE(entity != nullptr);
	CHECK(entity->GetName() == "creeper");

	bot->SyncAction(Botcraft::InteractEntity, entity->GetEntityID(), Botcraft::Hand::Main, true);

	// Wait for the creeper to be ignited
	std::shared_ptr<Botcraft::CreeperEntity> creeper = std::dynamic_pointer_cast<Botcraft::CreeperEntity>(entity);
	REQUIRE(Botcraft::WaitForCondition([&]()
		{
			std::lock_guard<std::mutex> lock(entity_manager->GetMutex());
			return creeper->GetDataIsIgnited();
		}, 2000));

	// Wait for the creeper to explode
	REQUIRE(Botcraft::WaitForCondition([&]()
		{
			std::lock_guard<std::mutex> lock(entity_manager->GetMutex());
			return entity_manager->GetEntity(creeper->GetEntityID()) == nullptr;
		}, 2000));
}
