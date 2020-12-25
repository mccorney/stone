#include "stone/System/Action.h"

using namespace stone;

ActionTable::ActionTable(const LangOptions &langOpts) : langOpts(langOpts) {
  AddActions(langOpts);
}

static void AddAction() {}

void ActionTable::AddActions(const LangOptions &LangOpts) { AddAction(); }

void ActionTableStats::Print() const {}
