#ifndef CUBICSERVER_PROTOCOL_SERIALIZATION_ADD_HPP
#define CUBICSERVER_PROTOCOL_SERIALIZATION_ADD_HPP

#include <cstdint>
#include <string>
#include <vector>

#include "addPrimaryType.hpp"
#include "protocol/ClientPackets.hpp"
#include "world_storage/DynamicStorage.hpp"
#include "world_storage/Section.hpp"

namespace protocol {
constexpr void addBlockEntity(std::vector<uint8_t> &out, const BlockEntity &data)
{
    addByte(out, data.sectionCoordinate);
    addShort(out, data.height);
    addVarInt(out, data.type);
    addNBT(out, data.data);
}

constexpr void addBlockEntities(std::vector<uint8_t> &out, const std::vector<BlockEntity> &data)
{
    addVarInt(out, data.size());
    for (auto &i : data)
        addBlockEntity(out, i);
}

constexpr void addLightArray(std::vector<uint8_t> &out, const std::vector<std::array<uint8_t, LIGHT_ARRAY_SIZE>> &data)
{
    addVarInt(out, data.size());
    for (auto &lightArray : data) {
        addVarInt(out, lightArray.size());
        for (auto light : lightArray)
            addByte(out, light);
    }
}

constexpr void addPalette(std::vector<uint8_t> &out, const world_storage::Palette &palette)
{
    auto bytePerBlock = palette.getBits();
    auto size = palette.size();

    addByte(out, bytePerBlock);
    // out.push_back(bytePerBlock);

    // No palette, default to single value palette with air
    if (size == 0) {
        addVarInt(out, 0);
        return;
    }

    // Single palette
    if (size == 1) {
        addVarInt(out, palette.data()[0]);
        return;
    }

    // Direct palette (Hard coded for now)
    // Need to be changed when we add more blocks
    if (bytePerBlock == 15)
        return;

    // Multiple palettes
    addArray<int32_t, addVarInt>(out, palette.data());
}

// https://wiki.vg/Chunk_Format#Serializing
constexpr void addChunkColumn(std::vector<uint8_t> &out, const world_storage::ChunkColumn &data)
{
    std::vector<uint8_t> chunkData;

    for (const auto &section : data.getSections()) {
        // Blocks
        addShort(chunkData, section.getBlockPalette().getTotalCount());
        addPalette(chunkData, section.getBlockPalette());
        if (section.hasBlocks())
            addArray<uint64_t, addUnsignedLong>(chunkData, section.getBlocks().data());
        else
            addVarInt(chunkData, 0);

        // Biomes
        addPalette(chunkData, section.getBiomePalette());
        if (section.hasBiomes())
            addArray<uint64_t, addUnsignedLong>(chunkData, section.getBiomes().data());
        else
            addVarInt(chunkData, 0);
    }
    // for (uint8_t sectionIdx = 0; sectionIdx < world_storage::NB_OF_SECTIONS; sectionIdx++) {
    //     auto blockSection = data.getBlocks().begin() + (sectionIdx * world_storage::SECTION_3D_SIZE);
    //     auto biomeSection = data.getBiomes().begin() + (sectionIdx * world_storage::BIOME_SECTION_3D_SIZE);
    //     addBlockSection(chunkData, blockSection);
    //     addBiomeSection(chunkData, biomeSection);
    // }

    // Add the chunk data
    addArray<uint8_t, addByte>(out, chunkData);
}
constexpr void addAttributesPropertyModifier(std::vector<uint8_t> &out, const protocol::UpdateAttributes::Property::Modifier &data)
{
    addUUID(out, data.uuid);
    addDouble(out, data.amount);
    addByte(out, (uint8_t) data.operation);
}

constexpr void addAttributesProperty(std::vector<uint8_t> &out, const protocol::UpdateAttributes::Property &data)
{
    addString(out, data.key);
    addString(out, data.value);
    addArray<protocol::UpdateAttributes::Property::Modifier, addAttributesPropertyModifier>(out, data.modifiers);
}

constexpr void addAdvancementDisplay(std::vector<uint8_t> &out, const UpdateAdvancements::AdvancementMapping::Advancement::Display &data)
{
    using Flags = UpdateAdvancements::AdvancementMapping::Advancement::Display::Flags;

    addChat(out, data.title);
    addChat(out, data.description);
    addSlot(out, data.icon);
    addVarInt(out, (uint8_t) data.frameType);
    addInt(out, (int32_t) data.flags);
    if ((int32_t) data.flags & (int32_t) Flags::hasBackgroundTexture)
        addString(out, data.backgroundTexture);
    addFloat(out, data.xCoord);
    addFloat(out, data.yCoord);
}

constexpr void addAdvancementCriteria(std::vector<uint8_t> &out, const UpdateAdvancements::AdvancementMapping::Advancement::Criteria &data)
{
    addIdentifier(out, data.key);
    // addString(out, data.value);
}

constexpr void addAdvancement(std::vector<uint8_t> &out, const UpdateAdvancements::AdvancementMapping::Advancement &data)
{
    using Criteria = UpdateAdvancements::AdvancementMapping::Advancement::Criteria;

    addBoolean(out, data.hasParent);
    if (data.hasParent)
        addString(out, data.parent);
    addBoolean(out, data.hasDisplay);
    if (data.hasDisplay)
        addAdvancementDisplay(out, data.displayData);
    addArray<Criteria, addAdvancementCriteria>(out, data.criteria);
    addArray<std::vector<std::string>, addArray<std::string, addString>>(out, data.requirements);
}

constexpr void addAdvancementMapping(std::vector<uint8_t> &out, const UpdateAdvancements::AdvancementMapping &data)
{
    addIdentifier(out, data.identifier);
    addAdvancement(out, data.advancement);
}

constexpr void addAdvancementCriterionProgress(std::vector<uint8_t> &out, const UpdateAdvancements::ProgressMapping::CriteriaMapping::CriterionProgress &data)
{
    addBoolean(out, data.achived);
    addLong(out, data.dateOfAchieving);
}

constexpr void addAdvancementCriteriaMapping(std::vector<uint8_t> &out, const UpdateAdvancements::ProgressMapping::CriteriaMapping &data)
{
    addIdentifier(out, data.identifier);
    addAdvancementCriterionProgress(out, data.criteria);
}

constexpr void addAdvancementProgressMapping(std::vector<uint8_t> &out, const UpdateAdvancements::ProgressMapping &data)
{
    using CriteriaMapping = UpdateAdvancements::ProgressMapping::CriteriaMapping;

    addIdentifier(out, data.identifier);
    addArray<CriteriaMapping, addAdvancementCriteriaMapping>(out, data.advancementProgress);
}

constexpr void addRawMessage(std::vector<uint8_t> &out, const std::pair<int32_t, std::vector<uint8_t>> &rawMessage)
{
    addVarInt(out, rawMessage.first);
    addArray<uint8_t, addByte>(out, rawMessage.second);
}

} // namespace protocol

#endif // CUBICSERVER_PROTOCOL_SERIALIZATION_ADD_HPP
