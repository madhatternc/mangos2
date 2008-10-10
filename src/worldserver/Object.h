/**
 *     \file  src/worldserver/Object.h
 *    \brief  Provides a basic object definition.
 *
 * Copyright (C) 2005 Team OpenWoW <http://openwow.quamquam.org/>
 * Copyright (C) 2008 MaNGOS foundation <http://www.getmangos.com/>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "Base.h"
#include "BitVector.h"
#include "UpdateFields.h"
#include "ObjectVector.h"
#include "StringFun.h"

/**
 * The upper 32 bits of the GUID seems to be some bitmask.
 * Alas, we don't know what exactly they are, so we'll use them as const values ...
 */
enum
{
    /// Player characters
    HIGHGUID_PLAYER        = 0x00000000,
    /// Items, containers
    HIGHGUID_THING         = 0x40000000,
    /// Non-Player-Character (NPC)
    HIGHGUID_UNIT          = 0xF0001000,
    /// Game objects
    HIGHGUID_GAMEOBJECT    = 0xF0007000,
    /// A dynamic object
    HIGHGUID_DYNAMICOBJECT = 0xF000A000,
};

#define MAKEGUID(h,l)   ((uint64 (h) << 32) | l)            //tolua_hide

/**
 * Object type mask bits.
 * A object can have multiple times at once, this is expressed as
 * setting several bits at once.
 *
 * This is used in the OBJECT_FIELD_TYPE field of the object.
 */
enum
{
    TYPE_OBJECT        = (1 << 0),
    TYPE_ITEM          = (1 << 1),
    TYPE_CONTAINER     = (1 << 2),
    TYPE_UNIT          = (1 << 3),
    TYPE_PLAYER        = (1 << 4),
    TYPE_GAMEOBJECT    = (1 << 5),
    TYPE_DYNAMICOBJECT = (1 << 6),
    TYPE_CORPSE        = (1 << 7),
    TYPE_AIGROUP       = (1 << 8),
    TYPE_AREATRIGGER   = (1 << 9)
};

/**
 * This structure describes the subblocks of the SMSG_UPDATE_OBJECT (aka 0xa9)
 * and SMSG_COMPRESSED_UPDATE_OBJECT packets. A single 0xa9 packet can have
 * multiple UPDATE_xxx subblocks.
 */
enum
{
    /**
     * Followed by:
     * - 8 bytes: GUID
     * - [Field Update subblock]
     */
    UPDATE_VALUES = 0,

    /**
     * Followed by:
     * - 8 bytes: GUID
     * - [Position Update subblock]
     */
    UPDATE_MOVEMENT = 1,

    /**
     * Followed by:
     * - 8 bytes: GUID
     * - 1 byte: Object Type
     * - [Position Update subblock]
     * - [Field Update subblock]
     */
    UPDATE_CREATE_OBJECT = 2,

    /**
     * Followed by:
     * - 4 bytes: Count
     * - Count * 8 bytes: GUIDs
     */
    UPDATE_OUT_OF_RANGE_OBJECTS = 3,

    /**
     * Followed by:
     * - 4 bytes - Count
     * - Count * 8 bytes: GUIDs
     * looks like 3 & 4 do the same thing
     */
    UPDATE_NEAR_OBJECTS = 4
};

class Database;
class GameClient;
class NetworkPacket;
class ObjectVector;
class NetworkPacket;

/**
 * Base class for every item, unit, player, corpse, container, etc
 */
class Object : public Base
{
    protected:
        friend class WorldServer;
        friend class ObjectMgr;
        friend class QuadTree;

        /// Walk speed
        float WalkSpeed;
        /// Run speed
        float RunSpeed;
        /// Speed when walking backwards
        float BackWalkSpeed;
        /// Swim speed
        float SwimSpeed;
        /// Speed when swimming backwards
        float BackSwimSpeed;
        /// The turn rate, radians/second
        float TurnRate;

        /**
         * Any object has an array of 32-bit values (which are interpreted as different
         * types - 32-bit integers, 8-bit integers, 32-bit floats etc depending on the
         * respective field meaning). This array has different length depending of
         * object type. The indices of the values are listed in UpdateFields.h
         *
         * Initially this object has a length of zero elements. The classes derived
         * from Object must set it to a certain length in their constructors.
         */
        class ObjectFields
        {
            uint32 *data;
            uint length;

            public:
                /**
                 * This bit vector will hold '1' in positions where vector elements
                 * were changed. It has the same length as the vector.
                 */
                BitVector Changes;
                /**
                 * Initially 0 (set by ClearChanges), this field will be updated
                 * to hold the highest modified field index plus one.
                 */
                uint HighestChange;

                ObjectFields () : data (NULL), length (0), HighestChange (0) {}
                ~ObjectFields () { free (data); }

                /**
                 * Encode the whole fields array into a minimal-overhead text string that
                 * can be stored into the SQL database.
                 * @arg oData
                 *   Pointer to output buffer or NULL to get the size required to hold
                 *   the result. The buffer is assumed to have enough space.
                 * @return
                 *   Number of bytes in the result, or number of bytes required to hold
                 *   the result (if oData == NULL).
                 */
                size_t EncodeSQL (void *oData)
                    { return ::EncodeSQL (data, length * sizeof (uint32), oData); }

                /**
                 * A simpler (but not always effective) version of EncodeSQL() that allocates
                 * and returns the encoded string directly
                 * @return
                 *   A string that should be freed with delete []
                 */
                char *EncodeSQL ()
                    { return ::EncodeSQL (data, length * sizeof (uint32)); }

                /**
                 * Decode the whole fields array from a text string that has been read from
                 * the SQL database.
                 * @arg iSqlStr
                 *   The SQL encoded string
                 * @return
                 *   true if there was enough data for the fields, false if not
                 */
                bool DecodeSQL (const char *iSqlStr)
                    { return ::DecodeSQL (iSqlStr, data, length * sizeof (uint32)) == length * sizeof (uint32); }

                /// Clear the changes array
                void ClearChanges ()
                {
                    Changes.Clear ();
                    HighestChange = 0;
                }

                /// Set vector length
                void SetLength (uint n);

                /// Get vector length in elements
                uint Length ()
                    { return length; }

                /// Get a uint32 value from the vector
                uint32 GetU32 (uint iIndex) const
                {
                    DEBUG_BREAK_IF (iIndex >= length);
                    return data [iIndex];
                }
                /// Get a uint64 value from the vector
                uint64 GetU64 (uint iIndex) const
                    { return uint64 (GetU32 (iIndex)) | (uint64 (GetU32 (iIndex + 1)) << 32); }
                /// Get a float32 value from the vector
                float GetF32 (uint iIndex) const
                {
                    DEBUG_BREAK_IF (iIndex >= length);
                    return *(float *)(data + iIndex);
                }

                /// Set a uint32 value in the vector and update the changemask
                void SetU32 (uint iIndex, uint32 iValue);
                /// Set a uint64 value in the vector and update the changemask
                void SetU64 (uint iIndex, uint64 iValue)
                    { SetU32 (iIndex, iValue & 0xffffffff); SetU32 (iIndex + 1, iValue >> 32);  }
                /// Set a float value in the vector and update the changemask
                void SetF32 (uint iIndex, float iValue)
                    { SetU32 (iIndex, *(uint32 *)&iValue); }

                /**
                 * Set/reset bitflags. This method can be used to set or clear
                 * an arbitrary number of bitflags at once. The mask defines
                 * which bits are touched, and the value defines to which state
                 * these bits will be set. For example, SetBits (0xffffffff, 0)
                 * will reset all bits to 0, while SetBits (0xff, 0x0f) will set
                 * the lower 4 bits of the flags to 1, next 4 bits to 0 and the
                 * rest will remain untouched.
                 * @arg iIndex
                 *   Field index
                 * @arg iMask
                 *   The mask of bits to be modified
                 * @arg iValue
                 *   The value of the bits given by Mask
                 */
                void SetBits (uint iIndex, uint32 iMask, uint32 iValue)
                    { SetU32 (iIndex, (GetU32 (iIndex) & ~iMask) | (iValue & iMask)); }

                /// Clear a range of fields with zeros
                void Clear (uint iIndex, uint iCount)
                {
                    // Use SetUInt32 instead of memset to update HighestChange
                    for (uint i = iCount; i; i--)
                        SetU32 (iIndex++, 0);
                }
        } Field;

        // Private field for internal use by QuadTree
        struct
        {
            void *Node;
            bool Bounding;
        } QTreeData;

    public:
        /// The zone we're currently in
        uint32 ZoneId;
        /// The map we're currently on
        uint32 MapId;
        /// True if this object is in the game world
        bool IsInWorld;

        /// Object position in the world
        float PositionX, PositionY, PositionZ;
        /// Object orientation angle, radians
        float Orientation;

        /// Object radius
        float Radius;

        /// Set of Objects receiving updates from this object
        ObjectVector ObjectsInRange;

        /// Create this object
        Object ();
        /// Destroy the object
        virtual ~Object ();

        /**
         * This function is called on every object at every frame.
         * It is meant to update time-dependent object parameters.
         */
        virtual void Update (uint32 iDeltaMs);

        /**
         * Get the serial number of this object (lower 32 bits of the GUID).
         */
        inline uint32 GetLowGUID () const
            { return Field.GetU32 (OBJECT_FIELD_GUID); }

        /**
         * Get the upper 32 bits of the GUID for this object
         */
        inline uint32 GetHighGUID () const
            { return Field.GetU32 (OBJECT_FIELD_GUID + 1); }

        /**
         * Get the GUID as a whole
         */
        inline uint64 GetGUID () const
            { return Field.GetU64 (OBJECT_FIELD_GUID); }

        /**
         * Get the object type
         */
        inline uint8 GetType () const
            { return Field.GetU32 (OBJECT_FIELD_TYPE); }

        /**
         * Create and send to given client a partial update SMSG_UPDATE_OBJECT
         * packet with just the changes that were done to this object since last checkpoint.
         */
        //void UpdateObject (GameClient *client = NULL);

        /**
         * Create and send to given client a full SMSG_UPDATE_OBJECT
         * with all fields.
         */
        //void CreateObject (uint32 flags, GameClient *client = NULL);

        /**
         *
         *
         */
        //virtual void UpdateObject (UpdateMask* updateMask, NetworkPacket * p_data);
        //virtual void UpdateMovement (uint32 flags, NetworkPacket * p_data);
        //virtual void CreateObject (UpdateMask* updateMask, NetworkPacket * p_data, uint32 flags);

        // These functions construct a specific block of a specific A9 packet
        //virtual void BuildMoveUpdate (uint32 flags, uint32 flags2, uint8 * data, int* length);
        //virtual void BuildUpdateBlock(UpdateMask *updateMask, uint8 * data, int* length);

        /**
         * Create a new packet that notifies a client about all fields
         * of this object, ready to be sent.
         */
        virtual NetworkPacket *BuildCreatePacket () const;

        /**
         * Build a packet that notifies the client that this object does
         * not longer exist for him.
         */
        virtual NetworkPacket *BuildDestroyPacket () const;

        //void BuildHeartBeat (NetworkPacket *data);
        //void TeleportAck (NetworkPacket *data, float x, float y, float z);

        /**
         * Change object position to given values.
         * This will instantly teleport the object to the given location.
         */
        void SetPosition (float x, float y, float z, float o)
            { PositionX = x; PositionY = y; PositionZ = z; Orientation = o; }
        /**
         * Make the object walk to given position
         */
        bool MoveTo (float x, float y, float z, float o);

        /**
         * Get the distance squared between this object and some other object.
         */
        inline float GetDistanceSq (Object *Obj) const
        {
            return Square <float> (Obj->PositionX - PositionX) +
                Square <float> (Obj->PositionY - PositionY) +
                Square <float> (Obj->PositionZ - PositionZ);
        };

        //---------- In Range Object management ----------//

        /// Check if a object is already in the in-range list
        bool IsInRangeSet (Object *Obj)
        {
            uint64 guid = Obj->GetGUID ();
            return ObjectsInRange.FindSortedKey (&guid, OVSORT_GUID) >= 0;
        }

        /// Add a object to the in-range list
        void AddInRangeObject (Object *Obj)
            { ObjectsInRange.InsertSorted (Obj, NULL, OVSORT_GUID); }

        /// Remove a object from the in-range list
        virtual void RemoveInRangeObject (Object *Obj)
        {
            uint64 guid = Obj->GetGUID ();
            int idx = ObjectsInRange.FindSortedKey (&guid, OVSORT_GUID);
            if (idx >= 0)
                ObjectsInRange.Delete (idx);
        }

        /// Clear all the objects from the in-range list
        void ClearInRangeSet ()
            { ObjectsInRange.DeleteAll (); }

        /**
         * Send a protocol packet to all the objects in range.
         * @arg packet
         *   The packet to send
         * @arg self
         *   true if the packet also should be sent to this object.
         *   This works only if the type of the object is PLAYER.
         */
        void SendToSet (NetworkPacket *packet, bool self);

        //----------------// Object saving & loading //----------------//

        /// Save this object to database
        virtual bool SaveToDB () = 0;
        /// Delete this object from database
        virtual bool DeleteFromDB () = 0;
};
#endif                                                      // __OBJECT_H__
