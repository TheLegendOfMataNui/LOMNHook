#include "stdafx.h"
#include "SaveDirector.h"

#include "LOMNAPI.h"
#include "Native/ScIdentifier.h"
#include "Native/Vector.h"

#define PUGIXML_CLASS __declspec(dllimport) // to import all classes from DLL
#include "pugixml.hpp"

using namespace LOMNHook::Native;

struct GtSaverData {
	ScIdentifier ID;
	ScIdentifier AreaID;
};

struct GtSaverTime {
	ScIdentifier AreaID;
	float Time;
};

struct GtConvMemory {
	ScIdentifier AreaID;
	ScIdentifier ID;
	unsigned char Number;
	char _pad[3];
};

typedef void*(__cdecl *SrMalloc)(unsigned int);

#if GAME_EDITION == BETA
SrMalloc pSrMalloc = (SrMalloc)0x004E4350;
char** pGcSaver__sPathString = (char**)0x00838CF0;
unsigned char* pGcSaver__sLevel = (unsigned char*)0x0074748C;
ScIdentifier* pGcSaver__sArea = (ScIdentifier*)0x00747490;
ScIdentifier* pGcSaver__sPos = (ScIdentifier*)0x00747494;
ScIdentifier* pGcSaver__sLook = (ScIdentifier*)0x00747498;
ScIdentifier* pGcSaver__sSaveToa = (ScIdentifier*)0x0074749C;
ScIdentifier* pGcSaver__sSaveMask = (ScIdentifier*)0x007474A0;
unsigned char* pGcSaver__sSaveGlyph = (unsigned char*)0x007474A4;
unsigned char* pGcSaver__sSaveHealth = (unsigned char*)0x007474A8;
unsigned char* pGcSaver__sSaveEnergy = (unsigned char*)0x007474AC;
unsigned char* pGcSaver__sTokenCount = (unsigned char*)0x0083B402;
GtSaverData* pGcSaver__sTokens = (GtSaverData*)0x00837AE8;
unsigned char* pGcSaver__sMaskCount = (unsigned char*)0x0083B401;
GtSaverData* pGcSaver__sMasks = (GtSaverData*)0x008384A0;
unsigned char* pGcSaver__sGlyphCount = (unsigned char*)0x0083B3FA;
GtSaverData* pGcSaver__sGlyphs = (GtSaverData*)0x007F79F0;
unsigned char* pGcSaver__sInventoryCount = (unsigned char*)0x0083B50F;
GtSaverData* pGcSaver__sInventory = (GtSaverData*)0x00838620;
unsigned char* pGcSaver__sCinemaCount = (unsigned char*)0x0083B3FF;
ScIdentifier* pGcSaver__sCinemas = (ScIdentifier*)0x007F7A10;
unsigned long* pGcSaver__sConvConditions = (unsigned long*)0x008391A0;
Vector<GtConvMemory>* pGcSaver__sConvMemory = (Vector<GtConvMemory>*)0x00838B90;
unsigned char* pGcSaver__sTimeCount = (unsigned char*)0x0083B3FC;
GtSaverTime** pGcSaver__sTimes = (GtSaverTime**)0x00838508;
unsigned char* pGcSaver__sQuests = (unsigned char*)0x0083B380;
unsigned char* pGcSaver__sMaskNums = (unsigned char*)0x007474B8;
unsigned char* pGcSaver__sGlyphFound = (unsigned char*)0x007474BC;
unsigned char* pGcSaver__sStoneFound = (unsigned char*)0x007474C0;
unsigned char* pGcSaver__sHookFound = (unsigned char*)0x007474C4;
unsigned short* pGcSaver__sAmmoCount = (unsigned short*)0x007474C8;
#elif GAME_EDITION == ALPHA

#endif

#define GCSAVER_LOAD_FAILURE 0
#define GCSAVER_LOAD_SUCCESS 1

namespace SaveDirector {

	char buffer[50];
	void SaveScId(pugi::xml_node& parent, const char* element, ScIdentifier id) {
		buffer[0] = id.AsString[3];
		buffer[1] = id.AsString[2];
		buffer[2] = id.AsString[1];
		buffer[3] = id.AsString[0];
		buffer[4] = '\0';
		parent.append_child(element).append_child(pugi::node_pcdata).set_value(buffer);
	}

	void SaveInt(pugi::xml_node& parent, const char* element, unsigned long i) {
		sprintf_s(buffer, "%u", i);
		parent.append_child(element).append_child(pugi::node_pcdata).set_value(buffer);
	}

	void SaveData(pugi::xml_node& parent, const char* element, const GtSaverData& data) {
		pugi::xml_node node = parent.append_child(element);
		buffer[0] = data.ID.AsString[3];
		buffer[1] = data.ID.AsString[2];
		buffer[2] = data.ID.AsString[1];
		buffer[3] = data.ID.AsString[0];
		buffer[4] = '\0';
		node.append_attribute("id").set_value(buffer);
		buffer[0] = data.AreaID.AsString[3];
		buffer[1] = data.AreaID.AsString[2];
		buffer[2] = data.AreaID.AsString[1];
		buffer[3] = data.AreaID.AsString[0];
		buffer[4] = '\0';
		node.append_attribute("area").set_value(buffer);
	}

	void SaveCinematic(pugi::xml_node& parent, const char* element, const ScIdentifier& id) {
		pugi::xml_node node = parent.append_child(element);
		buffer[0] = id.AsString[3];
		buffer[1] = id.AsString[2];
		buffer[2] = id.AsString[1];
		buffer[3] = id.AsString[0];
		buffer[4] = '\0';
		node.append_attribute("id").set_value(buffer);
	}

	void SaveConversationData(pugi::xml_node& parent, const char* element, const GtConvMemory& conv) {
		pugi::xml_node node = parent.append_child(element);
		buffer[0] = conv.ID.AsString[3];
		buffer[1] = conv.ID.AsString[2];
		buffer[2] = conv.ID.AsString[1];
		buffer[3] = conv.ID.AsString[0];
		buffer[4] = '\0';
		node.append_attribute("id").set_value(buffer);
		buffer[0] = conv.AreaID.AsString[3];
		buffer[1] = conv.AreaID.AsString[2];
		buffer[2] = conv.AreaID.AsString[1];
		buffer[3] = conv.AreaID.AsString[0];
		buffer[4] = '\0';
		node.append_attribute("area").set_value(buffer);
		sprintf_s(buffer, "%u", conv.Number);
		node.append_attribute("number").set_value(buffer);
	}

	void SaveTime(pugi::xml_node& parent, const char* element, const GtSaverTime& time) {
		pugi::xml_node node = parent.append_child(element);
		buffer[0] = time.AreaID.AsString[3];
		buffer[1] = time.AreaID.AsString[2];
		buffer[2] = time.AreaID.AsString[1];
		buffer[3] = time.AreaID.AsString[0];
		buffer[4] = '\0';
		node.append_attribute("id").set_value(buffer);
		sprintf_s(buffer, "%.3f", time.Time);
		node.append_attribute("time").set_value(buffer);
	}

	void SaveQuest(pugi::xml_node& parent, const char* element, int level, unsigned char value) {
		pugi::xml_node node = parent.append_child(element);
		sprintf_s(buffer, "%u", level);
		node.append_attribute("level").set_value(buffer);
		sprintf_s(buffer, "%u", value);
		node.append_attribute("value").set_value(buffer);
	}

	void Save() {
		using namespace pugi;

		xml_document doc;
		xml_node saveNode = doc.append_child("save");

		// Level
		SaveInt(saveNode, "level", *pGcSaver__sLevel);

		// Area
		SaveScId(saveNode, "area", *pGcSaver__sArea);

		// Position
		if (pGcSaver__sPos->AsDWORD == '????')
			pGcSaver__sPos->AsDWORD = 'str0';
		SaveScId(saveNode, "position", *pGcSaver__sPos);

		// Look
		if (pGcSaver__sLook->AsDWORD == '????')
			pGcSaver__sLook->AsDWORD = 'lok0';
		SaveScId(saveNode, "look", *pGcSaver__sLook);

		// Toa
		SaveScId(saveNode, "toa", *pGcSaver__sSaveToa);

		// Mask
		SaveInt(saveNode, "mask", pGcSaver__sSaveMask->AsDWORD);

		// Glyph
		SaveInt(saveNode, "glyph", *pGcSaver__sSaveGlyph);

		// Health
		SaveInt(saveNode, "health", *pGcSaver__sSaveHealth);

		// Energy
		SaveInt(saveNode, "energy", *pGcSaver__sSaveEnergy);

		// Tokens
		xml_node tokensElement = saveNode.append_child("tokens");
		for (unsigned char i = 0; i < *pGcSaver__sTokenCount; i++)
			SaveData(tokensElement, "token", (pGcSaver__sTokens)[i]);

		// Masks
		xml_node masksElement = saveNode.append_child("masks");
		for (unsigned char i = 0; i < *pGcSaver__sMaskCount; i++)
			SaveData(masksElement, "mask", (pGcSaver__sMasks)[i]);

		// Glyphs
		xml_node glyphsElement = saveNode.append_child("glyphs");
		for (unsigned char i = 0; i < *pGcSaver__sGlyphCount; i++)
			SaveData(glyphsElement, "glyph", (pGcSaver__sGlyphs)[i]);

		// Inventory
		xml_node inventoryElement = saveNode.append_child("inventory");
		for (unsigned char i = 0; i < *pGcSaver__sInventoryCount; i++)
			SaveData(inventoryElement, "item", (pGcSaver__sInventory)[i]);

		// Cinematics
		xml_node cinematicsElement = saveNode.append_child("cinematics");
		for (unsigned char i = 0; i < *pGcSaver__sCinemaCount; i++)
			SaveCinematic(cinematicsElement, "cinematic", (pGcSaver__sCinemas)[i]);

		// Legacy Conversation Conditions
		SaveInt(saveNode, "legacyconditionals", *pGcSaver__sConvConditions);

		// Conversation Memory
		xml_node conversationsElement = saveNode.append_child("conversations");
		for (int i = 0; i < pGcSaver__sConvMemory->Count; i++)
			SaveConversationData(conversationsElement, "conversation", pGcSaver__sConvMemory->Data[i]);

		// Times
		xml_node timesElement = saveNode.append_child("times");
		for (unsigned char i = 0; i < *pGcSaver__sTimeCount; i++)
			SaveTime(timesElement, "time", (*pGcSaver__sTimes)[i]);

		// Quests
		xml_node questsElement = saveNode.append_child("quests");
		for (int i = 0; i < 6; i++)
			if ((pGcSaver__sQuests)[i] != 0)
				SaveQuest(questsElement, "quest", i, (pGcSaver__sQuests)[i]);

		// Mask Flags
		SaveInt(saveNode, "maskflags", *pGcSaver__sMaskNums);

		// Glyph
		SaveInt(saveNode, "glyph", *pGcSaver__sGlyphFound);

		// Stone
		SaveInt(saveNode, "stone", *pGcSaver__sStoneFound);

		// Hook
		SaveInt(saveNode, "hook", *pGcSaver__sHookFound);

		// Ammo
		SaveInt(saveNode, "ammo", *pGcSaver__sAmmoCount);

		if (!doc.save_file(*pGcSaver__sPathString)) {
			OutputDebugStringA("[GcSaver] Could not write file '");
			OutputDebugStringA(*pGcSaver__sPathString);
			OutputDebugStringA("'!\n");
		}
	}

	ScIdentifier LoadScId(const char* text) {
		ScIdentifier result;
		result.AsString[0] = text[3];
		result.AsString[1] = text[2];
		result.AsString[2] = text[1];
		result.AsString[3] = text[0];
		return result;
	}

	void LoadData(GtSaverData& target, pugi::xml_node node) {
		target.ID = LoadScId(node.attribute("id").value());
		target.AreaID = LoadScId(node.attribute("area").value());
	}

	void LoadConversation(GtConvMemory& target, pugi::xml_node node) {
		target.ID = LoadScId(node.attribute("id").value());
		target.AreaID = LoadScId(node.attribute("area").value());
		target.Number = node.attribute("number").as_uint();
	}

	void LoadTime(GtSaverTime& target, pugi::xml_node node) {
		target.AreaID = LoadScId(node.attribute("area").value());
		target.Time = node.attribute("id").as_float();
	}

	char Load() {
		using namespace pugi;

		xml_document doc;
		xml_parse_result result = doc.load_file(*pGcSaver__sPathString);

		if (!result) {
			OutputDebugStringA("[GcSaver] Could not parse file '");
			OutputDebugStringA(*pGcSaver__sPathString);
			OutputDebugStringA("'!\n");
			return GCSAVER_LOAD_FAILURE;
		}

		xml_node saveNode = doc.child("save");

		// Level
		*pGcSaver__sLevel = saveNode.child("level").text().as_uint();

		// Area
		*pGcSaver__sArea = LoadScId(saveNode.child("area").text().get());

		// Position
		*pGcSaver__sPos = LoadScId(saveNode.child("position").text().get());

		// Look
		*pGcSaver__sLook = LoadScId(saveNode.child("look").text().get());

		// Toa
		*pGcSaver__sSaveToa = LoadScId(saveNode.child("toa").text().get());

		// Mask
		pGcSaver__sSaveMask->AsDWORD = saveNode.child("toa").text().as_uint();

		// Glyph
		*pGcSaver__sSaveGlyph = saveNode.child("glyph").text().as_uint();

		// Health
		*pGcSaver__sSaveHealth = saveNode.child("health").text().as_uint();

		// Energy
		*pGcSaver__sSaveEnergy = saveNode.child("energy").text().as_uint();

		// Tokens
		*pGcSaver__sTokenCount = 0;
		for (xml_node token : saveNode.child("tokens").children("token")) {
			LoadData((pGcSaver__sTokens)[*pGcSaver__sTokenCount], token);
			(*pGcSaver__sTokenCount)++;
		}
		
		// Masks
		*pGcSaver__sMaskCount = 0;
		for (xml_node mask : saveNode.child("masks").children("mask")) {
			LoadData((pGcSaver__sMasks)[*pGcSaver__sMaskCount], mask);
			(*pGcSaver__sMaskCount)++;
		}

		// Glyphs
		*pGcSaver__sGlyphCount = 0;
		for (xml_node glyph : saveNode.child("glyphs").children("glyph")) {
			LoadData((pGcSaver__sGlyphs)[*pGcSaver__sGlyphCount], glyph);
			(*pGcSaver__sGlyphCount)++;
		}

		// Inventory
		*pGcSaver__sInventoryCount = 0;
		for (xml_node item : saveNode.child("inventory").children("item")) {
			LoadData((pGcSaver__sInventory)[*pGcSaver__sInventoryCount], item);
			(*pGcSaver__sInventoryCount)++;
		}

		// Cinematics
		*pGcSaver__sCinemaCount = 0;
		for (xml_node cinematic : saveNode.child("cinematics").children("cinematic")) {
			(pGcSaver__sCinemas)[*pGcSaver__sCinemaCount] = LoadScId(cinematic.attribute("id").value());
			(*pGcSaver__sCinemaCount)++;
		}

		// Legacy Conversation Conditions
		*pGcSaver__sConvConditions = saveNode.child("legacyconditionals").text().as_uint();

		// Conversation Memory
		pGcSaver__sConvMemory->Count = 0;
		//   First, count the conversations
		for (xml_node conversation : saveNode.child("conversations").children("conversation"))
			pGcSaver__sConvMemory->Count++;
		//   Allocate the storage
		if (pGcSaver__sConvMemory->Data == nullptr) {
			pGcSaver__sConvMemory->Data = (GtConvMemory*)pSrMalloc(sizeof(GtConvMemory) * pGcSaver__sConvMemory->Count);
		}
		//   Then finally read the data
		for (xml_node conversation : saveNode.child("conversations").children("conversation")) {
			LoadConversation(pGcSaver__sConvMemory->Data[pGcSaver__sConvMemory->Count], conversation);
			pGcSaver__sConvMemory->Count++;
		}

		// Times
		*pGcSaver__sTimeCount = 0;
		for (xml_node time : saveNode.child("times").children("time")) {
			LoadTime((*pGcSaver__sTimes)[*pGcSaver__sTimeCount], time);
			(*pGcSaver__sTimeCount)++;
		}

		// Quests
		for (int i = 0; i < 6; i++)
			pGcSaver__sQuests[i] = 0;
		for (xml_node quest : saveNode.child("quests").children("quest")) {
			unsigned int l = quest.attribute("level").as_uint();
			pGcSaver__sQuests[l] = quest.attribute("value").as_uint();
		}

		// Mask Flags
		*pGcSaver__sMaskNums = saveNode.child("maskflags").text().as_uint();

		// Glyph
		*pGcSaver__sGlyphFound = saveNode.child("glyph").text().as_uint();

		// Stone
		*pGcSaver__sStoneFound = saveNode.child("stone").text().as_uint();

		// Hook
		*pGcSaver__sHookFound = saveNode.child("hook").text().as_uint();

		// Ammo
		*pGcSaver__sAmmoCount = saveNode.child("ammo").text().as_uint();

		return GCSAVER_LOAD_SUCCESS;
	}
}