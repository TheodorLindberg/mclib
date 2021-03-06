#ifndef MCLIB_BLOCK_SHULKERBOX_H_
#define MCLIB_BLOCK_SHULKERBOX_H_

#include <mclib/common/Nameable.h>
#include <mclib/block/BlockEntity.h>
#include <mclib/block/InventoryBlock.h>

#include <unordered_map>

namespace mc {
namespace block {

class ShulkerBox : public BlockEntity, public InventoryBlock, public Nameable {
public:
    MCLIB_API ShulkerBox(BlockEntityType type, Vector3i position) : BlockEntity(type, position) { }
    MCLIB_API bool ImportNBT(nbt::NBT* nbt);
};

} // ns block
} // ns mc

#endif
