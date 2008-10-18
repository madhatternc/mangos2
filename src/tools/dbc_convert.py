#!/usr/bin/env python
# Converts .DBC files to .SQL format
# Copyright (C) 2005 Team OpenWoW
# Copyright (C) 2005 by rischwa, Python version by zap
# Copyright (C) 2008 MaNGOS foundation <http://getmangos.com/>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

###############################################################################
# The DBC format does not contain information about field data.
# Thus, we have to hardcode the format for known databases directly here.
# If you're trying to convert a database unknown to this converter,
# it is advised that you use the -guess option, this will output
# the database format directly in the format that can be pasted here.

known_dbc =\
{
    # Used for unknown databases
    'Unknown':
    {
        # SQL table name
        'name' : 'Unknown',
        # Field types; I-integer, F-float, S-string
        'types': [],
        # Field names; more fields use names like "F{1,2,3,...}"
        'names': []
    },
    'AnimationData':
    {
        'name' : 'AnimationData',
        'types': ['I','S','I','I','S','I','I'],
        'names': [],
    },
    'AreaPOI':
    {
        'name' : 'AreaPOI',
        'types': ['I','I','I','I','F','F','F','S','I','I','S','I','I','I','I','I','I','I','I'],
        'names': [],
    },
    'AreaTable':
    {
        'name' : 'AreaTable',
        'types': ['I','S','I','I','I','I','I','I','I','I','I','S','I','I','I','I','I','I','I','I','I'],
        'names': [],
    },
    'AreaTrigger':
    {
        'name' : 'AreaTrigger',
        'types': ['I','I','F','F','F','F','I','I','I','I'],
        'names': [],
    },
    'AttackAnimKits':
    {
        'name' : 'AttackAnimKits',
        'types': ['I','I','I','I','I'],
        'names': [],
    },
    'AttackAnimTypes':
    {
        'name' : 'AttackAnimTypes',
        'types': ['I','S'],
        'names': [],
    },
    'AuctionHouse':
    {
        'name' : 'AuctionHouse',
        'types': ['I','I','I','I','S','I','I','I','I','I','I','I','I'],
        'names': [],
    },
    'BankBagSlotPrices':
    {
        'name' : 'BankBagSlotPrices',
        'types': ['I','I'],
        'names': [],
    },
    'CameraShakes':
    {
        'name' : 'CameraShakes',
        'types': ['I','I','I','F','F','F','I','F'],
        'names': [],
    },
    'Cfg_Categories':
    {
        'name' : 'Cfg_Categories',
        'types': ['S','I','S','I','I','I','I','I','I','I','I'],
        'names': [],
    },
    'Cfg_Configs':
    {
        'name' : 'Cfg_Configs',
        'types': ['I','I','I','I'],
        'names': [],
    },
    'CharacterCreateCameras':
    {
        'name' : 'CharacterCreateCameras',
        'types': ['I','I','I','F','F','F'],
        'names': [],
    },
    'CharacterFacialHairStyles':
    {
        'name' : 'CharacterFacialHairStyles',
        'types': ['I','I','I','I','I','I','I','I','I'],
        'names': [],
    },
    'CharHairGeosets':
    {
        'name' : 'CharHairGeosets',
        'types': ['I','I','I','I','I','I'],
        'names': [],
    },
    'CharHairTextures':
    {
        'name' : 'CharHairTextures',
        'types': ['I','I','I','I','I','I','I','I'],
        'names': [],
    },
    'CharSections':
    {
        'name' : 'CharSections',
        'types': ['I','I','S','I','I','I','S','S','I','I'],
        'names': [],
    },
    'CharVariations':
    {
        'name' : 'CharVariations',
        'types': ['I','I','I','I','I','I'],
        'names': [],
    },
    'ChatChannels':
    {
        'name' : 'ChatChannels',
        'types': ['S','I','I','S','I','I','I','I','I','I','I','I','S','I','I','I','I','I','I','I','I'],
        'names': [],
    },
    'ChatProfanity':
    {
        'name' : 'ChatProfanity',
        'types': ['I','S'],
        'names': [],
    },
    'ChrClasses':
    {
        'name' : 'ChrClasses',
        'types': ['I','S','I','I','S','S','I','I','I','I','I','I','I','I','S','I'],
        'names': [],
    },
    'ChrRaces':
    {
        'name' : 'ChrRaces',
        'types': ['I','I','S','I','I','I','S','F','S','I','I','I','I','I','I','S','I','S','I','I','I','I','I','I','I','I','S','S','S'],
        'names': [],
    },
    'CinematicCamera':
    {
        'name' : 'CinematicCamera',
        'types': ['I','S','I','F','F','F','F'],
        'names': [],
    },
    'CinematicSequences':
    {
        'name' : 'CinematicSequences',
        'types': ['I','I','I','I','I','I','I','I','I','I'],
        'names': [],
    },
    'CreatureDisplayInfo':
    {
        'name' : 'CreatureDisplayInfo',
        'types': ['I','I','I','I','F','I','S','I','I','S','I','I'],
        'names': [],
    },
    'CreatureDisplayInfoExtra':
    {
        'name' : 'CreatureDisplayInfoExtra',
        'types': ['I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','S'],
        'names': [],
    },
    'CreatureFamily':
    {
        'name' : 'CreatureFamily',
        'types': ['I','I','S','F','I','I','I','I','S','I','I','I','I','I','I','I','I','S'],
        'names': [],
    },
    'CreatureModelData':
    {
        'name' : 'CreatureModelData',
        'types': ['I','I','S','S','F','S','S','F','F','F','I','I','I','I','I','F'],
        'names': [],
    },
    'CreatureSoundData':
    {
        'name' : 'CreatureSoundData',
        'types': ['I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I'],
        'names': [],
    },
    'CreatureType':
    {
        'name' : 'CreatureType',
        'types': ['I','S','I','I','I','I','I','I','I','I','I'],
        'names': [],
    },
    'DeathThudLookups':
    {
        'name' : 'DeathThudLookups',
        'types': ['I','I','I','I','I'],
        'names': [],
    },
    'DurabilityCosts':
    {
        'name' : 'DurabilityCosts',
        'types': ['I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I'],
        'names': [],
    },
    'DurabilityQuality':
    {
        'name' : 'DurabilityQuality',
        'types': ['I','F'],
        'names': [],
    },
    'Emotes':
    {
        'name' : 'Emotes',
        'types': ['I','S','I','I','I','I','I'],
        'names': [],
    },
    'EmotesTextData':
    {
        'name' : 'EmotesTextData',
        'types': ['I','S','I','I','I','I','I','I','I','I'],
        'names': [],
    },
    'EmotesText':
    {
        'name' : 'EmotesText',
        'types': ['I','S','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I'],
        'names': [],
    },
    'EnvironmentalDamage':
    {
        'name' : 'EnvironmentalDamage',
        'types': ['I','I','I'],
        'names': [],
    },
    'Exhaustion':
    {
        'name' : 'Exhaustion',
        'types': ['S','I','F','F','F','S','I','I','I','I','I','I','I','I','F'],
        'names': [],
    },
    'Faction':
    {
        'name' : 'Faction',
        'types': ['I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','S','I','I','I','I','I','I','I','I'],
        'names': [],
    },
    'FactionGroup':
    {
        'name' : 'FactionGroup',
        'types': ['S','S','S','S','I','I','I','I','I','I','I','I'],
        'names': [],
    },
    'FactionTemplate':
    {
        'name' : 'FactionTemplate',
        'types': ['I','I','I','I','I','I','I','I','I','I','I','I','I','I'],
        'names': [],
    },
    'FootprintTextures':
    {
        'name' : 'FootprintTextures',
        'types': ['I','S'],
        'names': [],
    },
    'FootstepTerrainLookup':
    {
        'name' : 'FootstepTerrainLookup',
        'types': ['I','I','I','I','I'],
        'names': [],
    },
    'GameObjectDisplayInfo':
    {
        'name' : 'GameObjectDisplayInfo',
        'types': ['I','S','I','I','I','I','I','I','I','I','I','I'],
        'names': [],
    },
    'GMTicketCategory':
    {
        'name' : 'GMTicketCategory',
        'types': ['I','S','I','I','I','I','I','I','I','I'],
        'names': [],
    },
    'GroundEffectDoodad':
    {
        'name' : 'GroundEffectDoodad',
        'types': ['I','I','S'],
        'names': [],
    },
    'GroundEffectTexture':
    {
        'name' : 'GroundEffectTexture',
        'types': ['I','I','S','I','S','I','I','I','I','I','I'],
        'names': [],
    },
    'HelmetGeosetVisData':
    {
        'name' : 'HelmetGeosetVisData',
        'types': ['I','I','I','I','I','I'],
        'names': [],
    },
    'ItemClass':
    {
        'name' : 'ItemClass',
        'types': ['I','I','I','S','I','I','I','I','I','I','I','I'],
        'names': [],
    },
    'ItemDisplayInfo':
    {
        'name' : 'ItemDisplayInfo',
        'types': ['I','I','I','I','I','S','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I'],
        'names': [],
    },
    'ItemGroupSounds':
    {
        'name' : 'ItemGroupSounds',
        'types': ['I','I','I','I','I'],
        'names': [],
    },
    'ItemPetFood':
    {
        'name' : 'ItemPetFood',
        'types': ['S','S','I','I','I','I','I','I','I','I'],
        'names': [],
    },
    'ItemRandomProperties':
    {
        'name' : 'ItemRandomProperties',
        'types': ['I','S','I','I','I','I','I','S','I','I','I','I','I','I','I','I'],
        'names': [],
    },
    'ItemSet':
    {
        'name' : 'ItemSet',
        'types': ['I','S','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I'],
        'names': [],
    },
    'ItemSubClass':
    {
        'name' : 'ItemSubClass',
        'types': ['I','I','I','I','I','S','I','I','I','I','S','I','I','I','I','I','I','I','I','S','I','I','I','I','I','I','I','I'],
        'names': [],
    },
    'ItemSubClassMask':
    {
        'name' : 'ItemSubClassMask',
        'types': ['I','I','S','I','I','I','I','I','I','I','I'],
        'names': [],
    },
    'ItemVisualEffects':
    {
        'name' : 'ItemVisualEffects',
        'types': ['I','S'],
        'names': [],
    },
    'ItemVisuals':
    {
        'name' : 'ItemVisuals',
        'types': ['I','I','I','I','I','I'],
        'names': [],
    },
    'Languages':
    {
        'name' : 'Languages',
        'types': ['I','S','I','I','I','I','I','I','I','I'],
        'names': [],
    },
    'LanguageWords':
    {
        'name' : 'LanguageWords',
        'types': ['I','S','S'],
        'names': [],
    },
    'LoadingScreens':
    {
        'name' : 'LoadingScreens',
        'types': ['I','S','S'],
        'names': [],
    },
    'LoadingScreenTaxiSplines':
    {
        'name' : 'LoadingScreenTaxiSplines',
        'types': ['I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I'],
        'names': [],
    },
    'Lock':
    {
        'name' : 'Lock',
        'types': ['I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I'],
        'names': [],
    },
    'LockType':
    {
        'name' : 'LockType',
        'types': ['I','S','I','I','I','I','I','I','I','I','S','I','I','I','I','I','I','I','I','S','I','I','I','I','I','I','I','I','I'],
        'names': [],
    },
    'Map':
    {
        'name' : 'Map',
        'types': ['I','S','I','S','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I'],
        'names': [],
    },
    'Material':
    {
        'name' : 'Material',
        'types': ['I','I','I'],
        'names': [],
    },
    'NameGen':
    {
        'name' : 'NameGen',
        'types': ['I','S','I','S'],
        'names': [],
    },
    'NamesProfanity':
    {
        'name' : 'NamesProfanity',
        'types': ['I','S'],
        'names': [],
    },
    'NamesReserved':
    {
        'name' : 'NamesReserved',
        'types': ['I','S'],
        'names': [],
    },
    'NPCSounds':
    {
        'name' : 'NPCSounds',
        'types': ['I','I','I','I','I'],
        'names': [],
    },
    'Package':
    {
        'name' : 'Package',
        'types': ['S','S','S','S','S','S','S','S','S','S','S','S'],
        'names': [],
    },
    'PageTextMaterial':
    {
        'name' : 'PageTextMaterial',
        'types': ['S','S'],
        'names': [],
    },
    'PaperDollItemFrame':
    {
        'name' : 'PaperDollItemFrame',
        'types': ['S','S','I'],
        'names': [],
    },
    'PetLoyalty':
    {
        'name' : 'PetLoyalty',
        'types': ['I','S','I','I','I','I','I','I','I','I'],
        'names': [],
    },
    'PetPersonality':
    {
        'name' : 'PetPersonality',
        'types': ['S','S','S','S','S','S','S','S','S','S','S','S','S','S','F','F','F','F','F'],
        'names': [],
    },
    'QuestInfo':
    {
        'name' : 'QuestInfo',
        'types': ['S','S','I','I','I','I','I','I','I','I'],
        'names': [],
    },
    'QuestSort':
    {
        'name' : 'QuestSort',
        'types': ['I','S','I','I','I','I','I','I','I','I'],
        'names': [],
    },
    'Resistances':
    {
        'name' : 'Resistances',
        'types': ['I','I','I','S','I','I','I','I','I','I','I','I'],
        'names': [],
    },
    'ServerMessages':
    {
        'name' : 'ServerMessages',
        'types': ['S','S','I','I','I','I','I','I','I','I'],
        'names': [],
    },
    'SheatheSoundLookups':
    {
        'name' : 'SheatheSoundLookups',
        'types': ['I','I','I','I','I','I','I'],
        'names': [],
    },
    'SkillCostsData':
    {
        'name' : 'SkillCostsData',
        'types': ['I','I','I','I','I'],
        'names': [],
    },
    'SkillLineAbility':
    {
        'name' : 'SkillLineAbility',
        'types': ['I','I','I','I','I','I','I','I','I','I','I','I','I','I','I'],
        'names': [],
    },
    'SkillLineCategory':
    {
        'name' : 'SkillLineCategory',
        'types': ['I','S','I','I','I','I','I','I','I','I','I'],
        'names': [],
    },
    'SkillLine':
    {
        'name' : 'SkillLine',
        'types': ['I','I','I','S','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','S'],
        'names': [],
    },
    'SkillRaceClassInfo':
    {
        'name' : 'SkillRaceClassInfo',
        'types': ['I','I','I','I','I','I','I','I'],
        'names': [],
    },
    'SkillTiers':
    {
        'name' : 'SkillTiers',
        'types': ['I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I'],
        'names': [],
    },
    'SoundAmbience':
    {
        'name' : 'SoundAmbience',
        'types': ['I','I','I'],
        'names': [],
    },
    'SoundCharacterMacroLines':
    {
        'name' : 'SoundCharacterMacroLines',
        'types': ['I','I','I','I','I'],
        'names': [],
    },
    'SoundEntries':
    {
        'name' : 'SoundEntries',
        'types': ['I','I','S','S','S','I','I','I','I','I','I','I','I','S','S','S','S','S','S','S','S','S','S','S','F','I','F','F','I'],
        'names': [],
    },
    'SoundProviderPreferences':
    {
        'name' : 'SoundProviderPreferences',
        'types': ['I','S','I','I','F','F','F','I','I','F','I','I','I','I','I','F','I','F','I','I','I','I','F','F'],
        'names': [],
    },
    'SoundSamplePreferences':
    {
        'name' : 'SoundSamplePreferences',
        'types': ['S','S','S','S','S','S','F','S','F','F','S','F','S','F','F','F','S'],
        'names': [],
    },
    'SoundWaterType':
    {
        'name' : 'SoundWaterType',
        'types': ['I','I','I','I'],
        'names': [],
    },
    'SpellAuraNames':
    {
        'name' : 'SpellAuraNames',
        'types': ['I','I','S','S','I','I','I','I','I','I','I','I'],
        'names': [],
    },
    'SpellCastTimes':
    {
        'name' : 'SpellCastTimes',
        'types': ['I','I','I','I'],
        'names': [],
    },
    'SpellCategory':
    {
        'name' : 'SpellCategory',
        'types': ['I','I'],
        'names': [],
    },
    'SpellChainEffects':
    {
        'name' : 'SpellChainEffects',
        'types': ['I','F','I','I','I','I','I','S'],
        'names': [],
    },
    'Spell':
    {
        'name' : 'Spell',
        'types': ['I','I','I','I','I','I','I','I','I','I','I','I','I','I','S','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','S','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','S','I','I','S','I','I','I','I','I','I','I','I','I','I','I','S','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','S','I','I','I','I','I','I','I','I','S','I','I','I','I','I','I','I','I','S','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','F','F','F','I'],
        'names': [],
    },
    'SpellDispelType':
    {
        'name' : 'SpellDispelType',
        'types': ['I','S','I','I','I','I','I','I','I','I','S'],
        'names': [],
    },
    'SpellDuration':
    {
        'name' : 'SpellDuration',
        'types': ['I','I','I','I'],
        'names': [],
    },
    'SpellEffectCameraShakes':
    {
        'name' : 'SpellEffectCameraShakes',
        'types': ['I','I','I','I'],
        'names': [],
    },
    'SpellEffectNames':
    {
        'name' : 'SpellEffectNames',
        'types': ['I','S','I','I','I','I','I','I','I','I'],
        'names': [],
    },
    'SpellFocusObject':
    {
        'name' : 'SpellFocusObject',
        'types': ['I','S','I','I','I','I','I','I','I','I'],
        'names': [],
    },
    'SpellIcon':
    {
        'name' : 'SpellIcon',
        'types': ['I','S'],
        'names': [],
    },
    'SpellItemEnchantment':
    {
        'name' : 'SpellItemEnchantment',
        'types': ['I','I','I','I','I','I','I','I','I','I','I','I','I','S','I','I','I','I','I','I','I','I','I','I'],
        'names': [],
    },
    'SpellMechanic':
    {
        'name' : 'SpellMechanic',
        'types': ['I','I'],
        'names': [],
    },
    'SpellRadius':
    {
        'name' : 'SpellRadius',
        'types': ['I','F','I','F'],
        'names': [],
    },
    'SpellRange':
    {
        'name' : 'SpellRange',
        'types': ['I','F','F','I','S','I','I','I','I','I','I','I','I','S','I','I','I','I','I','I','I','I'],
        'names': [],
    },
    'SpellShapeshiftForm':
    {
        'name' : 'SpellShapeshiftForm',
        'types': ['I','I','S','I','I','I','I','I','I','I','I','I','I','I'],
        'names': [],
    },
    'SpellVisual':
    {
        'name' : 'SpellVisual',
        'types': ['I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I'],
        'names': [],
    },
    'SpellVisualEffectName':
    {
        'name' : 'SpellVisualEffectName',
        'types': ['I','S','S','I','F'],
        'names': [],
    },
    'SpellVisualKit':
    {
        'name' : 'SpellVisualKit',
        'types': ['I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I'],
        'names': [],
    },
    'SpellVisualPrecastTransitions':
    {
        'name' : 'SpellVisualPrecastTransitions',
        'types': ['S','S','S'],
        'names': [],
    },
    'StableSlotPrices':
    {
        'name' : 'StableSlotPrices',
        'types': ['S','S'],
        'names': [],
    },
    'Startup_Strings':
    {
        'name' : 'Startup_Strings',
        'types': ['S','S','S','I','I','I','I','I','I','I','I'],
        'names': [],
    },
    'Stationery':
    {
        'name' : 'Stationery',
        'types': ['S','S','S','S'],
        'names': [],
    },
    'StringLookups':
    {
        'name' : 'StringLookups',
        'types': ['I','S'],
        'names': [],
    },
    'Talent':
    {
        'name' : 'Talent',
        'types': ['I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I'],
        'names': [],
    },
    'TalentTab':
    {
        'name' : 'TalentTab',
        'types': ['I','S','I','I','I','I','I','I','I','I','I','I','I','I','S'],
        'names': [],
    },
    'TaxiNodes':
    {
        'name' : 'TaxiNodes',
        'types': ['I','S','F','F','F','S','I','I','I','I','I','I','I','I'],
        'names': [],
    },
    'TaxiPath':
    {
        'name' : 'TaxiPath',
        'types': ['I','I','I','I'],
        'names': [],
    },
    'TaxiPathNode':
    {
        'name' : 'TaxiPathNode',
        'types': ['I','I','I','I','F','F','F','I','I'],
        'names': [],
    },
    'TerrainType':
    {
        'name' : 'TerrainType',
        'types': ['I','S','I','I','S','I'],
        'names': [],
    },
    'TerrainTypeSounds':
    {
        'name' : 'TerrainTypeSounds',
        'types': ['I'],
        'names': [],
    },
    'TransportAnimation':
    {
        'name' : 'TransportAnimation',
        'types': ['I','I','I','F','I','F','I'],
        'names': [],
    },
    'UISoundLookups':
    {
        'name' : 'UISoundLookups',
        'types': ['I','I','S'],
        'names': [],
    },
    'UnitBlood':
    {
        'name' : 'UnitBlood',
        'types': ['S','I','I','I','I','S','S','S','S','I'],
        'names': [],
    },
    'UnitBloodLevels':
    {
        'name' : 'UnitBloodLevels',
        'types': ['I','I','I','I'],
        'names': [],
    },
    'VideoHardware':
    {
        'name' : 'VideoHardware',
        'types': ['I','I','I','I','S','I','S','S','S','I','S','S','I','I','I','I','I','I','I'],
        'names': [],
    },
    'VocalUISounds':
    {
        'name' : 'VocalUISounds',
        'types': ['I','I','I','I','I','I','I'],
        'names': [],
    },
    'WeaponImpactSounds':
    {
        'name' : 'WeaponImpactSounds',
        'types': ['I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I'],
        'names': [],
    },
    'WeaponSwingSounds2':
    {
        'name' : 'WeaponSwingSounds2',
        'types': ['I','I','I','I'],
        'names': [],
    },
    'WMOAreaTable':
    {
        'name' : 'WMOAreaTable',
        'types': ['I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I','I'],
        'names': [],
    },
    'WorldMapArea':
    {
        'name' : 'WorldMapArea',
        'types': ['I','S','I','S','F','F','F','F'],
        'names': [],
    },
    'WorldMapContinent':
    {
        'name' : 'WorldMapContinent',
        'types': ['S','S','S','S','S','S','F','F','S','F','F','F','F'],
        'names': [],
    },
    'WorldMapOverlay':
    {
        'name' : 'WorldMapOverlay',
        'types': ['I','I','I','I','I','I','I','I','S','I','I','I','I','I','I','I','I'],
        'names': [],
    },
    'WorldSafeLocs':
    {
        'name' : 'WorldSafeLocs',
        'types': ['I','S','F','F','F','S','I','I','I','I','I','I','I','I'],
        'names': [],
    },
    'WowError_Strings':
    {
        'name' : 'WowError_Strings',
        'types': ['I','S','S','I','I','I','I','I','I','I','I'],
        'names': [],
    },
    'ZoneIntroMusicTable':
    {
        'name' : 'ZoneIntroMusicTable',
        'types': ['I','S','I','S','S'],
        'names': [],
    },
    'ZoneMusic':
    {
        'name' : 'ZoneMusic',
        'types': ['I','S','I','I','I','I','I','I'],
        'names': [],
    }
}

###############################################################################

import time
import struct
import os.path
from optparse import OptionParser

# DBC file parser
class DBC:
    ok = False
    def __init__(self, fn):
        try:
            self.f = open (fn)
        except:
            print "Failed to open file", fn
            return
        Magic = self.Read32 ()
        if (Magic != 0x43424457):
            print "File '" + fn + "' doesn't look like a DBC file"
            return
        self.rows = self.Read32 ()
        self.cols = self.Read32 ()
        self.rowlen = self.Read32 ()
        self.strlen = self.Read32 ()
        self.f.seek (20 + self.rowlen * self.rows)
        self.strtab = self.f.read (self.strlen)
        self.f.seek (20)
        self.ok = True
        print "Opened database '%s', %d columns, %d rows, %d bytes per row" \
            %(fn, self.cols, self.rows, self.rowlen);
        if (self.cols * 4 != self.rowlen):
            raise "ERROR: Column elements are not 4 bytes, this script cannot handle it"

    def Read32 (self):
        x = self.f.read (4)
        if len (x) < 4:
            print "WARNING: broken database!"
            return 0
        return struct.unpack ("<I", x) [0]

    def ReadRow (self):
        row = list ()
        for x in range (self.cols):
            row.append (self.Read32 ())
        return row

    # The idea is as follows: we read all rows of the database and
    # for every cell gather statistics: which format it looks like
    # (it is even possible that some field may look like several formats
    # at once, this doesn't matter). Finally, the format with most hits
    # is chosen. Also we don't count the 'int' case, 'cause any value
    # is a legal integer, so it's kind of fallback value.
    #
    # Floating-point format:
    # bit 0        8        16       24
    #    +--------+--------+--------+--------+
    #    |mmmmmmmm|mmmmmmmm|mmmmmmme|eeeeeees|
    #    +|-------+--------+------||+------||+
    #     \---- mantissa ---------/\--exp--/\-sign
    def GatherStats (self, format):
        old_pos = self.f.tell ()
        print "Gathering field statistics ..."

        # FLOAT, STR
        stats = [[0L, 0L] for i in range (self.cols)]
        self.strwidth = [0] * self.cols

        for row_num in range (self.rows):
            row = self.ReadRow ()
            for col_num in range (self.cols):
                val = long (row [col_num])

                # Assume floats are in range -2^18...2^18
                exp = ((val & 0x7f800000) >> 23) - 127
                if ((exp >= 0) and (exp <= 18)):
                    stats [col_num][0] += 1

                # Check for a valid offset in the string table
                if ((val >= 0) and (val < self.strlen - 1) and
                    ((val == 0) or (self.strtab [val - 1] == chr (0)))):
                    s = self.GetString (val)
                    if (len (s) > 0):
                        stats [col_num][1] += 1
                        if (len (s) > self.strwidth [col_num]):
                            self.strwidth [col_num] = len (s)

        # If we have a 33% or more probability for one format, use it
        threshold = self.rows / 3;
        format ['types'] = ['I' for i in range (self.cols)]
        for col_num in range (self.cols):
            if (max (stats [col_num]) >= threshold):
                if (stats [col_num][0] > stats [col_num][1]):
                    format ['types'][col_num] = 'F'
                else:
                    format ['types'][col_num] = 'S'
        self.f.seek (old_pos)

    def GetString (self, ofs):
        return self.strtab [ofs : self.strtab.find (chr (0), ofs)]

###############################################################################

# Quote a string so that it is parsed correctly by SQL
def sqlQuoteString (st):
    return "'" + st.replace ("'", "''") + "'"

# Guess the format of the database
def GuessFormat (fn):
    dbc = DBC (fn)
    if (not dbc.ok):
        return False

    dbc_format = known_dbc ['Unknown']
    dbc.GatherStats (dbc_format)

    dbc_name = os.path.splitext (os.path.basename (fn)) [0]

    if (options.Create):
        print "CREATE TABLE `" + dbc_name + "` ("
        row = dbc.ReadRow ()
        for col_num in range (dbc.cols):
            cell_type = dbc_format ['types'][col_num]
            cell_name = "f" + str (col_num)
            line = "\t`" + cell_name + "` "
            if (cell_type == "I"):
                line += "int (4) NOT NULL default 0"
            elif (cell_type == "F"):
                line += "real (4) NOT NULL default 0.0"
            elif (cell_type == "S"):
                line += "char (" + str (dbc.strwidth [col_num]) + ") NOT NULL default ''"
            if (col_num < dbc.cols - 1):
                line += ","
            print line
        print ");\n"

    print "    '" + dbc_name + "':\n    {"
    print "        'name' : '" + dbc_name + "',"
    line = ""
    for col_num in range (dbc.cols):
        line += "'" + dbc_format ['types'][col_num] + "'"
        if (col_num < dbc.cols - 1):
            line += ","
    print "        'types': [" + line + "],"
    print "        'names': [],\n    },"

    return True

# Convert given database
def Convert (fn, ofn):
    dbc = DBC (fn)
    if (not dbc.ok):
        return False

    dbc_name = os.path.splitext (os.path.basename (fn)) [0]
    try:
        dbc_format = known_dbc [dbc_name]
    except:
        print "WARNING: Database file '" +  fn + "' format unknown, will try guessing it"
        dbc_format = known_dbc ['Unknown']
        dbc.GatherStats (dbc_format)

    if (ofn == ""):
        ofn = dbc_name + ".sql"
    if (fn == ofn):
        print "Input and output filenames must be different"
        return False

    of = open (ofn, "w+")

    of.write ("# Autogenerated from '" + fn + "' at " +
              time.strftime ("%c", time.gmtime ()) + "\n\n")

    of.write ("INSERT INTO " + dbc_name + " VALUES\n");
    for row_num in range (dbc.rows):
        row = dbc.ReadRow ()
        line = "\t("
        for col_num in range (dbc.cols):
            if (col_num < len (dbc_format ['types'])):
                cell_type = dbc_format ['types'][col_num]
            else:
                cell_type = 'I'

            if (cell_type == 'I'):
                line += str (row [col_num])
            elif (cell_type == 'F'):
                line += str (round (struct.unpack ('<f', struct.pack ('<I', row [col_num])) [0], 3))
            elif (cell_type == 'S'):
                line += sqlQuoteString (dbc.GetString (row [col_num]))
            else:
                print "WARNING: UNKNOWN FORMAT '" + cell_type + "' FOR COLUMN", col_num
            if (col_num < dbc.cols - 1):
                line += ','
        line += ")\n"
        of.write (line)

    return True

# List known databases
def ListKnown ():
    for d in known_dbc:
        db = known_dbc [d]
        print d + ".dbc -> SQL Table '" + db ['name'] + "'"
        print "\tField names:", db ['names']
        print "\tField types:", db ['types']

######################## Main function starts here ############################

usage = "%prog [options] [database.dbc[ ...]]"
version = "%prog 0.1.0"
parser = OptionParser (usage=usage, version=version)
parser.add_option ("-g", "--guess", help = "Guess database file format",
                   action = "store_true", dest = "Guess", default = False)
parser.add_option ("-c", "--create", help = "Guess statements for table creation as well",
                   action = "store_true", dest = "Create", default = False)
parser.add_option ("-l", "--list", help = "List known databases",
                   action = "store_true", dest = "List", default = False)
parser.add_option ("-o", "--output", help="Direct SQL output to FILE",
                   metavar="FILE", dest="FileName", default = "")

(options, args) = parser.parse_args ()

if (options.List):
    ListKnown ()
elif (len (args) == 0):
    print "Nothing to do, exiting; use --help for command-line format"
else:
    for fn in args:
        if (options.Guess):
            res = GuessFormat (fn)
        else:
            res = Convert (fn, options.FileName)

        if (not res):
            print "Aborting"
            break
