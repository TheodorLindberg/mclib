#ifndef ENTITY_MANAGER_H_
#define ENTITY_MANAGER_H_

#include "Entity.h"
#include "Player.h"
#include "../Packets/Packet.h"
#include "../Packets/PacketHandler.h"
#include "../ObserverSubject.h"
#include <array>

namespace Minecraft {

class EntityListener {
public:
    virtual ~EntityListener() { }

    virtual void OnPlayerSpawn(PlayerEntityPtr entity, Minecraft::UUID uuid) { }
    virtual void OnEntitySpawn(EntityPtr entity) { }
    virtual void OnEntityDestroy(EntityPtr entity) { }
    virtual void OnEntityMove(EntityPtr entity, Vector3d oldPos, Vector3d newPos) { }
};

class EntityManager : public Packets::PacketHandler, public ObserverSubject<EntityListener> {
private:
    std::map<EntityId, EntityPtr> m_Entities;
    // Entity Id for the client player
    EntityId m_EntityId;

public:
    EntityManager(Packets::PacketDispatcher* dispatcher);
    ~EntityManager();

    PlayerEntityPtr GetPlayerEntity() const { return std::dynamic_pointer_cast<PlayerEntity>(m_Entities.at(m_EntityId)); }

    EntityPtr GetEntity(EntityId eid) const { return m_Entities.at(eid); }

    void HandlePacket(Packets::Inbound::JoinGamePacket* packet);
    void HandlePacket(Packets::Inbound::PlayerPositionAndLookPacket* packet);
    void HandlePacket(Packets::Inbound::SpawnPlayerPacket* packet);
    void HandlePacket(Packets::Inbound::SpawnMobPacket* packet);
    void HandlePacket(Packets::Inbound::EntityPacket* packet);
    void HandlePacket(Packets::Inbound::EntityRelativeMovePacket* packet);
    void HandlePacket(Packets::Inbound::EntityLookAndRelativeMovePacket* packet);
    void HandlePacket(Packets::Inbound::EntityTeleportPacket* packet);
    void HandlePacket(Packets::Inbound::EntityHeadLookPacket* packet);
    void HandlePacket(Packets::Inbound::EntityMetadataPacket* packet);
    void HandlePacket(Packets::Inbound::EntityPropertiesPacket* packet);
    void HandlePacket(Packets::Inbound::DestroyEntitiesPacket* packet);
};

} // ns Minecraft

#endif