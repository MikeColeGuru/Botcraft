#include "protocolCraft/Types/Particles/NoDataTypedParticle.hpp"

namespace ProtocolCraft
{
#if PROTOCOL_VERSION > 392
    const std::vector<std::string> NoDataTypedParticle::names = {
        "ambient_entity_effect",
        "angry_villager",
#if PROTOCOL_VERSION < 757
        "barrier",
#endif
#if PROTOCOL_VERSION > 754 && PROTOCOL_VERSION < 757
        "light",
#endif
        "block",
#if PROTOCOL_VERSION > 756
        "block_marker",
#endif
        "bubble",
        "cloud",
        "crit",
        "damage_indicator",
        "dragon_breath",
        "dripping_lava",
#if PROTOCOL_VERSION > 476
        "falling_lava",
        "landing_lava",
#endif
        "dripping_water",
#if PROTOCOL_VERSION > 476
        "falling_water",
#endif
        "dust",
#if PROTOCOL_VERSION > 754
        "dust_color_transition",
#endif
        "effect",
        "elder_guardian",
        "enchanted_hit",
        "enchant",
        "end_rod",
        "entity_effect",
        "explosion_emitter",
        "explosion",
#if PROTOCOL_VERSION > 758
        "sonic_boom",
#endif
        "falling_dust",
        "firework",
        "fishing",
        "flame",
#if PROTOCOL_VERSION > 761
        "dripping_cherry_leaves",
        "falling_cherry_leaves",
        "landing_cherry_leaves",
#endif
#if PROTOCOL_VERSION > 758
        "sculk_soul",
        "sculk_charge",
        "sculk_charge_pop",
#endif
#if PROTOCOL_VERSION > 734
        "soul_fire_flame",
        "soul",
#endif
#if PROTOCOL_VERSION > 476
        "flash",
#endif
        "happy_villager",
#if PROTOCOL_VERSION > 476
        "composter",
#endif
        "heart",
        "instant_effect",
        "item",
#if PROTOCOL_VERSION > 754
        "vibration",
#endif
        "item_slime",
        "item_snowball",
        "large_smoke",
        "lava",
        "mycelium",
        "note",
        "poof",
        "portal",
        "rain",
        "smoke",
#if PROTOCOL_VERSION > 476
        "sneeze",
#endif
        "spit",
        "squid_ink",
        "sweep_attack",
        "totem_of_undying",
        "underwater",
        "splash",
        "witch",
        "bubble_pop",
        "current_down",
        "bubble_column_up",
        "nautilus",
        "dolphin",
#if PROTOCOL_VERSION > 476
        "campfire_cosy_smoke",
        "campfire_signal_smoke",
#endif
#if PROTOCOL_VERSION > 572
        "dripping_honey",
        "falling_honey",
        "landing_honey",
        "falling_nectar",
#endif
#if PROTOCOL_VERSION > 754
        "falling_spore_blossom",
#endif
#if PROTOCOL_VERSION > 734
        "ash",
        "crimson_spore",
        "warped_spore",
#endif
#if PROTOCOL_VERSION > 754
        "spore_blossom_air",
#endif
#if PROTOCOL_VERSION > 734
        "dripping_obsidian_tear",
        "falling_obsidian_tear",
        "landing_obsidian_tear",
        "reverse_portal",
        "white_ash",
#endif
#if PROTOCOL_VERSION > 754
        "small_flame",
        "snowflake",
        "dripping_dripstone_lava",
        "falling_dripstone_lava",
        "dripping_dripstone_water",
        "falling_dripstone_water",
        "glow_squid_ink",
        "glow",
        "wax_on",
        "wax_off",
        "electric_spark",
        "scrape",
#endif
#if PROTOCOL_VERSION > 758
        "shriek",
#endif
    };
#else
    const std::vector<std::string> NoDataTypedParticle::names = {
        "explode",
        "largeexplode",
        "hugeexplosion",
        "fireworksSpark",
        "bubble",
        "splash",
        "wake",
        "suspended",
        "depthsuspend",
        "crit",
        "magicCrit",
        "smoke",
        "largesmoke",
        "spell",
        "instantSpell",
        "mobSpell",
        "mobSpellAmbient",
        "witchMagic",
        "dripWater",
        "dripLava",
        "angryVillager",
        "happyVillager",
        "townaura",
        "note",
        "portal",
        "enchantmenttable",
        "flame",
        "lava",
        "footstep",
        "cloud",
        "reddust",
        "snowballpoof",
        "snowshovel",
        "slime",
        "heart",
        "barrier",
        "iconcrack",
        "blockcrack",
        "blockdust",
        "droplet",
        "take",
        "mobappearance",
        "dragonbreath",
        "endRod",
        "damageIndicator",
        "sweepAttack",
        "fallingdust",
        "totem",
        "spit",
    };
#endif

    NoDataTypedParticle::NoDataTypedParticle(const ParticleType type_)
    {
        type = type_;
    }

    NoDataTypedParticle::~NoDataTypedParticle()
    {

    }

    std::string NoDataTypedParticle::GetName() const
    {
        return names[static_cast<int>(type)];
    }

    ParticleType NoDataTypedParticle::GetType() const
    {
        return type;
    }

    void NoDataTypedParticle::ReadImpl(ReadIterator& iter, size_t& length)
    {

    }

    void NoDataTypedParticle::WriteImpl(WriteContainer& container) const
    {

    }

    Json::Value NoDataTypedParticle::SerializeImpl() const
    {
        return Json::Value();
    }
}