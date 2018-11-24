#include "stdafx.h"

#include "OSIUtil.h"

#include <queue>

using namespace LOMNHook::Util;

typedef void(__thiscall *ScOSISystem__RegisterFunction)(ScOSISystem*, _ScBaseString*, _ScBaseString*, OSIFunctionCallback, char, char, ScOSITypeID, ScOSITypeID, ScOSITypeID, ScOSITypeID, ScOSITypeID, ScOSITypeID, ScOSITypeID, ScOSITypeID, ScOSITypeID, ScOSITypeID);

#if GAME_EDITION == BETA
ScOSISystem** LOMNHook::Util::ScGlobalOSISystem__theOSISystem = (void**)0x0074D644;
ScOSISystem__RegisterFunction pScOSISystem__RegisterFunction = (ScOSISystem__RegisterFunction)0x005FAB30;
#elif GAME_EDITION == ALPHA
ScOSISystem** LOMNHook::Util::ScGlobalOSISystem__theOSISystem = (void**)0x00630CE8;
ScOSISystem__RegisterFunction pScOSISystem__RegisterFunction = (ScOSISystem__RegisterFunction)0x00572F90;
#endif

template<typename T>
struct TreeNode {
	TreeNode* Left;
	TreeNode* Right;
	size_t RedBlackMarker;
	T Payload;
};

template<typename T, typename U>
struct __declspec(align(4)) Pair {
	T Item1;
	U Item2;
};

void LOMNHook::Util::OSIRegisterFunction(OSIFunctionCallback callback, const char* ns, const char* name, char argMin, char argMax, ScOSITypeID paramType1, ScOSITypeID paramType2, ScOSITypeID paramType3, ScOSITypeID paramType4, ScOSITypeID paramType5, ScOSITypeID paramType6, ScOSITypeID paramType7, ScOSITypeID paramType8, ScOSITypeID paramType9, ScOSITypeID paramType10) {
	_ScBaseString ns1 = _ScBaseString(ns);
	_ScBaseString ns2 = _ScBaseString(name);
	pScOSISystem__RegisterFunction(*ScGlobalOSISystem__theOSISystem, &ns1, &ns2, callback, argMin, argMax, paramType1, paramType2, paramType3, paramType4, paramType5, paramType6, paramType7, paramType8, paramType9, paramType10);
}

typedef TreeNode<Pair<ScOSITypeID, _ScBaseString>> NameTreeNode;

ScOSITypeID LOMNHook::Util::OSIGetTypeID(const char* typeName) {
	void** pTree = (void**)((DWORD)*ScGlobalOSISystem__theOSISystem + 0x24);

	void** item0 = (void**)((DWORD)pTree + 4);

	std::queue<NameTreeNode*> nodes;

	NameTreeNode* rootNode = (NameTreeNode*)*item0;
	nodes.push(rootNode);

	while (nodes.size() > 0) {
		NameTreeNode* node = nodes.front();
		nodes.pop();

		OutputDebugStringA(std::to_string(node->Payload.Item1).c_str());
		OutputDebugStringA(": ");
		OutputDebugStringA(node->Payload.Item2.Data);
		OutputDebugStringA("\n");

		if (strcmp(node->Payload.Item2.Data, typeName) == 0) {
			return node->Payload.Item1;
		}

		if (node->Left != nullptr) {
			nodes.push(node->Left);
		}
		if (node->Right != nullptr) {
			nodes.push(node->Right);
		}
	}
	OutputDebugStringW(L"WARNING: No TypeID registered for type name '");
	OutputDebugStringA(typeName);
	OutputDebugStringW(L"'\n");
	return 0xF; // NULL typeID
}